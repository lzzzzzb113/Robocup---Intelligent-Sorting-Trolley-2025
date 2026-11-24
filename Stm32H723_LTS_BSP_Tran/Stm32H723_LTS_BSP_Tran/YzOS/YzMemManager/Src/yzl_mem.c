//
// Created by 32827 on 2024/1/26.
//
#include "yzl_mem.h"
#include "yz_log.h"

#if USE_MEM_MANAGER

#define YZL_MEM_ERROR_INDEX 0xFFFF
YZL_MEM_BLOCK yzl_mem_blocks[YZ_MEM_BLOCK_MAX_COUNT];   //保存内存块定义
#define SOFT_TYPE int16_t
SOFT_TYPE yzl_mem_block_soft[YZ_MEM_BLOCK_MAX_COUNT];     //保存内存块排序
SOFT_TYPE yzl_mem_block_count=0;                          //内存块总数
YZ_MemManger *yzl_mem_manger;

#define YZL_MEM_END_BLOCK_INDEX yzl_mem_block_soft[yzl_mem_block_count-1]
#define YZL_MEM_NEXT_FREE_SOFT_SPACE yzl_mem_block_soft[yzl_mem_block_count]
#define YZL_MEM_END_ADDRESS (yzl_mem_manger->baseAddress+yzl_mem_manger->size)
#define YZL_MEM_FREE_SIZE(top,end) (yzl_mem_blocks[top].baseAddress-yzl_mem_blocks[end].endAddress)

int16_t yzl_mem_get_empty_block_index(){
    for (int16_t i = 0; i < YZ_MEM_BLOCK_MAX_COUNT; i++) {
        if(yzl_mem_blocks[i].baseAddress==0){           //查找未使用内存块地址
            return i;
        }
    }
    return YZL_MEM_ERROR_INDEX;
}

void yzl_mem_init(YZ_MemManger* pMemManger){
    yzl_mem_manger=pMemManger;
    memset(yzl_mem_blocks,0,sizeof(yzl_mem_blocks));
    memset(yzl_mem_block_soft,0,sizeof(yzl_mem_block_soft));
    yzl_mem_manger->pMalloc=yzl_mem_malloc;
    yzl_mem_manger->pFree=yzl_mem_free;
}
void yzl_mem_insert_soft(int index,int16_t BlockIndex){
    memmove(&yzl_mem_block_soft[index+1],&yzl_mem_block_soft[index],sizeof(SOFT_TYPE)*(yzl_mem_block_count-index));
    yzl_mem_block_soft[index]=BlockIndex;
}
void yzl_mem_block_init(int index,int last_soft_index,uint32_t size){
    if(last_soft_index==-1){
        yzl_mem_blocks[index].baseAddress = yzl_mem_manger->baseAddress;
        yzl_mem_blocks[index].endAddress = yzl_mem_blocks[index].baseAddress + size;
        yzl_mem_insert_soft(last_soft_index+1, index);
    }else if(last_soft_index+1==yzl_mem_block_count){
        yzl_mem_blocks[index].baseAddress = yzl_mem_blocks[yzl_mem_block_soft[last_soft_index]].endAddress;
        yzl_mem_block_soft[yzl_mem_block_count]=index;
        yzl_mem_blocks[index].endAddress = yzl_mem_blocks[index].baseAddress + size;
    }else{
        yzl_mem_blocks[index].baseAddress = yzl_mem_blocks[yzl_mem_block_soft[last_soft_index]].endAddress;
        yzl_mem_insert_soft(last_soft_index+1, index);
        yzl_mem_blocks[index].endAddress = yzl_mem_blocks[index].baseAddress + size;
    }
    yzl_mem_block_count++;
}

