//
// Created by 32827 on 2025/5/7.
//

#include "../Inc/ArmGroup.hpp"

ArmGroup::ArmGroup() {
    Position *defPos;
    Pose *defPose;
    defPos=new Position(0,0,0);
    defPose=new Pose(defPos,0,0,0);

    yz_info("Arm07...\n");
    arm07 = new SpaceSensorArmPole(arm07_dir,YZF_NULL_PTR,TIM4,2,TIM8,*defPose,90,-90,20,YZF_TRUE);
    arm07->scale=800;//0.5cm

    yz_info("Arm08...\n");
    arm08 = new SpaceSensorArmPole(arm08_dir,YZF_NULL_PTR,TIM4,3,TIM8,*defPose,26,0,5,YZF_TRUE);
    arm08->scale=1000;//cm

    yz_info("Arm09...\n");
    arm09 = new SpaceSensorArmPole(arm09_dir,YZF_NULL_PTR,TIM4,4,TIM8,*defPose,60,0,0,YZF_TRUE);
    arm09->scale=800;//mm

    yz_info("Arm10...\n");
    arm10 = new SpaceSensorArmPole(arm10_dir,YZF_NULL_PTR,TIM4,1,TIM8,*defPose,10000,0,40,YZF_TRUE);
    arm10->scale=1000;

    yz_info("Arm01...\n");
    arm01 = new SpaceSensorArmPlate(YZF_NULL_PTR,TIM1,1,*defPose,RotateTypeZ,2499,499,tim1_ch1_duty,YZF_TRUE);

    yz_info("Arm02...\n");
    arm02 = new SpaceSensorArmPlate(arm01,TIM1,2,*defPose,RotateTypeX,2499,499,tim1_ch2_duty,YZF_TRUE);

    yz_info("Arm03...\n");
    arm03 = new SpaceSensorArmPlate(arm02,TIM1,3,*defPose,RotateTypeX,2499,499,tim1_ch3_duty,YZF_TRUE);

    yz_info("Arm04...\n");
    arm04 = new SpaceSensorArmPlate(arm03,TIM1,4,*defPose,RotateTypeX,2499,499,tim1_ch4_duty,YZF_TRUE);

    yz_info("Arm05...\n");
    arm05 = new SpaceSensorArmPlate(arm04,TIM3,1,*defPose,RotateTypeX,2499,499,tim3_ch1_duty,YZF_TRUE);

    yz_info("Arm06...\n");
    arm06 = new SpaceSensorArmPlate(arm05,TIM3,2,*defPose,RotateTypeX,2499,499,tim3_ch2_duty,YZF_TRUE);

    delete defPose;
    delete defPos;
}

ArmGroup::~ArmGroup() {
    delete arm06;
    delete arm05;
    delete arm04;
    delete arm03;
    delete arm02;
    delete arm01;
}

void ArmGroup::addParams(int index,float timeUnit) {
    if(index==0){
        arm01->addAngle(15.0f*timeUnit);
    }
    if(index==1){
        arm02->addAngle(15.0f*timeUnit);
    }
    if(index==2){
        arm03->addAngle(15.0f*timeUnit);
    }
    if(index==3){
        arm04->addAngle(15.0f*timeUnit);
    }
    if(index==4){
        arm05->addAngle(15.0f*timeUnit);
    }
    if(index==5){
        arm06->addAngle(15.0f*timeUnit);
    }
    if(index==6){
        arm07->addLength(10.0f*timeUnit);
    }
}

void ArmGroup::delParams(int index,float timeUnit) {
    if(index==0){
        arm01->delAngle(15.0f*timeUnit);
    }
    if(index==1){
        arm02->delAngle(15.0f*timeUnit);
    }
    if(index==2){
        arm03->delAngle(15.0f*timeUnit);
    }
    if(index==3){
        arm04->delAngle(15.0f*timeUnit);
    }
    if(index==4){
        arm05->delAngle(15.0f*timeUnit);
    }
    if(index==5){
        arm06->delAngle(15.0f*timeUnit);
    }
    if(index==6){
        arm07->delLength(10*timeUnit);
    }
}

uint32_t ArmGroup::ProgramTick = 0;
YZF_BOOL ArmGroup::isLoadTickHandler = YZF_FALSE;

YZF_RESULT ArmGroup::ProgramTickHandler(uint32_t tick) {
    ProgramTick+=tick;
    return YZF_HANDLER_NOT_FINISH;
}

void ArmGroup::act() {
    arm07->act(ProgramTick);
    arm01->act(ProgramTick);
    arm02->act(ProgramTick);
    arm03->act(ProgramTick);
    arm04->act(ProgramTick);
    arm05->act(ProgramTick);
    arm06->act(ProgramTick);
}

void ArmGroup::Init() {
    yz_heart_process_add(ProgramTickHandler);
    isLoadTickHandler = YZF_TRUE;
}

void ArmGroup::getEnd() {

}
float SpaceResultY1[4];

float arm01_fix=8.280f;
float arm01_len=25.0f;
float arm02_fix=1.0f;
float arm02_len=17.5f;
float arm03_fix=90.0f;
float arm04_fix=40.0f;
float arm0201_len_cos;
float arm0201_len_sin;
float arm0201_len;
float arm0201_up_angle;
float arm0201_ground_len;

float *ArmGroup::compile() {
    float bottom_angle=arm01->getAngle()-arm01_fix;
    float bottom_cos=COS(bottom_angle);
    float bottom_sin=SIN(bottom_angle);
    float up_angle=arm02->getAngle()-arm02_fix;
//    float up_cos=COS(up_angle);
//    float up_sin=SIN(up_angle);

    float up_dir_angle=arm03_fix-(arm03->getAngle()-180.0f);
    float up_dir_cos=COS(up_dir_angle);
    float up_dir_sin=SIN(up_dir_angle);

    arm0201_len_cos = arm01_len-arm02_len*up_dir_cos;
    arm0201_len_sin = arm02_len*up_dir_sin;
    arm0201_len=sqrt(arm0201_len_cos*arm0201_len_cos+arm0201_len_sin*arm0201_len_sin);
    arm0201_up_angle=up_angle-yzl_atan2_tab_calc(arm0201_len_sin,arm0201_len_cos);//TODO : need div PI

    SpaceResultY1[2] = arm0201_len * SIN(arm0201_up_angle); // Y
    arm0201_ground_len = arm0201_len * COS(arm0201_up_angle); // 2D Len 地映射
    SpaceResultY1[0] = arm0201_ground_len * bottom_cos;
    SpaceResultY1[1] = arm0201_ground_len * bottom_sin;
    SpaceResultY1[3] = 220.0f-arm03->getAngle()+up_angle;
    return SpaceResultY1;
}
