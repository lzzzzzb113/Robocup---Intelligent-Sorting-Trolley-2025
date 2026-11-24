//
// Created by 32827 on 2024/11/19.
//

#ifndef YZF_BASIC_RAM_H
#define YZF_BASIC_RAM_H

//YzApplication Ram
#define YZ_APPLICATION_TRANSMIT_BUF_SIZE 256  //u8 1

//YzBase Ram
#define YZ_BASE_PROGRAM_STATUS_SHEET_SIZE 64  //sizeof(YZF_GLOBAL_INDEX) int16_t 2
#define YZ_BASE_HEART_PROCESS_NUM 4
#define YZF_BASE_GLOBAL_SHEET_HANDLER_SIZE 32 //void* 4
#define YZF_BASE_GLOBAL_SHEET_DATA_SIZE 128   //void* + uint16_t 6

//YzMemManager Ram
#define YZ_MEM_BLOCK_MAX_COUNT 240            //uint32_t*2+int16_t 10

//YzFont Ram
#define YZL_STR_FORMAT_BUF_SIZE 256          //u8 1
#define YZL_ICONV_UTF8_BUF_SIZE 512         //u8 1
#define YZL_ICONV_UCS2_BUF_SIZE 256          //u8 1

#define YZL_FONT_SRAM_SIZE 24   //Font SRAM sizeof(struct FontPixel) + 3K 1K

//YzMiniUI
#define YZL_UI_IMG_TEMP 2048

#endif //YZF_BASIC_RAM_H
