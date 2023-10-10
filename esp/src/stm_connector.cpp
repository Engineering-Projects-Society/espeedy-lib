
#include "stm_connector.h"

#include "driver/i2c.h"
#include "esp_err.h"

#define WRITE_BIT           I2C_MASTER_WRITE                            /*!< I2C master write */
#define READ_BIT            I2C_MASTER_READ                             /*!< I2C master read */

#define I2C_NUMBER_(num)    I2C_NUM_##num
#define I2C_NUMBER(num)     I2C_NUMBER_(num)
#define I2C_CONTROL_NUM     I2C_NUMBER(ESPEEDY_I2C_CONTROL_PORT_NUM)    /*!< I2C port name for control */


STMConnector::STMConnector() {
    if (!active)
        active = !installDriver();
}

int STMConnector::installDriver() {
    // write configuration data
    i2c_config_t conf {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = ESPEEDY_I2C_CONTROL_SDA_IO,
            .scl_io_num = ESPEEDY_I2C_CONTROL_SCL_IO,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
            .master {
                    .clk_speed = ESPEEDY_I2C_CONTROL_FREQ_HZ,
            }
    };

    // configure pins
    esp_err_t err = i2c_param_config(I2C_CONTROL_NUM, &conf);
    if (err != ESP_OK)
        return err;

    // install callback driver
    return i2c_driver_install(I2C_CONTROL_NUM, conf.mode, 0, 0, 0);
}

int STMConnector::writeChannel(ESPEEDY_STM_CHANNEL_TYPE channel, ESPEEDY_STM_REGISTER_TYPE data) {
    // check if this object and channel is valid
#if ESPEEDY_ERROR_CHECKS_ENABLE
    if (active)
        return ESP_ERR_INVALID_STATE;

    if (channel > ESPEEDY_STM_REGISTER_COUNT)
        return ESP_ERR_INVALID_ARG;
#endif
    
    // create and start a new link
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);

    // write address, channel number and data
    i2c_master_write_byte(cmd, ESPEEDY_I2C_CONTROL_STM_ADDRESS << 1 | WRITE_BIT, ESPEEDY_I2C_CONTROL_ACK_CHECK);
    i2c_master_write_byte(cmd, channel, ESPEEDY_I2C_CONTROL_ACK_CHECK);
    i2c_master_write_byte(cmd, data, ESPEEDY_I2C_CONTROL_ACK_CHECK);

    // close link and send data
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(I2C_CONTROL_NUM, cmd, ESPEEDY_I2C_CONTROL_FREQ_HZ);
    i2c_cmd_link_delete(cmd);

    if (ret != ESP_OK)
        return ret;
}

int STMConnector::readChannel(ESPEEDY_STM_CHANNEL_TYPE channel, ESPEEDY_STM_SENSOR_TYPE* data) {
    // check if this object and channel is valid
#if ESPEEDY_ERROR_CHECKS_ENABLE
    if (active)
        return ESP_ERR_INVALID_STATE;

    if (channel > ESPEEDY_STM_SENSOR_COUNT)
        return ESP_ERR_INVALID_ARG;
#endif
    
    // create and start a new link
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, ESPEEDY_I2C_CONTROL_STM_ADDRESS << 1 | READ_BIT, ESPEEDY_I2C_CONTROL_ACK_CHECK);

    // read but discard low-byte sensor data
    if (channel > 0)
        i2c_master_read(cmd, nullptr, channel * sizeof(ESPEEDY_STM_SENSOR_TYPE), I2C_MASTER_ACK);

    // read our wanted sensor data, send nack
    i2c_master_read(cmd, (uint8_t*) data, sizeof(ESPEEDY_STM_SENSOR_TYPE), I2C_MASTER_NACK);

    // close link and send data
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(I2C_CONTROL_NUM, cmd, ESPEEDY_I2C_CONTROL_TIMEOUT);
    i2c_cmd_link_delete(cmd);

    if (ret != ESP_OK)
        return ret;
}

int STMConnector::readAll(ESPEEDY_STM_SENSOR_TYPE *data) {
    // check if this object is valid
#if ESPEEDY_ERROR_CHECKS_ENABLE
    if (active)
        return ESP_ERR_INVALID_STATE;
#endif

    // create and start a new link
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);

    // write address and read data from bus
    i2c_master_write_byte(cmd, ESPEEDY_I2C_CONTROL_STM_ADDRESS << 1 | READ_BIT, ESPEEDY_I2C_CONTROL_ACK_CHECK);
    i2c_master_read(cmd, (uint8_t*) data, sizeof(ESPEEDY_STM_SENSOR_TYPE) * ESPEEDY_STM_SENSOR_COUNT, I2C_MASTER_LAST_NACK);

    // close link and send data
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(I2C_CONTROL_NUM, cmd, ESPEEDY_I2C_CONTROL_TIMEOUT);
    i2c_cmd_link_delete(cmd);

    if (ret != ESP_OK)
        return ret;
}
