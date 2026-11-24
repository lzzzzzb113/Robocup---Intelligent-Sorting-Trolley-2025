//
// Created by 32827 on 2025/9/28.
//

#include "yzl_i2c_bno085.h"
#include "yz_log.h"
// Global Variables
unsigned char shtpHeader[4]; // Each packet has a header of 4 chars
unsigned char shtpData[MAX_PACKET_SIZE];
unsigned char sequenceNumber[6] = {0, 0, 0, 0, 0, 0}; // There are 6 com channels. Each channel has its own seqnum
unsigned char commandSequenceNumber = 0;              // Commands have a seqNum as well. These are inside command packet, the header uses its own seqNum per channel
unsigned long metaData[MAX_METADATA_SIZE];                 // There is more than 10 words in a metadata record but we'll stop at Q point 3
// Variables
unsigned char _deviceAddress;//跟踪 I2C 地址。setI2CAddress 更改了这一点。


// These are the raw sensor values pulled from the user requested Input Report
unsigned int rawAccelX, rawAccelY, rawAccelZ, accelAccuracy;
unsigned int rawLinAccelX, rawLinAccelY, rawLinAccelZ, accelLinAccuracy;
unsigned int rawGyroX, rawGyroY, rawGyroZ, gyroAccuracy;
unsigned int rawMagX, rawMagY, rawMagZ, magAccuracy;
unsigned int rawQuatI, rawQuatJ, rawQuatK, rawQuatReal, rawQuatRadianAccuracy, quatAccuracy;
unsigned int stepCount;
unsigned char stabilityClassifier;
unsigned char activityClassifier;
unsigned char *_activityConfidences; // Array that store the confidences of the 9 possible activities

// These Q values are defined in the datasheet but can also be obtained by querying the meta data records
// See the read metadata example for more info
int rotationVector_Q1 = 14;
int accelerometer_Q1 = 8;
int linear_accelerometer_Q1 = 8;
int gyro_Q1 = 9;
int magnetometer_Q1 = 4;

uint8_t i2c_tmp[32] = {0};

YZF_RESULT yzl_i2c_bno085_soft_reset(YZF_I2C_POINTER i2c){
    shtpData[0] = 1; // Reset

    yzl_i2c_bno085_send_packet(i2c,CHANNEL_EXECUTABLE,1);

    HAL_Delay(50);
    while (yzl_i2c_bno085_receive_packet(i2c) == YZF_ERROR){
        HAL_Delay(50);
    }
    HAL_Delay(50);
    while (yzl_i2c_bno085_receive_packet(i2c) == YZF_ERROR){
        HAL_Delay(50);
    }

    HAL_Delay(100);

    rotationVector_Q1 = yzl_i2c_bno085_get_q1(i2c,FRS_RECORDID_ROTATION_VECTOR);
    accelerometer_Q1 = yzl_i2c_bno085_get_q1(i2c,FRS_RECORDID_ACCELEROMETER);
    linear_accelerometer_Q1 = yzl_i2c_bno085_get_q1(i2c,FRS_RECORDID_LINEAR_ACCELERATION);
    gyro_Q1 = yzl_i2c_bno085_get_q1(i2c,FRS_RECORDID_GYROSCOPE_CALIBRATED);
    return YZF_OK;
}

YZF_RESULT yzl_i2c_bno085_send_packet(YZF_I2C_POINTER i2c,unsigned char channelNumber, unsigned char dataLength)
{
    unsigned char packetLength = dataLength + 4; // Add four bytes for the header
    // if(packetLength > I2C_BUFFER_LENGTH) return(0); //You are trying to send too much. Break into smaller packets.
    unsigned char i = 0;
    // Send the 4 byte packet header
    i2c_tmp[0] = (packetLength & 0xFF);             // Packet length LSB
    i2c_tmp[1] = (0);                               // Packet length MSB
    i2c_tmp[2] = (channelNumber);                   // Channel number
    i2c_tmp[3] = (sequenceNumber[channelNumber]++); // Send the sequence number, increments with each packet sent, different counter for each channel

    // Send the user's data packet
    for (i = 0; i < dataLength; i++)
    {
        i2c_tmp[4 + i] = (shtpData[i]);
    }
    yz_i2c_add7_transmit(i2c,BNO080_DEFAULT_ADDRESS,i2c_tmp, (uint8_t)(dataLength + 4));

    return YZF_OK;
}

