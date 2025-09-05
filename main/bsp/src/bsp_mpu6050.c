#include "bsp_mpu6050.h"
#include "bsp_i2c.h"
#include "esp_log.h"

static const char *TAG = "bsp_mpu6050"; // 日志标签

// MPU6050 I2C 配置
#define MPU6050_I2C_PORT      I2C_NUM_0  // I2C端口号
#define MPU6050_I2C_SDA       8         // SDA引脚
#define MPU6050_I2C_SCL       9         // SCL引脚
#define MPU6050_I2C_CLK_SPEED 100000     // I2C时钟频率
#define MPU6050_I2C_ADDR      0x68       // MPU6050 I2C设备地址

// MPU6050 寄存器地址
#define MPU6050_GYRO_CONFIG         0x1B // 陀螺仪配置寄存器
#define MPU6050_ACCEL_CONFIG        0x1C // 加速度计配置寄存器
#define MPU6050_ACCEL_XOUT_H        0x3B // 加速度计X轴高位数据寄存器
#define MPU6050_GYRO_XOUT_H         0x43 // 陀螺仪X轴高位数据寄存器
#define MPU6050_TEMP_XOUT_H         0x41 // 温度高位数据寄存器
#define MPU6050_PWR_MGMT_1          0x6B // 电源管理寄存器1
#define MPU6050_WHO_AM_I            0x75 // "我是谁"寄存器 (用于设备ID识别)
#define MPU6050_WHO_AM_I_VAL        0x68 // "我是谁"寄存器的期望值

/**
 * @brief 向MPU6050写入单个字节
 * @param reg 目标寄存器地址
 * @param data 要写入的数据
 * @return esp_err_t 错误码
 */
static esp_err_t mpu6050_write_reg(uint8_t reg, uint8_t data)
{
    return bsp_i2c_write_bytes(MPU6050_I2C_PORT, MPU6050_I2C_ADDR, reg, &data, 1);
}

/**
 * @brief 从MPU6050读取多个字节
 * @param reg 起始寄存器地址
 * @param data 存储读取数据的缓冲区
 * @param len 要读取的数据长度
 * @return esp_err_t 错误码
 */
static esp_err_t mpu6050_read_bytes(uint8_t reg, uint8_t *data, uint8_t len)
{
    return bsp_i2c_read_bytes(MPU6050_I2C_PORT, MPU6050_I2C_ADDR, reg, data, len);
}

/**
 * @brief 初始化MPU6050
 */
esp_err_t bsp_mpu6050_init(void)
{
    // 初始化I2C总线
    esp_err_t ret = bsp_i2c_init(MPU6050_I2C_PORT, MPU6050_I2C_SDA, MPU6050_I2C_SCL, MPU6050_I2C_CLK_SPEED);
    if (ret != ESP_OK) {
        return ret;
    }
    // 读取设备ID并验证
    uint8_t device_id = 0;
    ret = bsp_mpu6050_get_deviceid(&device_id);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "获取设备ID失败");
        return ret;
    }
    if (device_id != MPU6050_WHO_AM_I_VAL) {
        ESP_LOGE(TAG, "未找到MPU6050, 设备ID: 0x%02x", device_id);
        return ESP_FAIL;
    }
    ESP_LOGI(TAG, "找到MPU6050, 设备ID: 0x%02x", device_id);
    // 唤醒MPU6050
    return bsp_mpu6050_wake_up();
}

/**
 * @brief 卸载MPU6050
 */
esp_err_t bsp_mpu6050_deinit(void)
{
    return bsp_i2c_deinit(MPU6050_I2C_PORT);
}

/**
 * @brief 获取MPU6050的设备ID
 */
esp_err_t bsp_mpu6050_get_deviceid(uint8_t *deviceid)
{
    return mpu6050_read_bytes(MPU6050_WHO_AM_I, deviceid, 1);
}

/**
 * @brief 唤醒MPU6050
 */
esp_err_t bsp_mpu6050_wake_up(void)
{
    uint8_t pwr_mgmt_1 = 0; // 清除睡眠位
    return mpu6050_write_reg(MPU6050_PWR_MGMT_1, pwr_mgmt_1);
}

/**
 * @brief 使MPU6050进入睡眠模式
 */
