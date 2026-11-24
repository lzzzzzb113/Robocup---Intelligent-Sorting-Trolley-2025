//
// Created by 32827 on 2025/5/11.
//

#ifndef STM32H723_LTS_BSP_UI_VIEW_CAMERA_PARAMS_HPP
#define STM32H723_LTS_BSP_UI_VIEW_CAMERA_PARAMS_HPP


#include "view/yzl_ui_view_pp_base.hpp"
#include "widget/yzl_ui_widget_pp_text_button.hpp"
#include "yzl_ui_pp_layout_base_ver.hpp"
#include "ArmGroup.hpp"
#include "yzl_space_sensor_camera.hpp"

class ViewCameraParams : public ViewBase{
public:

    WidgetTextButton *mText1,*mText2,*mText3,*mText4,*mText5,*mText6;
    LayoutVertical *layout;
    char *bgPath;
    YZL_ACTIVE_DATA *actDataPtr;
    ArmGroup *armGroup;


    uint32_t MoveDir=0;
    uint8_t ButtonSelectType = 0;
    YZF_BOOL ButtonIsDown = YZF_FALSE;

    CameraInstance *cameraInstance;

    ViewCameraParams(YZL_VIEW *viewRam, char *bgPath,ArmGroup *armGroup,CameraInstance *cameraInstance);
    ~ViewCameraParams() = default;

    YZF_BOOL initP(void *initStructPointer, void *actStructPointer) override;

    YZF_BOOL deInitP() override;

    void wakeupP(void *actStructPointer) override;

    void sleepP(void *actStructPointer) override;

    char *getViewName() override;

    int getViewId() override;

    void resetBackground(UI_Rect *rect) override;

    void actP(void *actStructPointer) override;

    int SelectIndex;
    void ButtonUp();
    void ButtonDown();
    void ButtonEnter();
    void ButtonEsc();


    static void update_camera_view_default_listener(void *widget, YZL_UI_CTR_EVENT event);
    static void request_camera_view_default_listener(void *widget, YZL_UI_CTR_EVENT event);
    static void request_camera_view_default_listener2(void *widget, YZL_UI_CTR_EVENT event);
    static YZF_RESULT camera_listener(void *viewMenu, CameraStatus event);
    static YZF_RESULT camera_requestListener(void *viewMenu, CameraRequestStatus event,YZF_RECV_AREA *data);
};
#endif //STM32H723_LTS_BSP_UI_VIEW_CAMERA_PARAMS_HPP