YZF_RESULT yzl_i2c_bno085_receive_packet(YZF_I2C_POINTER i2c)
{
    int dataLength = 0;
    unsigned char packetLSB = 0;
    unsigned char packetMSB = 0;
    unsigned char channelNumber = 0;
    unsigned char sequenceNumber = 0;
    YZF_RESULT result=yz_i2c_add7_receive(i2c,BNO080_DEFAULT_ADDRESS,i2c_tmp, 4);
    if(result==YZF_ERROR){
        return YZF_ERROR;
    }

    // Get the first four bytes, aka the packet header
    packetLSB = i2c_tmp[0];
    packetMSB = i2c_tmp[1];
    channelNumber = i2c_tmp[2];
    sequenceNumber = i2c_tmp[3]; // Not sure if we need to store this or not

    // Store the header info.
    shtpHeader[0] = packetLSB;
    shtpHeader[1] = packetMSB;
    shtpHeader[2] = channelNumber;
    shtpHeader[3] = sequenceNumber;

    // Calculate the number of data bytes in this packet
    dataLength = ((unsigned int)packetMSB << 8 | packetLSB);
    dataLength &= ~(1 << 15);//清除 MSbit。
    //此位指示此包是否是上一个包的延续。暂时忽略它。
    //TODO 将此捕获为错误并退出
    if (dataLength == 0)
    {
        // Packet is empty
        return YZF_ERROR; // All done
    }else if(channelNumber>0x20){//错误？？
        return YZF_ERROR; // All done
    }
    dataLength -= 4; // Remove the header bytes from the data count

    yzl_i2c_bno085_get_data(i2c,dataLength);
//    yz_info("channelNumber:%d,sequenceNumber:%d,dataLength:%d,TIMESTAMP:%d\n",channelNumber,sequenceNumber,dataLength,shtpData[0]);

    return YZF_OK; // We're done!
}

// 向传感器发送多个请求，直到从传感器接收到所有数据字节
// shtpData 缓冲区的最大容量为 MAX_PACKET_SIZE。超过此量的任何字节都将丢失。
// Arduino I2C 读取限制为 32 字节。标头是 4 个字节，因此我们每个交互可以读取的最大数据为 28 字节
char yzl_i2c_bno085_get_data(YZF_I2C_POINTER i2c,unsigned int bytesRemaining)
{
    unsigned int dataSpot = 0; // Start at the beginning of shtpData array
    unsigned char x = 0;
    unsigned char incoming = 0;
    // Setup a series of chunked 32 byte reads
    while (bytesRemaining > 0)
    {
        unsigned int numberOfBytesToRead = bytesRemaining;
        if (numberOfBytesToRead > (I2C_BUFFER_LENGTH - 4))
            numberOfBytesToRead = (I2C_BUFFER_LENGTH - 4);
        while(yz_i2c_add7_receive(i2c,BNO080_DEFAULT_ADDRESS,i2c_tmp, (unsigned char)(numberOfBytesToRead + 4))!=YZF_OK){
            HAL_Delay(1);//读取错误
        }

        // 前四个字节是标头字节，被丢弃

        for (x = 0; x < numberOfBytesToRead; x++)
        {
            incoming = i2c_tmp[x + 4];
            if (dataSpot < MAX_PACKET_SIZE)
            {
                shtpData[dataSpot++] = incoming; // Store data into the shtpData array
            }
            else
            {
                // Do nothing with the data
            }
        }

        bytesRemaining -= numberOfBytesToRead;
    }
    return (1); // Done!
}

YZF_RESULT yzl_i2c_bno085_set_feature_command(YZF_I2C_POINTER i2c,unsigned char reportID, unsigned int timeBetweenReports, unsigned long specificConfig)
{
    long microsBetweenReports = (long)timeBetweenReports * 1000L;

    shtpData[0] = SHTP_REPORT_SET_FEATURE_COMMAND;     // Set feature command. Reference page 55
    shtpData[1] = reportID;                            // Feature Report ID. 0x01 = Accelerometer, 0x05 = Rotation vector
    shtpData[2] = 0;                                   // Feature flags
    shtpData[3] = 0;                                   // Change sensitivity (LSB)
    shtpData[4] = 0;                                   // Change sensitivity (MSB)
    shtpData[5] = (microsBetweenReports >> 0) & 0xFF;  // Report interval (LSB) in microseconds. 0x7A120 = 500ms
    shtpData[6] = (microsBetweenReports >> 8) & 0xFF;  // Report interval
    shtpData[7] = (microsBetweenReports >> 16) & 0xFF; // Report interval
    shtpData[8] = (microsBetweenReports >> 24) & 0xFF; // Report interval (MSB)
    shtpData[9] = 0;                                   // Batch Interval (LSB)
    shtpData[10] = 0;                                  // Batch Interval
    shtpData[11] = 0;                                  // Batch Interval
    shtpData[12] = 0;                                  // Batch Interval (MSB)
    shtpData[13] = (specificConfig >> 0) & 0xFF;       // Sensor-specific config (LSB)
    shtpData[14] = (specificConfig >> 8) & 0xFF;       // Sensor-specific config
    shtpData[15] = (specificConfig >> 16) & 0xFF;      // Sensor-specific config
    shtpData[16] = (specificConfig >> 24) & 0xFF;      // Sensor-specific config (MSB)

    // Transmit packet on channel 2, 17 bytes
    return yzl_i2c_bno085_send_packet(i2c,CHANNEL_CONTROL, 17);
}

