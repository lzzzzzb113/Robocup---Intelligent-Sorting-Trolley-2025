//
// Created by 32827 on 2025/5/11.
//

#include "../inc/ui_view_camera_params.hpp"

ViewCameraParams::ViewCameraParams(YZL_VIEW *viewRam, char *bgPath,ArmGroup *armGroup,CameraInstance *cameraInstance) : ViewBase(viewRam) {
    this->bgPath = bgPath;
    this->armGroup = armGroup;
    this->cameraInstance = cameraInstance;
    this->SelectIndex = 0;
}

void ViewCameraParams::ButtonUp() {
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

void ViewCameraParams::ButtonDown() {
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

void ViewCameraParams::ButtonEnter() {
    if(ButtonSelectType == 0){
        actDataPtr->Event=YZL_UI_CTR_EVENT_SELECTED;
        actDataPtr->Data=&SelectIndex;
    }else{
        ButtonSelectType = 0;
    }
}
extern "C" YZF_RESULT yzl_ui_pop_view();
void ViewCameraParams::ButtonEsc() {
    yzf_global_handler_add(yzl_ui_pop_view);
}

YZF_BOOL ViewCameraParams::initP(void *initStructPointer, void *actStructPointer) {
    ViewBase::initP(initStructPointer, actStructPointer);

    layout=new LayoutVertical(this);
    layout->setRange(0,0,YZ_SCREEN_WIDTH,YZ_SCREEN_HEIGHT,6);
    layout->setMargin(0);

    mText1=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "request");
    mText1->setListener(request_camera_view_default_listener);
    addChild(mText1);
    mText2=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "NONE");
    mText2->setListener(update_camera_view_default_listener);
    addChild(mText2);
    mText3=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "NONE");
    addChild(mText3);
    mText4=new WidgetTextButton((*this)[-1],layout->nextRect(),0,
                                (utf8 *) "request2");
    mText4->setListener(request_camera_view_default_listener2);
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

YZF_BOOL ViewCameraParams::deInitP() {
    return ViewBase::deInitP();
}

void ViewCameraParams::wakeupP(void *actStructPointer) {
    ViewBase::wakeupP(actStructPointer);

    mText1->instance->status=YZL_UI_CTR_EVENT_TOUCH_DOWN;
    mText1->instance->isRender=YZF_TRUE;
}

void ViewCameraParams::sleepP(void *actStructPointer) {
    ViewBase::sleepP(actStructPointer);
}

char *ViewCameraParams::getViewName() {
    return "ViewCameraParams";
}

int ViewCameraParams::getViewId() {
    return 104;
}

void ViewCameraParams::resetBackground(UI_Rect *rect) {
    yzl_ui_draw_565a(this->bgPath,0,0,rect->x,rect->y,rect->width,rect->height);
}

void ViewCameraParams::actP(void *actStructPointer) {
    ViewBase::actP(actStructPointer);
    armGroup->act();
    cameraInstance->act();
}

void ViewCameraParams::update_camera_view_default_listener(void *widget, YZL_UI_CTR_EVENT event) {
    if(event==YZL_UI_CTR_EVENT_TOUCH_UP||event==YZL_UI_CTR_EVENT_SELECTED){
        WidgetTextButton *w=(WidgetTextButton *)widget;
        YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewCameraParams,w)->cameraInstance->setStatusListener(YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewCameraParams,w),camera_listener);
        YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewCameraParams,w)->cameraInstance->UpdateCamera();
    }
}

void ViewCameraParams::request_camera_view_default_listener(void *widget, YZL_UI_CTR_EVENT event) {
    if(event==YZL_UI_CTR_EVENT_TOUCH_UP||event==YZL_UI_CTR_EVENT_SELECTED){
        WidgetTextButton *w=(WidgetTextButton *)widget;
        YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewCameraParams,w)->cameraInstance->setRequestListener(YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewCameraParams,w),camera_requestListener);
        YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewCameraParams,w)->cameraInstance->RequestCamera('0'+1);
    }
}
void ViewCameraParams::request_camera_view_default_listener2(void *widget, YZL_UI_CTR_EVENT event) {
    if(event==YZL_UI_CTR_EVENT_TOUCH_UP||event==YZL_UI_CTR_EVENT_SELECTED){
        WidgetTextButton *w=(WidgetTextButton *)widget;
        YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewCameraParams,w)->cameraInstance->setRequestListener(YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewCameraParams,w),camera_requestListener);
        YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewCameraParams,w)->cameraInstance->RequestCamera('0'+2);
    }
}

YZF_RESULT ViewCameraParams::camera_listener(void *viewMenu, CameraStatus event) {
    ((ViewCameraParams*)viewMenu)->cameraInstance->cameraStatus=event;
    ((ViewCameraParams*)viewMenu)->mText2->setText((utf8 *) (event == DISCONNECT ? "DISCONNECT" : "CONNECTING"));
    return  YZF_OK;
}
extern uint8_t recv_temp[120];
YZF_RESULT ViewCameraParams::camera_requestListener(void *viewMenu, CameraRequestStatus event, YZF_RECV_AREA *data) {
    if(event==REQUEST_SUCCESS){
        memset(recv_temp,0,120);
        int len;
        len = yzf_area_recv_get_size(data);
        for (int i = 0; i < len; i++) {
            recv_temp[i]=yzf_area_recv_get(data);
        }
        recv_temp[len]='\0';
        int count;
        CameraDetectResult *result=((ViewCameraParams*)viewMenu)->cameraInstance->CameraInfoDecode((char *)recv_temp,&count);
        ((ViewCameraParams*)viewMenu)->mText3->setText((utf8 *) result->tag);
    }else{
        ((ViewCameraParams*)viewMenu)->mText3->setText((utf8 *) ("R_FAIL"));
    }
    return YZF_OK;
}

