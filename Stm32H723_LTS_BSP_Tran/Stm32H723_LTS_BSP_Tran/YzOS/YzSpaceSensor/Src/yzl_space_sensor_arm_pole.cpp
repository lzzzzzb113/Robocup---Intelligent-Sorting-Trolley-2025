//
// Created by 32827 on 2025/4/25.
//

#include "yzl_space_sensor_arm_pole.hpp"
#include "yz_tim.h"
SpaceSensorArmPole::SpaceSensorArmPole(YZL_GPIO Dir, SpaceSensorArm *parent, YZF_TIM_POINTER tim, uint16_t ch_id,
                                       YZF_TIM_POINTER timCount,Pose defaultPose, float maxParam,
                                       float minParam,float defaultParam,YZF_BOOL isRoot)  {
    parentArm = parent;
    ArmPose = defaultPose;
    this->tim = tim;
    this->ch_id = ch_id;
    minLimit = minParam;
    maxLimit = maxParam;
    nowParam = defaultParam;
    this->isRoot = isRoot;
    this->Dir = Dir;
    this->isBack = YZF_FALSE;
    this->timCount = timCount;
    this->hasWidget = YZF_FALSE;
}

Position SpaceSensorArmPole::getPosition(SpaceSensorArm *ArmEnd) {

    //TODO: 实现位置计算
    return SpaceSensorArm::getPosition(ArmEnd);
}

float SpaceSensorArmPole::setLength(float len) {
    if(len>maxLimit) len = maxLimit;
    if(len<minLimit) len = minLimit;
    float param = (len-nowParam) * (float) scale;
    if(param>0){
        yzf_gpio_set_1(Dir.port,Dir.pin);
    }else{
        yzf_gpio_set_0(Dir.port,Dir.pin);
    }
#if YZSCREEN
    if(hasWidget){
        widgetText->setTextF((utf8 *)"%.3f",param);
    }
#endif

    int w=(int) roundf((((float )coreSpeed)/speed));
    if(w>65535){
        w=65535;
    }
    if(w<1){
        w=1;
    }
    yz_tim_pwm_data_set(tim,ch_id,w/2,w-1);

    if(yz_tim_pwm_with_count_fast(tim,ch_id,timCount,(uint32_t)param)==YZF_ERROR){
        return nowParam;
    }
    nowParam = nowParam + param/(float)scale;
    return len;
}

float SpaceSensorArmPole::getLength() {
    return nowParam;
}

YZF_BOOL SpaceSensorArmPole::isFinish() {
    return yz_tim_pwm_with_count_is_finish(timCount);
}

void SpaceSensorArmPole::addLength(float len) {
    setLength(getLength()+len);
}

void SpaceSensorArmPole::delLength(float len) {
    setLength(getLength()-len);
}

#ifdef YZSCREEN
void SpaceSensorArmPole::LinkTextUI(WidgetTextButton *pWidgetText) {
    this->widgetText = pWidgetText;
    hasWidget = YZF_TRUE;
    widgetText->setTextF((utf8 *)"%.3f",getLength());
}

void SpaceSensorArmPole::CancelLink() {
    hasWidget = YZF_FALSE;
}
#endif
void SpaceSensorArmPole::BackPoint() {
    this->isBack = YZF_TRUE;
    if(this->isBack){
        yzf_gpio_set_0(Dir.port,Dir.pin);
        int w=(int) roundf((((float )coreSpeed)/speed));
        if(w>65535){
            w=65535;
        }
        if(w<1){
            w=1;
        }
        yz_tim_pwm_data_set(tim,ch_id,w/2,w-1);
        yz_tim_pwm_enable_ch(tim,ch_id);
    }
}

void SpaceSensorArmPole::CallBackPoint() {
    if(this->isBack){
        yz_tim_pwm_disable_ch(tim,ch_id);
        this->isBack = YZF_FALSE;
    }
    nowParam = 0;
}

float SpaceSensorArmPole::getSpeed() {
    return this->speed;
}

void SpaceSensorArmPole::setSpeed(float speed) {
    if(speed<0){
        this->speed = -speed;
    }else if(speed==0){
        this->speed = 1;
    }else{
        this->speed = speed;
    }
}

SpaceSensorArmPole::SpaceSensorArmPole(SpaceSensorArmPolePortParam *param, Pose defaultPose, SpaceSensorArm *parent,
                                       YZF_BOOL isRoot) {
    this->parentArm = parent;
    this->ArmPose = defaultPose;
    this->isRoot = isRoot;

    this->tim = param->pwm_gen_tim;
    this->ch_id = param->ch_id;
    this->minLimit = param->minLimit;
    this->maxLimit = param->maxLimit;
    this->nowParam = param->nowParam;
    this->Dir = param->Dir;
    this->timCount = param->pwm_count_tim;
    this->coreSpeed = param->coreSpeed;
    this->scale = param->scale;
    setSpeed(param->speed);

    YLGPIO(param->Dir)
    yzf_gpio_open_clock_();
    yzf_gpio_set_PP_();
    yzf_gpio_set_Pull_Up_();
    yzf_gpio_set_HIGH_();

    this->isBack = YZF_FALSE;
    this->hasWidget = YZF_FALSE;
}
