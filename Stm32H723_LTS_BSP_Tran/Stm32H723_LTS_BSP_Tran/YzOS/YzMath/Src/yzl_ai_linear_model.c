//
// Created by 32827 on 2024/11/22.
//

#include "yzl_ai_linear_model.h"

void yzl_linear_model_init(linear_model *model){
    model->points=YZL_MEM_MANAGER.pMalloc(model->height*model->width*sizeof (linear_model_point));
    model->results=YZL_MEM_MANAGER.pMalloc(model->height*(sizeof (linear_model_result)));
    memset(model->points,0,model->height*model->width*sizeof (linear_model_point));
    memset(model->results,0,model->height*sizeof (linear_model_result));
}


void yzl_linear_model_complete(linear_model *model){
    for(y_i32 i=0; i < model->height; i++){
        linear_model_point *p_st=&model->points[i*model->width];
        linear_model_point *p_ed=&model->points[(i+1)*model->width];
        y_i32 count=model->width;

        y_f64 avg_x= yzl_math_avg_f32( &p_st->x, sizeof (linear_model_point)/sizeof (y_f32), model->width);

        y_f64 temp1=0;
        y_f64 temp2=0;
        y_f64 temp3=0;

        for (linear_model_point  *j = p_st;j<p_ed; j++) {
            temp1+=j->y*(j->x-avg_x);
            temp2+=(j->x*j->x);
            temp3+=j->x;
        }
        temp3 = temp3*temp3/(y_f32)count;

        temp1/=10000.0f;
        temp2/=10000.0f;
        temp3/=10000.0f;

        if((temp2-temp3)==0){
            model->results[i].w=0;
        }else{
            model->results[i].w = temp1/(temp2-temp3);
        }
        y_f64 b_temp1=0;
        for (linear_model_point  *j = p_st;j<p_ed; j++) {
            b_temp1+=((y_f64)j->y-(y_f64)(j->x*model->results[i].w));
        }
        model->results[i].b = b_temp1/(y_f64)count;
    }
}

void yzl_linear_model_deinit(linear_model *model){
    YZL_MEM_MANAGER.pFree(model->points);
    YZL_MEM_MANAGER.pFree(model->results);
}
