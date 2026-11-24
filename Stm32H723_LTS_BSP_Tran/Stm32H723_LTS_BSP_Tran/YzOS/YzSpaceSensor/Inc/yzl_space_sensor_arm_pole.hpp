//
// Created by 32827 on 2025/4/25.
//

#ifndef YZL_SPACE_SENSOR_ARM_POLE_HPP
#define YZL_SPACE_SENSOR_ARM_POLE_HPP
#include "yzl_space_sensor_arm.hpp"
#include "yzl_softport.h"

#ifdef YZSCREEN
#include "yzl_ui_widget_pp_text_button.hpp"
#endif


typedef struct {
    YZL_GPIO Dir;
    YZF_TIM_POINTER pwm_gen_tim;
    uint16_t ch_id;
    YZF_TIM_POINTER pwm_count_tim;
    float  maxLimit;
    float  minLimit;
    float  nowParam;

    float speed;
    int coreSpeed;
    int scale;
} SpaceSensorArmPolePortParam;

class SpaceSensorArmPole : public SpaceSensorArm{
public:
    int scale = 1000;
    float maxLimit;
    float minLimit;
    float nowParam;
    float speed= 2000;//Hz
    int coreSpeed=1000000;//1Mhz计时器
    YZF_TIM_POINTER tim;
    YZF_TIM_POINTER timCount;
    uint16_t ch_id;
    YZL_GPIO Dir;

#ifdef YZSCREEN
    YZF_BOOL hasWidget=YZF_FALSE;
    WidgetTextButton *widgetText;
#endif
    SpaceSensorArmPole(YZL_GPIO  Dir,SpaceSensorArm *parent,YZF_TIM_POINTER tim,uint16_t ch_id,YZF_TIM_POINTER timCount,Pose defaultPose,float maxParam,float minParam,float defaultParam,YZF_BOOL isRoot);
    SpaceSensorArmPole(SpaceSensorArmPolePortParam *param,Pose defaultPose,SpaceSensorArm *parent,YZF_BOOL isRoot);

    /**
     * @brief 每次运动时需判断是否处于等待状态，同一个PwmCountTim下的所有都要判断
     * */
    YZF_BOOL isFinish();

    float setLength(float len) override;

    float getLength() override;

    Position getPosition(SpaceSensorArm *ArmEnd) override;

    void addLength(float len);

    void delLength(float len);

    float getSpeed();

    void setSpeed(float speed);

    /**
     * @brief 是否处于复位运动中
     * */
    YZF_BOOL isBack;

    /**
     * @brief 开始复位到原点
     * */
    void BackPoint();

    /**
     * @brief 须在中断中调用表示已经复位到原点,停止运动
     * */
    void CallBackPoint();

#ifdef YZSCREEN
    void LinkTextUI(WidgetTextButton *pWidgetText);
    void CancelLink();
#endif
};
#endif //YZL_SPACE_SENSOR_ARM_POLE_HPP
