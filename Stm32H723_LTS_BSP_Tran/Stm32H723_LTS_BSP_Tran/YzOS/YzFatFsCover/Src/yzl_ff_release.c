//
// Created by 32827 on 2024/1/19.
//
#include "yzl_ff_release.h"
#include "yzl.h"
#include "yzx_base.h"

FATFS yzl_fs;
YZF_RESULT RAM_disk_status(){
    return YZF_NOT_INIT;
}
YZF_RESULT MMC_disk_status(){
    return YZF_OK;
}
YZF_RESULT USB_disk_status(){
    return YZF_NOT_INIT;
}
YZF_RESULT RAM_disk_initialize(){
    return YZF_NOT_INIT;
}
YZF_RESULT MMC_disk_initialize(){
    //return yzl_sd_spi_init(YZFATFS_SD_DRIVER_PORT);
    return yz_hal_get_sdmmc1()->State==HAL_SD_STATE_READY?YZF_OK:YZF_ERROR;
}
YZF_RESULT USB_disk_initialize(){
    return YZF_NOT_INIT;
}
YZF_RESULT RAM_disk_read(BYTE* buff,LBA_t sector,UINT count){
    return YZF_ERROR;
}
YZF_RESULT MMC_disk_read(BYTE* buff,LBA_t sector,UINT count){
    //return ReadSectorsFromMicroSD_Raw(YZFATFS_SD_DRIVER_PORT,sector*512,buff,count);
    __disable_irq();
    HAL_StatusTypeDef res=HAL_SD_ReadBlocks(yz_hal_get_sdmmc1(),(uint8_t *)buff,sector,count,0xFFFFFUL);
    __enable_irq();
    return res==HAL_OK?YZF_OK:YZF_ERROR;
}
YZF_RESULT USB_disk_read(BYTE* buff,LBA_t sector,UINT count){
    return YZF_ERROR;
}
YZF_RESULT RAM_disk_write(const BYTE* buff,LBA_t sector,UINT count){
    return YZF_ERROR;
}
YZF_RESULT MMC_disk_write(const BYTE* buff,LBA_t sector,UINT count){
    //return WriteSectorsToMicroSD_Raw(YZFATFS_SD_DRIVER_PORT,sector*512,buff,count);
    return HAL_SD_WriteBlocks(yz_hal_get_sdmmc1(),(uint8_t *)buff,sector,count,0xFFFFFUL)==HAL_OK?YZF_OK:YZF_ERROR;
}
YZF_RESULT USB_disk_write(const BYTE* buff,LBA_t sector,UINT count){
    return YZF_ERROR;
}
YZF_RESULT RAM_disk_ioctl(BYTE cmd, void* buff){
    return YZF_ERROR;
}
YZF_RESULT MMC_disk_ioctl(BYTE cmd, void* buff){
    //TODO: init disk information
    switch(cmd)
    {
        case CTRL_SYNC:
            return YZF_OK;
        case GET_SECTOR_SIZE:
            *(DWORD*)buff = 512;
            return YZF_OK;
        case GET_BLOCK_SIZE:
            *(WORD*)buff = 512;
            return YZF_OK;
        case GET_SECTOR_COUNT:
            *(DWORD*)buff = 128*1024*2;
            return YZF_OK;
        default:
            return YZF_ERROR;
    }
}
YZF_RESULT USB_disk_ioctl(BYTE cmd, void* buff){
    return YZF_ERROR;
}
DWORD get_fattime (void)
{
    return 0;
}
//动态分配内存
void *ff_memalloc (UINT size)
{
#if YZFATFS_MEMORY_MALLOC_DEBUG
    yz_info("FATFS: ff_memalloc(%d)\n",size);
#endif
    return (void*) YZL_MEM_MANAGER.pMalloc(size);
}
//释放内存
void ff_memfree (void* mf)
{
#if YZFATFS_MEMORY_MALLOC_DEBUG
    yz_info("FATFS: ff_memfree()\n");
#endif
    YZL_MEM_MANAGER.pFree(mf);
}