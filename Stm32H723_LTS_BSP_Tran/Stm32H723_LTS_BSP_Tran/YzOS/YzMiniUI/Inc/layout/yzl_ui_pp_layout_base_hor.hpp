//
// Created by 32827 on 2024/7/11.
//

#ifndef YZL_UI_PP_LAYOUT_BASE_HOR_HPP
#define YZL_UI_PP_LAYOUT_BASE_HOR_HPP
#include "yzl_ui_pp_layout.hpp"
#include "yzl.h"

class LayoutHorizontal : public LayoutBase {
private:
    UI_Rect range;
    uint16_t count;
    uint16_t margin=0;
    YZF_BOOL *rect_flag=NULL_PTR;//是否使用
    uint16_t *rect_weight=NULL_PTR;//宽度
public:
    LayoutHorizontal(ViewBase *view);
    ~LayoutHorizontal();
    void setRange(uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint16_t pCount);
    void setMargin(uint16_t m);
    void setWeight(uint16_t index,uint16_t weight);

    uint16_t getIndex(UI_Rect *rect) override;

    UI_Rect *nextRect() override;

    void delRect(UI_Rect *rect) override;

    void delRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height) override;
};
#endif //YZL_UI_PP_LAYOUT_BASE_HOR_HPP
