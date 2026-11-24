//
// Created by 32827 on 2024/2/11.
//

#ifndef YZL_UI_PP_DEF_HPP
#define YZL_UI_PP_DEF_HPP

#include "yz.h"

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
} UI_Rect;

typedef struct {
    uint16_t x;
    uint16_t y;
} UI_Point;

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint16_t angle;
} UI_RotateRect;

typedef struct {
    void *p_this;//指向ViewBase C++ 对象
} ViewBaseData;//链接C 与 C++ 位于YZL_VIEW.pViewData

typedef struct {
    void *p_this;//指向WidgetBase C++ 对象
} WidgetBaseData;//链接C 与 C++ 位于YZL_WIDGET.Data

///---------- View Define ---------------

#define YZL_UI_VIEW_ID_VIEW_PP_BASE 0
#define YZL_UI_VIEW_ID_VIEW_PP_DEMO 1
#define YZL_UI_VIEW_ID_VIEW_PP_1306_DEMO 2
#define YZL_UI_VIEW_ID_VIEW_PP_NO_LOAD_DEMO 3

#define ACT_VIEW_OBJECT_GET(type,x) ((type *)((ViewBaseData *)(((YZL_ACTIVE_DATA *) x)->handleView->pViewData))->p_this)
#define YZL_UI_WIDGET_PP_PARENT(x) ((ViewBase *)((ViewBaseData *)((YZL_VIEW *)((YZL_WIDGET *)x)->parent)->pViewData)->p_this)
#define YZL_UI_WIDGET_PP(x) ((WidgetBase *)((WidgetBaseData *)x->data)->p_this)
#endif //YZGD32_YZL_UI_PP_DEF_HPP
