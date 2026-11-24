//
// Created by 32827 on 2025/4/27.
//

#ifndef YZL_SPACE_SENSOR_ARM_ANGAL_HPP
#define YZL_SPACE_SENSOR_ARM_ANGAL_HPP

#include "yzl_space_sensor_action.hpp"
#include "yzl_space_sensor_arm_plate.hpp"

class SpaceSensorActionAngle : public SpaceSensorAction{
public:
    int TickStart;
    int TickLength;
    float FromAngle;
    float ToAngle;
    SpaceSensorArm *arm;

    SpaceSensorActionAngle(int TickStart,int TickLength,float FromAngle,float ToAngle);

    YZF_RESULT act(int SystemTick) override;

    ActionType getType() override;

    void setArm(void *pArm) override;
};
#endif //YZL_SPACE_SENSOR_ARM_ANGAL_HPP
