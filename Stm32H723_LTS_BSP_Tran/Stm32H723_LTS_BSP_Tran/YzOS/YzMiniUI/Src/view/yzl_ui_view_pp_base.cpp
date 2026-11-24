//
// Created by 32827 on 2024/2/1.
//
#include "yzl.h"
#include "view/yzl_ui_view_pp_base.hpp"

ViewBase::ViewBase(YZL_VIEW *viewRam) {
    this->instance = viewRam;
    instance->init=init;
    instance->act=act;
    instance->sleep=sleep;
    instance->wakeup=wakeup;
    instance->draw=draw;
    instance->deInit=deInit;

    instance->pViewData= YZL_MEM_MANAGER.pMalloc(sizeof (ViewBaseData));
    ((ViewBaseData *)instance->pViewData)->p_this=this;
}

ViewBase::~ViewBase() {
    deInitP();
    YZL_MEM_MANAGER.pFree(instance->pViewData);
}

YZF_BOOL ViewBase::init(void *initStructPointer, void *actStructPointer) {
    ACT_VIEW_OBJECT_GET(ViewBase,actStructPointer)->instance->ViewId=ACT_VIEW_OBJECT_GET(ViewBase,actStructPointer)->getViewId();
    ACT_VIEW_OBJECT_GET(ViewBase,actStructPointer)->instance->ViewName=ACT_VIEW_OBJECT_GET(ViewBase,actStructPointer)->getViewName();
    return ACT_VIEW_OBJECT_GET(ViewBase,actStructPointer)->initP(initStructPointer,actStructPointer);
}

void ViewBase::act(void *actStructPointer) {
    ACT_VIEW_OBJECT_GET(ViewBase,actStructPointer)->actP(actStructPointer);
}

void ViewBase::sleep(void *actStructPointer) {
    ACT_VIEW_OBJECT_GET(ViewBase,actStructPointer)->sleepP(actStructPointer);
}

void ViewBase::wakeup(void *actStructPointer) {
    ACT_VIEW_OBJECT_GET(ViewBase,actStructPointer)->wakeupP(actStructPointer);
}

void ViewBase::draw(void *actStructPointer) {
    ACT_VIEW_OBJECT_GET(ViewBase,actStructPointer)->drawP(actStructPointer);
}

YZF_BOOL ViewBase::deInit(void *actStructPointer) {
    delete ACT_VIEW_OBJECT_GET(ViewBase,actStructPointer);
    return  YZF_TRUE;
}
YZF_BOOL ViewBase::initP(void *initStructPointer, void *actStructPointer) {

    instance->pWidget=(YZL_WIDGET *)YZL_MEM_MANAGER.pMalloc(sizeof(YZL_WIDGET)*VIEW_WIDGET_MAX_COUNT);
    softIndex=(uint8_t *)YZL_MEM_MANAGER.pMalloc(sizeof(uint8_t)*VIEW_WIDGET_MAX_COUNT);

    instance->WidgetCount=0;
    idCount=0;

    return YZF_FALSE;
}

void ViewBase::actP(void *actStructPointer) {
    YZL_ACTIVE_DATA *pdata=(YZL_ACTIVE_DATA *)actStructPointer;
    switch (pdata->Event) {
        case YZL_UI_CTR_EVENT_NONE:
            return;
        case YZL_UI_CTR_EVENT_TOUCH_DOWN:
            for(int i=0;i<instance->WidgetCount;i++){
                if(yzl_ui_point_check((*this)[i],pdata->touch_data->Point[0].x,pdata->touch_data->Point[0].y)){
                    if((*this)[i]->touch(pdata->touch_data->Point[0].x,pdata->touch_data->Point[0].y,YZL_UI_CTR_EVENT_TOUCH_DOWN,(*this)[i])){
                        break;
                    };
                }
            }
            return;
        case YZL_UI_CTR_EVENT_TOUCH_MOVE:
            for(int i=0;i<instance->WidgetCount;i++){
                if((*this)[i]->touch(pdata->touch_data->Point[0].x,pdata->touch_data->Point[0].y,YZL_UI_CTR_EVENT_TOUCH_MOVE,(*this)[i])){
                    break;
                }
            }
            return;
        case YZL_UI_CTR_EVENT_TOUCH_UP:
            for(int i=0;i<instance->WidgetCount;i++){
                if((*this)[i]->touch(pdata->touch_data->Point[0].x,pdata->touch_data->Point[0].y,YZL_UI_CTR_EVENT_TOUCH_UP,(*this)[i])){
                    break;
                }
            }
            return;
        case YZL_UI_CTR_EVENT_SELECTED:
            (*this)[*(int *)(pdata->Data)]->touch(0,0,YZL_UI_CTR_EVENT_SELECTED,(*this)[*(int *)(pdata->Data)]);
            return;
        case YZL_UI_CTR_EVENT_VIEW_ADD_CHILD://DATA: Widget *
            addChild((YZL_WIDGET *)pdata->Data);
            return;
        case YZL_UI_CTR_EVENT_VIEW_REMOVE_CHILD://DATA: uint16_t * Id
            delChild((YZL_WIDGET *)pdata->Data);
            return;
        default:
            return;
    }
}

