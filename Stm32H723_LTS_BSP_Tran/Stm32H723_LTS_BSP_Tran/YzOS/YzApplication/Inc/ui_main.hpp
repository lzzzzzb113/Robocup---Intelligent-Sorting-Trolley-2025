//
// Created by 32827 on 2025/9/14.
//

#ifndef STM32H723_LTS_BSP_TRAN_UI_MAIN_HPP
#define STM32H723_LTS_BSP_TRAN_UI_MAIN_HPP

#include "view/yzl_ui_view_pp_base.hpp"
#include "widget/yzl_ui_widget_pp_text_button.hpp"
#include "layout/yzl_ui_pp_layout_base_ver.hpp"
#include "yzl_space_sensor_arm_pole.hpp"

class ViewMain : public ViewBase{
public:
    WidgetTextButton *mText1,*mText2,*mText3,*mText4,*mText5,*mText6;
    LayoutVertical *layout;
    YZL_ACTIVE_DATA *actDataPtr;
    char *bgPath;

    SpaceSensorArmPole *poleArm;
    int moveDir;

    ViewMain(YZL_VIEW *viewRam, char *bgPath);
    ~ViewMain();

    YZF_BOOL initP(void *initStructPointer, void *actStructPointer) override;

    void wakeupP(void *actStructPointer) override;

    char * getViewName() override;
    int getViewId() override;

    void resetBackground(UI_Rect *rect) override;

    int SelectIndex;
    void ButtonUp();
    void ButtonDown();
    void ButtonEnter();
    void ButtonEsc();

    static void ButtonRGBCallListener(void *widget, YZL_UI_CTR_EVENT event);
    static void ButtonGyroCallListener(void *widget, YZL_UI_CTR_EVENT event);

    void actP(void *actStructPointer) override;
};

#endif //STM32H723_LTS_BSP_TRAN_UI_MAIN_HPP