esp_err_t bsp_mpu6050_sleep(void)
{
    uint8_t pwr_mgmt_1 = 1 << 6; // 设置睡眠位
    return mpu6050_write_reg(MPU6050_PWR_MGMT_1, pwr_mgmt_1);
}

/**
 * @brief 配置MPU6050的量程
 */
esp_err_t bsp_mpu6050_config(bsp_mpu6050_acce_fs_t acce_fs, bsp_mpu6050_gyro_fs_t gyro_fs)
{
    esp_err_t ret = mpu6050_write_reg(MPU6050_ACCEL_CONFIG, acce_fs << 3);
    if (ret != ESP_OK) return ret;
    return mpu6050_write_reg(MPU6050_GYRO_CONFIG, gyro_fs << 3);
}

/**
 * @brief 获取加速度计的灵敏度
 */
esp_err_t bsp_mpu6050_get_acce_sensitivity(float *acce_sensitivity)
{
    uint8_t acce_fs;
    esp_err_t ret = mpu6050_read_bytes(MPU6050_ACCEL_CONFIG, &acce_fs, 1);
    acce_fs = (acce_fs >> 3) & 0x03;
    switch (acce_fs) {
        case ACCE_FS_2G:  *acce_sensitivity = 16384; break;
        case ACCE_FS_4G:  *acce_sensitivity = 8192;  break;
        case ACCE_FS_8G:  *acce_sensitivity = 4096;  break;
        case ACCE_FS_16G: *acce_sensitivity = 2048;  break;
        default: break;
    }
    return ret;
}

/**
 * @brief 获取陀螺仪的灵敏度
 */
esp_err_t bsp_mpu6050_get_gyro_sensitivity(float *gyro_sensitivity)
{
    uint8_t gyro_fs;
    esp_err_t ret = mpu6050_read_bytes(MPU6050_GYRO_CONFIG, &gyro_fs, 1);
    gyro_fs = (gyro_fs >> 3) & 0x03;
    switch (gyro_fs) {
        case GYRO_FS_250DPS:  *gyro_sensitivity = 131;   break;
        case GYRO_FS_500DPS:  *gyro_sensitivity = 65.5;  break;
        case GYRO_FS_1000DPS: *gyro_sensitivity = 32.8;  break;
        case GYRO_FS_2000DPS: *gyro_sensitivity = 16.4;  break;
        default: break;
    }
    return ret;
}

/**
 * @brief 获取原始加速度计数据
 */
esp_err_t bsp_mpu6050_get_raw_acce(bsp_mpu6050_raw_acce_value_t *raw_acce_value)
{
    uint8_t data_rd[6];
    esp_err_t ret = mpu6050_read_bytes(MPU6050_ACCEL_XOUT_H, data_rd, 6);
    raw_acce_value->raw_acce_x = (int16_t)((data_rd[0] << 8) | data_rd[1]);
    raw_acce_value->raw_acce_y = (int16_t)((data_rd[2] << 8) | data_rd[3]);
    raw_acce_value->raw_acce_z = (int16_t)((data_rd[4] << 8) | data_rd[5]);
    return ret;
}

/**
 * @brief 获取原始陀螺仪数据
 */
esp_err_t bsp_mpu6050_get_raw_gyro(bsp_mpu6050_raw_gyro_value_t *raw_gyro_value)
{
    uint8_t data_rd[6];
    esp_err_t ret = mpu6050_read_bytes(MPU6050_GYRO_XOUT_H, data_rd, 6);
    raw_gyro_value->raw_gyro_x = (int16_t)((data_rd[0] << 8) | data_rd[1]);
    raw_gyro_value->raw_gyro_y = (int16_t)((data_rd[2] << 8) | data_rd[3]);
    raw_gyro_value->raw_gyro_z = (int16_t)((data_rd[4] << 8) | data_rd[5]);
    return ret;
}

/**
 * @brief 获取温度数据
 */
esp_err_t bsp_mpu6050_get_temp(float *temp)
{
    uint8_t data_rd[2];
    esp_err_t ret = mpu6050_read_bytes(MPU6050_TEMP_XOUT_H, data_rd, 2);
    int16_t raw_temp = (int16_t)((data_rd[0] << 8) | data_rd[1]);
    // 转换为摄氏度
    *temp = raw_temp / 340.0 + 36.53;
    return ret;
}