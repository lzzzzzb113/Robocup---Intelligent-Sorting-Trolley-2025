//
// Created by 32827 on 2024/2/11.
//

#ifndef YZL_UI_PP_LAYOUT_HPP
#define YZL_UI_PP_LAYOUT_HPP
#include "yzl_ui_pp_def.hpp"
#include "view/yzl_ui_view_pp_base.hpp"

class LayoutBase{
protected:
    ViewBase *view;
    UI_Rect uiRect{};
public:
    LayoutBase(ViewBase *view);
    ~LayoutBase();

    virtual uint16_t getIndex(UI_Rect *rect);
    virtual UI_Rect *nextRect();
    virtual UI_Rect *nextRect(uint16_t width,uint16_t height);
    virtual void delRect(UI_Rect *rect);
    virtual void delRect(uint16_t x,uint16_t y,uint16_t width,uint16_t height);
};
#endif //YZL_UI_PP_LAYOUT_HPP
