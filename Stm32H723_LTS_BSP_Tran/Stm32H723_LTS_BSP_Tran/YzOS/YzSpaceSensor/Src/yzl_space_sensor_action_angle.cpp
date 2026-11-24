//
// Created by 32827 on 2025/4/27.
//

#include "yzl_space_sensor_action_angle.hpp"

SpaceSensorActionAngle::SpaceSensorActionAngle(int TickStart, int TickLength, float FromAngle, float ToAngle) {
    this->TickStart = TickStart;
    this->TickLength = TickLength;
    this->FromAngle = FromAngle;
    this->ToAngle = ToAngle;
}

ActionType SpaceSensorActionAngle::getType() {
    return ACTION_TYPE_ANGLE;
}

void SpaceSensorActionAngle::setArm(void *pArm) {
    arm  = (SpaceSensorArm *)(pArm);
}

YZF_RESULT SpaceSensorActionAngle::act(int SystemTick) {
    if(SystemTick < TickStart){
        return YZF_HANDLER_NOT_FINISH;
    }
    if(SystemTick > TickStart + TickLength){
        return YZF_OK;
    }
    float t = (float)(SystemTick - TickStart) / (float)TickLength;
    float angle = FromAngle + (ToAngle - FromAngle) * yzl_math_transform_a2(t);
    arm->setAngle(angle);
    return YZF_HANDLER_NOT_FINISH;
}
