//
// Created by 32827 on 2025/4/24.
//

#include "yzl_space_sensor_arm_plate.hpp"
#include "yz_tim.h"
SpaceSensorArmPlate::SpaceSensorArmPlate(SpaceSensorArm *parent, YZF_TIM_POINTER tim, uint16_t ch_id, Pose defaultPose,
                                         SpaceSensorArmRotateType type, int maxParam, int minParam, int defaultParam,
                                         YZF_BOOL isRoot) {
    parentArm = parent;
    ArmPoseBack = defaultPose;
    this->tim = tim;
    this->ch_id = ch_id;
    minLimit = minParam;
    maxLimit = maxParam;
    nowParam = defaultParam;
    this->isRoot = isRoot;
    rotateType = type;

    yz_tim_pwm_data_set(tim,ch_id,nowParam,19999);

    ArmPose=ArmPoseBack;

    switch (rotateType) {
        case RotateTypeX:
            ArmPose.RotateX(((float )(nowParam-499)/2000.0f)*180.0f);
            break;
        case RotateTypeY:
            ArmPose.RotateY(((float )(nowParam-499)/2000.0f)*180.0f);
            break;
        case RotateTypeZ:
            ArmPose.RotateZ(((float )(nowParam-499)/2000.0f)*180.0f);
            break;
        default:
        break;
    }
}

float SpaceSensorArmPlate::setAngle(float angle) {
    int param = 499+(int)((angle/180.0f)*2000.0f);
    if(param<minLimit){
        param = minLimit;
    }else if(param>maxLimit){
        param = maxLimit;
    }
    nowParam = param;
    yz_tim_pwm_data_set(tim,ch_id,nowParam,19999);
#if YZSCREEN
    if(hasWidget){
        memset(transmit_buf,0,64);
        sprintf(transmit_buf,"%.3f",((float )(nowParam-499)/2000.0f)*180.0f);
        widgetText->setText((utf8 *)transmit_buf);
    }
#endif

    ArmPose=ArmPoseBack;
    switch (rotateType) {
        case RotateTypeX:
            ArmPose.RotateX(((float )(nowParam-499)/2000.0f)*180.0f);
            break;
        case RotateTypeY:
            ArmPose.RotateY(((float )(nowParam-499)/2000.0f)*180.0f);
            break;
        case RotateTypeZ:
            ArmPose.RotateZ(((float )(nowParam-499)/2000.0f)*180.0f);
            break;
        default:
            break;
    }

    return ((float )(nowParam-499)/2000.0f)*180.0f;
}

Position SpaceSensorArmPlate::getPosition(SpaceSensorArm *ArmEnd) {
    //TODO: MAY RAM LEAK
    // 可能存在内存泄露，暂时不适用
    Position temp(0,0,0);
    SpaceSensorArm *tempArm=this;
    if(ArmEnd==this){
        return *(ArmPose * temp);
    }
    while(1){
        if(tempArm->isRoot==YZF_TRUE){
            return temp;
        }else if(parentArm!=YZF_NULL_PTR){
            tempArm=parentArm;
            Position *p=(tempArm->ArmPose * temp);
            temp = *p;
            delete p;
        }else{
            return temp;
        }
    }
}

float SpaceSensorArmPlate::getAngle() {
    return ((float )(nowParam-499)/2000.0f)*180.0f;
}

void SpaceSensorArmPlate::addAction(SpaceSensorAction *action) {
    if(action->getType()==ACTION_TYPE_ANGLE) {
        SpaceSensorArm::addAction(action);
    }else{
        delete action;
    }
}

#if YZSCREEN
void SpaceSensorArmPlate::LinkTextUI(WidgetTextButton *pWidgetText) {
    this->widgetText = pWidgetText;
    hasWidget = YZF_TRUE;
    memset(transmit_buf,0,64);
    sprintf(transmit_buf,"%.3f",((float )(nowParam-499)/2000.0f)*180.0f);
    widgetText->setText((utf8 *)transmit_buf);
}

void SpaceSensorArmPlate::CancelLink() {
    hasWidget = YZF_FALSE;
}

#endif


