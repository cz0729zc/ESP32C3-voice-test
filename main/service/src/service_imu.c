#include "service_imu.h"
#include "bsp_mpu6050.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <math.h>

static const char *TAG = "service_imu"; // 日志标签

// 滤波器和任务相关宏定义
#define ALPHA           0.99f        // 互补滤波器系数，陀螺仪权重
#define RAD_TO_DEG      57.27272727f // 弧度转角度系数
#define TASK_DELAY_MS   20           // IMU数据读取任务的周期（毫秒）

// 静态全局变量
static imu_data_callback_t s_data_cb = NULL; // 指向IMU数据回调函数的指针
static imu_data_t s_imu_data = {0};          // 存储IMU数据（姿态角和加速度）

/**
 * @brief 互补滤波器
 * @details 融合加速度计和陀螺仪数据，计算出更稳定的姿态角
 * @param acce 加速度计数据 (g)
 * @param gyro 陀螺仪数据 (度/秒)
 * @param dt 两次测量之间的时间间隔 (秒)
 */
static void complimentary_filter(const imu_acce_value_t *acce, const imu_gyro_value_t *gyro, float dt)
{
    float acce_angle[2];
    float gyro_angle[2];

    // 从加速度计计算角度
    acce_angle[0] = atan2(acce->acce_y, acce->acce_z) * RAD_TO_DEG;
    acce_angle[1] = atan2(acce->acce_x, acce->acce_z) * RAD_TO_DEG;

    // 从陀螺仪计算角度变化量
    gyro_angle[0] = gyro->gyro_x * dt;
    gyro_angle[1] = gyro->gyro_y * dt;

    // 互补滤波融合
    s_imu_data.angle.roll = (ALPHA * (s_imu_data.angle.roll + gyro_angle[0])) + ((1 - ALPHA) * acce_angle[0]);
    s_imu_data.angle.pitch = (ALPHA * (s_imu_data.angle.pitch + gyro_angle[1])) + ((1 - ALPHA) * acce_angle[1]);
}

/**
 * @brief IMU服务后台任务
 * @details 周期性地读取传感器数据，进行单位转换和滤波，并通过回调函数上报结果
 * @param pvParameters 任务参数 (未使用)
 */
static void service_imu_task(void *pvParameters)
{
    bsp_mpu6050_raw_acce_value_t raw_acce;
    bsp_mpu6050_raw_gyro_value_t raw_gyro;
    imu_acce_value_t acce;
    imu_gyro_value_t gyro;
    float acce_sensitivity, gyro_sensitivity;
    TickType_t last_wake_time = xTaskGetTickCount();

    // 获取传感器的灵敏度，用于将原始数据转换为标准单位
    bsp_mpu6050_get_acce_sensitivity(&acce_sensitivity);
    bsp_mpu6050_get_gyro_sensitivity(&gyro_sensitivity);

    while (1) {
        // 从BSP层获取原始数据
        bsp_mpu6050_get_raw_acce(&raw_acce);
        bsp_mpu6050_get_raw_gyro(&raw_gyro);

        // 将原始数据转换为标准单位 (g 和 度/秒)
        acce.acce_x = raw_acce.raw_acce_x / acce_sensitivity;
        acce.acce_y = raw_acce.raw_acce_y / acce_sensitivity;
        acce.acce_z = raw_acce.raw_acce_z / acce_sensitivity;

        gyro.gyro_x = raw_gyro.raw_gyro_x / gyro_sensitivity;
        gyro.gyro_y = raw_gyro.raw_gyro_y / gyro_sensitivity;
        gyro.gyro_z = raw_gyro.raw_gyro_z / gyro_sensitivity;

        // 使用互补滤波器计算姿态角
        complimentary_filter(&acce, &gyro, (float)TASK_DELAY_MS / 1000.0f);

        // 填充需要上报的Z轴加速度数据
        s_imu_data.acce_z = acce.acce_z;

        // 如果注册了回调函数，则调用它来上报完整数据
        if (s_data_cb) {
            s_data_cb(s_imu_data);
        }

        // 精确延时，保持任务周期稳定
        vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(TASK_DELAY_MS));
    }
}

/**
 * @brief 初始化IMU服务
 */
esp_err_t service_imu_init(void)
{
    // 初始化底层BSP
    esp_err_t ret = bsp_mpu6050_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "MPU6050 初始化失败");
        return ret;
    }
    // 配置MPU6050量程
    ret = bsp_mpu6050_config(ACCE_FS_4G, GYRO_FS_500DPS);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "MPU6050 配置失败");
        return ret;
    }
    return ESP_OK;
}

/**
 * @brief 启动IMU服务
 */
esp_err_t service_imu_start(void)
{
    // 创建后台任务
    if (xTaskCreate(service_imu_task, "imu_task", 4096, NULL, 5, NULL) != pdPASS) {
        ESP_LOGE(TAG, "创建IMU任务失败");
        return ESP_FAIL;
    }
    return ESP_OK;
}

/**
 * @brief 注册IMU数据回调函数
 */
void service_imu_register_callback(imu_data_callback_t cb)
{
    s_data_cb = cb;
}