// Tell the sensor to do a command
// See 6.3.8 page 41, Command request
// The caller is expected to set P0 through P8 prior to calling
YZF_RESULT yzl_i2c_bno085_send_command(YZF_I2C_POINTER i2c,unsigned char command)
{
    shtpData[0] = SHTP_REPORT_COMMAND_REQUEST; // Command Request
    shtpData[1] = commandSequenceNumber++;     // Increments automatically each function call
    shtpData[2] = command;                     // Command

    // Caller must set these
    /*shtpData[3] = 0; //P0
    shtpData[4] = 0; //P1
    shtpData[5] = 0; //P2
    shtpData[6] = 0;
    shtpData[7] = 0;
    shtpData[8] = 0;
    shtpData[9] = 0;
    shtpData[10] = 0;
    shtpData[11] = 0;*/

    // Transmit packet on channel 2, 12 bytes
    return yzl_i2c_bno085_send_packet(i2c,CHANNEL_CONTROL, 12);
}

// This tells the BNO080 to begin calibrating
// See page 50 of reference manual and the 1000-4044 calibration doc
YZF_RESULT yzl_i2c_bno085_send_calibrate_command(YZF_I2C_POINTER i2c,unsigned char thingToCalibrate)
{
    unsigned char x = 0;
    /*shtpData[3] = 0; //P0 - Accel Cal Enable
    shtpData[4] = 0; //P1 - Gyro Cal Enable
    shtpData[5] = 0; //P2 - Mag Cal Enable
    shtpData[6] = 0; //P3 - Subcommand 0x00
    shtpData[7] = 0; //P4 - Planar Accel Cal Enable
    shtpData[8] = 0; //P5 - Reserved
    shtpData[9] = 0; //P6 - Reserved
    shtpData[10] = 0; //P7 - Reserved
    shtpData[11] = 0; //P8 - Reserved*/

    for (x = 3; x < 12; x++) // Clear this section of the shtpData array
        shtpData[x] = 0;

    if (thingToCalibrate == CALIBRATE_ACCEL)
        shtpData[3] = 1;
    else if (thingToCalibrate == CALIBRATE_GYRO)
        shtpData[4] = 1;
    else if (thingToCalibrate == CALIBRATE_MAG)
        shtpData[5] = 1;
    else if (thingToCalibrate == CALIBRATE_PLANAR_ACCEL)
        shtpData[7] = 1;
    else if (thingToCalibrate == CALIBRATE_ACCEL_GYRO_MAG)
    {
        shtpData[3] = 1;
        shtpData[4] = 1;
        shtpData[5] = 1;
    }
    else if (thingToCalibrate == CALIBRATE_STOP); // Do nothing, bytes are set to zero

    // Using this shtpData packet, send a command
    return yzl_i2c_bno085_send_command(i2c,COMMAND_ME_CALIBRATE);
}

// This tells the BNO080 to save the Dynamic Calibration Data (DCD) to flash
// See page 49 of reference manual and the 1000-4044 calibration doc
YZF_RESULT yzl_i2c_bno085_save_calibration(YZF_I2C_POINTER i2c)
{
    unsigned char x = 0;
    /*shtpData[3] = 0; //P0 - Reserved
    shtpData[4] = 0; //P1 - Reserved
    shtpData[5] = 0; //P2 - Reserved
    shtpData[6] = 0; //P3 - Reserved
    shtpData[7] = 0; //P4 - Reserved
    shtpData[8] = 0; //P5 - Reserved
    shtpData[9] = 0; //P6 - Reserved
    shtpData[10] = 0; //P7 - Reserved
    shtpData[11] = 0; //P8 - Reserved*/

    for (x = 3; x < 12; x++) // Clear this section of the shtpData array
        shtpData[x] = 0;

    // Using this shtpData packet, send a command
    return yzl_i2c_bno085_send_command(i2c,COMMAND_DCD); // Save DCD command
}

// Sends the commands to begin calibration of the accelerometer
YZF_RESULT yzl_i2c_bno085_calibrate_accelerometer(YZF_I2C_POINTER i2c)
{
    return yzl_i2c_bno085_send_calibrate_command(i2c, CALIBRATE_ACCEL);
}

