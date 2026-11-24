//
// Created by 32827 on 2025/9/14.
//

#include "ui_main.hpp"
#include "yz_tim.h"
ViewMain::ViewMain(YZL_VIEW *viewRam, char *bgPath ) : ViewBase( viewRam){
    this->bgPath = bgPath;
    this->SelectIndex = 0;
    Pose defaultPose(0,0,0);
    this->moveDir = 1;//单向正转，即只为正数
}

YZF_BOOL ViewMain::initP(void *initStructPointer, void *actStructPointer) {
    ViewBase::initP(initStructPointer, actStructPointer);

    layout=new LayoutVertical(this);
    layout->setRange(0,0,YZ_SCREEN_WIDTH,YZ_SCREEN_HEIGHT,6);
    layout->setMargin(2);

    mText1=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "RGBCall");
    addChild(mText1);
    mText1->setListener(ButtonRGBCallListener);
    mText2=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "GYRO");
    addChild(mText2);
    mText2->setListener(ButtonGyroCallListener);
    mText3=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "XXX,XXX,XXX");
    addChild(mText3);
    mText4=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "XXX,XXX,XXX");
    addChild(mText4);
    mText5=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "XXX,XXX,XXX");
    addChild(mText5);
    mText6=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "XXX,XXX,XXX");
    addChild(mText6);
    actDataPtr=(YZL_ACTIVE_DATA *)actStructPointer;

    return YZF_TRUE;
}

void ViewMain::wakeupP(void *actStructPointer) {
    ViewBase::wakeupP(actStructPointer);

    yzl_ui_draw_565a(this->bgPath,0,0,0,0,128,128);
    yzl_ui_refresh();

    mText1->instance->status=YZL_UI_CTR_EVENT_TOUCH_DOWN;   //使第一个被选中
    mText1->instance->isRender=YZF_TRUE;
}

char *ViewMain::getViewName() {
    return (char *)"物流比赛主界面";
}

int ViewMain::getViewId() {
    return 914;
}

void ViewMain::resetBackground(UI_Rect *rect) {
    yzl_ui_draw_565a(this->bgPath,0,0,rect->x,rect->y,rect->width,rect->height);
}

extern int EXTIPoleDestSUM;
void ViewMain::ButtonUp() {
    if(SelectIndex<5) {
        (*this)[SelectIndex]->status=YZL_UI_CTR_EVENT_TOUCH_UP;
        (*this)[SelectIndex]->isRender=YZF_TRUE;
        SelectIndex++;
        (*this)[SelectIndex]->status=YZL_UI_CTR_EVENT_TOUCH_DOWN;
        (*this)[SelectIndex]->isRender=YZF_TRUE;
    }
}
extern "C" void getBallColor();
int inCail=0;
#include "yzl_i2c_bno085.h"
void ViewMain::ButtonDown() {
    if(SelectIndex>0) {
        (*this)[SelectIndex]->status=YZL_UI_CTR_EVENT_TOUCH_UP;
        (*this)[SelectIndex]->isRender=YZF_TRUE;
        SelectIndex--;
        (*this)[SelectIndex]->status=YZL_UI_CTR_EVENT_TOUCH_DOWN;
        (*this)[SelectIndex]->isRender=YZF_TRUE;
    }
}

void ViewMain::ButtonEnter() {
    actDataPtr->Event=YZL_UI_CTR_EVENT_SELECTED;
    actDataPtr->Data=&SelectIndex;
}

void ViewMain::ButtonEsc() {
    if(inCail){
        yzl_i2c_bno085_send_calibrate_command(I2C1, CALIBRATE_STOP);
        yzl_i2c_bno085_save_calibration(I2C1);
        inCail=0;
        mText1->setTextF((utf8 *) "STOP");
    }else{
        yzl_i2c_bno085_calibrate_all(I2C1);
        inCail=1;
        mText1->setTextF((utf8 *) "START");
    }
}

ViewMain::~ViewMain() = default;
void ViewMain::ButtonRGBCallListener(void *widget, YZL_UI_CTR_EVENT event) {
    if(event==YZL_UI_CTR_EVENT_TOUCH_UP||event==YZL_UI_CTR_EVENT_SELECTED) {
        if(inCail){
            yzl_i2c_bno085_send_calibrate_command(I2C1, CALIBRATE_STOP);
            yzl_i2c_bno085_save_calibration(I2C1);
            inCail=0;
            YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMain,widget)->mText1->setTextF((utf8 *) "STOP");
        }else{
//            yzl_i2c_bno085_calibrate_accelerometer(I2C1);
            yzl_i2c_bno085_calibrate_gyro(I2C1);
//            yzl_i2c_bno085_calibrate_all(I2C1);
            inCail=1;
            YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMain,widget)->mText1->setTextF((utf8 *) "START");
        }
    }
}

void ViewMain::actP(void *actStructPointer) {
    if(inCail){
        mText3->setTextF((utf8 *) "%d,%d,%d", yzl_i2c_bno085_get_gyro_accuracy(), yzl_i2c_bno085_get_accel_accuracy(),yzl_i2c_bno085_get_quat_accuracy());
    }
    ViewBase::actP(actStructPointer);
}

void ViewMain::ButtonGyroCallListener(void *widget, YZL_UI_CTR_EVENT event) {
    if(inCail){
        yzl_i2c_bno085_send_calibrate_command(I2C1, CALIBRATE_STOP);
        yzl_i2c_bno085_save_calibration(I2C1);
        inCail=0;
        YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMain,widget)->mText1->setTextF((utf8 *) "STOP");
    }else{
        yzl_i2c_bno085_calibrate_gyro(I2C1);
        inCail=1;
        YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMain,widget)->mText1->setTextF((utf8 *) "START");
    }
}

