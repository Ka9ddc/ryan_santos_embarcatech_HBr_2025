#include "hardware/adc.h"
#include "sensor_temp.h"

// Não necessária para os testes unitários

void init_sensor(void) {
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4); // canal do sensor interno
}

float read_tension_sensor(void) {
    uint16_t adc_val = adc_read();
    const float conversion_factor = 3.3f / (1 << 12);
    return adc_val * conversion_factor;
}
