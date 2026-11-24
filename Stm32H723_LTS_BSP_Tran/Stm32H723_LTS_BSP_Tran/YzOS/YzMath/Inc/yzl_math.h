//
// Created by 32827 on 2024/11/22.
//

#ifndef YZL_MATH_H
#define YZL_MATH_H

#include "yzx_base.h"
#include "yzl.h"

#if YZL_MATH_USE_HAL
#include "arm_math.h"
#endif

#ifdef   __cplusplus
extern "C"
{
#endif

//三角函数精度
#define YZL_TRIG_EPSILON 0.006
#define YZL_M_PI        3.1415926535897932384626433832795f
#define YZL_M_PI_2      (3.1415926535897932384626433832795f / 2)
#define	YZL_LUT_NUM		4096*2	/*该值越大表精度越高,精度为atan(1/LUT_NUM)*/    //Need 4K RAM

#define COS arm_cos_f32
#define SIN arm_sin_f32

typedef float y_f32;
typedef double y_f64;
typedef int y_i32;
typedef uint64_t y_i64;

#define y_matrix_get(D, i, j) (((D)->x)[i*((D)->m)+j])
#define y_matrix_T_get(D, i, j) (((D)->x)[j*((D)->n)+i])
#define y_matrix_size_f32(D) (sizeof(y_f32)*((D)->m)*((D)->n))
#define y_matrix_size_f64(D) (sizeof(y_f64)*((D)->m)*((D)->n))
#define y_vector_size_f32(D) (sizeof(y_f32)*((D)->len))
#define y_vector_size_f64(D) (sizeof(y_f64)*((D)->len))
typedef struct {
    y_f32 *x;
    y_i32 m;
    y_i32 n;
} y_matrix_f32;

typedef struct {
    y_f64 *x;
    y_i32 m;
    y_i32 n;
} y_matrix_f64;

typedef struct {
    y_f32 *x;
    y_i32 len;
} y_vector_f32;

typedef struct {
    y_f64 *x;
    y_i32 len;
} y_vector_f64;

typedef struct {
    y_f32 mean;
    y_f32 variance;
} y_normal_distribution;


y_f32 yzl_arcsin(y_f32 x);
void yzl_atan2_tab_init(void);
y_f32 yzl_atan2_tab_calc(y_f32 y, y_f32 x);

/**
 * @description: 计算均值
 *
 * @param data 数据
 * @param step 步长
 * @param len 长度
 * */
y_f64 yzl_math_avg_f32(y_f32 *data, y_i32 step, y_i32 len);

y_f64 yzl_math_avg_f64(y_f64 *data, y_i32 step, y_i32 len);

/**
 * @description: 计算方差
 *
 * @param data 数据
 * @param step 步长
 * */
y_f64 yzl_math_variance_f32(y_f32 *x, y_i32 step, y_i32 len);

y_f64 yzl_math_variance_f64(y_f64 *x, y_i32 step, y_i32 len);

/**
 * @description: 计算协方差
 *
 * @param x 数据1
 * @param y 数据2
 * @param step_x 数据1步长
 * @param step_y 数据2步长
 * @param len 长度
 * */
y_f64 yzl_math_covariance_f32(y_f32 *x, y_f32 *y, y_i32 step_x, y_i32 step_y, y_i32 len);

y_f64 yzl_math_covariance_f64(y_f64 *x, y_f64 *y, y_i32 step_x, y_i32 step_y, y_i32 len);

/**
 * @description: 初始化矩阵
 *
 * @param matrix 矩阵
 * @param m 行数
 * @param n 列数
 * */
void yzl_math_matrix_init_f32(y_matrix_f32 *matrix, y_i32 m, y_i32 n);

void yzl_math_matrix_deinit_f32(y_matrix_f32 *matrix);

void yzl_math_matrix_init_f64(y_matrix_f64 *matrix, y_i32 m, y_i32 n);

void yzl_math_matrix_deinit_f64(y_matrix_f64 *matrix);

void yzl_math_matrix_clear_f32(y_matrix_f32 *matrix);

void yzl_math_matrix_clear_f64(y_matrix_f64 *matrix);


/**
 * @description: 初始化向量
 *
 * */
void yzl_math_vector_init_f32(y_vector_f32 *vector, y_i32 len);

void yzl_math_vector_deinit_f32(y_vector_f32 *vector);

void yzl_math_vector_init_f64(y_vector_f64 *vector, y_i32 len);

void yzl_math_vector_deinit_f64(y_vector_f64 *vector);

/**
 * @description: 矩阵乘法
 *
 * @param matrix_left 左矩阵
 * @param matrix_right 右矩阵
 * @param matrix_out 结果矩阵
 * */
void yzl_math_matrix_mul_f32(y_matrix_f32 *matrix_left, y_matrix_f32 *matrix_right, y_matrix_f32 *matrix_out);
void yzl_math_matrix_mul_vector_f32(y_matrix_f32 *matrix_left, y_vector_f32 *vector_right, y_vector_f32 *vector_out);
void yzl_math_matrix_mul_f64(y_matrix_f64 *matrix_left, y_matrix_f64 *matrix_right, y_matrix_f64 *matrix_out);
void yzl_math_matrix_mul_vector_f64(y_matrix_f64 *matrix_left, y_vector_f64 *vector_right, y_vector_f64 *vector_out);
/**
 * @description: 矩阵加法
 *
 * @param matrix_left 左矩阵
 * @param matrix_right 右矩阵
 * @param matrix_out 结果矩阵
 * */

void yzl_math_matrix_add_f32(y_matrix_f32 *matrix_left, y_matrix_f32 *matrix_right, y_matrix_f32 *matrix_out);
void yzl_math_matrix_add_f64(y_matrix_f64 *matrix_left, y_matrix_f64 *matrix_right, y_matrix_f64 *matrix_out);

/**
 * @description: 计算谐方差矩阵
 *
 * @param x 数据
 * @param d 维度
 * @param len 长度
 * */
void yzl_math_matrix_covariance_f32(y_f32 **x, y_i32 d, y_i32 len, y_matrix_f64 *cov);
void yzl_math_matrix_covariance_f64(y_f64 **x, y_i32 d, y_i32 len, y_matrix_f64 *cov);

void yzl_math_matrix_I_f32(y_matrix_f32 *matrix);
void yzl_math_matrix_I_f64(y_matrix_f64 *matrix);

void yzl_math_matrix_print_f32(y_matrix_f32 *matrix);
void yzl_math_matrix_print_f64(y_matrix_f64 *matrix);
void yzl_math_vector_print_f32(y_vector_f32 *vector);
void yzl_math_vector_print_f64(y_vector_f64 *vector);

void yzl_math_normal_distribution_mul(y_normal_distribution *dst, y_normal_distribution *src1, y_normal_distribution *src2);

#ifdef   __cplusplus
}
#endif
#endif //YZL_MATH_H
