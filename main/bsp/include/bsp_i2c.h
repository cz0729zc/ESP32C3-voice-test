#ifndef BSP_I2C_H_
#define BSP_I2C_H_

#include "driver/i2c.h"

/**
 * @brief 初始化I2C总线
 *
 * @param port I2C端口号
 * @param sda_pin SDA引脚的GPIO号
 * @param scl_pin SCL引脚的GPIO号
 * @param clk_speed I2C时钟频率
 * @return esp_err_t 错误码
 */
esp_err_t bsp_i2c_init(i2c_port_t port, int sda_pin, int scl_pin, uint32_t clk_speed);

/**
 * @brief 卸载I2C总线
 *
 * @param port I2C端口号
 * @return esp_err_t 错误码
 */
esp_err_t bsp_i2c_deinit(i2c_port_t port);

/**
 * @brief I2C写入字节
 *
 * @param port I2C端口号
 * @param dev_addr I2C设备地址
 * @param reg_addr 寄存器地址
 * @param data 要写入的数据
 * @param len 数据长度
 * @return esp_err_t 错误码
 */
esp_err_t bsp_i2c_write_bytes(i2c_port_t port, uint8_t dev_addr, uint8_t reg_addr, const uint8_t *data, uint8_t len);

/**
 * @brief I2C读取字节
 *
 * @param port I2C端口号
 * @param dev_addr I2C设备地址
 * @param reg_addr 寄存器地址
 * @param data 用于存储读取数据的数据缓冲区
 * @param len 数据长度
 * @return esp_err_t 错误码
 */
esp_err_t bsp_i2c_read_bytes(i2c_port_t port, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len);

#endif /* BSP_I2C_H_ */