//
// Created by 32827 on 2024/11/22.
//
#include "yzl_math.h"
#include "yzl_mem.h"

y_f32 yzl_abs_f64(y_f32 x){
    return (x > 0) ? x : -x;
}
/*
 * arcCos w/ inverse and newton's method
 * function to find roots of :  cos(x) - x
 * newton's method formula   :  xk+1 = xk - (cos(x) - x)/-sin(x)
 * 				     = xk + (cos(x) - x)/sin(x)
 */
y_f32 yzl_arccos_f32(y_f32 x) {
    if(x==1.0f){
        return 0.0f;
    }
    if(x==-1.0f){
        return YZL_M_PI;
    }
    y_f64 inp_x = 1.0; // initial guess
    y_f64 temp_res = 0.1; // xk to be compared to epsilon
    while (yzl_abs_f64(temp_res) > YZL_TRIG_EPSILON) {
        temp_res = (COS(inp_x) - x) / (y_f64)SIN(inp_x); // calculating f(xk)/f'(xk)
        inp_x += temp_res; // xk+1 += xk
    }
    return inp_x;
}

/*
 * arcTan with the formula arctan = arccos(1/sq_root(1+x^2))
 */
y_f32 yzl_arctan_f32(y_f32 x) {
    y_f32  temp;
    arm_sqrt_f32(1 + (x * x),&temp);
    return yzl_arccos_f32(1 / (temp));
}

y_f32 g_atan_tab[YZL_LUT_NUM];
void yzl_atan2_tab_init(void){
    uint32_t i = 0;

    for (i = 0; i < YZL_LUT_NUM; i++)
    {
        g_atan_tab[i] = yzl_arctan_f32((y_f32)i / (YZL_LUT_NUM - 1));
    }
}

y_f32 yzl_arcsin(y_f32 x)
{
    float d=1;
    float t=x;
    unsigned char cnt = 1;
    float result = 0;
    float X2 = x*x;

    if (x >= 1.0f)
    {
        return YZL_M_PI/2;
    }
    if (x <= -1.0f)
    {
        return -YZL_M_PI/2;
    }
    do
    {
        result += t / (d * ((cnt << 1) - 1));
        t *= X2 * ((cnt << 1) - 1);//
        d *= (cnt << 1);//2 4 6 8 10 ...
        cnt++;
    }while(cnt <= 6);

    return result;
}
y_f32 yzl_atan2_tab_calc(y_f32 y, y_f32 x){
    y_f32 Y_X, Y_X_temp;
    y_f32 result = 0;

    Y_X = (x == 0) ? (y_f32)x / y : (y_f32)y / x;
    Y_X_temp = Y_X;

    if (y == 0)
    {
        if (x >= 0)
            return 0;
        else
            return (YZL_M_PI);  //Return Pi
    }
    else if (x > 0 && y > 0)
    {
        //第一象限
        Y_X = (Y_X <= 1) ? Y_X  : 1 / Y_X;
        result = (Y_X_temp > 1)? YZL_M_PI_2 - g_atan_tab[(int16_t)(Y_X*(YZL_LUT_NUM - 1))] : g_atan_tab[(int16_t)(Y_X*(YZL_LUT_NUM - 1))];
    }
    else if (x < 0 && y > 0)
    {
        //第二象限
        Y_X = (Y_X < -1)? (-1 / Y_X) : -Y_X;
        result = (Y_X_temp >= -1) ? YZL_M_PI - g_atan_tab[(int16_t)(Y_X*(YZL_LUT_NUM - 1))] : //小于45°
                 YZL_M_PI_2 + g_atan_tab[(int16_t)(Y_X*(YZL_LUT_NUM - 1))];
    }
    else if (x < 0 && y < 0)
    {
        //第三象限
        Y_X = (Y_X <= 1) ? Y_X : 1 / Y_X;
        result = (Y_X_temp <= 1) ? g_atan_tab[(int16_t)(Y_X*(YZL_LUT_NUM - 1))] - YZL_M_PI: -YZL_M_PI_2 - g_atan_tab[(int16_t)(Y_X*(YZL_LUT_NUM - 1))];
    }
    else if(x > 0 && y < 0)
    {
        //第四象限
        Y_X = (Y_X < -1) ?(-1 / Y_X) : -Y_X;
        result = (Y_X_temp >= -1) ? -g_atan_tab[(int16_t)(Y_X*(YZL_LUT_NUM - 1))] : //小于45°
                 -(YZL_M_PI_2 - g_atan_tab[(int16_t)(Y_X*(YZL_LUT_NUM - 1))]);
    }
    else if(x == 0 && y > 0)
    {
        result = YZL_M_PI_2;
    }
    else
    {
        result = -YZL_M_PI_2;
    }

    return result;
}

