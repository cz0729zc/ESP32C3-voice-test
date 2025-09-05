#ifndef APP_IMU_H_
#define APP_IMU_H_

#include "esp_err.h"

/**
 * @brief 初始化 IMU 应用
 *
 * @return esp_err_t 错误码
 */
esp_err_t app_imu_init(void);

#endif /* APP_IMU_H_ */