#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "ssd1306/ssd1306.h"

ssd1306_t disp;

// ATUALIZAR O DISPLAY COM OS NOVOS VALORES
void update_display(float temp_c) {
    char buffer[32];
    ssd1306_clear(&disp);
    
    sprintf(buffer, "Temperatura: %.2f C\n", temp_c);
    ssd1306_draw_string(&disp, 0, 0, 1, buffer);

    ssd1306_show(&disp);
}

float read_temperature() {
    adc_select_input(4);  // CANAL DO SENSOR DE TEMPERATURA INTERNO
    uint16_t raw = adc_read();

    float voltage = raw * 3.3f / 4095.0f;

    float temperature = 27.0f - (voltage - 0.706f) / 0.001721f;

    return temperature;
}

int main() {
    stdio_init_all();

    // INICIALIZA I2C PARA O DISPLAY
    i2c_init(i2c1, 400 * 1000);
    gpio_set_function(14, GPIO_FUNC_I2C); // SDA
    gpio_set_function(15, GPIO_FUNC_I2C); // SCL
    gpio_pull_up(14);
    gpio_pull_up(15);
    ssd1306_init(&disp, 128, 64, 0X3C, i2c1);

    // INICIALIZA ADC PARA O SENSOR DE TEMPERATURA
    adc_init();
    adc_set_temp_sensor_enabled(true);

    while (true) {
        float temp_c = read_temperature();
        update_display(temp_c);
        sleep_ms(1000);
    }
}