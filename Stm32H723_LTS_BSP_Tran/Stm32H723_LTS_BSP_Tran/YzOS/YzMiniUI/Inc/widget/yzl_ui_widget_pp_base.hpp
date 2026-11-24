//
// Created by 32827 on 2024/2/1.
//

#ifndef YZL_UI_WIDGET_PP_BASE_HPP
#define YZL_UI_WIDGET_PP_BASE_HPP

#include "yzx_base.h"
#include "yzl_ui_pp_def.hpp"
#include "yzl_ui.h"

class WidgetBase{
    //C:View dispose ->del ~WidgetBase() -> disposeP()
    //C++:View del ~WidgetBase() -> disposeP()
public:
    YZL_WIDGET *instance;           //C 层实例
    YZF_BOOL isBackup=YZF_FALSE;    //是否已经备份
    YZF_BOOL isViewReset=YZF_FALSE;  //是否由View恢复背景
    Yz_Color *recover;              //备份的被覆盖的显存内容
    WidgetBase(YZL_WIDGET *Ram,int x, int y,int z, int width, int height);
    virtual ~WidgetBase();

    void setSize(int x, int y,int z, int width, int height) const;

    virtual void drawP();

    virtual YZF_BOOL touchP(uint16_t x,uint16_t y,YZL_UI_CTR_EVENT event);

    virtual void disposeP();

    void BackUp();
    void RollBack();
    void RollBack(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    void Restore();
    //兼容C层的调用
    static void draw(void *widget);                                             //由具体控件实现
    static YZF_BOOL touch(uint16_t x,uint16_t y,YZL_UI_CTR_EVENT event,void *widget);   //由具体控件实现
    static void dispose(void *widget);
};
#endif //YZL_UI_WIDGET_PP_BASE_HPP
