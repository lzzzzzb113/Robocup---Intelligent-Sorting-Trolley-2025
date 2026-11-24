//
// Created by 32827 on 2024/1/9.
//
#include "yzl_font.h"
#include "yzl_iconv.h"

#if USE_FONT

struct FontSoftIndex SoftIndex[YZL_FONT_SOFT_INDEX_NUMBER];
struct FontIndexConvert IndexConvert[YZL_FONT_INDEX_NUMBER];
struct FontPixel yzl_font_sram[YZL_FONT_SRAM_SIZE];

const char *FontDir;
YZF_BOOL Yz_FontInitFlag=YZF_FALSE;
FIL SDFile_SoftIndex;
FIL SDFile_Index;
FIL SDFile_Pixel;
FRESULT retSD;

YZF_RESULT yzl_font_file_Index_init(){
    retSD = f_open(&SDFile_Index,yzl_str_format("%s%s/FontIndex.bin",YZL_FONT_FF_DRIVER,FontDir),FA_READ | FA_OPEN_EXISTING);
    if(retSD!=FR_OK){
        yz_info("FontIndex.bin open failed.Code: %d\n",retSD);
        return YZF_ERROR;
    }
    //Open FontIndex
    return YZF_OK;
}
YZF_RESULT yzl_font_file_Pixel_init(){
    retSD = f_open(&SDFile_Pixel,yzl_str_format("%s%s/FontPixel.bin",YZL_FONT_FF_DRIVER,FontDir),FA_READ | FA_OPEN_EXISTING);
    if (retSD!=FR_OK){
        yz_info("FontPixel.bin open failed.Code: %d\n",retSD);
        return YZF_ERROR;
    }
    //Open FontPixel
    return YZF_OK;
}
YZF_RESULT yzl_font_init(const char *fontDir){
    //Init SoftIndex
    retSD = f_open(&SDFile_SoftIndex,yzl_str_format("%s%s/FontSoftIndex.bin",YZL_FONT_FF_DRIVER,fontDir),FA_READ | FA_OPEN_EXISTING);
    if(retSD!=FR_OK){
        yz_info("FontSoftIndex.bin open failed.Code: %d\n",retSD);
        return YZF_ERROR;
    }

    UINT readByte;
    retSD = f_read(&SDFile_SoftIndex,SoftIndex,sizeof(SoftIndex)*(YZL_FONT_SOFT_INDEX_NUMBER-1),&readByte);   //最后一位人为设置为0xFFFF
    if(retSD!=FR_OK){
        yz_info("FontSoftIndex.bin read failed.Code: %d\n",retSD);
        f_close(&SDFile_SoftIndex);
        return YZF_ERROR;
    }
    f_close(&SDFile_SoftIndex);

    FontDir=fontDir;

    SoftIndex[YZL_FONT_SOFT_INDEX_NUMBER-1].page_start_char_id=0xFFFF;    //设置末尾
    //END Init SoftIndex

    yzl_font_file_Index_init();

    yzl_font_file_Pixel_init();

    Yz_FontInitFlag=YZF_TRUE;
    return YZF_OK;
}

