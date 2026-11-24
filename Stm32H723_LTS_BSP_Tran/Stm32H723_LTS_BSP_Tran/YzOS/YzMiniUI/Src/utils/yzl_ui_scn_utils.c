//
// Created by 32827 on 2024/1/27.
//
#include "utils/yzl_ui_scn_utils.h"
#include "yzl.h"
YZ_COLOR* yzl_ui_scn_ram_Backup(uint16_t x,uint16_t y,uint16_t width,uint16_t height){
    YZ_COLOR *pBackAddress=YZL_MEM_MANAGER.pMalloc(width*height*sizeof(YZ_COLOR));
    for(uint16_t i=0;i<height;i++){
        yzl_ui_get_pixels_line(x,y+i,width,((YZ_COLOR *)pBackAddress)+i*width);
    }
    return pBackAddress;
}
void yzl_ui_scn_ram_Restore(YZ_COLOR* data,uint16_t x,uint16_t y,uint16_t width,uint16_t height){
    yzl_ui_draw_pixels(x,y,width,height,data);
}