// Sends the commands to begin calibration of the gyro
YZF_RESULT yzl_i2c_bno085_calibrate_gyro(YZF_I2C_POINTER i2c)
{
    return yzl_i2c_bno085_send_calibrate_command(i2c, CALIBRATE_GYRO);
}

// Sends the commands to begin calibration of the magnetometer
YZF_RESULT yzl_i2c_bno085_calibrate_magnetometer(YZF_I2C_POINTER i2c)
{
    return yzl_i2c_bno085_send_calibrate_command(i2c, CALIBRATE_MAG);
}

// Sends the commands to begin calibration of the planar accelerometer
YZF_RESULT yzl_i2c_bno085_calibrate_planar_accelerometer(YZF_I2C_POINTER i2c)
{
    return yzl_i2c_bno085_send_calibrate_command(i2c, CALIBRATE_PLANAR_ACCEL);
}

// See 2.2 of the Calibration Procedure document 1000-4044
YZF_RESULT yzl_i2c_bno085_calibrate_all(YZF_I2C_POINTER i2c)
{
    return yzl_i2c_bno085_send_calibrate_command(i2c, CALIBRATE_ACCEL_GYRO_MAG);
}

// End calibration process
YZF_RESULT yzl_i2c_bno085_end_calibration(YZF_I2C_POINTER i2c)
{
    return yzl_i2c_bno085_send_calibrate_command(i2c, CALIBRATE_STOP); // Disables all calibrations
}

// Sends the packet to enable the rotation vector
YZF_RESULT yzl_i2c_bno085_enable_rotation_vector(YZF_I2C_POINTER i2c, unsigned int timeBetweenReports)
{
    return yzl_i2c_bno085_set_feature_command(i2c, SENSOR_REPORTID_ROTATION_VECTOR, timeBetweenReports, 0);
}

// Sends the packet to enable the game rotation vector
YZF_RESULT yzl_i2c_bno085_enable_game_rotation_vector(YZF_I2C_POINTER i2c, unsigned int timeBetweenReports)
{
    return yzl_i2c_bno085_set_feature_command(i2c, SENSOR_REPORTID_GAME_ROTATION_VECTOR, timeBetweenReports, 0);
}

// Sends the packet to enable the accelerometer
YZF_RESULT yzl_i2c_bno085_enable_accelerometer(YZF_I2C_POINTER i2c, unsigned int timeBetweenReports)
{
    return yzl_i2c_bno085_set_feature_command(i2c, SENSOR_REPORTID_ACCELEROMETER, timeBetweenReports, 0);
}

// Sends the packet to enable the linear accelerometer
YZF_RESULT yzl_i2c_bno085_enable_linear_accelerometer(YZF_I2C_POINTER i2c, unsigned int timeBetweenReports)
{
    return yzl_i2c_bno085_set_feature_command(i2c, SENSOR_REPORTID_LINEAR_ACCELERATION, timeBetweenReports, 0);
}

// Sends the packet to enable the gyro
YZF_RESULT yzl_i2c_bno085_enable_gyro(YZF_I2C_POINTER i2c, unsigned int timeBetweenReports)
{
    return yzl_i2c_bno085_set_feature_command(i2c, SENSOR_REPORTID_GYROSCOPE, timeBetweenReports, 0);
}

// Sends the packet to enable the magnetometer
YZF_RESULT yzl_i2c_bno085_enable_magnetometer(YZF_I2C_POINTER i2c, unsigned int timeBetweenReports)
{
    return yzl_i2c_bno085_set_feature_command(i2c, SENSOR_REPORTID_MAGNETIC_FIELD, timeBetweenReports, 0);
}

// Sends the packet to enable the step counter
YZF_RESULT yzl_i2c_bno085_enable_step_counter(YZF_I2C_POINTER i2c, unsigned int timeBetweenReports)
{
    return yzl_i2c_bno085_set_feature_command(i2c, SENSOR_REPORTID_STEP_COUNTER, timeBetweenReports, 0);
}

// Sends the packet to enable the Stability Classifier
YZF_RESULT yzl_i2c_bno085_enable_stability_classifier(YZF_I2C_POINTER i2c, unsigned int timeBetweenReports)
{
    return yzl_i2c_bno085_set_feature_command(i2c, SENSOR_REPORTID_STABILITY_CLASSIFIER, timeBetweenReports, 0);
}

