//
// Created by 32827 on 2024/2/15.
//

#ifndef YZL_UI_WIDGET_PP_TEXT_HPP
#define YZL_UI_WIDGET_PP_TEXT_HPP
#include "yzl_ui_widget_pp_base.hpp"
#include "yzl_ui_pp_def.hpp"
class WidgetText : public WidgetBase{
private:
    YZF_BOOL show_bar=YZF_FALSE;
    YZ_COLOR text_color=WHITE;
    uint16_t textLen=0;
    ucs2 *text=YZF_NULL_PTR;       //32
    struct FontPixel *fontPixel=YZF_NULL_PTR;
public:
    WidgetText(YZL_WIDGET *Ram, int x,int y, int z, int width, int height, utf8  *text);
    WidgetText(YZL_WIDGET *Ram, int x,int y, int z, int width, int height, utf8  *text,YZ_COLOR textColor);
    WidgetText(YZL_WIDGET *Ram, UI_Rect *rect,int z,utf8  *text);
    WidgetText(YZL_WIDGET *Ram, UI_Rect *rect,int z,utf8  *text,YZ_COLOR textColor);

    ~WidgetText() = default;

    void drawP() override;

    void disposeP() override;

    void setText(utf8 *srcText);
    void clearTextCache();
    void showBar(YZF_BOOL isShow);
    void setTextColor(YZ_COLOR color);
};
#endif //YZL_UI_WIDGET_PP_TEXT_HPP