y_f64 yzl_math_avg_f32(y_f32 *data,y_i32 step,y_i32 len){
    y_f64 sum = 0;
    y_i32 l=len;
    while (l--){
        sum += *data;
        data += step;
    }
    return sum/(y_f64)len;
}
y_f64 yzl_math_avg_f64(y_f64 *data,y_i32 step, y_i32 len){
    y_f64 sum = 0;
    y_i32 l=len;
    while (l--){
        sum += *data;
        data += step;
    }
    return sum/(y_f64)len;
}
y_f64 yzl_math_variance_f32(y_f32 *x,y_i32 step,y_i32 len){
    y_f64 x_avg=yzl_math_avg_f32(x,step,len);
    y_f64 sum=0;
    for (int i = 0; i < len; ++i) {
        sum += (x[i*step]-x_avg)*(x[i*step]-x_avg);
    }
    return sum/(y_f64)len;
}
y_f64 yzl_math_variance_f64(y_f64 *x,y_i32 step,y_i32 len){
    y_f64 x_avg=yzl_math_avg_f64(x,step,len);
    y_f64 sum=0;
    for (int i = 0; i < len; ++i) {
        sum += (x[i*step]-x_avg)*(x[i*step]-x_avg);
    }
    return sum/(y_f64)len;
}
y_f64 yzl_math_covariance_f32(y_f32 *x,y_f32 *y,y_i32 step_x,y_i32 step_y,y_i32 len){
    y_f64 x_avg=yzl_math_avg_f32(x,step_x,len);
    y_f64 y_avg=yzl_math_avg_f32(y,step_y,len);
    y_f64 sum=0;
    for (int i = 0; i < len; ++i) {
        sum += (x[i*step_x]-x_avg)*(y[i*step_y]-y_avg);
    }
    return sum/(y_f64)len;
}
y_f64 yzl_math_covariance_f64(y_f64 *x,y_f64 *y,y_i32 step_x,y_i32 step_y,y_i32 len){
    y_f64 x_avg=yzl_math_avg_f64(x,step_x,len);
    y_f64 y_avg=yzl_math_avg_f64(y,step_y,len);
    y_f64 sum=0;
    for (int i = 0; i < len; ++i) {
        sum += (x[i*step_x]-x_avg)*(y[i*step_y]-y_avg);
    }
    return sum/(y_f64)len;
}


void yzl_math_matrix_init_f32(y_matrix_f32 *matrix,y_i32 m,y_i32 n){
    matrix->m=m;
    matrix->n=n;
    matrix->x=(y_f32 *)YZL_MEM_MANAGER.pMalloc(sizeof(y_f32)*(m*n+1));
    memset(matrix->x,0,sizeof(y_f32)*(m*n+1));
    matrix->x=yzl_mem_address_align(matrix->x,sizeof(y_f32));
}

void yzl_math_matrix_deinit_f32(y_matrix_f32 *matrix){
    if(matrix->x!=YZF_NULL_PTR) {
        YZL_MEM_MANAGER.pFree(matrix->x);
    }
    matrix->x=YZF_NULL_PTR;
}

