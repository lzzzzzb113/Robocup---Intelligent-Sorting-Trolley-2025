//
// Created by 32827 on 2024/1/20.
//
#include "yzl_ui.h"

YZ_COLOR YZL_UI_Background=YZ_COLOR_Value(0xFFFFFF);
YZF_BOOL YZL_UI_IS_INIT=YZF_FALSE;

YZF_BOOL yzl_ui_point_check(YZL_WIDGET *pWidget,uint16_t x,uint16_t y){
    if(pWidget->x <= x && x <= pWidget->x + pWidget->width && pWidget->y <= y && y <= pWidget->y + pWidget->height){
        return YZF_TRUE;
    }else{
        return YZF_FALSE;
    }
}
//TODO: 完善图片缓存机制
uint8_t imgTemp[YZL_UI_IMG_TEMP];
FIL imgFile;
YZF_BOOL yzl_ui_draw_img(char *path,uint16_t x,uint16_t y,uint16_t width,uint16_t height){
    FRESULT retSD = f_open(&imgFile,(const char*)path,FA_READ|FA_OPEN_EXISTING);
    if(retSD!=FR_OK){
        yz_error("File Open Error: %d\n",retSD);
    }else{
        yz_info("Name %s Picture Size:%d KB\n",path,f_size(&imgFile)/1024);
        for(uint16_t i=0;i<height;i++) {
            UINT f_size = 0;
            retSD = f_read(&imgFile, (void *) imgTemp, width*2, &f_size);//读一行
            imgTemp[f_size] = 0;
            if (retSD != FR_OK) {
                yz_error("File Read Error: %d\n", retSD);
                break;
            } else {
                yzl_ui_draw_pixels(x, y + i, width, 1, (YZ_COLOR *) imgTemp);
            }
        }
    }
    f_close(&imgFile);
    return YZF_TRUE;
}
YZ_IMAGE_565A_Header image565AHeader;
YZF_BOOL yzl_ui_draw_565a(char *path,uint16_t x,uint16_t y,uint16_t mask_x,uint16_t mask_y,uint16_t mask_width,uint16_t mask_height){
    FRESULT retSD = f_open(&imgFile,(const char*)path,FA_READ|FA_OPEN_EXISTING);
    if(retSD!=FR_OK){
        yz_error("File Open Error: %d\n",retSD);
    }else{
        retSD=f_read(&imgFile, (void *) &image565AHeader, 10, NULL);
        if (retSD != FR_OK) {
            yz_error("File Read Error: %d\n", retSD);
        } else {
            FSIZE_t tempSeek=f_tell(&imgFile);
            UINT f_size = 0;
            uint16_t dest_height=(mask_height+mask_y)>image565AHeader.height?image565AHeader.height:(mask_height+mask_y);
            for(uint32_t i=mask_y;i<dest_height;i++){
                f_lseek(&imgFile,tempSeek+(i*image565AHeader.width*2)+mask_x*2);
                retSD = f_read(&imgFile, (void *) imgTemp, (mask_width)*2, &f_size);//读一行
                if (retSD != FR_OK) {
                    yz_error("File Read Error: %d\n", retSD);
                    break;
                } else {
                    yzl_ui_draw_pixels_ex(x+mask_x,y + i, image565AHeader.width<mask_width?image565AHeader.width:mask_width, 1, (YZ_COLOR *) imgTemp,*((YZ_COLOR *)&image565AHeader.alphaColor));
                }
            }
        }
    }
    return YZF_TRUE;
}

YZF_RESULT yzl_ui_draw_string(uint16_t x,uint16_t y,uint16_t limitX,uint16_t *str,uint16_t len,YZ_COLOR back_color,YZ_COLOR text_color){
    if(Yz_FontInitFlag!=YZF_TRUE){
        return YZF_ERROR;
    }
    uint16_t startX=x,startY=y;
    uint32_t offx,offy;
    int tempLen=len;
    uint16_t wlen = 0;
    while (len!=0) {
        if(len>YZL_FONT_SRAM_SIZE){
            wlen=YZL_FONT_SRAM_SIZE;
            len-=YZL_FONT_SRAM_SIZE;
        }else{
            wlen=len;
            len=0;
        }
        if (yzl_font_get_pixels(&str[tempLen-len-wlen], yzl_font_sram, wlen) == YZF_OK) {
            for (int m = 0; m < wlen; m++) {
                if(str[tempLen-len-wlen+m]=='\000'){
                    continue;
                }else
                if(str[tempLen-len-wlen+m]=='\r'){
                    startX=0;
                    continue;
                }else
                if(str[tempLen-len-wlen+m]=='\n'){
                    startY+=YZL_FONT_LINE_HEIGHT;
                    startX=x;
                    continue;
                }

                if (startX + yzl_font_sram[m].xOffset < 0 || (startY + yzl_font_sram[m].yOffset) < 0) {
                    offx=startX;
                    offy=startY;
                } else {
                    offx=startX+yzl_font_sram[m].xOffset;
                    offy=startY+yzl_font_sram[m].yOffset;
                }
                int count = 0;
                int pixelIndex = 0;
                for (int i = 0; i < yzl_font_sram[m].height; i++) {
                    for (int j = 0; j < yzl_font_sram[m].width; j++) {
                        if (count >= 8) {
                            pixelIndex++;
                            count = 0;
                        }
                        if ((yzl_font_sram[m].pixel[pixelIndex] & (0b1 << (7 - count))) != 0) {
                            yzl_ui_draw_pixel(offx + j, offy + i, text_color);
                        } else {
//                            yzl_ui_draw_pixel(offx + j, offy + i, back_color);
                        }
                        count++;
                    }
                }

                startX = startX + yzl_font_sram[m].xAdvance;

                if (startX + YZL_FONT_SIZE > limitX) {
                    startY+=YZL_FONT_LINE_HEIGHT;
                    startX=x;
                }
            }
        } else {
            return YZF_ERROR;
        }
    }
    return YZF_OK;
}