//
// Created by 32827 on 2025/4/18.
//

#ifndef YZL_SPACE_SENSOR_POSITION_HPP
#define YZL_SPACE_SENSOR_POSITION_HPP

#include "yzl_math.h"

class Position {
public:
    y_vector_f32 data; // 4*1 矩阵
    Position(y_vector_f32 *position);
    Position(y_f32 x,y_f32 y,y_f32 z);
    Position();
    ~Position();

    y_f32& X();
    y_f32& Y();
    y_f32& Z();
    void setPosition(y_f32 x,y_f32 y,y_f32 z);

    y_f32& operator[](int i);
    Position& operator+(Position& b);
    Position& operator-(Position& b);

    void toString();
};

#endif //YZL_SPACE_SENSOR_POSITION_HPP
