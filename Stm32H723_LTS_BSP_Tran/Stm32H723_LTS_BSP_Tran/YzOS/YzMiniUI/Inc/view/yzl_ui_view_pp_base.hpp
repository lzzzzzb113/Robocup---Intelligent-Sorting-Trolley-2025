//
// Created by 32827 on 2024/2/1.
//

#ifndef YZL_UI_VIEW_PP_BASE_HPP
#define YZL_UI_VIEW_PP_BASE_HPP

#include "yzl_ui.h"

#include "widget/yzl_ui_widget_pp_base.hpp"
#include "yzl_ui_pp_def.hpp"


/**
 * View 销毁链图
 *   / 兼容C层 /                                             / 兼容C层 /
 * View::deInit() -> View::~View()  -> View::deInitP() -> Widget::dispose() -> Widget::~Widget() -> Widget::disposeP()
 *                -> del C++相关实例  -> free C相关                           -> del C++相关实例    -> free C相关
 * 所以无需手动销毁 View C++ 实例 和 Widget C++ 实例
 * */
class ViewBase{
private:
    YZL_VIEW *instance;
public:
    ViewBase(YZL_VIEW *viewRam);
    ///C++控件实例会由View进行销毁
    virtual ~ViewBase();
    constexpr static int VIEW_WIDGET_MAX_COUNT=YZL_UI_VIEW_WIDGET_MAX_COUNT;

    uint8_t *softIndex;
    uint16_t idCount;

    virtual YZF_BOOL initP(void *initStructPointer,void *actStructPointer);
    virtual void actP(void *actStructPointer);
    virtual void sleepP(void *actStructPointer);
    virtual void wakeupP(void *actStructPointer);
    virtual void drawP(void *drawStructPointer);
    /** 背景重绘制*/
    virtual void resetBackground(UI_Rect *rect);
    virtual YZF_BOOL deInitP();
    virtual char *getViewName();                    //获取视图名称
    virtual int getViewId();                        //获取视图ID

    YZF_BOOL addChild(YZL_WIDGET *child);
    YZF_BOOL addChild(WidgetBase *child);
    YZF_BOOL delChild(YZL_WIDGET *child);
    YZF_BOOL delChild(WidgetBase *child);
    void updateSoftIndex();

    /**
     * @param i 子控件索引，如果为负数，则从最后一个子控件开始查找
     * @return 返回子控件YZL_WIDGET *
     * */
    YZL_WIDGET* operator [](int i);

    static YZF_BOOL init(void *initStructPointer,void *actStructPointer); //初始化
    static void act(void *actStructPointer);              //活动
    static void sleep(void *actStructPointer);            //休眠
    static void wakeup(void *actStructPointer);           //唤醒
    ///@param drawStructPointer 保留参数
    static void draw(void *actStructPointer);             //绘制
    ///C++控件实例会由View进行销毁
    static YZF_BOOL deInit(void *actStructPointer);       //销毁
};
#endif //YZL_UI_VIEW_PP_BASE_HPP
