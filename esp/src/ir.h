//
// Created by RedNicStone on 09/10/23.
//


#pragma once

#ifndef ESPEEDY_ESP_IR_H
#define ESPEEDY_ESP_IR_H

#include "uniform_sensor.h"


enum IRKind : uint8_t {
    IR_KIND_O   = ESPEEDY_STM_SENSOR_ID_IR_0,
    IR_KIND_1   = ESPEEDY_STM_SENSOR_ID_IR_1,
    IR_KIND_2   = ESPEEDY_STM_SENSOR_ID_IR_2,
    IR_KIND_3   = ESPEEDY_STM_SENSOR_ID_IR_3,
    IR_KIND_4   = ESPEEDY_STM_SENSOR_ID_IR_4,
    IR_KIND_5   = ESPEEDY_STM_SENSOR_ID_IR_5,
    IR_KIND_BL  = ESPEEDY_STM_SENSOR_ID_IR_BL,
    IR_KIND_BR  = ESPEEDY_STM_SENSOR_ID_IR_BR,
};

template<IRKind kind>
class IRSensor {
  public:
    inline IRSensor() { UniformSensorAccess(); }

    inline static uint16_t getRaw() { return UniformSensorAccess::get(kind); }
    inline static int update() { return UniformSensorAccess::update(); }
};

typedef IRSensor<IR_KIND_O>     IRSensor0;
typedef IRSensor<IR_KIND_1>     IRSensor1;
typedef IRSensor<IR_KIND_2>     IRSensor2;
typedef IRSensor<IR_KIND_3>     IRSensor3;
typedef IRSensor<IR_KIND_4>     IRSensor4;
typedef IRSensor<IR_KIND_5>     IRSensor5;
typedef IRSensor<IR_KIND_BL>    IRSensorBL;
typedef IRSensor<IR_KIND_BR>    IRSensorBR;

#endif //ESPEEDY_ESP_IR_H