void ViewBase::sleepP(void *actStructPointer) {

}
void ViewBase::resetBackground(UI_Rect *rect) {

}
void ViewBase::wakeupP(void *actStructPointer) {
    //重新绘制子控件
    for (int i=0;i<instance->WidgetCount;i++) {
        (*this)[i]->isRender=YZF_TRUE;
    }
}
void ViewBase::drawP(void *drawStructPointer) {
    bool isRendered=YZF_FALSE;
    for(int i=0;i<instance->WidgetCount;i++){
        if((*this)[softIndex[i]]->isRender){
            (*this)[softIndex[i]]->draw((*this)[softIndex[i]]);
#if YZL_UI_VIEW_POSITION_DEBUG
            yzl_ui_draw_rect((*this)[softIndex[i]]->x,(*this)[softIndex[i]]->y,(*this)[softIndex[i]]->width,(*this)[softIndex[i]]->height,YZF_FALSE,YZL_UI_VIEW_POSITION_DEBUG_COLOR);
            yz_info("Parent[ 0x%x ] , Widget[%d]{ x:%d , y:%d , width:%d , height:%d }]\n",(*this)[softIndex[i]]->parent,(*this)[softIndex[i]]->id,(*this)[softIndex[i]]->x,(*this)[softIndex[i]]->y,(*this)[softIndex[i]]->width,(*this)[softIndex[i]]->height);
#endif
            isRendered=YZF_TRUE;
        }
    }
    if(isRendered==YZF_TRUE){
        yzl_ui_refresh();
    }
}

YZF_BOOL ViewBase::deInitP() {
    for (int i = 0; i < instance->WidgetCount; i++){
        (*this)[i]->dispose((*this)[i]);
    }
    YZL_MEM_MANAGER.pFree(instance->pWidget);
    YZL_MEM_MANAGER.pFree(softIndex);
    return YZF_TRUE;
}

YZL_WIDGET * ViewBase::operator[](int i) {
    if(i<0){
        return &instance->pWidget[instance->WidgetCount+i+1];
    }
    return &instance->pWidget[i];
}

YZF_BOOL ViewBase::addChild(YZL_WIDGET *child) {
    if(instance->WidgetCount>=VIEW_WIDGET_MAX_COUNT){
        return YZF_FALSE;
    }
    if(child!=YZF_NULL_PTR&&child!=(*this)[-1]){
        memcpy((*this)[-1],child,sizeof(YZL_WIDGET));//添加Widget数据
    }
    (*this)[-1]->id=idCount;                      //设置Id
    (*this)[-1]->parent=instance;                 //设置父控件
    idCount++;
    instance->WidgetCount++;
    updateSoftIndex();
    return YZF_TRUE;
}

YZF_BOOL ViewBase::delChild(YZL_WIDGET *child) {
    if(instance->WidgetCount<=0){
        return YZF_FALSE;
    }
    uint16_t id=child->id;
    uint16_t ind=0xFFFF;
    for(uint16_t i=0;i<instance->WidgetCount;i++){
        if((*this)[i]->id==id){
            ind=i;
            break;
        }
    }
    if(ind==0xFFFF){
        return YZF_FALSE;
    }
    (*this)[ind]->dispose((*this)[ind]);//调用销毁
    if(ind!=instance->WidgetCount-1){
        memcpy((*this)[ind],(*this)[-1],sizeof(YZL_WIDGET));//删除Widget数据
    }
    instance->WidgetCount--;
    updateSoftIndex();
    return YZF_TRUE;
}
/**
 * 按照z轴进行排序，用于绘制控件的顺序
 * */
void ViewBase::updateSoftIndex() {
    uint8_t minIndex=0;
    for(int i=0;i<instance->WidgetCount;i++){
        if((*this)[minIndex]->z >(*this)[i]->z){
            minIndex=i;
        }
    }
    for(int i=0;i<instance->WidgetCount;i++){//获取最大值Count次
        uint8_t max=minIndex;
        for(int j=0;j<instance->WidgetCount;j++){//遍历数组
            if((*this)[j]->z>=(*this)[max]->z){//记录最大值
                YZF_BOOL isHas=YZF_FALSE;
                for(int k=0;k<i;k++){   //判断是否已经获取
                    if(softIndex[k]==j){
                        isHas=YZF_TRUE;
                    }
                }
                if(!isHas){
                    max=j;
                }
            }
        }
        softIndex[i]=max;
    }
}

YZF_BOOL ViewBase::addChild(WidgetBase *child) {
    return addChild(child->instance);
}

YZF_BOOL ViewBase::delChild(WidgetBase *child) {
    return delChild(child->instance);
}

char *ViewBase::getViewName() {
    return (char *)"ViewBase";
}

int ViewBase::getViewId() {
    return YZL_UI_VIEW_ID_VIEW_PP_BASE;
}
