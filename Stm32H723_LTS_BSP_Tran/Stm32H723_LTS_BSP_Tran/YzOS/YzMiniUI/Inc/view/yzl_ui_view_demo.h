//
// Created by 32827 on 2024/1/26.
//

#ifndef YZL_UI_VIEW_DEMO_H
#define YZL_UI_VIEW_DEMO_H
#include "yzl_ui.h"
#define VIEW_DEMO_MAX_WIDGET_NUM 10
typedef struct {
    char *logoPath;
    uint8_t softIndex[VIEW_DEMO_MAX_WIDGET_NUM];
}YZL_VIEW_DEMO_INIT;
YZF_RESULT yzl_ui_view_demo_create(YZL_VIEW *viewRam);
#endif //YZGD32_YZL_UI_VIEW_DEMO_H
