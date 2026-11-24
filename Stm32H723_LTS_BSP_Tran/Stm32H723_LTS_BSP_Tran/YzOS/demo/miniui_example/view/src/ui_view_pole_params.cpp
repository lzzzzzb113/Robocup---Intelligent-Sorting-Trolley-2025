//
// Created by 32827 on 2025/5/10.
//

#include "../inc/ui_view_pole_params.hpp"

ViewParamsPole::ViewParamsPole(YZL_VIEW *viewRam, char *bgPath, ArmGroup *armGroup): ViewBase(viewRam) {
    this->bgPath = bgPath;
    this->SelectIndex = 0;
    this->armGroup = armGroup;
}

YZF_BOOL ViewParamsPole::initP(void *initStructPointer, void *actStructPointer) {
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
                                (utf8 *) "复位测试");
    mText3->setListener(reset_listener);
    addChild(mText3);
    mText4=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "装配测试");
    mText4->setListener(zp_listener);
    addChild(mText4);
    mText5=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "抓取测试");
    mText5->setListener(zq_listener);
    addChild(mText5);
    mText6=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "NONE");
    addChild(mText6);

    actDataPtr=(YZL_ACTIVE_DATA *)actStructPointer;
    return YZF_TRUE;
}

void ViewParamsPole::wakeupP(void *actStructPointer) {
    ViewBase::wakeupP(actStructPointer);

    actDataPtr=(YZL_ACTIVE_DATA *)actStructPointer;

    yzl_ui_draw_565a(this->bgPath,0,0,0,0,128,128);
    yzl_ui_refresh();

    mText1->instance->status=YZL_UI_CTR_EVENT_TOUCH_DOWN;
    mText1->instance->isRender=YZF_TRUE;

    armGroup->arm07->LinkTextUI(mText1);
    armGroup->arm08->LinkTextUI(mText2);
}

char *ViewParamsPole::getViewName() {
    return "PoleParamsView";
}

int ViewParamsPole::getViewId() {
    return 103;
}

void ViewParamsPole::resetBackground(UI_Rect *rect) {
    yzl_ui_draw_565a(this->bgPath,0,0,rect->x,rect->y,rect->width,rect->height);
}
extern "C" YZF_RESULT yzl_ui_pop_view();

void ViewParamsPole::ButtonUp() {
    if(ButtonSelectType == 0) {
        if(SelectIndex<5) {
            (*this)[SelectIndex]->status=YZL_UI_CTR_EVENT_TOUCH_UP;
            (*this)[SelectIndex]->isRender=YZF_TRUE;
            SelectIndex++;
            (*this)[SelectIndex]->status=YZL_UI_CTR_EVENT_TOUCH_DOWN;
            (*this)[SelectIndex]->isRender=YZF_TRUE;
        }
    }else if(ButtonSelectType == 1){
        armGroup->addParams(SelectIndex+6,1000);
        ButtonIsDown = YZF_TRUE;
        MoveDir = 1;
    }
}

void ViewParamsPole::ButtonDown() {
    if(ButtonSelectType == 0){
        if(SelectIndex>0) {
            (*this)[SelectIndex]->status=YZL_UI_CTR_EVENT_TOUCH_UP;
            (*this)[SelectIndex]->isRender=YZF_TRUE;
            SelectIndex--;
            (*this)[SelectIndex]->status=YZL_UI_CTR_EVENT_TOUCH_DOWN;
            (*this)[SelectIndex]->isRender=YZF_TRUE;
        }
    }else if(ButtonSelectType == 1){
        armGroup->delParams(SelectIndex+6,1000);
        ButtonIsDown = YZF_TRUE;
        MoveDir = 0;
    }
}

void ViewParamsPole::ButtonEnter() {
    actDataPtr->Event=YZL_UI_CTR_EVENT_SELECTED;
    actDataPtr->Data=&SelectIndex;
}
//extern int Status_zq;//抓取
void ViewParamsPole::ButtonEsc() {
//    Status_zq = 100;
    yzf_global_handler_add(yzl_ui_pop_view);
}

void ViewParamsPole::actP(void *actStructPointer) {
    ViewBase::actP(actStructPointer);
    armGroup->act();
    if(ButtonIsDown){
        if(MoveDir == 1){
            if(yzf_gpio_get(GPIOE,YZF_PIN_4)==0){
                ButtonIsDown = YZF_FALSE;
            }
        }else{
            if(yzf_gpio_get(GPIOE,YZF_PIN_3)==0){
                ButtonIsDown = YZF_FALSE;
            }
        }
    }
    lastActTime = armGroup->ProgramTick;
}

void ViewParamsPole::sleepP(void *actStructPointer) {
    ViewBase::sleepP(actStructPointer);

    armGroup->arm07->CancelLink();
}

//复位
//extern int Status_RESET;
//extern "C" YZF_RESULT robot_reset();
void ViewParamsPole::reset_listener(void *widget, YZL_UI_CTR_EVENT event) {
    if(event==YZL_UI_CTR_EVENT_TOUCH_UP||event==YZL_UI_CTR_EVENT_SELECTED){
//        yzf_global_handler_add(robot_reset);
//        Status_RESET = 0;
    }
}

//装配
//extern int Status_zp;//装配
//extern "C" YZF_RESULT robot_zp();
void ViewParamsPole::zp_listener(void *widget, YZL_UI_CTR_EVENT event) {
    if(event==YZL_UI_CTR_EVENT_TOUCH_UP||event==YZL_UI_CTR_EVENT_SELECTED){
//        yzf_global_handler_add(robot_zp);
//        Status_zp = 0;
    }
}

//抓取
//extern "C" YZF_RESULT robot_zq();
void ViewParamsPole::zq_listener(void *widget, YZL_UI_CTR_EVENT event) {
    if(event==YZL_UI_CTR_EVENT_TOUCH_UP||event==YZL_UI_CTR_EVENT_SELECTED){
//        yzf_global_handler_add(robot_zq);
//        Status_zq = 0;
    }
}