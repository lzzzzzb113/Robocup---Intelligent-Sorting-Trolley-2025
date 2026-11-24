//
// Created by 32827 on 2025/5/7.
//

#ifndef STM32H723_LTS_BSP_ARMGROUP_HPP
#define STM32H723_LTS_BSP_ARMGROUP_HPP

#include "yzl_space_sensor_arm_pole.hpp"
#include "yzl_space_sensor_arm_plate.hpp"

class ArmGroup {
public:
    uint32_t tim1_ch1_duty=1298;
    uint32_t tim1_ch2_duty=2499;
    uint32_t tim1_ch3_duty=2499;
    uint32_t tim1_ch4_duty=1998;
    uint32_t tim3_ch1_duty=499;
    uint32_t tim3_ch2_duty=1499;

    YZL_GPIO arm07_dir={YZF_PIN_9,GPIOD};
    YZL_GPIO arm08_dir={YZF_PIN_10,GPIOD};
    YZL_GPIO arm09_dir={YZF_PIN_11,GPIOD};
    YZL_GPIO arm10_dir={YZF_PIN_8,GPIOD};

    SpaceSensorArmPlate *arm01,*arm02,*arm03,*arm04,*arm05,*arm06;
    SpaceSensorArmPole *arm07,*arm08,*arm09,*arm10;

    ArmGroup();
    ~ArmGroup();

    void Init();
    void addParams(int index,float timeUnit);
    void delParams(int index,float timeUnit);
    void act();
    void getEnd();
    float * compile();

    static uint32_t ProgramTick;
    static YZF_BOOL isLoadTickHandler;
    static YZF_RESULT ProgramTickHandler(uint32_t tick);
};
#endif //STM32H723_LTS_BSP_ARMGROUP_HPP
