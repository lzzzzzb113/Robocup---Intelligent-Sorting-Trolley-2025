//
// Created by 32827 on 2025/5/7.
//

#include "../inc/ui_view_startup_menu.hpp"
#include "yzl_space_sensor_action_angle.hpp"
#include "yz_uart.h"
#include "yzl_uart_tmc2209.h"
#include "yz_tim.h"

YZL_GPIO ViewMenu::armh_dir={YZF_PIN_8,GPIOD};
YZL_GPIO ViewMenu::armv_dir={YZF_PIN_9,GPIOD};

ViewMenu::~ViewMenu() = default;
extern "C" YZF_RESULT yzl_ui_push_view();
//void ViewMenu::load_params_view_default_listener(void *widget, YZL_UI_CTR_EVENT event) {
//    if(event==YZL_UI_CTR_EVENT_TOUCH_UP||event==YZL_UI_CTR_EVENT_SELECTED){
//        WidgetTextButton *w=(WidgetTextButton *)widget;
//        if(YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMenu,w)->viewParams==YZF_NULL_PTR){
//            YZL_UI_ROOT *root=(YZL_UI_ROOT *) yzf_global_data_get(yz_status_sheet_get(YZ_SHEET_POINTER_FOR_UI_ROOT));
//            YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMenu,w)->viewParams=new ViewParams(&YZL_NextTopView((*root))
//                    ,YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMenu,w)->bgPath
//                    ,YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMenu,w)->armGroup);
//            yzf_global_handler_add(yzl_ui_push_view);
//        }
//    }
//}
void ViewMenu::actP(void *actStructPointer) {
/// cameraUpdate
//    cameraInstance->act();
//    if(programStatus==PROGRAM_RESET&&ReqLock==FLAG_OFF){
//        ReqLock=FLAG_ON;
//        cameraInstance->RequestCamera('1');
//    }
    ViewBase::actP(actStructPointer);
}
YZF_BOOL ViewMenu::initP(void *initStructPointer, void *actStructPointer) {
    ViewBase::initP(initStructPointer, actStructPointer);

    layout=new LayoutVertical(this);
    layout->setRange(0,0,YZ_SCREEN_WIDTH,YZ_SCREEN_HEIGHT,6);
    layout->setMargin(2);

    mText1=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                          (utf8 *) "MotorStart");
    addChild(mText1);
    mText1->setListener(ButtonCaptureListener);
    mText2=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                          (utf8 *) "SpeedUp");
    addChild(mText2);
    mText2->setListener(ButtonResetListener);
    mText3=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                          (utf8 *) "SpeedDown");
    addChild(mText3);
    mText3->setListener(ButtonTestListener);
    mText4=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                          (utf8 *) "Back");
    addChild(mText4);
    mText4->setListener(ButtonBackListener);
    mText5=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                          (utf8 *) "NONE");
    addChild(mText5);
    mText6=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                          (utf8 *) "NONE");
    addChild(mText6);
    actDataPtr=(YZL_ACTIVE_DATA *)actStructPointer;

    return YZF_TRUE;
}

void ViewMenu::wakeupP(void *actStructPointer) {
    ViewBase::wakeupP(actStructPointer);

    yzl_ui_draw_565a(this->bgPath,0,0,0,0,128,128);
    yzl_ui_refresh();

    mText1->instance->status=YZL_UI_CTR_EVENT_TOUCH_DOWN;
    mText1->instance->isRender=YZF_TRUE;
}

char *ViewMenu::getViewName() {
    return "ViewMainMenu";
}

int ViewMenu::getViewId() {
    return 101;
}

void ViewMenu::resetBackground(UI_Rect *rect) {
    yzl_ui_draw_565a(this->bgPath,0,0,rect->x,rect->y,rect->width,rect->height);
}

void ViewMenu::ButtonUp() {
    if(SelectIndex<5) {
        (*this)[SelectIndex]->status=YZL_UI_CTR_EVENT_TOUCH_UP;
        (*this)[SelectIndex]->isRender=YZF_TRUE;
        SelectIndex++;
        (*this)[SelectIndex]->status=YZL_UI_CTR_EVENT_TOUCH_DOWN;
        (*this)[SelectIndex]->isRender=YZF_TRUE;
    }
}

void ViewMenu::ButtonDown() {
    if(SelectIndex>0) {
        (*this)[SelectIndex]->status=YZL_UI_CTR_EVENT_TOUCH_UP;
        (*this)[SelectIndex]->isRender=YZF_TRUE;
        SelectIndex--;
        (*this)[SelectIndex]->status=YZL_UI_CTR_EVENT_TOUCH_DOWN;
        (*this)[SelectIndex]->isRender=YZF_TRUE;
    }
}

void ViewMenu::ButtonEnter() {
    actDataPtr->Event=YZL_UI_CTR_EVENT_SELECTED;
    actDataPtr->Data=&SelectIndex;
}

void ViewMenu::ButtonEsc() {

}

