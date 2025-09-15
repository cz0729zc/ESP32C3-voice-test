#ifndef SERVICE_IMU_H_
#define SERVICE_IMU_H_

#include "esp_err.h"

/**
 * @brief 加速度计数据结构体 (单位: g)
 */
typedef struct {
    float acce_x; /*!< X轴加速度 */
    float acce_y; /*!< Y轴加速度 */
    float acce_z; /*!< Z轴加速度 */
} imu_acce_value_t;

/**
 * @brief 陀螺仪数据结构体 (单位: 度/秒)
 */
typedef struct {
    float gyro_x; /*!< X轴角速度 */
    float gyro_y; /*!< Y轴角速度 */
    float gyro_z; /*!< Z轴角速度 */
} imu_gyro_value_t;

/**
 * @brief 姿态角数据结构体 (单位: 度)
 */
typedef struct {
    float roll;  /*!< 横滚角 */
    float pitch; /*!< 俯仰角 */
} imu_angle_t;

/**
 * @brief IMU上报给应用层的完整数据结构
 */
typedef struct {
    imu_angle_t angle;      /*!< 姿态角 */
    imu_gyro_value_t gyro;  /*!< 角速度 (新添加) */
    float acce_z;           /*!< Z轴加速度 (单位: g) */
} imu_data_t;

/**
 * @brief IMU数据回调函数类型定义
 * @param data 计算出的IMU数据
 */
typedef void (*imu_data_callback_t)(imu_data_t data);

/**
 * @brief 初始化IMU服务
 *
 * @return esp_err_t 错误码
 */
esp_err_t service_imu_init(void);

/**
 * @brief 启动IMU服务
 * @details 这将创建一个后台任务来周期性地读取和处理IMU数据
 *
 * @return esp_err_t 错误码
 */
esp_err_t service_imu_start(void);

/**
 * @brief 注册一个回调函数以接收IMU数据
 *
 * @param cb 回调函数指针
 */
void service_imu_register_callback(imu_data_callback_t cb);

#endif /* SERVICE_IMU_H_ */