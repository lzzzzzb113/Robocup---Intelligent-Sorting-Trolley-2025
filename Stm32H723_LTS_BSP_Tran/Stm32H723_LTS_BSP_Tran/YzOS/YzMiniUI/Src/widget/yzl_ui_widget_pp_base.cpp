//
// Created by 32827 on 2024/2/1.
//

#include "yzl.h"
#include "widget/yzl_ui_widget_pp_base.hpp"
#include "view/yzl_ui_view_pp_base.hpp"
#include "yzl_ui_scn_utils.h"

WidgetBase::WidgetBase(YZL_WIDGET *Ram,int x, int y,int z, int width, int height){
    this->instance = Ram;

    instance->dispose=dispose;
    instance->touch=touch;
    instance->draw=draw;

    ((WidgetBaseData *)instance->data)->p_this= this;//注册对象

    setSize(x,y,z,width,height);
    instance->status = YZL_UI_CTR_EVENT_TOUCH_UP;
    instance->isRender = YZF_TRUE;

    isViewReset = YZF_TRUE;
}

WidgetBase::~WidgetBase() {
    disposeP();
}
/**
 * <h1>WidgetBase</h1>
 * <h3>
 * Method Do:
 * </h3>
 * 1.BackUp 自动备份显存
 *
 * <h3>
 * Override Notice:
 * </h3>
 * 1.绘制完成设置 instance->isRender=YZF_FALSE; 已确认绘制循环结束
 * */
void WidgetBase::drawP() {
    if((!isBackup)&&(!isViewReset)){
        BackUp();
    }
}

YZF_BOOL WidgetBase::touchP(uint16_t x, uint16_t y, YZL_UI_CTR_EVENT event) {

    return YZF_FALSE;
}

void WidgetBase::disposeP() {
    Restore();
}

//C -> C++ 兼容转发
void WidgetBase::draw(void *widget) {
    ((WidgetBase *)YZL_UI_WIDGET_DATA_VALUE(WidgetBaseData,widget)->p_this)->drawP();
}

YZF_BOOL WidgetBase::touch(uint16_t x, uint16_t y, YZL_UI_CTR_EVENT event, void *widget) {
    return ((WidgetBase *)YZL_UI_WIDGET_DATA_VALUE(WidgetBaseData,widget)->p_this)->touchP(x,y,event);
}

void WidgetBase::dispose(void *widget) {
    delete ((WidgetBase *)YZL_UI_WIDGET_DATA_VALUE(WidgetBaseData,widget)->p_this);
}

void WidgetBase::BackUp() {
    if(isViewReset){

    }else{
        if(isBackup){
            Restore();
            recover=yzl_ui_scn_ram_Backup(instance->x,instance->y,instance->width,instance->height);
        }else{
            recover=yzl_ui_scn_ram_Backup(instance->x,instance->y,instance->width,instance->height);
        }
        isBackup=YZF_TRUE;
    }
}
void WidgetBase::RollBack(){
    if(isViewReset){
        UI_Rect pdata={this->instance->x,this->instance->y,this->instance->width,this->instance->height};
        YZL_UI_WIDGET_PP_PARENT(instance)->resetBackground(&pdata);
    }else{
        if(isBackup){
            yzl_ui_scn_ram_Restore(recover,instance->x,instance->y,instance->width,instance->height);
        }
    }

}
void WidgetBase::Restore() {
    if(isViewReset){
        UI_Rect pdata={this->instance->x,this->instance->y,this->instance->width,this->instance->height};
        YZL_UI_WIDGET_PP_PARENT(instance)->resetBackground(&pdata);
    }else{
        if(isBackup){
            yzl_ui_scn_ram_Restore(recover,instance->x,instance->y,instance->width,instance->height);
            YZL_MEM_MANAGER.pFree(recover);
            isBackup=YZF_FALSE;
        }
    }

}

void WidgetBase::RollBack(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    if(isViewReset){
        UI_Rect pdata={x,y,width,height};
        YZL_UI_WIDGET_PP_PARENT(instance)->resetBackground(&pdata);
    }else{
        if(isBackup){
            yzl_ui_scn_ram_Restore(recover,instance->x,instance->y,instance->width,instance->height);
            YZL_MEM_MANAGER.pFree(recover);
            isBackup=YZF_FALSE;
        }
    }
}

void WidgetBase::setSize(int x, int y, int z, int width, int height) const {
    instance->x=x;
    instance->y=y;
    instance->z=(int16_t)z;
    instance->width=width;
    instance->height=height;

    instance->isRender = YZF_TRUE;
}
