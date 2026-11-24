//
// Created by 32827 on 2024/2/1.
//
#include "view/yzl_ui_view_pp_demo.hpp"
//-----------------------------------------------------------------------

ViewDemo::ViewDemo(YZL_VIEW *viewRam, char *logoPath,char *personPath): ViewBase(viewRam) {
    this->logoPath = logoPath;
    this->personPath = personPath;

    yzl_ui_draw_565a((char *)"/MMC/test.565",0,0,0,0,128,128);
    yzl_ui_refresh();
}

ViewDemo::~ViewDemo() = default;

YZF_BOOL ViewDemo::initP(void *initStructPointer, void *actStructPointer) {
    ViewBase::initP(initStructPointer, actStructPointer);

    layout=new LayoutVertical(this);
    layout->setRange(0,0,YZ_SCREEN_WIDTH,YZ_SCREEN_HEIGHT,6);
    layout->setMargin(2);

    mText1=new WidgetText((*this)[-1],layout->nextRect(),0,
                          (utf8 *) "T1C1",CYAN);
    addChild(mText1);
    mText2=new WidgetText((*this)[-1],layout->nextRect(),0,
                          (utf8 *) "T1C2",CYAN);
    addChild(mText2);
    mText3=new WidgetText((*this)[-1],layout->nextRect(),0,
                          (utf8 *) "T1C3",CYAN);
    addChild(mText3);
    mText4=new WidgetText((*this)[-1],layout->nextRect(),0,
                          (utf8 *) "T1C4",CYAN);
    addChild(mText4);
    mText5=new WidgetText((*this)[-1],layout->nextRect(),0,
                          (utf8 *) "T3C1",CYAN);
    addChild(mText5);
    mText6=new WidgetText((*this)[-1],layout->nextRect(),0,
                          (utf8 *) "T3C2",CYAN);
    addChild(mText6);
    return YZF_TRUE;
}

char *ViewDemo::getViewName() {
    return (char *)"ViewDemo";
}

int ViewDemo::getViewId() {
    return YZL_UI_VIEW_ID_VIEW_PP_DEMO;
}

void ViewDemo::wakeupP(void *actStructPointer) {
    ViewBase::wakeupP(actStructPointer);
}

void ViewDemo::resetBackground(UI_Rect *rect) {
//    yzl_ui_draw_rect(rect->x,rect->y, rect->width, rect->height, YZF_TRUE, RED);
    yzl_ui_draw_565a((char *)"/MMC/test.565",0,0,rect->x,rect->y,rect->width,rect->height);
}
