//
// Created by 32827 on 2025/5/7.
//

#ifndef STM32H723_LTS_BSP_UI_VIEW_STARTUP_MENU_HPP
#define STM32H723_LTS_BSP_UI_VIEW_STARTUP_MENU_HPP

#include "view/yzl_ui_view_pp_base.hpp"
#include "widget/yzl_ui_widget_pp_text_button.hpp"
#include "widget/yzl_ui_widget_pp_text.hpp"
#include "yzl_ui_pp_layout_base_ver.hpp"

#include "ui_view_params.hpp"
#include "ArmGroup.hpp"
#include "ui_view_pole_params.hpp"
#include "ui_view_camera_params.hpp"

#include "yzl_space_sensor_camera.hpp"
#include "yzl_space_sensor_arm_2d_pole.hpp"

typedef enum {
    PROGRAM_NOP,
    PROGRAM_CAPTURE,
    PROGRAM_RESET
} ProgramStatus;

class ViewMenu : public ViewBase {
public:
    WidgetTextButton *mText1,*mText2,*mText3,*mText4,*mText5,*mText6;
    LayoutVertical *layout;
    char *bgPath;
    YZL_ACTIVE_DATA *actDataPtr;

    ArmGroup *armGroup;
    CameraInstance *cameraInstance;
    Wall *wall;
    SpaceSensorArmPole2D *arm2d;
    ProgramStatus programStatus;
    YZF_FLAG ReqLock;

    static YZL_GPIO armh_dir,armv_dir;
    int speed_now;

    ViewMenu(YZL_VIEW *viewRam, char *bgPath,ArmGroup *armGroup);

    ~ViewMenu();

    YZF_BOOL initP(void *initStructPointer, void *actStructPointer) override;

    void wakeupP(void *actStructPointer) override;

    char *getViewName() override;

    int getViewId() override;

    void resetBackground(UI_Rect *rect) override;

    void actP(void *actStructPointer) override;

    int SelectIndex;
    void ButtonUp();
    void ButtonDown();
    void ButtonEnter();
    void ButtonEsc();

    static YZF_RESULT CameraStatusListener(void *viewMenu, CameraStatus event);
    static YZF_RESULT CameraRequestListener(void *viewMenu, CameraRequestStatus event,YZF_RECV_AREA *data);
    static void ButtonResetListener(void *widget, YZL_UI_CTR_EVENT event);
    static void ButtonCaptureListener(void *widget, YZL_UI_CTR_EVENT event);
    static void ButtonTestListener(void *widget, YZL_UI_CTR_EVENT event);
    static void ButtonBackListener(void *widget, YZL_UI_CTR_EVENT event);
};

#endif //STM32H723_LTS_BSP_UI_VIEW_STARTUP_MENU_HPP
