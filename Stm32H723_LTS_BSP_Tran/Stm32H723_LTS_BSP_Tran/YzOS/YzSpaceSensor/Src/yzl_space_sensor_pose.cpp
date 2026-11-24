//
// Created by 32827 on 2025/4/17.
//

#include "yzl_space_sensor_pose.hpp"

Pose::Pose(y_vector_f32* position, y_f32 degree_x, y_f32 degree_y, y_f32 degree_z) {
    yzl_math_matrix_init_f32(&data,4,4);
    yzl_math_matrix_init_f32(&r_ram,4,4);
    yzl_math_matrix_init_f32(&mul_ram,4,4);
    yzl_math_matrix_I_f32(&data);
    Position(position);
    RotateX(degree_x);
    RotateY(degree_y);
    RotateZ(degree_z);
}
Pose::Pose(y_matrix_f32* raw){
    yzl_math_matrix_init_f32(&data,4,4);
    yzl_math_matrix_init_f32(&r_ram,4,4);
    yzl_math_matrix_init_f32(&mul_ram,4,4);
    memcpy(data.x,raw->x,y_matrix_size_f32(&data));
}
Pose::Pose(class Position *position, y_f32 degree_x, y_f32 degree_y, y_f32 degree_z) {
    yzl_math_matrix_init_f32(&data,4,4);
    yzl_math_matrix_init_f32(&r_ram,4,4);
    yzl_math_matrix_init_f32(&mul_ram,4,4);
    yzl_math_matrix_I_f32(&data);
    Position(position);
    RotateX(degree_x);
    RotateY(degree_y);
    RotateZ(degree_z);
}
Pose::~Pose(){
    yzl_math_matrix_deinit_f32(&data);
    yzl_math_matrix_deinit_f32(&r_ram);
    yzl_math_matrix_deinit_f32(&mul_ram);
}

void Pose::Position(y_vector_f32* position) {
    y_matrix_get((&data),0,3)=position->x[0];
    y_matrix_get((&data),1,3)=position->x[1];
    y_matrix_get((&data),2,3)=position->x[2];
}
void Pose::Position(class Position *position){
    y_matrix_get((&data),0,3)=position->data.x[0];
    y_matrix_get((&data),1,3)=position->data.x[1];
    y_matrix_get((&data),2,3)=position->data.x[2];
}
void Pose::RotateX(y_f32 x) {
    yzl_math_matrix_clear_f32(&r_ram);
    yzl_math_matrix_clear_f32(&mul_ram);
    yzl_math_matrix_I_f32(&r_ram);
    y_matrix_get(&r_ram,1,1)=COS(x);
    y_matrix_get(&r_ram,1,2)=-SIN(x);
    y_matrix_get(&r_ram,2,1)=SIN(x);
    y_matrix_get(&r_ram,2,2)=COS(x);
    yzl_math_matrix_mul_f32(&data,&r_ram,&mul_ram);
    memcpy(data.x,mul_ram.x,y_matrix_size_f32(&data));
}

void Pose::RotateY(y_f32 y) {
    yzl_math_matrix_clear_f32(&r_ram);
    yzl_math_matrix_clear_f32(&mul_ram);
    yzl_math_matrix_I_f32(&r_ram);
    y_matrix_get(&r_ram,0,0)=COS(y);
    y_matrix_get(&r_ram,0,2)=SIN(y);
    y_matrix_get(&r_ram,2,0)=-SIN(y);
    y_matrix_get(&r_ram,2,2)=COS(y);
    yzl_math_matrix_mul_f32(&data,&r_ram,&mul_ram);
    memcpy(data.x,mul_ram.x,y_matrix_size_f32(&data));
}

void Pose::RotateZ(y_f32 z) {
    yzl_math_matrix_clear_f32(&r_ram);
    yzl_math_matrix_clear_f32(&mul_ram);
    yzl_math_matrix_I_f32(&r_ram);
    y_matrix_get(&r_ram,0,0)=COS(z);
    y_matrix_get(&r_ram,0,1)=-SIN(z);
    y_matrix_get(&r_ram,1,0)=SIN(z);
    y_matrix_get(&r_ram,1,1)=COS(z);
    yzl_math_matrix_mul_f32(&data,&r_ram,&mul_ram);
    memcpy(data.x,mul_ram.x,y_matrix_size_f32(&data));
}

void Pose::toString(){
    yzl_math_matrix_print_f32(&data);
}

Pose& Pose::operator+(Pose *b) {
    yzl_math_matrix_clear_f32(&mul_ram);
    yzl_math_matrix_add_f32(&b->data,&data,&mul_ram);
    memcpy(data.x,mul_ram.x,y_matrix_size_f32(&data));
    return *this;
}
Pose& Pose::operator+(Pose& b){
    yzl_math_matrix_clear_f32(&mul_ram);
    yzl_math_matrix_add_f32(&b.data,&data,&mul_ram);
    memcpy(data.x,mul_ram.x,y_matrix_size_f32(&data));
    return *this;
}

