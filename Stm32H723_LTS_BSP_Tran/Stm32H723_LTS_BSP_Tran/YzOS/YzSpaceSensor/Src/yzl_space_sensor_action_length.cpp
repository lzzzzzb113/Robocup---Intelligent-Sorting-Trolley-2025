//
// Created by 32827 on 2025/5/2.
//

#include "yzl_space_sensor_action_length.hpp"

SpaceSensorActionLength::SpaceSensorActionLength(int TickStart, int TickLength, float FromLength, float ToLength) {
    this->TickStart = TickStart;
    this->TickLength = TickLength;
    this->FromLength = FromLength;
    this->ToLength = ToLength;
}

YZF_RESULT SpaceSensorActionLength::act(int SystemTick) {
    if(SystemTick < TickStart){
        return YZF_HANDLER_NOT_FINISH;
    }
    if((SystemTick > (TickStart + TickLength)) && (arm->getLength() == ToLength) && arm->isFinish()){
        return YZF_OK;
    }
    if(arm->isFinish()){
        float t = (float)(SystemTick - TickStart) / (float)TickLength;
        float length = FromLength + (ToLength - FromLength) * yzl_math_transform_a2(t);
        arm->setLength(length);
    }
    return YZF_HANDLER_NOT_FINISH;
}

ActionType SpaceSensorActionLength::getType() {
    return ACTION_TYPE_POSITION;
}

void SpaceSensorActionLength::setArm(void *pArm) {
    arm  = (SpaceSensorArmPole *)(pArm);
}
