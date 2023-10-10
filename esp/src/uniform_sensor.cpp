
#include "uniform_sensor.h"


int UniformSensorAccess::update() {
    auto res = STMConnector::readAll(data.data());
    if (!res)
        read = 0;

    return res;
}

ESPEEDY_STM_SENSOR_TYPE UniformSensorAccess::get(ESPEEDY_STM_CHANNEL_TYPE channel) {
#if ESPEEDY_ERROR_CHECKS_ENABLE
    if (channel > ESPEEDY_STM_SENSOR_COUNT)
        return ESP_ERR_INVALID_ARG;
#endif

    std::bitset<ESPEEDY_STM_SENSOR_COUNT> mask = 1 << channel;
    if ((read & mask).any() & autoUpdate)
        update();

    read |= mask;
    return data[channel];
}
