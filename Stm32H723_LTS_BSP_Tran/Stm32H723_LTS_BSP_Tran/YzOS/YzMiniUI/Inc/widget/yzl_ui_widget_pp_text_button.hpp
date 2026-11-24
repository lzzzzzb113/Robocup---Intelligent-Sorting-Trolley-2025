//
// Created by 32827 on 2024/2/1.
//

#ifndef YZGD32_YZL_UI_WIDGET_PP_BUTTON_HPP
#define YZGD32_YZL_UI_WIDGET_PP_BUTTON_HPP
#include "yzl_ui_widget_pp_base.hpp"
#include "yzl_ui_pp_def.hpp"
class WidgetTextButton : public WidgetBase {
private:
    YZ_COLOR up_color;
    YZ_COLOR down_color;    //32
    YZ_COLOR text_color;
    uint16_t textLen;
    ucs2 *text;       //32
    void (*listener)(void *widget, YZL_UI_CTR_EVENT event); //32
    struct FontPixel *fontPixel;
public:
    WidgetTextButton(YZL_WIDGET *Ram, int x,int y, int z, int width, int height, utf8  *text);
    WidgetTextButton(YZL_WIDGET *Ram, UI_Rect *rect, int z, utf8  *text);
    ~WidgetTextButton();

    void drawP() override;

    YZF_BOOL touchP(uint16_t x, uint16_t y, YZL_UI_CTR_EVENT event) override;

    void disposeP() override;

    void setListener(void (*listener)(void *widget, YZL_UI_CTR_EVENT event));

    void setText(utf8 *srcText);

    void setTextF(utf8 *format, ...);

    void setTextColor(YZ_COLOR color);

    static void default_listener(void *widget,YZL_UI_CTR_EVENT event);
};
#endif //YZGD32_YZL_UI_WIDGET_PP_BUTTON_HPP
