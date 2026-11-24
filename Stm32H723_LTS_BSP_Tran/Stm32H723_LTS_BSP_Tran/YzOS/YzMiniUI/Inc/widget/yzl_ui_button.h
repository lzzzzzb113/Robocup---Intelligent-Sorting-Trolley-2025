//
// Created by 32827 on 2024/1/11.
//

#ifndef YZL_UI_BUTTON_H
#define YZL_UI_BUTTON_H
#include "yzl_ui.h"
enum YZL_BUTTON_EVENT{
    YZL_BUTTON_PRESS,
    YZL_BUTTON_UN_PRESS
};
typedef struct{
    YZ_COLOR up_color;
    YZ_COLOR down_color;    //32
    YZ_COLOR text_color;
    uint16_t textLen;
    ucs2 *text;       //32
    void (*listener)(void *widget, enum YZL_BUTTON_EVENT event); //32
} YZL_BUTTON_DATA;

YZ_CHECK_SIZE_OVER(YZL_BUTTON_DATA,YZL_UI_WIDGET_DATA_SRAM_SIZE);   //检查数据大小是否超出

#define YZL_BUTTON_DATA_VALUE(widget)  ((YZL_BUTTON_DATA *)(&((YZL_WIDGET *)widget)->data))

#ifdef __cplusplus
extern "C" {
#endif

void yzl_ui_button_create(YZL_WIDGET *ButtonRam, int x, int y, int z, int width, int height, YZ_COLOR up, YZ_COLOR down,
                          YZ_COLOR text_color, const utf8 *text);

void yzl_ui_button_set_listener(void *widget, void (*p)(void *widget, enum YZL_BUTTON_EVENT event));

#ifdef __cplusplus
}
#endif
#endif //YZL_UI_BUTTON_H