YZF_RESULT yzl_font_get_fnt_id(uint16_t char_id,uint16_t *fnt_id){
    uint16_t find_char_page=0;
    for(int i=0;i<(YZL_FONT_SOFT_INDEX_NUMBER-1);i++){
        if(SoftIndex[i].page_start_char_id<=char_id&&SoftIndex[i+1].page_start_char_id>char_id){
            find_char_page=i;
            break;
        }
    }


    UINT readByte;
    retSD = f_lseek(&SDFile_Index,YZL_FONT_INDEX_PAGE_SIZE*find_char_page);
    retSD = f_read(&SDFile_Index,&IndexConvert,YZL_FONT_INDEX_PAGE_SIZE,&readByte);
    if(retSD!=FR_OK){
        yz_info("FontIndex.bin read failed.Code: %d\n",retSD);
        return YZF_ERROR;
    }

    //获取fnt_id
    *fnt_id=0;
    for(int i=0;i<YZL_FONT_INDEX_NUMBER;i++){
        if(IndexConvert[i].char_id==char_id){
            *fnt_id=IndexConvert[i].fnt_id;
            return YZF_OK;
        }
    }
    return YZF_NOT_FOUND;
}
YZF_RESULT yzl_font_get_fnt_ids(uint16_t *char_id,uint16_t *fnt_id,uint16_t size){
    uint16_t find_char_page[size];
    for(int j=0;j<size;j++){
        for(int i=0;i<(YZL_FONT_SOFT_INDEX_NUMBER-1);i++){
            if(SoftIndex[i].page_start_char_id<=char_id[j]&&SoftIndex[i+1].page_start_char_id>char_id[j]){
                find_char_page[j]=i;
                break;
            }
        }
    }

    DWORD temp=0;
    for(int j=0;j<size;j++) {
        UINT readByte;
        if(temp!=YZL_FONT_INDEX_PAGE_SIZE * find_char_page[j]||temp==0){
            retSD = f_lseek(&SDFile_Index, YZL_FONT_INDEX_PAGE_SIZE * find_char_page[j]);
            if(retSD != FR_OK){
                if(retSD==FR_INVALID_OBJECT){
                    f_close(&SDFile_Index);
                    yzl_font_file_Index_init();
                }else{
                    yz_info("FontIndex.bin seek failed.Code: %d\n", retSD);
                    return YZF_ERROR;
                }
            }
            temp=YZL_FONT_INDEX_PAGE_SIZE * find_char_page[j];
            retSD = f_read(&SDFile_Index, &IndexConvert, YZL_FONT_INDEX_PAGE_SIZE, &readByte);
            if (retSD != FR_OK) {
                yz_info("FontIndex.bin read failed.Code: %d\n", retSD);
                return YZF_ERROR;
            }
        }
        //获取fnt_id
        fnt_id[j] = 0;
        for (int i = 0; i < YZL_FONT_INDEX_NUMBER; i++) {
            if (IndexConvert[i].char_id == char_id[j]) {
                fnt_id[j] = IndexConvert[i].fnt_id;
            }
        }
    }
    return YZF_OK;
}

YZF_RESULT yzl_font_get_pixel(uint16_t char_id,struct FontPixel *pixel){
    uint16_t fnt_id;
    YZF_RESULT re=yzl_font_get_fnt_id(char_id,&fnt_id);

    if(re!=YZF_OK){
        return re;
    }

    DWORD address=fnt_id*sizeof (struct FontPixel);

    f_lseek(&SDFile_Pixel,address);
    UINT readByte;
    retSD = f_read(&SDFile_Pixel,pixel,sizeof(struct FontPixel),&readByte);
    if (retSD != FR_OK) {
        yz_info("FontPixel.bin read failed.Code: %d\n", retSD);
        return YZF_ERROR;
    }

    return YZF_OK;
}
YZF_RESULT yzl_font_get_pixels(uint16_t *char_id,struct FontPixel *pixel,uint16_t size){
    uint16_t fnt_id[size];

    YZF_RESULT re=yzl_font_get_fnt_ids(char_id,fnt_id,size);
    if(re!=YZF_OK){
        return re;
    }
    for(int j=0;j<size;j++){
        DWORD address=fnt_id[j]*sizeof (struct FontPixel);

        retSD = f_lseek(&SDFile_Pixel,address);
        if (retSD != FR_OK) {
            yz_info("FontPixel.bin seek failed.Code: %d\n", retSD);
            return YZF_ERROR;
        }
        UINT readByte;
        retSD = f_read(&SDFile_Pixel,&pixel[j],sizeof(struct FontPixel),&readByte);
        if (retSD != FR_OK) {
            yz_info("FontPixel.bin read failed.Code: %d\n", retSD);
            return YZF_ERROR;
        }
    }
    return YZF_OK;
}

#endif