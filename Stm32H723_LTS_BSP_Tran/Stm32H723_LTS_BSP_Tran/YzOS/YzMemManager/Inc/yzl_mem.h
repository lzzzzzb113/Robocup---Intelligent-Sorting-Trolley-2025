//
// Created by 32827 on 2024/1/26.
//

#ifndef YZL_MEM_H
#define YZL_MEM_H
#include "yzl.h"
#include "string.h"

#if USE_MEM_MANAGER

typedef struct {
    uint32_t baseAddress;
    uint32_t endAddress;
} YZL_MEM_BLOCK;
#ifdef __cplusplus
extern "C" {
#endif

///用于和UI库配合
void yzl_mem_init(YZ_MemManger *pMemManger);

void *yzl_mem_malloc(size_t size);

void yzl_mem_free(void *ptr);

void * yzl_mem_address_align(void * address, uint32_t align);

void yzl_mem_zip();

void yzl_mem_print();

#ifdef __cplusplus
}
#endif

#endif
#endif //YZL_MEM_H