void yzl_mem_print(){
    for (int i = 0; i < yzl_mem_block_count; i++) {
        uint16_t BlockIndex=yzl_mem_block_soft[i];
        yz_info("============================\n");
        yz_info("BlockIndex: %d\n",BlockIndex);
        yz_info("BaseAddress: 0x%x\n",yzl_mem_blocks[BlockIndex].baseAddress);
        yz_info("EndAddress: 0x%x\n",yzl_mem_blocks[BlockIndex].endAddress);
        yz_info("============================\n");
    }
}
void* yzl_mem_malloc(size_t size){
    int16_t index=yzl_mem_get_empty_block_index();
    if(index==(int16_t)YZL_MEM_ERROR_INDEX){    //内存块分配完
        yz_error("yzl_mem_malloc error: NOT EMPTY BLOCK");
        return NULL_PTR;
    }
    if(yzl_mem_block_count==0){                                             //首个内存块
//        yzl_mem_blocks[index].baseAddress=yzl_mem_manger->baseAddress;      //从基址分配
//        yzl_mem_blocks[index].endAddress=yzl_mem_blocks[index].baseAddress+size;
//        YZL_MEM_NEXT_FREE_SOFT_SPACE=index;                      //设置基址最低内存块
//        yzl_mem_block_count++;
        yzl_mem_block_init(index,-1,size);

#if YZL_MEMORY_MANAGER_DEBUG
        yz_info("============================\n");
        yz_info("Malloc BlockIndex: %d\n",index);
        yz_info("Malloc Size: %d\n",size);
        yz_info("Total Blocks: %d\n",yzl_mem_block_count);
        yz_info("Ptr : 0x%x\n",yzl_mem_blocks[index].baseAddress);
        yz_info("============================\n");
#endif
        return (void *)yzl_mem_blocks[index].baseAddress;
    }else{
        if(YZL_MEM_END_ADDRESS-yzl_mem_blocks[YZL_MEM_END_BLOCK_INDEX].endAddress>=size){
            //从当前最后一个内存块结束地址开始分配
//            yzl_mem_blocks[index].baseAddress=yzl_mem_blocks[YZL_MEM_END_BLOCK_INDEX].endAddress;
//            yzl_mem_blocks[index].endAddress=yzl_mem_blocks[index].baseAddress+size;
//            yzl_mem_block_soft[yzl_mem_block_count]=index;
//            yzl_mem_block_count++;
            yzl_mem_block_init(index,yzl_mem_block_count-1,size);
#if YZL_MEMORY_MANAGER_DEBUG
            yz_info("============================\n");
            yz_info("Malloc BlockIndex: %d\n",index);
            yz_info("Malloc Size: %d\n",size);
            yz_info("Total Blocks: %d\n",yzl_mem_block_count);
            yz_info("Ptr : 0x%x\n",yzl_mem_blocks[index].baseAddress);
            yz_info("============================\n");
#endif
            return (void *)yzl_mem_blocks[index].baseAddress;
        }else{
            //寻找块间可分配内存
            for (int i = 0; i < yzl_mem_block_count; i++) {
#if YZL_MEMORY_MANAGER_DEBUG
                yz_info("============================\n");
                yz_info("BlockIndex: %d\n",yzl_mem_block_soft[i]);
                yz_info("Ptr : 0x%x\n",yzl_mem_blocks[yzl_mem_block_soft[i]].baseAddress);
                yz_info("EndPtr : 0x%x\n",yzl_mem_blocks[yzl_mem_block_soft[i]].endAddress);
                yz_info("============================\n");
#endif
                if(i==0){
                    if(yzl_mem_blocks[yzl_mem_block_soft[i]].baseAddress-yzl_mem_manger->baseAddress>=size){//基址和第一个块之间
                        yzl_mem_block_init(index,-1,size);
//                        yzl_mem_insert_soft(i,index);
//                        yzl_mem_blocks[index].baseAddress=yzl_mem_manger->baseAddress;
//                        yzl_mem_blocks[index].endAddress=yzl_mem_manger->baseAddress+size;
//                        yzl_mem_block_count++;
#if YZL_MEMORY_MANAGER_DEBUG
                        yz_info("============================\n");
                        yz_info("Malloc BlockIndex: %d\n",index);
                        yz_info("Malloc Size: %d\n",size);
                        yz_info("Total Blocks: %d\n",yzl_mem_block_count);
                        yz_info("Ptr : 0x%x\n",yzl_mem_blocks[index].baseAddress);
                        yz_info("============================\n");
#endif
                        return (void *)yzl_mem_blocks[index].baseAddress;
                    }
                }else{
                    if(yzl_mem_blocks[yzl_mem_block_soft[i+1]].baseAddress-yzl_mem_blocks[yzl_mem_block_soft[i]].endAddress>=size) {//块与块间
//                        yzl_mem_blocks[index].baseAddress = yzl_mem_blocks[yzl_mem_block_soft[i]].endAddress;
//                        yzl_mem_insert_soft(i, index);
//                        yzl_mem_blocks[index].endAddress = yzl_mem_blocks[index].baseAddress + size;
//                        yzl_mem_block_count++;
                        yzl_mem_block_init(index,i,size);
#if YZL_MEMORY_MANAGER_DEBUG
                        yz_info("============================\n");
                        yz_info("Malloc BlockIndex: %d\n",index);
                        yz_info("Malloc Size: %d\n",size);
                        yz_info("Total Blocks: %d\n",yzl_mem_block_count);
                        yz_info("Ptr : 0x%x\n",yzl_mem_blocks[index].baseAddress);
                        yz_info("============================\n");
#endif
                        return (void *)yzl_mem_blocks[index].baseAddress;
                    }
                }
            }

            //yzl_mem_zip() 整理内存碎片
//            if(yzl_mem_manger->baseAddress+yzl_mem_manger->size-yzl_mem_blocks[yzl_mem_block_soft[yzl_mem_block_count-1]].endAddress>=size){
//                //从当前最后一个内存块结束地址开始分配
//                yzl_mem_blocks[index].baseAddress=yzl_mem_blocks[yzl_mem_block_soft[yzl_mem_block_count-1]].endAddress;
//                yzl_mem_blocks[index].endAddress=yzl_mem_blocks[index].baseAddress+size;
//                yzl_mem_block_soft[yzl_mem_block_count]=index;
//                yzl_mem_block_count++;
//                return (void *)yzl_mem_blocks[index].baseAddress;
//            }else{
//                //寻找块间可分配内存
//                for (int i = 0; i < yzl_mem_block_count; i++) {
//                    if(i==0){
//                        if(yzl_mem_blocks[yzl_mem_block_soft[i]].baseAddress-yzl_mem_manger->baseAddress>=size){//基址和第一个块之间
//                            yzl_mem_insert_soft(i,index);
//                            yzl_mem_blocks[index].baseAddress=yzl_mem_manger->baseAddress;
//                            yzl_mem_blocks[index].endAddress=yzl_mem_manger->baseAddress+size;
//                            return (void *)yzl_mem_blocks[index].baseAddress;
//                        }
//                    }else{
//                        if(yzl_mem_blocks[yzl_mem_block_soft[i+1]].baseAddress-yzl_mem_blocks[yzl_mem_block_soft[i]].endAddress>=size) {//块与块间
//                            yzl_mem_insert_soft(i, index);
//                            yzl_mem_blocks[index].baseAddress = yzl_mem_blocks[yzl_mem_block_soft[i]].endAddress;
//                            yzl_mem_blocks[index].endAddress = yzl_mem_blocks[index].baseAddress + size;
//                            return (void *)yzl_mem_blocks[index].baseAddress;
//                        }
//                    }
//                }
            //未找到可分配内存
            yz_error("yzl_mem_malloc error: NOT ENOUGH MEMORY");
        }
        return NULL_PTR;
    }
}

