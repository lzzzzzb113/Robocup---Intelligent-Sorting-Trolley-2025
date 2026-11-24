//
// Created by 32827 on 2025/4/24.
//

#ifndef YZL_SPACE_SENSOR_ARM_HPP
#define YZL_SPACE_SENSOR_ARM_HPP
#include "yzl_space_sensor_pose.hpp"
#include "yzl_space_sensor_action.hpp"

class SpaceSensorArm{
public:
    YZF_BOOL isRoot;
    SpaceSensorArm *parentArm;
    Pose ArmPose;
    Pose ArmPoseBack;
    SpaceSensorAction *CurrentAction;
    SpaceSensorArm();
    virtual ~SpaceSensorArm() = default;

    float addAngle(float angle);
    float delAngle(float angle);
    void act(int SystemTick);

    YZF_BOOL isActionFinish();
    virtual void addAction(SpaceSensorAction *action);
    virtual float setAngle(float angle);
    virtual float getAngle();
    virtual float setLength(float len);
    virtual float getLength();
    virtual Position getPosition(SpaceSensorArm *ArmEnd);
};

#endif //YZL_SPACE_SENSOR_ARM_HPP
