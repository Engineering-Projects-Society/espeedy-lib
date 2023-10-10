
#ifndef ESPEEDY_ESP_DEFINES_H
#define ESPEEDY_ESP_DEFINES_H

#define ACK_CHECK_EN                    0x1                                 /*!< I2C master will check ack from slave */
#define ACK_CHECK_DIS                   0x0                                 /*!< I2C master will not check ack from slave */

#define ESPEEDY_ERROR_CHECKS_ENABLE     true                                /*!< enable additional error checks */

#define ESPEEDY_I2C_CONTROL_PORT_NUM    0                                   /*!< I2C port number for control */
#define ESPEEDY_I2C_CONTROL_SCL_IO      10                                  /*!< gpio number for I2C control clock */
#define ESPEEDY_I2C_CONTROL_SDA_IO      11                                  /*!< gpio number for I2C control data  */
#define ESPEEDY_I2C_CONTROL_FREQ_HZ     100000                              /*!< I2C control clock frequency */
#define ESPEEDY_I2C_CONTROL_TIMEOUT     1000                                /*!< number of I2C ticks to wait for timeout */
#define ESPEEDY_I2C_CONTROL_ACK_CHECK   ACK_CHECK_EN                        /*!< should I2C master check for ACK */

#define ESPEEDY_I2C_CONTROL_STM_ADDRESS 0x01                                /*!< address of the STM on I2C bus */

#define ESPEEDY_STM_CHANNEL_TYPE        uint8_t                             /*!< type to use to select STM channel */
#define ESPEEDY_STM_SENSOR_COUNT        12                                  /*!< number of data points to read from STM */
#define ESPEEDY_STM_SENSOR_TYPE         uint16_t                            /*!< type of data points to read from STM */
#define ESPEEDY_STM_REGISTER_COUNT      12                                  /*!< number of data registers writable for STM */
#define ESPEEDY_STM_REGISTER_TYPE       uint8_t                             /*!< type of data registers writable for STM */

#define ESPEEDY_STM_REGISTER_ID_MOTOR_L 7
#define ESPEEDY_STM_REGISTER_ID_MOTOR_R 6

#define ESPEEDY_STM_SENSOR_ID_ECHO      0
#define ESPEEDY_STM_SENSOR_ID_IR_0      1
#define ESPEEDY_STM_SENSOR_ID_IR_1      2
#define ESPEEDY_STM_SENSOR_ID_IR_2      3
#define ESPEEDY_STM_SENSOR_ID_IR_3      4
#define ESPEEDY_STM_SENSOR_ID_IR_4      5
#define ESPEEDY_STM_SENSOR_ID_IR_5      6
#define ESPEEDY_STM_SENSOR_ID_IR_BL     7
#define ESPEEDY_STM_SENSOR_ID_IR_BR     8

#endif //ESPEEDY_ESP_DEFINES_H
