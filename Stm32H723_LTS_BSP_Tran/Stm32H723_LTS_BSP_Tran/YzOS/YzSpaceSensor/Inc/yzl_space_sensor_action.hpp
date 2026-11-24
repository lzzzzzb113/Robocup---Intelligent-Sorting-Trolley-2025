//
// Created by 32827 on 2025/4/27.
//

#ifndef YZL_SPACE_SENSOR_ACTION_HPP
#define YZL_SPACE_SENSOR_ACTION_HPP
#include "yzx_base.h"
#include "yzl_transform_segment.h"
typedef enum {
    BASE_ACTION = 0,
    ACTION_TYPE_ANGLE,
    ACTION_TYPE_POSITION,
} ActionType;

class SpaceSensorAction{
public:
    SpaceSensorAction()=default;
    virtual ~SpaceSensorAction()=default;

    virtual YZF_RESULT act(int SystemTick);
    virtual ActionType getType();
    virtual void setArm(void *pArm);
};

#endif //YZL_SPACE_SENSOR_ACTION_HPP
