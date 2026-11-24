//
// Created by 32827 on 2025/7/28.
//

#include "../Inc/yzl_space_sensor_wall.hpp"

Wall::Wall(Position *origin, y_f32 yaw, y_f32 pitch, y_f32 roll, y_f32 wall_width, y_f32 wall_height) {
    this->origin = origin;
    this->wall_width = wall_width;
    this->wall_height = wall_height;
    this->yaw = yaw;
    this->pitch = pitch;
    this->roll = roll;
    this->dataRam = new Position(0,0,0);
}

Wall::~Wall() {
    delete this->origin;
    delete this->dataRam;
}

Position *Wall::getWallPositionXYZ(y_f32 x, y_f32 y) {
    Pose *pose=new Pose(origin);
    pose->RotateX(this->roll);
    pose->RotateY(this->pitch);
    pose->RotateZ(this->yaw);
    dataRam->setPosition(0,x,y);
    Position *result = *pose * dataRam;
    delete pose;
    return result;
}

Position *Wall::getWallPositionZYX(y_f32 x, y_f32 y) {
    Pose *pose=new Pose(origin);
    pose->RotateZ(this->yaw);
    pose->RotateY(this->pitch);
    pose->RotateX(this->roll);
    dataRam->setPosition(0,x,y);
    Position *result = *pose * dataRam;
    delete pose;
    return result;
}

Position *Wall::getWallPositionYZX(y_f32 x, y_f32 y) {
    Pose *pose=new Pose(origin);
    pose->RotateY(this->yaw);
    pose->RotateZ(this->pitch);
    pose->RotateX(this->roll);
    dataRam->setPosition(0,x,y);
    Position *result = *pose * dataRam;
    delete pose;
    return result;
}

void Wall::getCameraDir(y_f32 x,y_f32 y,Position *camera, y_f32 *yaw, y_f32 *pitch) {
    Position *wallPoint= this->getWallPositionXYZ(x,y);
    wallPoint->toString();
    *wallPoint = *wallPoint - *camera;
    wallPoint->toString();
    delete camera;
    *yaw = yzl_atan2_tab_calc(wallPoint->Y(), wallPoint->X());
    y_f32 r;
    arm_sqrt_f32(wallPoint->X()*wallPoint->X()+wallPoint->Y()*wallPoint->Y(),&r);
    *pitch = yzl_atan2_tab_calc(wallPoint->Z(),r);
    delete wallPoint;
}
