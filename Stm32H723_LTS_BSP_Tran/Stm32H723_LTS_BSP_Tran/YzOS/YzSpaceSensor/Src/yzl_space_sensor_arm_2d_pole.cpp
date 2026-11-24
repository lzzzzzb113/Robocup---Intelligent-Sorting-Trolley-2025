//
// Created by 32827 on 2025/7/26.
//

#include "../Inc/yzl_space_sensor_arm_2d_pole.hpp"

SpaceSensorArmPole2D::SpaceSensorArmPole2D(Wall *wall) {
    defaultPose=new Pose();
    pos = new Position();
    this->wall = wall;
}

void SpaceSensorArmPole2D::setVerArm(YZL_GPIO Dir, YZF_TIM_POINTER tim, uint16_t ch_id, YZF_TIM_POINTER timCount) {
    armV=new SpaceSensorArmPole(Dir,YZF_NULL_PTR,tim,ch_id,timCount,*defaultPose,100000,-100000,0,YZF_FALSE);
    armV->scale = 1;
}

void SpaceSensorArmPole2D::setHorArm(YZL_GPIO Dir, YZF_TIM_POINTER tim, uint16_t ch_id, YZF_TIM_POINTER timCount) {
    armH=new SpaceSensorArmPole(Dir,YZF_NULL_PTR,tim,ch_id,timCount,*defaultPose,100000,-100000,0,YZF_FALSE);
    armH->scale = 1;
}

SpaceSensorArmPole2D::~SpaceSensorArmPole2D() {
    delete defaultPose;
    if(armV!=YZF_NULL_PTR){
        delete armV;
    }
    if(armH!=YZF_NULL_PTR){
        delete armH;
    }
}

float SpaceSensorArmPole2D::setAngle(float angle) {
    this->angle = angle;
    float speedH= cos(angle*PI/180.0) * speed;
    float speedV= sin(angle*PI/180.0) * speed;
    armH->setSpeed(speedH);
    armV->setSpeed(speedV);
    return angle;
}


float SpaceSensorArmPole2D::getAngle() {
    return SpaceSensorArm::getAngle();
}

float SpaceSensorArmPole2D::getSpeed() {
    return speed;
}

void SpaceSensorArmPole2D::setSpeed(float speed) {
    this->speed = speed;
}

void SpaceSensorArmPole2D::addLength(float length) {
    float lenH = cos(angle*PI/180.0) * length;
    float lenV = sin(angle*PI/180.0) * length;
    armV->addLength(lenV);
    armH->addLength(lenH);
}

void SpaceSensorArmPole2D::addVLength(float length) {
    float lenV=length;
    float lenH= (1.0/tan(angle*PI/180.0)) * length;
    armV->addLength(lenV);
    armH->addLength(lenH);
}

void SpaceSensorArmPole2D::addHLength(float length) {
    float lenH=length;
    float lenV= tan(angle*PI/180.0) * length;
    armV->addLength(lenV);
    armH->addLength(lenH);
}

void SpaceSensorArmPole2D::move(float x, float y) {
    armV->addLength(x);
    armH->addLength(y);
}

YZF_BOOL SpaceSensorArmPole2D::isFinish() {
    return (armV->isFinish()&&armH->isFinish())?YZF_TRUE:YZF_FALSE;
}

void SpaceSensorArmPole2D::moveWall(float x, float y) {
    y_f32 yaw,pitch;
    wall->getCameraDir(x,y,new Position(&pos->data),&yaw,&pitch);

    yaw = (yaw/(PI/180.0)) / unitAngle * preDiv;
    pitch = (pitch/(PI/180.0)) / unitAngle * preDiv;

    float VT=pitch-armV->getAngle();
    float HT=yaw-armH->getAngle();

    float nAngle = yzl_atan2_tab_calc(HT,VT);
    setAngle(nAngle/(PI/180));
    addLength(sqrt(HT*HT+VT*VT));
}

void SpaceSensorArmPole2D::setUnitAngle(float angle) {
    this->unitAngle = angle;
}

void SpaceSensorArmPole2D::setPreDiv(float preDiv) {
    this->preDiv = preDiv;
}


