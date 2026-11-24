//
// Created by 32827 on 2025/5/2.
//

#ifndef YZL_SPACE_SENSOR_ACTION_LENGTH_HPP
#define YZL_SPACE_SENSOR_ACTION_LENGTH_HPP
#include "yzl_space_sensor_action.hpp"
#include "yzl_space_sensor_arm_pole.hpp"

class SpaceSensorActionLength : public SpaceSensorAction{
public:
    int TickStart;
    int TickLength;
    float FromLength;
    float ToLength;
    SpaceSensorArmPole *arm;

    SpaceSensorActionLength(int TickStart,int TickLength,float FromLength,float ToLength);

    YZF_RESULT act(int SystemTick) override;

    ActionType getType() override;

    void setArm(void *pArm) override;
};

#endif //YZL_SPACE_SENSOR_ACTION_LENGTH_HPP
