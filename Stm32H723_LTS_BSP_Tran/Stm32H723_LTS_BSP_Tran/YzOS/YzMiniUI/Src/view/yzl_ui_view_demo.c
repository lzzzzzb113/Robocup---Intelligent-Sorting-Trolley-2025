//
// Created by 32827 on 2024/1/26.
//
#include "view/yzl_ui_view_demo.h"
#include "widget/yzl_ui_label.h"
#include "yzl.h"
uint16_t yzl_ui_view_demo_idCount=0;
void yzl_ui_view_demo_soft(YZL_VIEW *view){
    YZL_VIEW_DEMO_INIT  *pdata=view->pViewData;
    uint8_t minIndex=0;
    for(int i=0;i<view->WidgetCount;i++){
        if(view->pWidget[minIndex].z>view->pWidget[i].z){
            minIndex=i;
        }
    }
    for(int i=0;i<view->WidgetCount;i++){//获取最大值Count次
        uint8_t max=minIndex;
        for(int j=0;j<view->WidgetCount;j++){//遍历数组
            if(view->pWidget[j].z>=view->pWidget[max].z){//记录最大值
                YZF_BOOL isHas=YZF_FALSE;
                for(int k=0;k<i;k++){   //判断是否已经获取
                    if(pdata->softIndex[k]==j){
                        isHas=YZF_TRUE;
                    }
                }
                if(!isHas){
                    max=j;
                }
            }
        }
        pdata->softIndex[i]=max;
    }
}
YZF_BOOL yzl_ui_view_demo_init(void *initStructPointer,void *actStructPointer){
    /** Init Widget RAM */
    YZL_ACTIVE_DATA *pdata=actStructPointer;
    pdata->handleView->pWidget=YZL_MEM_MANAGER.pMalloc(sizeof(YZL_WIDGET)*VIEW_DEMO_MAX_WIDGET_NUM);//Max 10
    pdata->handleView->WidgetCount=1;

    /** Init Widget */
    yzl_ui_view_demo_idCount=0;
    YZL_WIDGET *widget_label=pdata->handleView->pWidget;
    yzl_ui_label_create(widget_label,YZ_SCREEN_WIDTH/2-YZL_FONT_SIZE*2,0,0,YZL_FONT_SIZE*4,YZL_FONT_LINE_HEIGHT,WHITE,RED,(utf8 *)"点击开始");
    widget_label->id=yzl_ui_view_demo_idCount;
    yzl_ui_view_demo_idCount++;

    /** Init Data*/
    YZL_VIEW_DEMO_INIT *pinit=initStructPointer;
    pdata->handleView->pViewData= YZL_MEM_MANAGER.pMalloc(sizeof(YZL_VIEW_DEMO_INIT));
    memcpy(pdata->handleView->pViewData,pinit,sizeof(YZL_VIEW_DEMO_INIT));

    yzl_ui_view_demo_soft(pdata->handleView);
    return YZF_TRUE;
}
void yzl_ui_view_demo_act(void *actStructPointer){
    YZL_ACTIVE_DATA *pdata=actStructPointer;
    YZL_WIDGET *pWs=pdata->handleView->pWidget;
    //TODO: Support Mutl touch And Depth
    uint16_t ind=0xFFFF;
    switch (pdata->Event) {
        case YZL_UI_CTR_EVENT_NONE:
            return;
        case YZL_UI_CTR_EVENT_TOUCH_DOWN:
            for(int i=0;i<pdata->handleView->WidgetCount;i++){
                if(yzl_ui_point_check(pWs+i,pdata->touch_data->Point[0].x,pdata->touch_data->Point[0].y)){
                    if(pWs[i].touch(pdata->touch_data->Point[0].x,pdata->touch_data->Point[0].y,YZL_UI_CTR_EVENT_TOUCH_DOWN,pWs+i)){
                        break;
                    };
                }
            }
            return;
        case YZL_UI_CTR_EVENT_TOUCH_MOVE:
            for(int i=0;i<pdata->handleView->WidgetCount;i++){
                if(pWs[i].touch(pdata->touch_data->Point[0].x,pdata->touch_data->Point[0].y,YZL_UI_CTR_EVENT_TOUCH_MOVE,pWs+i)){
                    break;
                }
            }
            return;
        case YZL_UI_CTR_EVENT_TOUCH_UP:
            for(int i=0;i<pdata->handleView->WidgetCount;i++){
                if(pWs[i].touch(pdata->touch_data->Point[0].x,pdata->touch_data->Point[0].y,YZL_UI_CTR_EVENT_TOUCH_UP,pWs+i)){
                    break;
                }
            }
            return;
        case YZL_UI_CTR_EVENT_SELECTED:
            pWs[*(int *)pdata->Data].touch(0,0,YZL_UI_CTR_EVENT_SELECTED,pWs+(*(int *)pdata->Data));
            return;
        case YZL_UI_CTR_EVENT_VIEW_ADD_CHILD://DATA: Widget *
            if(pdata->handleView->WidgetCount>=10){
                return;
            }
            if(pdata->Data!=YZF_NULL_PTR){
                memcpy(pWs+pdata->handleView->WidgetCount,pdata->Data,sizeof(YZL_WIDGET));//添加Widget数据
            }
            pWs[pdata->handleView->WidgetCount].id=yzl_ui_view_demo_idCount;              //设置Id
            yzl_ui_view_demo_idCount++;
            pWs[pdata->handleView->WidgetCount].parent=pdata->handleView;                 //设置父控件
            pdata->handleView->WidgetCount++;
            yzl_ui_view_demo_soft(pdata->handleView);
            return;
        case YZL_UI_CTR_EVENT_VIEW_REMOVE_CHILD://DATA: uint16_t * Id
            if(pdata->handleView->WidgetCount<=0){
                return;
            }
            uint16_t id=(*(YZL_WIDGET *)pdata->Data).id;//获取索引
            for(uint16_t i=0;i<pdata->handleView->WidgetCount;i++){
                if(pWs[i].id==id){
                    ind=i;
                    break;
                }
            }
            if(ind==0xFFFF){
                return;
            }
            (pWs+ind)->dispose(pWs+ind);//调用销毁
            if(ind!=pdata->handleView->WidgetCount-1){
                memcpy(pWs+ind,pWs+pdata->handleView->WidgetCount-1,sizeof(YZL_WIDGET));//删除Widget数据
            }
            pdata->handleView->WidgetCount--;
            yzl_ui_view_demo_soft(pdata->handleView);
            return;
        default:
            return;
    }
}
void yzl_ui_view_sleep(void *actStructPointer){

}
void yzl_ui_view_wakeup(void *actStructPointer){

}
///@param drawStructPointer 保留参数
void yzl_ui_view_draw(void *actStructPointer){
    YZF_BOOL HasRender=YZF_FALSE;
    YZL_ACTIVE_DATA *pdata=actStructPointer;
    YZL_WIDGET *pWs=pdata->handleView->pWidget;
    YZL_VIEW_DEMO_INIT  *pd=pdata->handleView->pViewData;
    for(int i=0;i<pdata->handleView->WidgetCount;i++){
        if(pWs[pd->softIndex[i]].isRender){
            pWs[pd->softIndex[i]].draw(pWs+pd->softIndex[i]);
            pWs[pd->softIndex[i]].isRender=YZF_FALSE;
            HasRender=YZF_TRUE;
        }
    }
    if(HasRender){
        yzl_ui_refresh();
    }
}
YZF_BOOL yzl_ui_view_deInit(void *actStructPointer){
    YZL_ACTIVE_DATA *pdata=actStructPointer;
    for(int i=0;i<pdata->handleView->WidgetCount;i++){      /** 销毁控件 */
        pdata->handleView->pWidget[i].dispose(&pdata->handleView->pWidget[i]);
    }
    YZL_MEM_MANAGER.pFree(pdata->handleView->pWidget);              /** 销毁View */
    YZL_MEM_MANAGER.pFree(pdata->handleView->pViewData);
    return YZF_TRUE;
}
char *demoName="ViewDemo";
YZF_RESULT yzl_ui_view_demo_create(YZL_VIEW *viewRam){
    viewRam->init=yzl_ui_view_demo_init;
    viewRam->act=yzl_ui_view_demo_act;
    viewRam->sleep=yzl_ui_view_sleep;
    viewRam->wakeup=yzl_ui_view_wakeup;
    viewRam->draw=yzl_ui_view_draw;
    viewRam->deInit=yzl_ui_view_deInit;
    viewRam->ViewId=0x5000;//NeedChange
    viewRam->ViewName=demoName;
    return YZF_OK;
}
