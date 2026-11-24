//
// Created by 32827 on 2024/12/16.
//

#ifndef STM32H723ZGTXCOVER_YZL_KALMAN_FILTER_H
#define STM32H723ZGTXCOVER_YZL_KALMAN_FILTER_H

typedef struct {
    double x;
    double p;
    double q;
    double r;
} KalmanFilter;

void KalmanFilter_Init(KalmanFilter* kf, double initial_value, double process_noise, double measurement_noise);
double KalmanFilter_Update(KalmanFilter* kf, double measurement);

#endif //STM32H723ZGTXCOVER_YZL_KALMAN_FILTER_H
