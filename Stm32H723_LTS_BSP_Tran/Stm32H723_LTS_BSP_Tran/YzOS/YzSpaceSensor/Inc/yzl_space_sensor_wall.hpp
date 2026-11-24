//
// Created by 32827 on 2025/7/28.
//

#ifndef STM32H723_LTS_BSP_YZL_SPACE_SENSOR_WALL_HPP
#define STM32H723_LTS_BSP_YZL_SPACE_SENSOR_WALL_HPP

/**
 * 在3D空间中放一个二维的墙
 *
 * 用户应将origin的管理权交给Wall处理
 *
 * y
 * |
 * |
 * + - - - x
 *
 * z    x
 * |  /
 * |/
 * + - - - y
 * */
#include "yzl_math.h"
#include "yzl_space_sensor_pose.hpp"

class Wall {
    public:
        y_f32 yaw, pitch, roll;
        Position *origin;
        y_f32 wall_width;
        y_f32 wall_height;
        Pose *WallPose;//记录墙的状态

        Position *dataRam;
        /**
         * @param origin 墙的起始位置用户应将origin的管理权交给Wall处理
         * */
        Wall(Position *origin, y_f32 yaw, y_f32 pitch, y_f32 roll, y_f32 wall_width, y_f32 wall_height);
        ~Wall();

        /**
         * @return you need delete this return value
         * */
        Position *getWallPositionXYZ(y_f32 x,y_f32 y);
        Position *getWallPositionZYX(y_f32 x,y_f32 y);
        Position *getWallPositionYZX(y_f32 x,y_f32 y);

        /**
         * @param camera 摄像机位置用户应将origin的管理权交给Wall处理
         * */
        void getCameraDir(y_f32 x,y_f32 y,Position *camera,y_f32* yaw,y_f32* pitch);
};


#endif //STM32H723_LTS_BSP_YZL_SPACE_SENSOR_WALL_HPP
