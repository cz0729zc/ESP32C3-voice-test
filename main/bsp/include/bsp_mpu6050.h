#ifndef BSP_MPU6050_H_
#define BSP_MPU6050_H_

#include "esp_err.h"

/**
 * @brief 加速度计量程枚举
 */
typedef enum {
    ACCE_FS_2G  = 0, /*!< 加速度计量程: ±2g */
    ACCE_FS_4G  = 1, /*!< 加速度计量程: ±4g */
    ACCE_FS_8G  = 2, /*!< 加速度计量程: ±8g */
    ACCE_FS_16G = 3, /*!< 加速度计量程: ±16g */
} bsp_mpu6050_acce_fs_t;

/**
 * @brief 陀螺仪量程枚举
 */
typedef enum {
    GYRO_FS_250DPS  = 0, /*!< 陀螺仪量程: ±250 度/秒 */
    GYRO_FS_500DPS  = 1, /*!< 陀螺仪量程: ±500 度/秒 */
    GYRO_FS_1000DPS = 2, /*!< 陀螺仪量程: ±1000 度/秒 */
    GYRO_FS_2000DPS = 3, /*!< 陀螺仪量程: ±2000 度/秒 */
} bsp_mpu6050_gyro_fs_t;

/**
 * @brief 加速度计原始数据结构体
 */
typedef struct {
    int16_t raw_acce_x; /*!< X轴原始加速度值 */
    int16_t raw_acce_y; /*!< Y轴原始加速度值 */
    int16_t raw_acce_z; /*!< Z轴原始加速度值 */
} bsp_mpu6050_raw_acce_value_t;

/**
 * @brief 陀螺仪原始数据结构体
 */
typedef struct {
    int16_t raw_gyro_x; /*!< X轴原始陀螺仪值 */
    int16_t raw_gyro_y; /*!< Y轴原始陀螺仪值 */
    int16_t raw_gyro_z; /*!< Z轴原始陀螺仪值 */
} bsp_mpu6050_raw_gyro_value_t;

/**
 * @brief 初始化 MPU6050
 *
 * @return esp_err_t 错误码
 */
esp_err_t bsp_mpu6050_init(void);

/**
 * @brief 卸载 MPU6050
 *
 * @return esp_err_t 错误码
 */
esp_err_t bsp_mpu6050_deinit(void);

/**
 * @brief 获取 MPU6050 的设备ID
 *
 * @param deviceid 指向设备ID存储位置的指针
 * @return esp_err_t 错误码
 */
esp_err_t bsp_mpu6050_get_deviceid(uint8_t *deviceid);

/**
 * @brief 唤醒 MPU6050
 *
 * @return esp_err_t 错误码
 */
esp_err_t bsp_mpu6050_wake_up(void);

/**
 * @brief 使 MPU6050 进入睡眠模式
 *
 * @return esp_err_t 错误码
 */
esp_err_t bsp_mpu6050_sleep(void);

/**
 * @brief 设置加速度计和陀螺仪的量程
 *
 * @param acce_fs 加速度计量程
 * @param gyro_fs 陀螺仪量程
 * @return esp_err_t 错误码
 */
esp_err_t bsp_mpu6050_config(bsp_mpu6050_acce_fs_t acce_fs, bsp_mpu6050_gyro_fs_t gyro_fs);

/**
 * @brief 获取加速度计的灵敏度
 *
 * @param acce_sensitivity 指向加速度计灵敏度存储位置的指针
 * @return esp_err_t 错误码
 */
esp_err_t bsp_mpu6050_get_acce_sensitivity(float *acce_sensitivity);

/**
 * @brief 获取陀螺仪的灵敏度
 *
 * @param gyro_sensitivity 指向陀螺仪灵敏度存储位置的指针
 * @return esp_err_t 错误码
 */
esp_err_t bsp_mpu6050_get_gyro_sensitivity(float *gyro_sensitivity);

/**
 * @brief 读取加速度计的原始测量值
 *
 * @param raw_acce_value 指向原始加速度计测量值结构体的指针
 * @return esp_err_t 错误码
 */
esp_err_t bsp_mpu6050_get_raw_acce(bsp_mpu6050_raw_acce_value_t *raw_acce_value);

/**
 * @brief 读取陀螺仪的原始测量值
 *
 * @param raw_gyro_value 指向原始陀螺仪测量值结构体的指针
 * @return esp_err_t 错误码
 */
esp_err_t bsp_mpu6050_get_raw_gyro(bsp_mpu6050_raw_gyro_value_t *raw_gyro_value);

/**
 * @brief 读取温度值
 *
 * @param temp 指向温度值存储位置的指针
 * @return esp_err_t 错误码
 */
esp_err_t bsp_mpu6050_get_temp(float *temp);

#endif /* BSP_MPU6050_H_ */