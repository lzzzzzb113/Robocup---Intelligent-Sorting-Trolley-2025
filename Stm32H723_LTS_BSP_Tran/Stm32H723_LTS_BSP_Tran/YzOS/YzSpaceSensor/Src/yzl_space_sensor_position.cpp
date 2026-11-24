//
// Created by 32827 on 2025/4/18.
//

#include "yzl_space_sensor_position.hpp"

Position::Position(y_vector_f32 *position) {
    yzl_math_vector_init_f32(&data,4);
    data.x[0] = position->x[0];
    data.x[1] = position->x[1];
    data.x[2] = position->x[2];
    data.x[3] = 1;
}

Position::Position() {
    yzl_math_vector_init_f32(&data,4);
    data.x[3] = 1;
}

Position::Position(y_f32 x, y_f32 y, y_f32 z) {
    yzl_math_vector_init_f32(&data,4);
    data.x[0] = x;
    data.x[1] = y;
    data.x[2] = z;
    data.x[3] = 1;
}

Position::~Position() {
    yzl_math_vector_deinit_f32(&data);
}

void Position::toString() {
    yzl_math_vector_print_f32(&data);
}

y_f32& Position::operator[](int i) {
    if(i<0||i>=data.len){
        i=data.len-1;
    }
    return data.x[i];
}

Position &Position::operator+(Position &b) {
    (*this)[0] = (*this)[0] + b[0];
    (*this)[1] = (*this)[1] + b[1];
    (*this)[2] = (*this)[2] + b[2];
    return *this;
}

y_f32 &Position::X() {
    return (*this)[0];
}

y_f32 &Position::Y() {
    return (*this)[1];
}

y_f32 &Position::Z() {
    return (*this)[2];
}

Position &Position::operator-(Position &b) {
    (*this)[0] = (*this)[0] - b[0];
    (*this)[1] = (*this)[1] - b[1];
    (*this)[2] = (*this)[2] - b[2];
    return *this;
}

void Position::setPosition(y_f32 x, y_f32 y, y_f32 z) {
    data.x[0] = x;
    data.x[1] = y;
    data.x[2] = z;
    data.x[3] = 1;
}