void yzl_i2c_bno085_parse_input_report(){
    // Calculate the number of data bytes in this packet
    int dataLength = ((unsigned int)shtpHeader[1] << 8 | shtpHeader[0]);

    //    Bits 1:0 – indicate the status of a sensor.
    //    0 – Unreliable
    //    1 – Accuracy low
    //    2 – Accuracy medium
    //    3 – Accuracy high
    //    Bits 7:2 – Delay upper bits: 6 most-significant bits of
    //    report delay. See blow.
    unsigned char status = shtpData[5 + 2] & 0x03; // Get status bits

    unsigned int data1 = (unsigned int)shtpData[5 + 5] << 8 | shtpData[5 + 4];
    unsigned int data2 = (unsigned int)shtpData[5 + 7] << 8 | shtpData[5 + 6];
    unsigned int data3 = (unsigned int)shtpData[5 + 9] << 8 | shtpData[5 + 8];
    unsigned int data4 = (unsigned int)shtpData[5 + 11] << 8 | shtpData[5 + 10];
    unsigned int data5 = 0;
    unsigned char x = 0;
    dataLength &= ~(1 << 15); // Clear the MSbit. This bit indicates if this package is a continuation of the last.
    // Ignore it for now. TODO catch this as an error and exit

    dataLength -= 4; // Remove the header bytes from the data count

    if (dataLength - 5 > 9)
    {
        data4 = (unsigned int)shtpData[5 + 11] << 8 | shtpData[5 + 10];
    }
    if (dataLength - 5 > 11)
    {
        data5 = (unsigned int)shtpData[5 + 13] << 8 | shtpData[5 + 12];
    }

    // Store these generic values to their proper global variable
    if (shtpData[5] == SENSOR_REPORTID_ACCELEROMETER)
    {
        accelAccuracy = status;
        rawAccelX = (int16_t)data1;
        rawAccelY = (int16_t)data2;
        rawAccelZ = (int16_t)data3;
    }
    else if (shtpData[5] == SENSOR_REPORTID_LINEAR_ACCELERATION)
    {
        accelLinAccuracy = status;
        rawLinAccelX = (int16_t)data1;
        rawLinAccelY = (int16_t)data2;
        rawLinAccelZ = (int16_t)data3;
    }
    else if (shtpData[5] == SENSOR_REPORTID_GYROSCOPE)
    {
        gyroAccuracy = status;
        rawGyroX = (int16_t)data1;
        rawGyroY = (int16_t)data2;
        rawGyroZ = (int16_t)data3;
    }
    else if (shtpData[5] == SENSOR_REPORTID_MAGNETIC_FIELD)
    {
        magAccuracy = status;
        rawMagX = (int16_t)data1;
        rawMagY = (int16_t)data2;
        rawMagZ = (int16_t)data3;
    }
    else if (shtpData[5] == SENSOR_REPORTID_ROTATION_VECTOR || shtpData[5] == SENSOR_REPORTID_GAME_ROTATION_VECTOR)
    {
        quatAccuracy = status;
        rawQuatI = (int16_t)data1;
        rawQuatJ = (int16_t)data2;
        rawQuatK = (int16_t)data3;
        rawQuatReal = (int16_t)data4;
        rawQuatRadianAccuracy = data5; // Only available on rotation vector, not game rot vector
    }
    else if (shtpData[5] == SENSOR_REPORTID_STEP_COUNTER)
    {
        stepCount = data3; // Bytes 8/9
    }
    else if (shtpData[5] == SENSOR_REPORTID_STABILITY_CLASSIFIER)
    {
        stabilityClassifier = shtpData[5 + 4]; // Byte 4 only
    }
    else if (shtpData[5] == SENSOR_REPORTID_PERSONAL_ACTIVITY_CLASSIFIER)
    {
        activityClassifier = shtpData[5 + 5]; // Most likely state

        // Load activity classification confidences into the array
        for (x = 0; x < 9; x++)                            // Hardcoded to max of 9. TODO - bring in array size
            _activityConfidences[x] = shtpData[5 + 6 + x]; // 5 bytes of timestamp, byte 6 is first confidence byte
    }
    else
    {
        // This sensor report ID is unhandled.
        // See reference manual to add additional feature reports as needed
    }

    // TODO additional feature reports may be strung together. Parse them all.
}

YZF_RESULT yzl_i2c_bno085_data_available(YZF_I2C_POINTER i2c){
    if (yzl_i2c_bno085_receive_packet(i2c) == YZF_OK)
    {
        // Check to see if this packet is a sensor reporting its data to us
        if (shtpHeader[2] == CHANNEL_REPORTS && shtpData[0] == SHTP_REPORT_BASE_TIMESTAMP)
        {
            yzl_i2c_bno085_parse_input_report(); // This will update the rawAccelX, etc variables depending on which feature report is found
            return YZF_OK;
        }
    }
    return YZF_ERROR;
}