ViewMenu::ViewMenu(YZL_VIEW *viewRam, char *bgPath, ArmGroup *armGroup) : ViewBase(viewRam) {
    this->bgPath = bgPath;
    this->SelectIndex = 0;
    this->armGroup = armGroup;
    this->programStatus = PROGRAM_NOP;
    this->ReqLock = FLAG_OFF;
}

YZF_RESULT ViewMenu::CameraStatusListener(void *viewMenu, CameraStatus event) {
    if(event==CONNECTING){
        ((ViewMenu *)(viewMenu))->mText6->setText((utf8 *)"Connect");
    }else{
        ((ViewMenu *)(viewMenu))->mText6->setText((utf8 *)"Disconnect");
    }
    return YZF_OK;
}
uint8_t recv_temp[120];
int CaptureList[8][2];
int CaptureWrite=0;
int CaptureRead=0;
YZF_RESULT ViewMenu::CameraRequestListener(void *viewMenu, CameraRequestStatus event, YZF_RECV_AREA *data) {
    if(event==REQUEST_SUCCESS){
        memset(recv_temp,0,120);
        int len;
        len = yzf_area_recv_get_size(data);
        for (int i = 0; i < len; i++) {
            recv_temp[i]=yzf_area_recv_get(data);
        }
        recv_temp[len]='\0';
        int count;
        CameraDetectResult *result=((ViewMenu *)(viewMenu))->cameraInstance->CameraInfoDecode((char *)recv_temp,&count);


        int OffsetX = result->x+result->w/2;
        int OffsetY = result->y+result->h/2;

        if (((ViewMenu *)viewMenu)->programStatus == PROGRAM_CAPTURE){
            CaptureList[CaptureWrite][0] = OffsetX;
            CaptureList[CaptureWrite][1] = OffsetY;
            CaptureWrite =  (CaptureWrite+1)%8;
            ((ViewMenu *)viewMenu)->programStatus = PROGRAM_NOP;
        }

        if(((ViewMenu *)viewMenu)->programStatus == PROGRAM_RESET){
            if((OffsetX-CaptureList[CaptureRead][0]) < 5 && (OffsetX-CaptureList[CaptureRead][0]) > -5 && (OffsetY-CaptureList[CaptureRead][1]) < 5 && (OffsetY-CaptureList[CaptureRead][1]) > -5){
                if(CaptureRead!=CaptureWrite){
                    CaptureRead =  (CaptureRead+1)%8;
                    if(CaptureRead==CaptureWrite){
                        CaptureRead = 0;
                        ((ViewMenu *)viewMenu)->programStatus = PROGRAM_NOP;
                    }
                }
            }

            ((ViewMenu *)viewMenu)->arm2d->move((float )(OffsetX-CaptureList[CaptureRead][0])*10,-(float )(OffsetY-CaptureList[CaptureRead][1])*10);
            while (((ViewMenu *)viewMenu)->arm2d->isFinish()==0);
        }
    }
    ((ViewMenu *)viewMenu)->ReqLock = FLAG_OFF;
    return YZF_OK;
}

void ViewMenu::ButtonResetListener(void *widget, YZL_UI_CTR_EVENT event) {
    if(event==YZL_UI_CTR_EVENT_TOUCH_UP||event==YZL_UI_CTR_EVENT_SELECTED){
        YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMenu,widget)->speed_now += 30;
        yz_tim_pwm_data_set(TIM1,1,YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMenu,widget)->speed_now,19999);
        YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMenu,widget)->mText6->setTextF(
                (utf8 *) "%d",
                YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMenu,widget)->speed_now);
    }
}

void ViewMenu::ButtonCaptureListener(void *widget, YZL_UI_CTR_EVENT event) {
    if(event==YZL_UI_CTR_EVENT_TOUCH_UP||event==YZL_UI_CTR_EVENT_SELECTED) {
        yz_tim_pwm_start_and_data_set(TIM1,1,274,900,19999);
        HAL_Delay(2000);
        yz_tim_pwm_data_set(TIM1,1,950,19999);
        HAL_Delay(1000);
        yz_tim_pwm_data_set(TIM1,1,1100,19999);
        YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMenu,widget)->speed_now = 1100;
        YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMenu,widget)->mText6->setTextF((utf8 *) "%d", 1100);
    }
}

void ViewMenu::ButtonTestListener(void *widget, YZL_UI_CTR_EVENT event) {
    if(event==YZL_UI_CTR_EVENT_TOUCH_UP||event==YZL_UI_CTR_EVENT_SELECTED) {
        YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMenu,widget)->speed_now -= 30;
        yz_tim_pwm_data_set(TIM1,1,YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMenu,widget)->speed_now,19999);
        YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMenu,widget)->mText6->setTextF(
                (utf8 *) "%d",
                YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMenu,widget)->speed_now);
    }
}

void ViewMenu::ButtonBackListener(void *widget, YZL_UI_CTR_EVENT event) {
    if(event==YZL_UI_CTR_EVENT_TOUCH_UP||event==YZL_UI_CTR_EVENT_SELECTED) {

    }
}