void yzl_math_matrix_init_f64(y_matrix_f64 *matrix,y_i32 m,y_i32 n){
    matrix->m=m;
    matrix->n=n;
    matrix->x=(y_f64 *)YZL_MEM_MANAGER.pMalloc(sizeof(y_f64)*(m*n+1));
    memset(matrix->x,0,sizeof(y_f64)*(m*n+1));
    matrix->x=yzl_mem_address_align(matrix->x,sizeof(y_f64));
}

void yzl_math_matrix_deinit_f64(y_matrix_f64 *matrix){
    if(matrix->x!=YZF_NULL_PTR){
        YZL_MEM_MANAGER.pFree(matrix->x);
    }
    matrix->x=YZF_NULL_PTR;
}

void yzl_math_matrix_clear_f32(y_matrix_f32 *matrix){
    memset(matrix->x,0,sizeof(y_f32)*matrix->m*matrix->n);
}

void yzl_math_matrix_clear_f64(y_matrix_f64 *matrix){
    memset(matrix->x,0,sizeof(y_f64)*matrix->m*matrix->n);
}

void yzl_math_matrix_clear_f64(y_matrix_f64 *matrix);

void yzl_math_vector_init_f32(y_vector_f32 *vector, y_i32 len){
    vector->len=len;
    vector->x=(y_f32 *)YZL_MEM_MANAGER.pMalloc(sizeof(y_f32)*(len+1));
    memset(vector->x,0,sizeof(y_f32)*(len+1));
    vector->x=yzl_mem_address_align(vector->x,sizeof(y_f32));
}

void yzl_math_vector_deinit_f32(y_vector_f32 *vector){
    YZL_MEM_MANAGER.pFree(vector->x);
    vector->x=NULL;
}

void yzl_math_vector_init_f64(y_vector_f64 *vector, y_i32 len){
    vector->len=len;
    vector->x=(y_f64 *)YZL_MEM_MANAGER.pMalloc(sizeof(y_f64)*(len+1));
    memset(vector->x,0,sizeof(y_f64)*(len+1));
    vector->x=yzl_mem_address_align(vector->x,sizeof(y_f64));
}

void yzl_math_vector_deinit_f64(y_vector_f64 *vector){
    YZL_MEM_MANAGER.pFree(vector->x);
    vector->x=NULL;
}


void yzl_math_matrix_mul_f32(y_matrix_f32 *matrix_left,y_matrix_f32 *matrix_right,y_matrix_f32 *matrix_out){
    for(int i = 0; i < matrix_left->n; i++){
        for(int j = 0; j < matrix_right->m; j++){
            for (int k = 0; k < matrix_left->m; ++k) {
                y_matrix_get(matrix_out,i,j)=y_matrix_get(matrix_out,i,j) + y_matrix_get(matrix_left,i,k) * y_matrix_get(matrix_right,k,j);
            }
        }
    }
}
void yzl_math_matrix_mul_vector_f32(y_matrix_f32 *matrix_left, y_vector_f32 *vector_right, y_vector_f32 *vector_out){
    for(int i = 0; i < matrix_left->n; i++) {
        for (int k = 0; k < matrix_left->m; ++k) {
            vector_out->x[i] = vector_out->x[i] + y_matrix_get(matrix_left, i, k) * vector_right->x[k];
        }
    }
}
void yzl_math_matrix_mul_vector_f64(y_matrix_f64 *matrix_left, y_vector_f64 *vector_right, y_vector_f64 *vector_out){
    for(int i = 0; i < matrix_left->n; i++) {
        for (int k = 0; k < matrix_left->m; ++k) {
            vector_out->x[i] = vector_out->x[i] + y_matrix_get(matrix_left, i, k) * vector_right->x[k];
        }
    }
}
void yzl_math_matrix_mul_f64(y_matrix_f64 *matrix_left,y_matrix_f64 *matrix_right,y_matrix_f64 *matrix_out){
    for(int i = 0; i < matrix_left->n; i++) {
        for (int j = 0; j < matrix_right->m; j++) {
            for (int k = 0; k < matrix_left->m; ++k) {
                y_matrix_get(matrix_out, i, j) =y_matrix_get(matrix_out,i,j) + y_matrix_get(matrix_left, i, k) * y_matrix_get(matrix_right, k, j);
            }
        }
    }
}