float yzl_i2c_bno085_qToFloat(int fixedPointValue, unsigned char qPoint)
{
    float qFloat = fixedPointValue;
    qFloat *= pow(2, qPoint * -1);
    return (qFloat);
}

// Return the rotation vector quaternion I
float yzl_i2c_bno085_get_quat_i(void)
{
    float quat = yzl_i2c_bno085_qToFloat(rawQuatI, (uint8_t)rotationVector_Q1);
    return (quat);
}

// Return the rotation vector quaternion J
float yzl_i2c_bno085_get_quat_j(void)
{
    float quat = yzl_i2c_bno085_qToFloat(rawQuatJ, (uint8_t)rotationVector_Q1);
    return (quat);
}

// Return the rotation vector quaternion K
float yzl_i2c_bno085_get_quat_k(void)
{
    float quat = yzl_i2c_bno085_qToFloat(rawQuatK, (uint8_t)rotationVector_Q1);
    return (quat);
}

// Return the rotation vector quaternion Real
float yzl_i2c_bno085_get_quat_real(void)
{
    float quat = yzl_i2c_bno085_qToFloat(rawQuatReal, (uint8_t)rotationVector_Q1);
    return (quat);
}

// Return the rotation vector accuracy
float yzl_i2c_bno085_get_quat_radian_accuracy(void)
{
    float quat = yzl_i2c_bno085_qToFloat(rawQuatRadianAccuracy, (uint8_t)rotationVector_Q1);
    return (quat);
}

// Return the quaternion accuracy
uint8_t yzl_i2c_bno085_get_quat_accuracy(void)
{
    return (quatAccuracy);
}

// Return the acceleration X component
float yzl_i2c_bno085_get_accel_x(void)
{
    float accel = yzl_i2c_bno085_qToFloat(rawAccelX, (uint8_t)accelerometer_Q1);
    return (accel);
}

// Return the acceleration Y component
float yzl_i2c_bno085_get_accel_y(void)
{
    float accel = yzl_i2c_bno085_qToFloat(rawAccelY, (uint8_t)accelerometer_Q1);
    return (accel);
}

// Return the acceleration Z component
float yzl_i2c_bno085_get_accel_z(void)
{
    float accel = yzl_i2c_bno085_qToFloat(rawAccelZ, (uint8_t)accelerometer_Q1);
    return (accel);
}

// Return the acceleration accuracy
uint8_t yzl_i2c_bno085_get_accel_accuracy(void)
{
    return (accelAccuracy);
}

// linear acceleration, i.e. minus gravity

// Return the linear acceleration X component
float yzl_i2c_bno085_get_lin_accel_x(void)
{
    float accel = yzl_i2c_bno085_qToFloat(rawLinAccelX, (uint8_t)linear_accelerometer_Q1);
    return (accel);
}

// Return the linear acceleration Y component
float yzl_i2c_bno085_get_lin_accel_y(void)
{
    float accel = yzl_i2c_bno085_qToFloat(rawLinAccelY, (uint8_t)linear_accelerometer_Q1);
    return (accel);
}

// Return the linear acceleration Z component
float yzl_i2c_bno085_get_lin_accel_z(void)
{
    float accel = yzl_i2c_bno085_qToFloat(rawLinAccelZ, (uint8_t)linear_accelerometer_Q1);
    return (accel);
}

// Return the linear acceleration accuracy
uint8_t yzl_i2c_bno085_get_lin_accel_accuracy(void)
{
    return (accelLinAccuracy);
}

// Return the gyro X component
float yzl_i2c_bno085_get_gyro_x(void)
{
    float gyro = yzl_i2c_bno085_qToFloat(rawGyroX, (uint8_t)gyro_Q1);
    return (gyro);
}

// Return the gyro Y component
float yzl_i2c_bno085_get_gyro_y(void)
{
    float gyro = yzl_i2c_bno085_qToFloat(rawGyroY, (uint8_t)gyro_Q1);
    return (gyro);
}

// Return the gyro Z component
float yzl_i2c_bno085_get_gyro_z(void)
{
    float gyro = yzl_i2c_bno085_qToFloat(rawGyroZ, (uint8_t)gyro_Q1);
    return (gyro);
}

// Return the gyro accuracy
uint8_t yzl_i2c_bno085_get_gyro_accuracy(void)
{
    return (gyroAccuracy);
}

// Return the magnetometer X component
float yzl_i2c_bno085_get_mag_x(void)
{
    float mag = yzl_i2c_bno085_qToFloat(rawMagX, (uint8_t)magnetometer_Q1);
    return (mag);
}

