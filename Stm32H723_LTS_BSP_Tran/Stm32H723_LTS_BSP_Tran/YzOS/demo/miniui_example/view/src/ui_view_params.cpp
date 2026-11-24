//
// Created by 32827 on 2025/5/7.
//

#include "../inc/ui_view_params.hpp"
#include "yzl_space_sensor_action_angle.hpp"

ViewParams::ViewParams(YZL_VIEW *viewRam, char *bgPath ,ArmGroup *armGroup) : ViewBase(viewRam){
    this->bgPath = bgPath;
    this->SelectIndex = 0;
    this->armGroup = armGroup;
}

ViewParams::~ViewParams() = default;

YZF_BOOL ViewParams::initP(void *initStructPointer, void *actStructPointer) {
    ViewBase::initP(initStructPointer, actStructPointer);

    layout=new LayoutVertical(this);
    layout->setRange(0,0,YZ_SCREEN_WIDTH,YZ_SCREEN_HEIGHT,6);
    layout->setMargin(0);

    mText1=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "NONE");
    addChild(mText1);
    mText2=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "NONE");
    addChild(mText2);
    mText3=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "NONE");
    addChild(mText3);
    mText4=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "NONE");
    addChild(mText4);
    mText5=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "NONE");
    addChild(mText5);
    mText6=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "NONE");
    addChild(mText6);

    actDataPtr=(YZL_ACTIVE_DATA *)actStructPointer;
    return YZF_TRUE;
}

void ViewParams::wakeupP(void *actStructPointer) {
    ViewBase::wakeupP(actStructPointer);
    actDataPtr=(YZL_ACTIVE_DATA *)actStructPointer;

    yzl_ui_draw_565a(this->bgPath,0,0,0,0,128,128);
    yzl_ui_refresh();

    mText1->instance->status=YZL_UI_CTR_EVENT_TOUCH_DOWN;
    mText1->instance->isRender=YZF_TRUE;

    armGroup->arm01->LinkTextUI(mText1);
    armGroup->arm02->LinkTextUI(mText2);
    armGroup->arm03->LinkTextUI(mText3);
    armGroup->arm04->LinkTextUI(mText4);
    armGroup->arm05->LinkTextUI(mText5);
    armGroup->arm06->LinkTextUI(mText6);
}

void ViewParams::sleepP(void *actStructPointer) {
    ViewBase::sleepP(actStructPointer);

    armGroup->arm01->CancelLink();
    armGroup->arm02->CancelLink();
    armGroup->arm03->CancelLink();
    armGroup->arm04->CancelLink();
    armGroup->arm05->CancelLink();
    armGroup->arm06->CancelLink();
}

YZF_BOOL ViewParams::deInitP() {
    return ViewBase::deInitP();
}

char *ViewParams::getViewName() {
    return "ViewParams";
}

int ViewParams::getViewId() {
    return 102;
}

void ViewParams::resetBackground(UI_Rect *rect) {
    yzl_ui_draw_565a(this->bgPath,0,0,rect->x,rect->y,rect->width,rect->height);
}

void ViewParams::ButtonUp() {
    if(ButtonSelectType == 0) {
        if(SelectIndex<5) {
            (*this)[SelectIndex]->status=YZL_UI_CTR_EVENT_TOUCH_UP;
            (*this)[SelectIndex]->isRender=YZF_TRUE;
            SelectIndex++;
            (*this)[SelectIndex]->status=YZL_UI_CTR_EVENT_TOUCH_DOWN;
            (*this)[SelectIndex]->isRender=YZF_TRUE;
        }
    }else if(ButtonSelectType == 1){
        ButtonIsDown = YZF_TRUE;
        MoveDir = 1;
    }
}

void ViewParams::ButtonDown() {
    if(ButtonSelectType == 0){
        if(SelectIndex>0) {
            (*this)[SelectIndex]->status=YZL_UI_CTR_EVENT_TOUCH_UP;
            (*this)[SelectIndex]->isRender=YZF_TRUE;
            SelectIndex--;
            (*this)[SelectIndex]->status=YZL_UI_CTR_EVENT_TOUCH_DOWN;
            (*this)[SelectIndex]->isRender=YZF_TRUE;
        }
    }else if(ButtonSelectType == 1){
        ButtonIsDown = YZF_TRUE;
        MoveDir = 0;
    }
}

void ViewParams::ButtonEnter() {
    if(ButtonSelectType == 0){
        ButtonSelectType = 1;
    }else{
        ButtonSelectType = 0;
    }
}
extern "C" YZF_RESULT yzl_ui_pop_view();

void ViewParams::ButtonEsc() {
    yzf_global_handler_add(yzl_ui_pop_view);
}

void ViewParams::actP(void *actStructPointer) {
    ViewBase::actP(actStructPointer);
    armGroup->act();
    if(ButtonIsDown){
        if(MoveDir == 1){
            if(yzf_gpio_get(GPIOE,YZF_PIN_4)==0){
                ButtonIsDown = YZF_FALSE;
            }
            armGroup->addParams(SelectIndex,(armGroup->ProgramTick-lastActTime)*0.001f);
        }else{
            if(yzf_gpio_get(GPIOE,YZF_PIN_3)==0){
                ButtonIsDown = YZF_FALSE;
            }
            armGroup->delParams(SelectIndex,(armGroup->ProgramTick-lastActTime)*0.001f);
        }
    }
    lastActTime = armGroup->ProgramTick;
}