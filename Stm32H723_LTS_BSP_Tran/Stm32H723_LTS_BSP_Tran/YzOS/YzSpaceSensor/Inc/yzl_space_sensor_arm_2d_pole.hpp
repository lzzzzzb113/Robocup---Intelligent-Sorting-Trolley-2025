//
// Created by 32827 on 2025/7/26.
//

#ifndef STM32H723_LTS_BSP_YZL_SPACE_SENSOR_ARM_2D_POLE_HPP
#define STM32H723_LTS_BSP_YZL_SPACE_SENSOR_ARM_2D_POLE_HPP


#include "yzl_space_sensor_arm.hpp"
#include "yzl_space_sensor_arm_pole.hpp"
#include "yzl_space_sensor_wall.hpp"

class SpaceSensorArmPole2D : public SpaceSensorArm {
public:
    SpaceSensorArmPole *armV=YZF_NULL_PTR;
    SpaceSensorArmPole *armH=YZF_NULL_PTR;
    Pose *defaultPose;
    Position *pos;
    Wall *wall;
    float angle;
    float speed=2000;
    float unitAngle=1.8;//步进角度
    float preDiv=256;

    explicit SpaceSensorArmPole2D(Wall *wall);
    ~SpaceSensorArmPole2D() override;

    void setVerArm(YZL_GPIO  Dir,YZF_TIM_POINTER tim,uint16_t ch_id,YZF_TIM_POINTER timCount);
    void setHorArm(YZL_GPIO  Dir,YZF_TIM_POINTER tim,uint16_t ch_id,YZF_TIM_POINTER timCount);

    //移动方向
    float setAngle(float angle) override;
    void setSpeed(float speed);
    float getSpeed();
    float getAngle() override;
    void addLength(float length);
    void addVLength(float length);
    void addHLength(float length);
    void move(float x,float y);

    void setUnitAngle(float angle);
    void setPreDiv(float preDiv);
    void moveWall(float x,float y);

    YZF_BOOL isFinish();
};


#endif //STM32H723_LTS_BSP_YZL_SPACE_SENSOR_ARM_2D_POLE_HPP
