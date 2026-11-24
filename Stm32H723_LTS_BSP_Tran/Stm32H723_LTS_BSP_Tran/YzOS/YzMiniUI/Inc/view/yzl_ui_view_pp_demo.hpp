//
// Created by 32827 on 2024/2/1.
//

#ifndef YZL_UI_VIEW_PP_DEMO_H
#define YZL_UI_VIEW_PP_DEMO_H

#include "view/yzl_ui_view_pp_base.hpp"
#include "widget/yzl_ui_widget_pp_text_button.hpp"
#include "widget/yzl_ui_widget_pp_text.hpp"
#include "yzl_ui_pp_layout_base_ver.hpp"

class ViewDemo : public ViewBase {
public:
    WidgetText *mText1,*mText2,*mText3,*mText4,*mText5,*mText6,*mText7,*mText8;
    LayoutVertical *layout;
    char *logoPath;
    char *personPath;

    ViewDemo(YZL_VIEW *viewRam, char *logoPath,char *personPath);

    ~ViewDemo();

    YZF_BOOL initP(void *initStructPointer, void *actStructPointer) override;

    void wakeupP(void *actStructPointer) override;

    char *getViewName() override;

    int getViewId() override;

    void resetBackground(UI_Rect *rect) override;
};

#endif //YZL_UI_VIEW_PP_DEMO_H
