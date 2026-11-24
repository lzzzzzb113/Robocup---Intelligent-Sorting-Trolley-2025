//
// Created by 32827 on 2024/1/11.
//

#ifndef YZL_UI_H
#define YZL_UI_H

#include "yzl_iconv.h"
#include "yzl_conf.h"
#include "yz_color.h"
#include "yzl_font.h"

#ifdef __cplusplus
extern "C" {
#endif

#if YZSCREEN

typedef enum{
    YZL_UI_CTR_EVENT_NONE,
    YZL_UI_CTR_EVENT_TOUCH_DOWN,
    YZL_UI_CTR_EVENT_TOUCH_UP,
    YZL_UI_CTR_EVENT_TOUCH_MOVE,
    YZL_UI_CTR_EVENT_SELECTED,
    YZL_UI_CTR_EVENT_VIEW_ADD_CHILD,
    YZL_UI_CTR_EVENT_VIEW_REMOVE_CHILD,
} YZL_UI_CTR_EVENT;

typedef struct{
    int32_t x;
    int32_t y;
} YZL_TouchPoint;

typedef struct {
    void *parent;                                   //父节点View
    uint16_t id;
    uint16_t x;
    uint16_t y;
    int16_t z;                                      //Z越大越在上层
    uint16_t width;
    uint16_t height;
    uint16_t status;                                //状态保存
    YZF_BOOL isRender;                              //是否需要重新渲染
    uint32_t data[YZL_UI_WIDGET_DATA_SRAM_SIZE/4];  //控件自行分配
    void (*draw)(void *widget);                                             //由具体控件实现
    YZF_BOOL (*touch)(uint16_t x,uint16_t y,YZL_UI_CTR_EVENT event,void *widget);   //由具体控件实现
    void (*dispose)(void *widget);
} YZL_WIDGET;

typedef struct{
  YZL_WIDGET *pWidget;                              //控件
  char *ViewName;                                   //名字
  uint16_t WidgetCount;                             //控件数量
  uint16_t ViewId;                                  //识别号
  void *pViewData;                                  //数据
  ///@param actStructPointer UI活动数据指针
  ///@param initStructPointer UI初始化数据指针
  YZF_BOOL (*init)(void *initStructPointer,void *actStructPointer); //初始化
  void (*act)(void *actStructPointer);              //活动
  void (*sleep)(void *actStructPointer);            //休眠
  void (*wakeup)(void *actStructPointer);           //唤醒
  ///@param actStructPointer 保留参数
  void (*draw)(void *actStructPointer);            //绘制
  YZF_BOOL (*deInit)(void *actStructPointer);       //销毁
} YZL_VIEW;

typedef struct {
    ///View数据栈
    int8_t  ViewTop;                                //View 栈顶
    YZL_VIEW pView[YZL_UI_VIEW_DEEP_MAX];           //View 数据
} YZL_UI_ROOT;

typedef struct {
    YZL_TouchPoint PointTemp[YZ_SCREEN_MAX_TOUCH];  //上一次点击数据
    YZL_TouchPoint Point[YZ_SCREEN_MAX_TOUCH];      //本次点击数据
    uint8_t touchSize;                              //触摸点数量
}YZL_TOUCH_DATA;

typedef struct {
    YZL_UI_CTR_EVENT Event;                         //控制操作
    YZL_UI_ROOT *root;                              //UI根节点
    YZL_TOUCH_DATA *touch_data;                     //触摸数据
    YZL_VIEW *handleView;                           //当前操作的View
    void *Data;                                     //其他控制数据
}YZL_ACTIVE_DATA;

#define YZL_UI_WIDGET_DATA_VALUE(type,widget) ((type *)(&((YZL_WIDGET *)widget)->data))    //取出 data
#define YZL_NextTopView(x) x.pView[x.ViewTop+1]           //顶部View
#define YZL_TopView(x) x.pView[x.ViewTop]           //顶部View
#define YZL_PreTopView(x) x.pView[(x.ViewTop-1)]    //前一个View
#define YZL_UI_WIDGET_PARENT(x) ((YZL_VIEW *)((YZL_WIDGET *)x)->parent)
#define YZL_UI_WIDGET_PARENT_CPP_INSTANCE(type,x) ((type *)(((ViewBaseData *)((YZL_VIEW *)((YZL_WIDGET *)x)->parent)->pViewData)->p_this))

extern YZ_COLOR YZL_UI_Background;
extern YZF_BOOL YZL_UI_IS_INIT;


YZF_RESULT yzl_ui_init(YZ_COLOR background);

YZF_RESULT yzl_ui_clear_screen(void);

YZF_RESULT yzl_ui_fill_screen(YZ_COLOR color);

YZF_RESULT yzl_ui_draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, YZF_BOOL isFill, YZ_COLOR color);

YZF_RESULT yzl_ui_draw_circle(uint16_t x, uint16_t y, uint16_t radius, YZF_BOOL isFill, YZ_COLOR color);

YZF_RESULT yzl_ui_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, YZ_COLOR color);

YZF_RESULT yzl_ui_draw_pixel(uint16_t x1, uint16_t y1, YZ_COLOR color);

///@param alphaColor 被屏蔽的颜色
YZF_RESULT yzl_ui_draw_pixels_ex(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, YZ_COLOR *img, YZ_COLOR alphaColor);

YZF_RESULT yzl_ui_draw_pixels(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height, YZ_COLOR *img);

YZF_RESULT yzl_ui_draw_string(uint16_t x, uint16_t y, uint16_t limitX, uint16_t *str, uint16_t len, YZ_COLOR back_color,
                              YZ_COLOR text_color);

YZF_RESULT yzl_ui_get_pixel(uint16_t x, uint16_t y, YZ_COLOR *color);

YZF_RESULT yzl_ui_get_pixels_line(uint16_t x, uint16_t y, uint16_t width, YZ_COLOR *color);

YZF_RESULT yzl_ui_refresh();


#if YZ_SCREEN_DRIVER==YZ_SCREEN_DRIVER_ILI9341
#define YZL_UI_ILI9341
#elif YZ_SCREEN_DRIVER==YZ_SCREEN_DRIVER_TLI4384
#define YZL_UI_TLI4384
#elif YZ_SCREEN_DRIVER==YZ_SCREEN_DRIVER_I2C_1306
#define YZL_UI_1306
#elif YZ_SCREEN_DRIVER==YZ_SCREEN_DRIVER_ST7735S
#define YZL_UI_ST7735S
#endif


YZF_BOOL yzl_ui_point_check(YZL_WIDGET *pWidget, uint16_t x, uint16_t y);

YZF_BOOL yzl_ui_draw_img(char *path, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

//注意YZ_COLOR 设置
YZF_BOOL yzl_ui_draw_565a(char *path, uint16_t x, uint16_t y,uint16_t mask_x,uint16_t mask_y,uint16_t mask_width,uint16_t mask_height);

#endif

#ifdef __cplusplus
}
#endif

#endif //YZL_UI_H