// Return the magnetometer Y component
float yzl_i2c_bno085_get_mag_y(void)
{
    float mag = yzl_i2c_bno085_qToFloat(rawMagY, (uint8_t)magnetometer_Q1);
    return (mag);
}

// Return the magnetometer Z component
float yzl_i2c_bno085_get_mag_z(void)
{
    float mag = yzl_i2c_bno085_qToFloat(rawMagZ, (uint8_t)magnetometer_Q1);
    return (mag);
}

// Return the magnetometer accuracy
uint8_t yzl_i2c_bno085_get_mag_accuracy(void)
{
    return (magAccuracy);
}

// Ask the sensor for data from the Flash Record System
// See 6.3.6 page 40, FRS Read Request
void yzl_i2c_bno085_frs_read_request(YZF_I2C_POINTER i2c,unsigned int recordID, unsigned int readOffset, unsigned int blockSize)
{
    shtpData[0] = SHTP_REPORT_FRS_READ_REQUEST; // FRS Read Request
    shtpData[1] = 0;                            // Reserved
    shtpData[2] = (readOffset >> 0) & 0xFF;     // Read Offset LSB
    shtpData[3] = (readOffset >> 8) & 0xFF;     // Read Offset MSB
    shtpData[4] = (recordID >> 0) & 0xFF;       // FRS Type LSB
    shtpData[5] = (recordID >> 8) & 0xFF;       // FRS Type MSB
    shtpData[6] = (blockSize >> 0) & 0xFF;      // Block size LSB
    shtpData[7] = (blockSize >> 8) & 0xFF;      // Block size MSB

    // Transmit packet on channel 2, 8 bytes
    yzl_i2c_bno085_send_packet(i2c,CHANNEL_CONTROL, 8);
}

// Given a sensor or record ID, and a given start/stop bytes, read the data from the Flash Record System (FRS) for this sensor
// Returns 1 if metaData array is loaded successfully
// Returns 0 if failure
char yzl_i2c_bno085_read_frs_data(YZF_I2C_POINTER i2c,unsigned int recordID, unsigned char startLocation, unsigned char wordsToRead)
{
    unsigned char spot = 0;
    unsigned char dataLength = 0;
    unsigned char frsStatus = 0;
    unsigned long data0 = 0;
    unsigned long data1 = 0;
    // First we send a Flash Record System (FRS) request
    yzl_i2c_bno085_frs_read_request(i2c,recordID, startLocation, wordsToRead); // From startLocation of record, read a # of words

    // Read bytes until FRS reports that the read is complete
    while (1)
    {
        // Now we wait for response
        while (1)
        {
            unsigned char counter = 0;
            while (yzl_i2c_bno085_receive_packet(i2c) == YZF_ERROR)
            {
                if (counter++ > 100)
                    return (0); // Give up
                HAL_Delay(1);
            }

            // We have the packet, inspect it for the right contents
            // See page 40. Report ID should be 0xF3 and the FRS types should match the thing we requested
            if (shtpData[0] == SHTP_REPORT_FRS_READ_RESPONSE)
                if (((unsigned int)shtpData[13] << 8 | shtpData[12]) == recordID)
                    break; // This packet is one we are looking for
        }

        dataLength = shtpData[1] >> 4;
        frsStatus = shtpData[1] & 0x0F;

        data0 = (unsigned long)shtpData[7] << 24 | (unsigned long)shtpData[6] << 16 | (unsigned long)shtpData[5] << 8 | (unsigned long)shtpData[4];
        data1 = (unsigned long)shtpData[11] << 24 | (unsigned long)shtpData[10] << 16 | (unsigned long)shtpData[9] << 8 | (unsigned long)shtpData[8];

        // Record these words to the metaData array
        if (dataLength > 0)
        {
            metaData[spot++] = data0;
        }
        if (dataLength > 1)
        {
            metaData[spot++] = data1;
        }

        if (frsStatus == 3 || frsStatus == 6 || frsStatus == 7)
        {
            return (1); // FRS status is read completed! We're done!
        }
    }
}

// Given a record ID and a word number, look up the word data
// Helpful for pulling out a Q value, range, etc.
// Use readFRSdata for pulling out multi-word objects for a sensor (Vendor data for example)
unsigned long yzl_i2c_bno085_read_frs_word(YZF_I2C_POINTER i2c,unsigned int recordID, unsigned char wordNumber)
{
    if (yzl_i2c_bno085_read_frs_data(i2c,recordID, wordNumber, 1) == 1) // Get word number, just one word in length from FRS
        return (metaData[0]);                      // Return this one word

    return (0); // Error
}

