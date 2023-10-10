
#pragma once

#ifndef ESPEEDY_ESP_UNIFORM_SENSOR_H
#define ESPEEDY_ESP_UNIFORM_SENSOR_H

#include "stm_connector.h"
#include <array>
#include <bitset>


class UniformSensorAccess {
  private:
    static std::array<ESPEEDY_STM_SENSOR_TYPE, ESPEEDY_STM_SENSOR_COUNT> data;
    static std::bitset<ESPEEDY_STM_SENSOR_COUNT> read;
    inline static bool autoUpdate = true;

  public:
    inline UniformSensorAccess() { STMConnector(); }

    static int update();
    static ESPEEDY_STM_SENSOR_TYPE get(ESPEEDY_STM_CHANNEL_TYPE channel);
    static void setAutoUpdate(bool behaviour) { autoUpdate = behaviour; }
};

#endif //ESPEEDY_ESP_UNIFORM_SENSOR_H
