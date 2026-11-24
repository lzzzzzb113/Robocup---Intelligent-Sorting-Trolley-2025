//
// Created by 32827 on 2025/3/21.
//
#include "yzl_ui_thread.h"
#include "yz_status.h"

YZL_UI_ROOT UI_ROOT;
YZL_TOUCH_DATA UI_TOUCH_DATA;
YZL_ACTIVE_DATA UI_ACTIVE_DATA;
YZF_RESULT yzl_ui_boot(){
    /** init Root */
    UI_ROOT.ViewTop=-1;
    /** init touch data */
    UI_TOUCH_DATA.touchSize=0;
    /** init active data */
    UI_ACTIVE_DATA.root = &UI_ROOT;
    UI_ACTIVE_DATA.touch_data= &UI_TOUCH_DATA;
    UI_ACTIVE_DATA.Event = YZL_UI_CTR_EVENT_NONE;
    UI_ACTIVE_DATA.Data = YZF_NULL_PTR;

    //将UI Root的地址告知用户
    yz_status_sheet_set(YZ_SHEET_POINTER_FOR_UI_ROOT,yzf_global_data_add(&UI_ROOT));
    yzf_global_handler_add(yzl_ui_view_boot);
    return YZF_OK;
}
YZF_RESULT yzl_ui_view_boot(){
    YZF_GLOBAL_INDEX index=yz_status_sheet_get(YZ_SHEET_POINTER_FOR_UI_VIEW);
    if(index==YZF_NULL_PTR){
        return YZF_HANDLER_NOT_FINISH;
    }
    //等待用户设置初始view界面
    UI_ACTIVE_DATA.handleView = (YZL_VIEW *)yzf_global_data_get(index);
    yzf_global_handler_add(yzl_ui_boot_view_init);
    return YZF_OK;
}
YZF_RESULT yzl_ui_boot_view_init(){
    //view初始化数据
    YZF_GLOBAL_INDEX index= yz_status_sheet_get(YZ_SHEET_POINTER_FOR_UI_VIEW_INIT_DATA);
    if(index==YZF_NULL_PTR){
        return YZF_HANDLER_NOT_FINISH;
    }
    YZL_TopView(UI_ROOT).init(yzf_global_data_get(index),&UI_ACTIVE_DATA);
    YZL_TopView(UI_ROOT).wakeup(&UI_ACTIVE_DATA);

    YZL_UI_IS_INIT = YZF_TRUE;

    yzf_global_handler_add(yzl_ui_loop);
    yzf_global_handler_add(yzl_ui_init_done);
    return YZF_OK;
}
YZF_RESULT yzl_ui_loop(){
    if(YZL_UI_IS_INIT){
        YZL_TopView(UI_ROOT).act(&UI_ACTIVE_DATA);
        UI_ACTIVE_DATA.Event=YZL_UI_CTR_EVENT_NONE;
        YZL_TopView(UI_ROOT).draw(&UI_ACTIVE_DATA);  //绘制
    }
    return YZF_HANDLER_NOT_FINISH;
}

YZF_RESULT yzl_ui_push_view(){
    YZL_TopView(UI_ROOT).sleep(&UI_ACTIVE_DATA);
    UI_ROOT.ViewTop++;

    UI_ACTIVE_DATA.handleView = &YZL_TopView(UI_ROOT);
    UI_ACTIVE_DATA.Event = YZL_UI_CTR_EVENT_NONE;
    UI_ACTIVE_DATA.Data = YZF_NULL_PTR;
    YZL_TopView(UI_ROOT).init(YZF_NULL_PTR,&UI_ACTIVE_DATA);
    YZL_TopView(UI_ROOT).wakeup(&UI_ACTIVE_DATA);
    return YZF_OK;
}

YZF_RESULT  yzl_ui_pop_view(){
    YZL_TopView(UI_ROOT).sleep(&UI_ACTIVE_DATA);
    YZL_TopView(UI_ROOT).deInit(&UI_ACTIVE_DATA);
    UI_ROOT.ViewTop--;
    UI_ACTIVE_DATA.handleView = &YZL_TopView(UI_ROOT);
    UI_ACTIVE_DATA.Event = YZL_UI_CTR_EVENT_NONE;
    UI_ACTIVE_DATA.Data = YZF_NULL_PTR;
    YZL_TopView(UI_ROOT).wakeup(&UI_ACTIVE_DATA);
    return YZF_OK;
}