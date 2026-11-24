//
// Created by 32827 on 2024/1/19.
//

#ifndef YZGD32_YZL_FF_RELEASE_H
#define YZGD32_YZL_FF_RELEASE_H
#include "yzl.h"
#include "diskio.h"
#include "ff.h"
//#include "yzl_spi_sd.h"
#ifdef __cplusplus
extern "C" {
#endif
extern FATFS yzl_fs;

YZF_RESULT RAM_disk_status();

YZF_RESULT MMC_disk_status();

YZF_RESULT USB_disk_status();

YZF_RESULT RAM_disk_initialize();

YZF_RESULT MMC_disk_initialize();

YZF_RESULT USB_disk_initialize();

YZF_RESULT RAM_disk_read(BYTE *buff, LBA_t sector, UINT count);

YZF_RESULT MMC_disk_read(BYTE *buff, LBA_t sector, UINT count);

YZF_RESULT USB_disk_read(BYTE *buff, LBA_t sector, UINT count);

YZF_RESULT RAM_disk_write(const BYTE *buff, LBA_t sector, UINT count);

YZF_RESULT MMC_disk_write(const BYTE *buff, LBA_t sector, UINT count);

YZF_RESULT USB_disk_write(const BYTE *buff, LBA_t sector, UINT count);

YZF_RESULT RAM_disk_ioctl(BYTE cmd, void *buff);

YZF_RESULT MMC_disk_ioctl(BYTE cmd, void *buff);

YZF_RESULT USB_disk_ioctl(BYTE cmd, void *buff);

#ifdef __cplusplus
}
#endif
#endif //YZGD32_YZL_FF_RELEASE_H
