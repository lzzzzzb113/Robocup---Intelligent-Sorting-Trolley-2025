//
// Created by 32827 on 2024/1/26.
//

#ifndef YZL_UI_LABEL_H
#define YZL_UI_LABEL_H
#include "yzl_ui.h"
typedef struct {
    YZ_COLOR text_color;
    YZ_COLOR back_color;
    YZF_BOOL hasBackground;
    ucs2 *text;
    uint16_t textLen;
    void (*listener)(void *widget, YZL_UI_CTR_EVENT event);
} YZL_LABEL_DATA;
#ifdef __cplusplus
extern "C" {
#endif

void yzl_ui_label_create(YZL_WIDGET *labelRam, int x, int y, int z, int width, int height, YZ_COLOR text_color,
                         YZ_COLOR back_color, const utf8 *text);

#ifdef __cplusplus
}
#endif
#endif //YZL_UI_LABEL_H
