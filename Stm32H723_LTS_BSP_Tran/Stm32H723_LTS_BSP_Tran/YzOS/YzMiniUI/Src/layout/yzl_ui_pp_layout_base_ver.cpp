//
// Created by 32827 on 2024/2/11.
//
#include "layout/yzl_ui_pp_layout_base_ver.hpp"

UI_Rect *LayoutVertical::nextRect() {
    uint16_t index=0;
    for(uint16_t i=0;i<count;i++){
        if(rect_flag[i]==YZF_FALSE){
            index=i;
            break;
        }
    }
    uint16_t unitH=(range.height/count) - margin * 2;
    uiRect.x = range.x + margin;
    uiRect.y = range.y + (margin * (2 * index + 1)) + index * unitH;
    uiRect.width = range.width - margin * 2;
    uiRect.height = unitH;
    rect_flag[index]=YZF_TRUE;
    return &uiRect;
}

UI_Rect *LayoutVertical::nextRect(uint16_t width, uint16_t height) {
    uint16_t index=0;
    for(uint16_t i=0;i<count;i++){
        if(rect_flag[i]==YZF_FALSE){
            index=i;
            break;
        }
    }
    uint16_t unitH=(range.height/count) - margin * 2;

    uint16_t maxWidth=(range.width-margin*2);
    uint16_t maxHeight=unitH;
    uiRect.width = width>maxWidth?maxWidth:width;
    uiRect.height = height>maxHeight?maxHeight:height;
    uiRect.x = range.x + (range.width-uiRect.width)/2;
    uiRect.y = range.y + (margin * (2 * index + 1)) + index * unitH + (unitH-uiRect.height)/2;
    rect_flag[index]=YZF_TRUE;
    return &uiRect;
}

void LayoutVertical::delRect(UI_Rect *rect) {
    uint16_t index=(rect->y - range.y)/(range.height/count);
    rect_flag[index]=YZF_FALSE;
}

void LayoutVertical::delRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    uint16_t index=(y - range.y)/(range.height/count);
    rect_flag[index>=count?count-1:index]=YZF_FALSE;
}

void LayoutVertical::setRange(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t pCount) {
    range.x = x;
    range.y = y;
    range.width = w;
    range.height = h;
    this->count = pCount;
    if(this->rect_flag!=NULL_PTR){
#if YZL_MEMORY_MANAGER_DEBUG
        yz_info("Layout pFree");
#endif
        YZL_MEM_MANAGER.pFree(this->rect_flag);
    }
#if YZL_MEMORY_MANAGER_DEBUG
        yz_info("Layout pMalloc");
#endif
    this->rect_flag=(YZF_BOOL *)YZL_MEM_MANAGER.pMalloc(sizeof(YZF_BOOL) * pCount);
    memset(this->rect_flag,0,sizeof(YZF_BOOL) * pCount);
}

LayoutVertical::~LayoutVertical() {
    if(this->rect_flag!=NULL_PTR){
#if YZL_MEMORY_MANAGER_DEBUG
        yz_info("Layout pFree");
#endif
        YZL_MEM_MANAGER.pFree(this->rect_flag);
    }
}

LayoutVertical::LayoutVertical(ViewBase *view) : LayoutBase(view) {

}

void LayoutVertical::setMargin(uint16_t m) {
    this->margin = m;
}

uint16_t LayoutVertical::getIndex(UI_Rect *rect) {
    return (rect->y - range.y)/(range.height/count);
}
