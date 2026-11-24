//
// Created by 32827 on 2023/11/17.
//
#include "yzf_area.h"
/**
 * 数据未超出部分由函数处理
 * 超出部分交予事件监听器处理，未设置会丢失数据
 * */
void yzf_area_recv_init(YZF_RECV *area,void (*listener)(YZF_RECV_EVENT event,struct YZF_RECV_AREA* area,YZF_GLOBAL_INDEX dataIndex)){
    area->yzf_recv_listener=listener;
    area->yzf_recv_size=0;
    area->yzf_area_recv_add_count=0;
    area->yzf_area_recv_del_count=0;
    area->yzf_recv_write_ptr = 0;
    area->yzf_recv_read_ptr = 0;
}
/**
 * Bug 第二次图片传输会少4位 会删除两次标志
 * */
///o(4)
void yzf_area_recv_add(YZF_RECV *area,YZF_RECV_DATA t){
    if(area->yzf_recv_size+1>YZF_AREA_RECV_SIZE){
        if(area->yzf_recv_listener==YZF_NULL_PTR){
            return;
        }
        ///生成 recv_full事件
        YZF_GLOBAL_INDEX index=yzf_global_data_add(&t);
        area->yzf_recv_listener(recv_full,area,index);
        yzf_global_data_delRef(index);

        area->yzf_recv_size++;
        return;
    }
    area->yzf_recv[area->yzf_recv_write_ptr] = t;
    area->yzf_recv_write_ptr=(area->yzf_recv_write_ptr+1)%YZF_AREA_RECV_SIZE;
    area->yzf_recv_size++;
    area->yzf_area_recv_add_count++;
}
///o(5)
YZF_RECV_DATA yzf_area_recv_get(YZF_RECV *area){
    if(area->yzf_recv_size==0){
        return EOF;
    }else if(area->yzf_recv_size>YZF_AREA_RECV_SIZE){
        if(area->yzf_recv_listener==YZF_NULL_PTR){
            return EOF;
        }
        ///生成 recv_get事件
        YZF_RECV_DATA_INDEX ind=area->yzf_recv_size-YZF_AREA_RECV_SIZE;
        YZF_GLOBAL_INDEX index=yzf_global_data_add(&ind);
        area->yzf_recv_listener(recv_get,area,index);
        YZF_RECV_DATA data= *(YZF_RECV_DATA *)yzf_global_data_get(index);
        yzf_global_data_delRef(index);
        area->yzf_recv_size--;
        return data;
    }
    YZF_RECV_DATA re=area->yzf_recv[area->yzf_recv_read_ptr];
    area->yzf_recv_read_ptr=(area->yzf_recv_read_ptr+1)%YZF_AREA_RECV_SIZE;
    area->yzf_recv_size--;
    area->yzf_area_recv_del_count++;
    return re;
}
///o(1)
YZF_RECV_DATA_INDEX yzf_area_recv_get_size(YZF_RECV *area){
    return area->yzf_recv_size;
}
///o(2)
YZF_RECV_DATA * yzf_area_recv_get_read_ptr(YZF_RECV *area){
    //交给事件监听器处理
    if(area->yzf_recv_size>YZF_AREA_RECV_SIZE){
        if(area->yzf_recv_listener==YZF_NULL_PTR){
            return YZF_NULL_PTR;
        }
        ///生成 recv_get事件
        YZF_RECV_DATA *read_ptr;
        YZF_GLOBAL_INDEX index=yzf_global_data_add(&read_ptr);
        area->yzf_recv_listener(recv_read_ptr,area,index);
        read_ptr= *(YZF_RECV_DATA **)yzf_global_data_get(index);
        yzf_global_data_delRef(index);
        return read_ptr;
    }
    return &area->yzf_recv[area->yzf_recv_read_ptr];
}
/**
 * 获取本次线性的结尾
 * */
YZF_RECV_DATA * yzf_area_recv_get_end_ptr(YZF_RECV *area){
    if(area->yzf_recv_size>YZF_AREA_RECV_SIZE){
        if(area->yzf_recv_listener==YZF_NULL_PTR){
            return YZF_NULL_PTR;
        }
        ///生成 recv_get事件
        YZF_RECV_DATA *end_ptr;
        YZF_GLOBAL_INDEX index=yzf_global_data_add(&end_ptr);
        area->yzf_recv_listener(recv_end_ptr,area,index);
        end_ptr= *(YZF_RECV_DATA **)yzf_global_data_get(index);
        yzf_global_data_delRef(index);
        return end_ptr;
    }
    if(area->yzf_recv_read_ptr<area->yzf_recv_write_ptr||(area->yzf_recv_read_ptr==area->yzf_recv_write_ptr&&area->yzf_recv_size==0)){
        return  &area->yzf_recv[area->yzf_recv_write_ptr];//返回末尾
    }else{
        return (&area->yzf_recv[YZF_AREA_RECV_SIZE-1])+1;//返回区域结尾
    }
}
void yzf_area_recv_del(YZF_RECV *area,YZF_RECV_DATA_INDEX len){
    if(area->yzf_recv_size>YZF_AREA_RECV_SIZE){
        if(area->yzf_recv_listener==YZF_NULL_PTR){
            return;
        }
        YZF_RECV_DATA_INDEX outLen=area->yzf_recv_size-YZF_AREA_RECV_SIZE+1;
        YZF_GLOBAL_INDEX index;
        if(outLen>=len){
            index=yzf_global_data_add(&len);
        }else{
            index=yzf_global_data_add(&outLen);
        }
        ///生成 recv_full事件
        area->yzf_recv_listener(recv_del,area,index);
        yzf_global_data_delRef(index);
        if(outLen<len){
            area->yzf_recv_read_ptr=(area->yzf_recv_read_ptr+(len-outLen))%YZF_AREA_RECV_SIZE;
        }
        area->yzf_recv_size-=len;
        return;
    }
    area->yzf_recv_read_ptr=(area->yzf_recv_read_ptr+len)%YZF_AREA_RECV_SIZE;
    area->yzf_recv_size-=len;
    area->yzf_area_recv_del_count+=len;
}
uint32_t yzf_area_recv_add_count(YZF_RECV *area){
    return area->yzf_area_recv_add_count;
}
uint32_t yzf_area_recv_del_count(YZF_RECV *area){
    return area->yzf_area_recv_del_count;
}
YZF_RECV_DATA_INDEX yzf_area_line_lenght(YZF_RECV *area){
    uint32_t pst= (uint32_t )yzf_area_recv_get_read_ptr(area);
    uint32_t pse= (uint32_t )yzf_area_recv_get_end_ptr(area);
    return pse-pst;
}