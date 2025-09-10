#include "bsp_iis_MAX98357A.h"
#include "driver/i2s_std.h"
#include "esp_check.h"
#include "esp_log.h"
#include "driver/gpio.h"

static const char *TAG = "BSP_MAX98357A";
static i2s_chan_handle_t tx_chan; // I2S tx channel handler

esp_err_t bsp_iis_max98357a_init(uint32_t sample_rate)
{
    /* Initialize SD_MODE GPIO */
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BSP_I2S_SD_MODE_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);
    gpio_set_level(BSP_I2S_SD_MODE_PIN, 1);

    /* Initialize GAIN_PIN GPIO */
    gpio_config_t gain_io_conf = {
        .pin_bit_mask = (1ULL << BSP_I2S_GAIN_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&gain_io_conf);

    /* Setp 1: Determine the I2S channel configuration and allocate a TX channel */
    i2s_chan_config_t tx_chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_AUTO, I2S_ROLE_MASTER);
    ESP_RETURN_ON_ERROR(i2s_new_channel(&tx_chan_cfg, &tx_chan, NULL), TAG, "Failed to create new I2S channel");

    /* Step 2: Setting the configurations of standard mode */
    i2s_std_config_t tx_std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(sample_rate),
        .slot_cfg = {
            .data_bit_width = I2S_DATA_BIT_WIDTH_16BIT,
            .slot_bit_width = I2S_SLOT_BIT_WIDTH_AUTO,
            .slot_mode = I2S_SLOT_MODE_MONO,
            .slot_mask = I2S_STD_SLOT_LEFT,
            .ws_width = I2S_DATA_BIT_WIDTH_16BIT,
            .ws_pol = false,
            .bit_shift = true,
        },
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = BSP_I2S_BCLK_PIN,
            .ws = BSP_I2S_WS_PIN,
            .dout = BSP_I2S_DOUT_PIN,
            .din = I2S_GPIO_UNUSED,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };
    ESP_RETURN_ON_ERROR(i2s_channel_init_std_mode(tx_chan, &tx_std_cfg), TAG, "Failed to init I2S channel");

    /* Step 3: Channel is not enabled here, it will be enabled by the player task before writing data */
    return ESP_OK;
}

esp_err_t bsp_iis_max98357a_set_gain(uint8_t gain_db)
{
    switch (gain_db) {
        case 15:
            gpio_set_level(BSP_I2S_GAIN_PIN, 1);
            break;
        case 12:
            gpio_set_level(BSP_I2S_GAIN_PIN, 0);
            break;
        default:
            return ESP_ERR_INVALID_ARG;
    }
    return ESP_OK;
}

esp_err_t bsp_iis_max98357a_write(const void *src, size_t data_size, size_t *bytes_written, uint32_t timeout_ms)
{
    if (tx_chan == NULL || src == NULL || bytes_written == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    return i2s_channel_write(tx_chan, src, data_size, bytes_written, timeout_ms);
}

esp_err_t bsp_iis_max98357a_deinit(void)
{
    if (tx_chan) {
        ESP_RETURN_ON_ERROR(i2s_channel_disable(tx_chan), TAG, "Failed to disable channel");
        ESP_RETURN_ON_ERROR(i2s_del_channel(tx_chan), TAG, "Failed to delete channel");
        tx_chan = NULL;
    }
    gpio_reset_pin(BSP_I2S_SD_MODE_PIN);
    return ESP_OK;
}
esp_err_t bsp_iis_max98357a_disable(void)
{
    if (tx_chan) {
        return i2s_channel_disable(tx_chan);
    }
    return ESP_OK;
}

esp_err_t bsp_iis_max98357a_enable(void)
{
    if (tx_chan) {
        return i2s_channel_enable(tx_chan);
    }
    return ESP_ERR_INVALID_STATE;
}

esp_err_t bsp_iis_max98357a_stop(void)
{
    return bsp_iis_max98357a_disable();
}

esp_err_t bsp_iis_max98357a_reconfig_clk(uint32_t sample_rate)
{
    if (tx_chan == NULL) {
        return ESP_ERR_INVALID_STATE;
    }
    i2s_std_clk_config_t clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(sample_rate);
    esp_err_t ret = i2s_channel_reconfig_std_clock(tx_chan, &clk_cfg);
    return ret;
}