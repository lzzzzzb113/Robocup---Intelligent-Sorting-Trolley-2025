//
// Created by 32827 on 2025/3/21.
//
#include "YzCWithClass.hpp"
#include "yzl_mem.h"

void * operator new(size_t size)
{
    void *temp=YZL_MEM_MANAGER.pMalloc(size+4);
    return yzl_mem_address_align(temp,4);
}

void operator delete (void * pointer)
{
    return YZL_MEM_MANAGER.pFree(pointer);
}