void yzl_math_matrix_add_f32(y_matrix_f32 *matrix_left, y_matrix_f32 *matrix_right, y_matrix_f32 *matrix_out){
    for (int i = 0; i < matrix_left->m; i++) {
        for (int j = 0; j < matrix_left->n; j++) {
            y_matrix_get(matrix_out, i, j) = y_matrix_get(matrix_left, i, j) + y_matrix_get(matrix_right, i, j);
        }
    }
}
void yzl_math_matrix_add_f64(y_matrix_f64 *matrix_left, y_matrix_f64 *matrix_right, y_matrix_f64 *matrix_out){
    for (int i = 0; i < matrix_left->m; i++) {
        for (int j = 0; j < matrix_left->n; j++) {
            y_matrix_get(matrix_out, i, j) = y_matrix_get(matrix_left, i, j) + y_matrix_get(matrix_right, i, j);
        }
    }
}

void yzl_math_normal_distribution_mul(y_normal_distribution *dst, y_normal_distribution *src1,  y_normal_distribution *src2){
    dst->mean=(src1->mean*src2->variance+src2->mean*src1->variance)/(src1->variance+src2->variance);
    dst->variance=src1->variance*src2->variance/(src1->variance+src2->variance);
}
/**
 *  X X X ---- M
 *  X X X
 *  X X X
 *  |
 *  |
 *  N
 * */
void yzl_math_matrix_covariance_f32(y_f32 **x,y_i32 d,y_i32 len,y_matrix_f64 *cov){
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < i+1; j++) {
            y_matrix_get(cov,i,j)=yzl_math_covariance_f32(x[i],x[j],1,1,len);
            if(j<i){
                y_matrix_T_get(cov,i,j)=y_matrix_get(cov,i,j);
            }
        }
    }
}
void yzl_math_matrix_covariance_f64(y_f64 **x,y_i32 d,y_i32 len,y_matrix_f64 *cov){
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < i+1; j++) {
            y_matrix_get(cov,i,j)=yzl_math_covariance_f64(x[i],x[j],1,1,len);
            if(j<i){
                y_matrix_T_get(cov,i,j)=y_matrix_get(cov,i,j);
            }
        }
    }
}

void yzl_math_matrix_I_f32(y_matrix_f32 *matrix){
    for (int i = 0; i < (matrix->m>=matrix->n?matrix->n:matrix->m); i++) {
        y_matrix_get(matrix,i,i)=1;
    }
}
void yzl_math_matrix_I_f64(y_matrix_f64 *matrix){
    for (int i = 0; i < (matrix->m>=matrix->n?matrix->n:matrix->m); i++) {
        y_matrix_get(matrix,i,i)=1;
    }
}

void yzl_math_matrix_print_f32(y_matrix_f32 *matrix){
    for (int i = 0; i < matrix->m; ++i) {
        yz_printf("[INFO]");
        for (int j = 0; j < matrix->n; ++j) {
            yz_printf("%f ",y_matrix_get(matrix,i,j));
        }
        yz_printf("\n");
    }
}

void yzl_math_matrix_print_f64(y_matrix_f64 *matrix){
    for (int i = 0; i < matrix->m; ++i) {
        yz_printf("[INFO]");
        for (int j = 0; j < matrix->n; ++j) {
            yz_printf("%lf ",y_matrix_get(matrix,i,j));
        }
        yz_printf("\n");
    }
}
void yzl_math_vector_print_f32(y_vector_f32 *vector){
    yz_printf("[INFO]");
    for (int i = 0; i < vector->len; ++i) {
        yz_printf("%f ", vector->x[i]);
    }
    yz_printf("\n");
}
void yzl_math_vector_print_f64(y_vector_f64 *vector){
    yz_printf("[INFO]");
    for (int i = 0; i < vector->len; ++i) {
        yz_printf("%lf ", vector->x[i]);
    }
    yz_printf("\n");
}