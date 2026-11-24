# YzMiniUI

### 主要使用C++进行开发，但同时支持C开发，动画等将在未来开发，是个简单的UI系统

---

## 生命周期相关

---

### 首个界面初始化

```c
    // 从全局表中取UI_ROOT的地址，UI初始化线程会将地址放入全局表
    // 该程序应该确保在其后使用
    uiRoot=(YZL_UI_ROOT *) yzf_global_data_get(yz_status_sheet_get(YZ_SHEET_POINTER_FOR_UI_ROOT));

    // 在UI_ROOT中创建首层View,ViewMenu以显示,ViewTop++使其指向下一个可用内存
    // 以完成内存初始化
    uiRoot->ViewTop++;
    mainMenu=new ViewMenu(&YZL_TopView((*uiRoot)),bgImg,armGroup);

    // 在全局表中配置首层View地址
    // 告诉UI初始化线程要执行首个初始化声明周期的界面的地址
    YZF_GLOBAL_INDEX index=yzf_global_data_add(&YZL_TopView((*uiRoot)));
    yz_status_sheet_set(YZ_SHEET_POINTER_FOR_UI_VIEW,index);

    //在全局表中配置初始化数据指针，告诉UI线程初始化对应UI所需要的数据指针
    YZF_GLOBAL_INDEX index2=yzf_global_data_add(YZF_NULL_PTR);
    yz_status_sheet_set(YZ_SHEET_POINTER_FOR_UI_VIEW_INIT_DATA,index2);
```


### 关于生命周期

    new -> init -> wakeup -> act -> draw -> act -> draw -> ... ->sleep -> deInit(delete)

其中sleep状态可以 -> wakeup状态


### 关于加载下一个View

```c

//从全局表中获取UI_ROOT地址
YZL_UI_ROOT *root = (YZL_UI_ROOT *) yzf_global_data_get(yz_status_sheet_get(YZ_SHEET_POINTER_FOR_UI_ROOT));

//在UI_ROOT的下一个View内存中创建新的View界面
viewParamsPole = new ViewParamsPole(&YZL_NextTopView((*root)),YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMenu,w)->bgPath,YZL_UI_WIDGET_PARENT_CPP_INSTANCE(ViewMenu,w)->armGroup);

//创建自动初始化推入函数
yzf_global_handler_add(yzl_ui_push_view);
```

### 关于推出当前View

```c
//直接调用弹出函数
yzf_global_handler_add(yzl_ui_pop_view);
```

### 关于对象的其他宏定义

```c
YZL_UI_WIDGET_PARENT_CPP_INSTANCE(type,x) //获取控件的父View(C++实例对象)
YZL_NextTopView(x)                        //获取下一个View空间
YZL_TopView(x)                            //获取顶部空间
```

## 线程相关

---

YzMiniUI共有2个进程线
+ yzl_ui_boot (初始化UI_ROOT)
    - yzl_ui_boot_view_init (等待第一个View,引导生命周期)
    - yzl_ui_loop (UI主循环)
    - yzl_ui_init_done (初始化回调)
+ yzl_ui_main_view_boot (第一个View初始化)

 yzl_ui_boot 引导UI_ROOT初始化，并设置UI_ROOT的全局表，然后将yzl_ui_boot_view_init
放入进程池等待第一个View的设置，然后将主循环yzl_ui_loop放入，并产生yzl_ui_init_done回调。

 yzl_ui_main_view_boot 引导第一个View的初始化，由用户编写.