void Pose::operator=(Pose *b) {
//    if(b!=NULL_PTR){
        memcpy(data.x,b->data.x,y_matrix_size_f32(&data));
//    }
}
void Pose::operator=(Pose& b){
//    if(&b!=NULL_PTR) {
        memcpy(data.x, b.data.x, y_matrix_size_f32(&data));
//    }
}

Pose Pose::operator*(Pose* b){
    yzl_math_matrix_clear_f32(&mul_ram);
    yzl_math_matrix_mul_f32(&data,&b->data,&mul_ram);
    Pose t(&mul_ram);
    return t;
}
Pose Pose::operator*(Pose& b){
    yzl_math_matrix_clear_f32(&mul_ram);
    yzl_math_matrix_mul_f32(&data,&b.data,&mul_ram);
    Pose t(&mul_ram);
    return t;
}

Pose::Pose() {
    yzl_math_matrix_init_f32(&data,4,4);
    yzl_math_matrix_init_f32(&r_ram,4,4);
    yzl_math_matrix_init_f32(&mul_ram,4,4);
    yzl_math_matrix_I_f32(&data);
}

y_vector_f32& Pose::operator*(y_vector_f32 *position) {
    yzl_math_matrix_clear_f32(&mul_ram);
    yzl_math_matrix_mul_vector_f32(&data, position, (y_vector_f32 *)(&mul_ram));
    return *(y_vector_f32 *)(&mul_ram);
}

class Position * Pose::operator*(class Position *position) {
    yzl_math_matrix_clear_f32(&mul_ram);
    yzl_math_matrix_mul_vector_f32(&data, &position->data, (y_vector_f32 *)(&mul_ram));
    return new class Position((y_vector_f32 *)(&mul_ram));
}

class Position *Pose::operator*(class Position &position) {
    yzl_math_matrix_clear_f32(&mul_ram);
    yzl_math_matrix_mul_vector_f32(&data, &position.data, (y_vector_f32 *)(&mul_ram));
    return new class Position((y_vector_f32 *)(&mul_ram));
}

Pose::Pose(struct Position position, y_f32 degree_x, y_f32 degree_y, y_f32 degree_z):Pose(&position,degree_x,degree_y,degree_z) {}

y_f32 Pose::GetRotateX() {
    double y = GetRotateY();
    double cy=COS(y);
    if(y==PI/2){
        return yzl_atan2_tab_calc(y_matrix_get(&data,0,1)/cy,y_matrix_get(&data,1,1)/cy);
    }else if(y==-PI/2){
        return -yzl_atan2_tab_calc(y_matrix_get(&data,0,1)/cy,y_matrix_get(&data,1,1)/cy);
    }
    return yzl_atan2_tab_calc(y_matrix_get(&data,2,1)/cy,y_matrix_get(&data,2,2)/cy);
}

y_f32 Pose::GetRotateY() {
    y_f32 x;
    arm_sqrt_f32(y_matrix_get(&data,0,0)*y_matrix_get(&data,0,0)+y_matrix_get(&data,1,0)*y_matrix_get(&data,1,0),&x);
    return yzl_atan2_tab_calc(-y_matrix_get(&data,2,0),x);
}

y_f32 Pose::GetRotateZ() {
    double y = GetRotateY();
    double cy=COS(y);
    if(cy==0.0f){
        return 0;
    }
    return yzl_atan2_tab_calc(y_matrix_get(&data,1,0)/cy,y_matrix_get(&data,0,0)/cy);
}

Pose::Pose(y_f32 x, y_f32 y, y_f32 z) {
    yzl_math_matrix_init_f32(&data,4,4);
    yzl_math_matrix_init_f32(&r_ram,4,4);
    yzl_math_matrix_init_f32(&mul_ram,4,4);
    yzl_math_matrix_I_f32(&data);
    y_matrix_get((&data),0,3)=x;
    y_matrix_get((&data),1,3)=y;
    y_matrix_get((&data),2,3)=z;
}

Pose::Pose(class Position *position) {
    yzl_math_matrix_init_f32(&data,4,4);
    yzl_math_matrix_init_f32(&r_ram,4,4);
    yzl_math_matrix_init_f32(&mul_ram,4,4);
    yzl_math_matrix_I_f32(&data);
    y_matrix_get((&data),0,3)=position->data.x[0];
    y_matrix_get((&data),1,3)=position->data.x[1];
    y_matrix_get((&data),2,3)=position->data.x[2];
}



