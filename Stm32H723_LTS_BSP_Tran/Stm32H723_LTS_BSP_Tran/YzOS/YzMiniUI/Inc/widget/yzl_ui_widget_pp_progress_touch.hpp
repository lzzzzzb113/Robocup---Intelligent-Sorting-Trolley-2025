//
// Created by 32827 on 2024/3/3.
//

#ifndef YZGD32_YZL_UI_WIDGET_PP_PROGRESS_TOUCH_HPP
#define YZGD32_YZL_UI_WIDGET_PP_PROGRESS_TOUCH_HPP
#include "yzl_ui_widget_pp_progress.hpp"

class WidgetProgressTouch : public WidgetProgress {
protected:
    YZL_TouchPoint UpPoint;
    YZL_TouchPoint DownPoint;
public:
    void (*listener)(void *widget, YZL_UI_CTR_EVENT event)=YZF_NULL_PTR; //32
    WidgetProgressTouch(YZL_WIDGET *Ram,int x, int y,int z, int width, int height,Yz_Color barColor,Yz_Color backgroundColor,int32_t border,int32_t maxValue,int32_t value);
    WidgetProgressTouch(YZL_WIDGET *Ram, UI_Rect *rect,int z,Yz_Color barColor,Yz_Color backgroundColor,int32_t border,int32_t maxValue,int32_t value);
    YZF_BOOL touchP(uint16_t x, uint16_t y, YZL_UI_CTR_EVENT event) override;
};
#endif //YZGD32_YZL_UI_WIDGET_PP_PROGRESS_TOUCH_HPP
