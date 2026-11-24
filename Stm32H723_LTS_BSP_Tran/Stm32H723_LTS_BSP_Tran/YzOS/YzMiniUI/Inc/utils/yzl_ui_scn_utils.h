//
// Created by 32827 on 2024/1/27.
//

#ifndef YZL_UI_SCN_UTILS_H
#define YZL_UI_SCN_UTILS_H
#include "yzl_ui.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * 用于备份显存
 * @param x 备份的起始x坐标
 * @param y 备份的起始y坐标
 * @param width 备份的宽度
 * @param height 备份的高度
 * @return 备份的显存指针
 * @notes 记得释放指向备份显存的指针
 * */
YZ_COLOR *yzl_ui_scn_ram_Backup(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

void yzl_ui_scn_ram_Restore(YZ_COLOR *data, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

#ifdef __cplusplus
}
#endif
#endif //YZL_UI_SCN_UTILS_H
