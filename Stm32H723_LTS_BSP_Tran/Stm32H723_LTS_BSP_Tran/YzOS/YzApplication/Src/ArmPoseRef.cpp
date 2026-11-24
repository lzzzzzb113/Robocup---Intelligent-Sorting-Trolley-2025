//
// Created by 32827 on 2025/5/12.
//

#include "../Inc/ArmPoseRef.hpp"

ArmPoseRef::ArmPoseRef(ArmGroup *armGroup) {
    this->armGroup=armGroup;
}

ArmPoseRef::~ArmPoseRef() {

}

void ArmPoseRef::Capture() {
    arm_data[0] = armGroup->arm01->getAngle();
    arm_data[1] = armGroup->arm02->getAngle();
    arm_data[2] = armGroup->arm03->getAngle();
    arm_data[3] = armGroup->arm04->getAngle();
    arm_data[4] = armGroup->arm05->getAngle();
    arm_data[5] = armGroup->arm06->getAngle();
}

void ArmPoseRef::Restore(int time) {
    armGroup->arm01->addAction(new SpaceSensorActionAngle(armGroup->ProgramTick,time,armGroup->arm01->getAngle(),arm_data[0]));
    armGroup->arm02->addAction(new SpaceSensorActionAngle(armGroup->ProgramTick,time,armGroup->arm02->getAngle(),arm_data[1]));
    armGroup->arm03->addAction(new SpaceSensorActionAngle(armGroup->ProgramTick,time,armGroup->arm03->getAngle(),arm_data[2]));
    armGroup->arm04->addAction(new SpaceSensorActionAngle(armGroup->ProgramTick,time,armGroup->arm04->getAngle(),arm_data[3]));
    armGroup->arm05->addAction(new SpaceSensorActionAngle(armGroup->ProgramTick,time,armGroup->arm05->getAngle(),arm_data[4]));
    armGroup->arm06->addAction(new SpaceSensorActionAngle(armGroup->ProgramTick,time,armGroup->arm06->getAngle(),arm_data[5]));
//    armGroup->arm07->addAction(new SpaceSensorActionLength(armGroup->ProgramTick,time,armGroup->arm07->getLength(),arm_data[6]));
}

YZF_BOOL ArmPoseRef::IsRestore() {
    if( armGroup->arm01->isActionFinish()&&
        armGroup->arm02->isActionFinish()&&
        armGroup->arm03->isActionFinish()&&
        armGroup->arm04->isActionFinish()&&
        armGroup->arm05->isActionFinish()&&
        armGroup->arm06->isActionFinish()&&
        armGroup->arm07->isActionFinish()){
        return YZF_TRUE;
    }else{
        return YZF_FALSE;
    }
}

void ArmPoseRef::act() {
    isFinish = YZF_TRUE;
}

ArmPoseRef::ArmPoseRef(float *arm_data, ArmGroup *armGroup) {
    memcpy(this->arm_data,arm_data,sizeof(float)*7);
    this->armGroup = armGroup;
}

void ArmPoseRef::SetData(float *pArm_data) {
    for (int i = 0; i < 7; ++i) {
        arm_data[i]=pArm_data[i];
    }
}
