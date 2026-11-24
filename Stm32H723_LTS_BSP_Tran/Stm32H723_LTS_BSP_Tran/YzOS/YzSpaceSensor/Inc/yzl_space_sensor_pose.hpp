//
// Created by 32827 on 2025/4/17.
//

#ifndef YZL_SPACE_SENSOR_POSE_HPP
#define YZL_SPACE_SENSOR_POSE_HPP

#include "yzl_math.h"
#include "yzl_space_sensor_position.hpp"
/**
 * 位置运动学 - 位姿
 *
 * 以x , y , z 的顺序旋转，即roll, pitch, yaw
 * */
class Pose {
public:
    y_matrix_f32 data; // 4*4 矩阵 包含3*3姿态矩阵 以及位置矢量
    y_matrix_f32 r_ram; //旋转操作内存
    y_matrix_f32 mul_ram; //乘法中间变量内存
    Pose(y_f32 x,y_f32 y,y_f32 z);
    Pose(class Position *position);
    Pose(y_vector_f32 *position,y_f32 degree_x,y_f32 degree_y,y_f32 degree_z);
    Pose(class Position *position,y_f32 degree_x,y_f32 degree_y,y_f32 degree_z);
    Pose(class Position position,y_f32 degree_x,y_f32 degree_y,y_f32 degree_z);
    Pose(y_matrix_f32 *raw);
    Pose();
    ~Pose();

    /**
     * @description 设置坐标系相对位置
     * */
    void Position(y_vector_f32 *position);
    void Position(class Position *position);
    void RotateX(y_f32  x);
    void RotateY(y_f32  y);
    void RotateZ(y_f32  z);
    y_f32 GetRotateX();
    y_f32 GetRotateY();
    y_f32 GetRotateZ();
    void toString();

    Pose& operator+(Pose* b);// 你可以 Pose& + (Pose*/Pose&) 以同样效果的矩阵相加
    Pose& operator+(Pose& b);
    void operator=(Pose* b);//Pose* = (Pose*/Pose&) 仅复制data.x;
    void operator=(Pose& b);
    Pose operator*(Pose* b);// 你可以 Pose& * (Pose*/Pose&) 以同样效果的矩阵相乘
    Pose operator*(Pose& b);

    y_vector_f32& operator* (y_vector_f32 *position);// 你可以直接乘以 y_vector_f64 *position，以返回一个 y_vector_f64 *
    class Position* operator* (class Position* position);// 你可以直接乘以 Position以返回一个 Position
    class Position* operator* (class Position& position);// 你可以直接乘以 Position以返回一个 Position
};

#endif //YZL_SPACE_SENSOR_POSE_HPP
