#include <stdio.h>
#include "sensor_temp.h"
#include "hal_temp.h"

int main() {
    init_sensor();
    while (1) {
        float tensao = read_tension_sensor();
        float temperatura = adc_to_celsius(tensao);
        printf("Temperatura: %.2f C\n", temperatura);
        sleep_ms(1000);
    }
    return 0;
}