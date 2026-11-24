//
// Created by 32827 on 2025/4/24.
//

#include "yzl_space_sensor_arm.hpp"

Position SpaceSensorArm::getPosition(SpaceSensorArm *ArmEnd) {
    //TODO: ERROR RETURN
    return Position();
}

float SpaceSensorArm::setAngle(float angle) {
    return 0;
}

float SpaceSensorArm::getAngle() {
    return 0;
}

float SpaceSensorArm::addAngle(float angle) {
    return setAngle(getAngle() + angle);
}

float SpaceSensorArm::delAngle(float angle) {
    return setAngle(getAngle() - angle);
}

void SpaceSensorArm::act(int SystemTick) {
    if(CurrentAction != YZF_NULL_PTR){
        if(CurrentAction->act(SystemTick)==YZF_OK){
            delete CurrentAction;
            CurrentAction = YZF_NULL_PTR;
        }
    }
}

void SpaceSensorArm::addAction(SpaceSensorAction *action) {
    if(CurrentAction==YZF_NULL_PTR){
        CurrentAction = action;
        CurrentAction->setArm(this);
    }else{
        delete action;
    }
}

YZF_BOOL SpaceSensorArm::isActionFinish() {
    if(CurrentAction==YZF_NULL_PTR){
        return YZF_TRUE;
    }else{
        return YZF_FALSE;
    }
}

SpaceSensorArm::SpaceSensorArm() {
    this->isRoot =YZF_TRUE;
    this->CurrentAction =YZF_NULL_PTR;
    this->parentArm = YZF_NULL_PTR;
}

float SpaceSensorArm::setLength(float len) {
    return 0;
}

float SpaceSensorArm::getLength() {
    return 0;
}
