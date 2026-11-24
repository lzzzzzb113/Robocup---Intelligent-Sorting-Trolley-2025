//
// Created by 32827 on 2024/2/11.
//

#ifndef YZL_UI_PP_LAYOUT_BASE_VER_HPP
#define YZL_UI_PP_LAYOUT_BASE_VER_HPP
#include "yzl_ui_pp_layout.hpp"
#include "yzl.h"

/**
 * 本布局管理只提供布局建议设置，如果控件自行修改设置，则可能出现错误，需要注意。<br>
 * 如使用WidgetText需在下部至少有Text Height的要求，不然会出现控件错位。
 * */
class LayoutVertical:public LayoutBase{
private:
    UI_Rect range;
    uint16_t count;
    uint16_t margin=0;
    YZF_BOOL *rect_flag=NULL_PTR;//是否使用
public:
    LayoutVertical(ViewBase *view);
    ~LayoutVertical();
    void setRange(uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint16_t pCount);
    void setMargin(uint16_t m);

    UI_Rect *nextRect() override;

    UI_Rect *nextRect(uint16_t width, uint16_t height) override;

    void delRect(UI_Rect *rect) override;

    void delRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height) override;

    uint16_t getIndex(UI_Rect *rect) override;
};
#endif //YZL_UI_PP_LAYOUT_BASE_VER_HPP
