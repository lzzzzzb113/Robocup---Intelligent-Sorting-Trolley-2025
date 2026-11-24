//
// Created by 32827 on 2024/1/27.
//

#ifndef YZ_UI_DIALOG_H
#define YZ_UI_DIALOG_H
#include "yzl_ui.h"
typedef struct {
    YZ_COLOR text_color;
    YZ_COLOR back_color;
    uint16_t textLen;
    ucs2 *text;
    struct FontPixel *fontPixel;
    void (*listener)(void *widget, YZL_UI_CTR_EVENT event);
    YZ_COLOR *recover;  //保存显存的内容
} YZL_DIALOG_DATA;
#ifdef __cplusplus
extern "C" {
#endif

void yzl_ui_dialog_create(YZL_WIDGET *dialogRam, int x, int y, int z, int width, int height, YZ_COLOR text_color,
                          YZ_COLOR back_color, const utf8 *text);

void yzl_ui_dialog_set_listener(YZL_WIDGET *dialogRam, void (*listener)(void *widget, YZL_UI_CTR_EVENT event));

#ifdef __cplusplus
}
#endif
#endif //YZ_UI_DIALOG_H