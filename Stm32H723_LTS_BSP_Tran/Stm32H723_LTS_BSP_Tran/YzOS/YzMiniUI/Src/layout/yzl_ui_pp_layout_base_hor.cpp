//
// Created by 32827 on 2024/7/11.
//
#include "layout/yzl_ui_pp_layout_base_hor.hpp"

LayoutHorizontal::~LayoutHorizontal() {
    if(this->rect_flag!=NULL_PTR){
#if YZL_MEMORY_MANAGER_DEBUG
        yz_info("Layout pFree");
#endif
        YZL_MEM_MANAGER.pFree(this->rect_flag);
    }
    if(this->rect_weight!=NULL_PTR){
#if YZL_MEMORY_MANAGER_DEBUG
        yz_info("Layout pFree");
#endif
        YZL_MEM_MANAGER.pFree(this->rect_weight);
    }
}

LayoutHorizontal::LayoutHorizontal(ViewBase *view) : LayoutBase(view) {

}

void LayoutHorizontal::setRange(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t pCount) {
    range.x=x;
    range.y=y;
    range.width=w;
    range.height=h;
    this->count=pCount;
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
    if(this->rect_weight!=NULL_PTR){
#if YZL_MEMORY_MANAGER_DEBUG
        yz_info("Layout pFree");
#endif
        YZL_MEM_MANAGER.pFree(this->rect_weight);
    }
#if YZL_MEMORY_MANAGER_DEBUG
    yz_info("Layout pMalloc");
#endif
    this->rect_weight=(uint16_t *)YZL_MEM_MANAGER.pMalloc(sizeof(uint16_t) * pCount);
    for(uint16_t i=0;i<pCount;i++){
        this->rect_weight[i]=1;
    }
}

void LayoutHorizontal::setMargin(uint16_t m) {
    this->margin=m;
}

UI_Rect *LayoutHorizontal::nextRect() {
    uint16_t index=0;
    for(uint16_t i=0;i<count;i++){
        if(this->rect_flag[i]==YZF_FALSE){
            index=i;
            break;
        }
    }
    uint16_t sumWeight=0;
    for(uint16_t i=0;i<count;i++){
        sumWeight+=this->rect_weight[i];
    }
    uint16_t unitWeight=(range.width-margin*2*(count))/sumWeight;
    uiRect.y=range.y+margin;
    uint16_t foreSumX=0;
    for(uint16_t i=0;i<index;i++){
        foreSumX+=margin*2;
        foreSumX+=this->rect_weight[i]*unitWeight;
    }
    uiRect.x=range.x+margin+foreSumX;
    uiRect.height=range.height-margin*2;
    uiRect.width=this->rect_weight[index]*unitWeight;
    rect_flag[index]=YZF_TRUE;
    return &uiRect;
}

void LayoutHorizontal::delRect(UI_Rect *rect) {
    uint16_t sumWeight=0;
    for(uint16_t i=0;i<count;i++){
        sumWeight+=this->rect_weight[i];
    }
    uint16_t unitWeight=(range.width-margin*2*(count))/sumWeight;
    uint16_t foreSumX=range.x;
    for(uint16_t i=0;i<count;i++){
        if(foreSumX<=rect->x&&foreSumX+this->rect_weight[i]*unitWeight>=rect->x+rect->width){
            this->rect_flag[i]=YZF_FALSE;
            break;
        }
        foreSumX+=margin*2;
        foreSumX+=this->rect_weight[i]*unitWeight;
    }
}

void LayoutHorizontal::delRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    uiRect.x=x;
    uiRect.y=y;
    uiRect.width=width;
    uiRect.height=height;
    delRect(&uiRect);
}

void LayoutHorizontal::setWeight(uint16_t index, uint16_t weight) {
    this->rect_weight[index]=weight;
}

uint16_t LayoutHorizontal::getIndex(UI_Rect *rect) {
    uint16_t sumWeight=0;
    for(uint16_t i=0;i<count;i++){
        sumWeight+=this->rect_weight[i];
    }
    uint16_t unitWeight=(range.width-margin*2*(count))/sumWeight;
    uint16_t foreSumX=range.x;
    for(uint16_t i=0;i<count;i++){
        if(foreSumX<=rect->x&&foreSumX+this->rect_weight[i]*unitWeight>=rect->x+rect->width){
            return i;
        }
    }
    return 0;
}
