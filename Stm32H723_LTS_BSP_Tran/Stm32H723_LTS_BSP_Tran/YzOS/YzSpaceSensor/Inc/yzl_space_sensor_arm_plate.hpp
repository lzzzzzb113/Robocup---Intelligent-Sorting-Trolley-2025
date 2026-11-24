//
// Created by 32827 on 2025/4/24.
//

#ifndef YZL_SPACE_SENSOR_ARM_PLATE_HPP
#define YZL_SPACE_SENSOR_ARM_PLATE_HPP
#include "yzl_space_sensor_arm.hpp"

#ifdef YZSCREEN
#include "yzl_ui_widget_pp_text.hpp"
#include "yzl_ui_widget_pp_text_button.hpp"

#endif

typedef enum {
    RotateTypeX,
    RotateTypeY,
    RotateTypeZ
} SpaceSensorArmRotateType;

class SpaceSensorArmPlate : public SpaceSensorArm{
public:
    int maxLimit;
    int minLimit;
    int nowParam;
    YZF_TIM_POINTER tim;
    uint16_t ch_id;
    SpaceSensorArmRotateType rotateType;
#ifdef YZSCREEN
    YZF_BOOL hasWidget=YZF_FALSE;
    WidgetTextButton *widgetText;
#endif

    SpaceSensorArmPlate(SpaceSensorArm *parent,YZF_TIM_POINTER tim,uint16_t ch_id,Pose defaultPose,SpaceSensorArmRotateType type,int maxParam,int minParam,int defaultParam,YZF_BOOL isRoot);

    float setAngle(float angle) override;
    float getAngle() override;
    Position getPosition(SpaceSensorArm *ArmEnd) override;

    void addAction(SpaceSensorAction *action) override;

#ifdef YZSCREEN
    void LinkTextUI(WidgetTextButton *pWidgetText);
    void CancelLink();
#endif
};
#endif //YZL_SPACE_SENSOR_ARM_PLATE_HPP
