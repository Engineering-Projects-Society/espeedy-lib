//
// Created by RedNicStone on 10/10/23.
//


#pragma once

#ifndef ESPEEDY_ESP_ECHO_H
#define ESPEEDY_ESP_ECHO_H

#include "uniform_sensor.h"


class EchoSensor {
  public:
    inline EchoSensor() { UniformSensorAccess(); }

    inline static uint16_t getRaw() { return UniformSensorAccess::get(ESPEEDY_STM_SENSOR_ID_ECHO); }
    inline static int update() { return UniformSensorAccess::update(); }
};

#endif //ESPEEDY_ESP_ECHO_H