void yzl_mem_free(void* ptr){
    for(int i=0;i<yzl_mem_block_count;i++){
        if(yzl_mem_blocks[yzl_mem_block_soft[i]].baseAddress<=(uint32_t)ptr&&yzl_mem_blocks[yzl_mem_block_soft[i]].endAddress-1>=(uint32_t)ptr){
            yzl_mem_blocks[yzl_mem_block_soft[i]].baseAddress=0;
            yzl_mem_blocks[yzl_mem_block_soft[i]].endAddress=0;

            if(i!=yzl_mem_block_count-1){
                memmove(yzl_mem_block_soft+i,yzl_mem_block_soft+i+1,sizeof(SOFT_TYPE)*(yzl_mem_block_count-i-1));
                yzl_mem_block_count--;
#if YZL_MEMORY_MANAGER_DEBUG
                yz_info("============================\n");
                yz_info("Ptr : 0x%x\n",(uint32_t)ptr);
                yz_info("Free BlockIndex: %d\n",yzl_mem_block_soft[i]);
                yz_info("Total Blocks: %d\n",yzl_mem_block_count);
                yz_info("============================\n");
#endif
                yzl_mem_block_soft[yzl_mem_block_count]=0;
                return;
            }else{
                yzl_mem_block_count--;
#if YZL_MEMORY_MANAGER_DEBUG
                yz_info("============================\n");
                yz_info("Ptr : 0x%x\n",(uint32_t)ptr);
                yz_info("Free BlockIndex: %d\n",yzl_mem_block_soft[i]);
                yz_info("Total Blocks: %d\n",yzl_mem_block_count);
                yz_info("============================\n");
#endif
                yzl_mem_block_soft[yzl_mem_block_count]=0;
                return;
            }
        }
    }
}
void yzl_mem_zip(){
    if(yzl_mem_blocks[yzl_mem_block_soft[0]].baseAddress!=yzl_mem_manger->baseAddress){
        int32_t size=yzl_mem_blocks[yzl_mem_block_soft[0]].endAddress-yzl_mem_blocks[yzl_mem_block_soft[0]].baseAddress;
        memcpy((void *)yzl_mem_manger->baseAddress,(void *)yzl_mem_blocks[yzl_mem_block_soft[0]].baseAddress,size);
        yzl_mem_blocks[yzl_mem_block_soft[0]].baseAddress=yzl_mem_manger->baseAddress;
        yzl_mem_blocks[yzl_mem_block_soft[0]].endAddress=yzl_mem_blocks[yzl_mem_block_soft[0]].baseAddress+size;
    }
    for(int i=1;i<yzl_mem_block_count;i++){
        if(yzl_mem_blocks[yzl_mem_block_soft[i-1]].endAddress!=yzl_mem_blocks[yzl_mem_block_soft[i]].baseAddress){
            //size = end - base
            int32_t size=yzl_mem_blocks[yzl_mem_block_soft[i]].endAddress-yzl_mem_blocks[yzl_mem_block_soft[i]].baseAddress;
            //move data
            memcpy((void *)yzl_mem_blocks[yzl_mem_block_soft[i-1]].endAddress,(void *)yzl_mem_blocks[yzl_mem_block_soft[i]].baseAddress,size);
            //end -> base
            yzl_mem_blocks[yzl_mem_block_soft[i]].baseAddress=yzl_mem_blocks[yzl_mem_block_soft[i-1]].endAddress;
            //relink
            yzl_mem_blocks[yzl_mem_block_soft[i]].endAddress=yzl_mem_blocks[yzl_mem_block_soft[0]].baseAddress+size;
        }
    }
}

void * yzl_mem_address_align(void * address, uint32_t align){
    return (void *)(((uint32_t)address+align-1)&~(align-1));
}
#endif