// Given a record ID, read the Q1 value from the metaData record in the FRS
// Q1 is used to change the resolution of sensor values
int yzl_i2c_bno085_get_q1(YZF_I2C_POINTER i2c, unsigned int recordID)
{
    // Q1 is always the lower 16 bits of word 7
    unsigned int q = yzl_i2c_bno085_read_frs_word(i2c, recordID, 7) & 0xFFFF; // Get word 7, lower 16 bits
    return (q);
}

// Given a record ID, read the Q2 value from the metaData record in the FRS
// Q2 is used in sensor bias
int yzl_i2c_bno085_get_q2(YZF_I2C_POINTER i2c, unsigned int recordID)
{
    // Q2 is always the upper 16 bits of word 7
    unsigned int q = yzl_i2c_bno085_read_frs_word(i2c, recordID, 7) >> 16; // Get word 7, upper 16 bits
    return (q);
}

// Given a record ID, read the Q3 value from the metaData record in the FRS
// Q3 is used in sensor change sensitivity
int yzl_i2c_bno085_get_q3(YZF_I2C_POINTER i2c, unsigned int recordID)
{
    // Q3 is always the upper 16 bits of word 8
    unsigned int q = yzl_i2c_bno085_read_frs_word(i2c, recordID, 8) >> 16; // Get word 8, upper 16 bits
    return (q);
}

// Given a record ID, read the resolution value from the metaData record in the FRS for a given sensor
float yzl_i2c_bno085_get_resolution(YZF_I2C_POINTER i2c, unsigned int recordID)
{
    // The resolution Q value are 'the same as those used in the sensor's input report'
    // This should be Q1.
    int Q = yzl_i2c_bno085_get_q1(i2c, recordID);

    // Resolution is always word 2
    unsigned long value = yzl_i2c_bno085_read_frs_word(i2c, recordID, 2); // Get word 2

    float resolution = yzl_i2c_bno085_qToFloat((unsigned int)value, (uint8_t)Q);

    return (resolution);
}

// Given a record ID, read the range value from the metaData record in the FRS for a given sensor
float yzl_i2c_bno085_get_range(YZF_I2C_POINTER i2c, unsigned int recordID)
{
    // The resolution Q value are 'the same as those used in the sensor's input report'
    // This should be Q1.
    int Q = yzl_i2c_bno085_get_q1(i2c, recordID);

    // Range is always word 1
    unsigned long value = yzl_i2c_bno085_read_frs_word(i2c, recordID, 1); // Get word 1

    float range = yzl_i2c_bno085_qToFloat((unsigned int)value, (uint8_t)Q);

    return (range);
}

#include "yzl_math.h"
void  yzl_i2c_bno085_quat_2_euler(Quaternion *q, float *yaw, float *pitch, float *roll)
{

//    *roll = atan2(2 * (q->w * q->x + q->y * q->z), q->w * q->w - q->x * q->x - q->y * q->y + q->z * q->z);
//
//    *yaw = atan2(2 * (q->w * q->z - q->x * q->y), 1 - 2 * (q->y * q->y + q->z * q->z));
//
//    *pitch = 0;

//    float w = q->w;
    float w = q->w;
    float x = q->x;
    float y = q->y;
    float z = q->z;

    // 计算四元数的平方和（用于归一化检查）
    float sqw = w * w;
    float sqx = x * x;
    float sqy = y * y;
    float sqz = z * z;

    // 计算俯仰角 (pitch) - 绕Y轴旋转
    float sinp = 2.0f * (w * y - z * x);

    // 处理俯仰角接近±90度时的数值稳定性
    if (fabs(sinp) >= 1.0f) {
        *pitch = copysign(M_PI / 2.0f, sinp); // ±90度
    } else {
        *pitch = asin(sinp);
    }

    // 计算偏航角 (yaw) 和滚转角 (roll)
    float sinr_cosp = 2.0f * (w * x + y * z);
    float cosr_cosp = 1.0f - 2.0f * (sqx + sqy);
    *roll = yzl_atan2_tab_calc(sinr_cosp, cosr_cosp);

    float siny_cosp = 2.0f * (w * z + x * y);
    float cosy_cosp = 1.0f - 2.0f * (sqy + sqz);
    *yaw = yzl_atan2_tab_calc(siny_cosp, cosy_cosp);

    // 确保角度在 [-π, π] 范围内
    if (*yaw > M_PI) *yaw -= 2.0f * M_PI;
    if (*yaw < -M_PI) *yaw += 2.0f * M_PI;
    if (*roll > M_PI) *roll -= 2.0f * M_PI;
    if (*roll < -M_PI) *roll += 2.0f * M_PI;
}