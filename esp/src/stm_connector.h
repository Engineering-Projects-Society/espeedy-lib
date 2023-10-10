
#ifndef ESPEEDY_LIB_ESP32_STM_CONNECTOR_H
#define ESPEEDY_LIB_ESP32_STM_CONNECTOR_H

#include <Wire.h>
#include <cstdint>

#include "defines.h"


class STMConnector {
  private:
    inline static bool active = false;

    static int installDriver();

  public:
    STMConnector();

    /// Writes data to specified channel
    /// \param channel Index of channel to write to
    /// \param data Chunk of data to return
    /// \return ESP error code, 0 is success
    static int writeChannel(ESPEEDY_STM_CHANNEL_TYPE channel, ESPEEDY_STM_REGISTER_TYPE data);

    /// Reads single data point from channel
    /// \param channel Index of channel to read from, must be lower than ESPEEDY_STM_SENSOR_COUNT
    /// \param data Pointer where to write the acquired data to
    /// \return ESP error code, 0 is success
    static int readChannel(ESPEEDY_STM_CHANNEL_TYPE channel, ESPEEDY_STM_SENSOR_TYPE* data);

    /// Reads array of data points from all channels
    /// \param data Pointer to array of size ESPEEDY_STM_SENSOR_COUNT to write data to
    /// \return ESP error code, 0 is success
    static int readAll(ESPEEDY_STM_SENSOR_TYPE* data);
};

#endif //ESPEEDY_LIB_ESP32_STM_CONNECTOR_H
