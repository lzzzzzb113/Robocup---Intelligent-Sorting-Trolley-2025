//
// Created by 32827 on 2025/3/21.
//

#ifndef YZL_UI_THREAD_H
#define YZL_UI_THREAD_H
#include "yzx_base.h"
#include "yzl_ui.h"

#ifdef __cplusplus
extern "C" {
#endif
extern YZF_RESULT yzl_ui_init_done();

YZF_RESULT yzl_ui_boot();

YZF_RESULT yzl_ui_view_boot();

YZF_RESULT yzl_ui_boot_view_init();

YZF_RESULT yzl_ui_loop();

YZF_RESULT yzl_ui_push_view();

YZF_RESULT yzl_ui_pop_view();

#ifdef __cplusplus
};
#endif


#endif //YZL_UI_THREAD_H
