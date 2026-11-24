//
// Created by 32827 on 2024/3/3.
//

#ifndef YZGD32_YZL_UI_WIDGET_PP_PROGRESS_HPP
#define YZGD32_YZL_UI_WIDGET_PP_PROGRESS_HPP
#include "yzl_ui_widget_pp_base.hpp"
#include "yzl_ui_pp_def.hpp"
/**
 * 进度条控件 <br/>
 * @link 可控制 WidgetProgressTouch
 * */
class WidgetProgress : public WidgetBase {
public:
    int32_t maxValue;
    int32_t value;
    uint16_t border=0;
    Yz_Color barColor=BLACK;
    Yz_Color backgroundColor=RED;
    WidgetProgress(YZL_WIDGET *Ram,int x, int y,int z, int width, int height,Yz_Color barColor,Yz_Color backgroundColor,int32_t border,int32_t maxValue,int32_t value);
    WidgetProgress(YZL_WIDGET *Ram, UI_Rect *rect,int z,Yz_Color barColor,Yz_Color backgroundColor,int32_t border,int32_t maxValue,int32_t value);
    ~WidgetProgress() = default;

    void drawP() override;

    void setValue(int32_t value);
    int32_t getValue();
};
#endif //YZGD32_YZL_UI_WIDGET_PP_PROGRESS_HPP
