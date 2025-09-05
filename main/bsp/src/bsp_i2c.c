#include "bsp_i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "bsp_i2c"; // 用于日志输出的标签

/**
 * @brief 初始化I2C总线
 */
esp_err_t bsp_i2c_init(i2c_port_t port, int sda_pin, int scl_pin, uint32_t clk_speed)
{
    // I2C配置结构体
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,             // 设置为I2C主模式
        .sda_io_num = sda_pin,               // SDA引脚
        .sda_pullup_en = GPIO_PULLUP_ENABLE, // 使能SDA内部上拉电阻
        .scl_io_num = scl_pin,               // SCL引脚
        .scl_pullup_en = GPIO_PULLUP_ENABLE, // 使能SCL内部上拉电阻
        .master.clk_speed = clk_speed,       // I2C时钟频率
        .clk_flags = 0,
    };
    // 配置I2C参数
    esp_err_t ret = i2c_param_config(port, &conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "I2C参数配置失败");
        return ret;
    }
    // 安装I2C驱动
    ret = i2c_driver_install(port, conf.mode, 0, 0, 0);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "I2C驱动安装失败");
        return ret;
    }
    return ESP_OK;
}

/**
 * @brief 卸载I2C总线
 */
esp_err_t bsp_i2c_deinit(i2c_port_t port)
{
    return i2c_driver_delete(port);
}

/**
 * @brief I2C写入字节
 */
esp_err_t bsp_i2c_write_bytes(i2c_port_t port, uint8_t dev_addr, uint8_t reg_addr, const uint8_t *data, uint8_t len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();                                  // 创建I2C命令链接
    i2c_master_start(cmd);                                                       // 发送起始位
    i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);         // 发送设备地址和写操作位
    i2c_master_write_byte(cmd, reg_addr, true);                                  // 发送寄存器地址
    i2c_master_write(cmd, data, len, true);                                      // 写入数据
    i2c_master_stop(cmd);                                                        // 发送停止位
    esp_err_t ret = i2c_master_cmd_begin(port, cmd, 1000 / portTICK_PERIOD_MS); // 执行命令
    i2c_cmd_link_delete(cmd);                                                    // 删除命令链接
    return ret;
}

/**
 * @brief I2C读取字节
 */
esp_err_t bsp_i2c_read_bytes(i2c_port_t port, uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();                                 // 创建I2C命令链接
    i2c_master_start(cmd);                                                      // 发送起始位
    i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);        // 发送设备地址和写操作位
    i2c_master_write_byte(cmd, reg_addr, true);                                 // 发送要读取的寄存器地址
    i2c_master_start(cmd);                                                      // 重新发送起始位
    i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_READ, true);         // 发送设备地址和读操作位
    i2c_master_read(cmd, data, len, I2C_MASTER_LAST_NACK);                      // 读取数据
    i2c_master_stop(cmd);                                                       // 发送停止位
    esp_err_t ret = i2c_master_cmd_begin(port, cmd, 1000 / portTICK_PERIOD_MS); // 执行命令
    i2c_cmd_link_delete(cmd);                                                   // 删除命令链接
    return ret;
}