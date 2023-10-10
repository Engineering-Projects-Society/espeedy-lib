
#ifndef ESPEEDY_LIB_ESP32_MOTOR_H
#define ESPEEDY_LIB_ESP32_MOTOR_H

#include "stm_connector.h"


enum MotorKind : uint8_t {
    MOTOR_KIND_LEFT     = ESPEEDY_STM_REGISTER_ID_MOTOR_L,
    MOTOR_KIND_RIGHT    = ESPEEDY_STM_REGISTER_ID_MOTOR_R
};

template<MotorKind kind>
class Motor {
  private:
    inline static int8_t currentPower = 0;

  public:
    inline Motor() { STMConnector(); }

    inline static void setPower(int8_t power) { if (!STMConnector::writeChannel(kind, power)) currentPower = power; }
    [[nodiscard]] inline static int8_t getPower() { return currentPower; }
};

typedef Motor<MOTOR_KIND_LEFT> MotorL;
typedef Motor<MOTOR_KIND_RIGHT> MotorR;

#endif //ESPEEDY_LIB_ESP32_MOTOR_H
