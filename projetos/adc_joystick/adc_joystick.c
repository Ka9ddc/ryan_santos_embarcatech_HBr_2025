#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "ssd1306/ssd1306.h"

#define I2C_PORT i2c1
#define OLED_SDA 14
#define OLED_SCL 15

#define JOY_X 26  // ADC0
#define JOY_Y 27  // ADC1

ssd1306_t disp;

// ATUALIZAR O DISPLAY COM OS NOVOS VALORES
void update_display(uint16_t x, uint16_t y) {
    char buffer[32];
    ssd1306_clear(&disp);
    
    sprintf(buffer, "X: %d", x);
    ssd1306_draw_string(&disp, 0, 0, 1, buffer);
    
    sprintf(buffer, "Y: %d", y);
    ssd1306_draw_string(&disp, 0, 16, 1, buffer);

    ssd1306_show(&disp);
}

int main() {
    stdio_init_all();

    // INICIALIZA I2C PARA O DISPLAY
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(OLED_SDA, GPIO_FUNC_I2C);
    gpio_set_function(OLED_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(OLED_SDA);
    gpio_pull_up(OLED_SCL);
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);

    // INICIALIZA ADC
    adc_init();
    adc_gpio_init(JOY_Y);
    adc_gpio_init(JOY_X);

    // LOOP PRINCIPAL
    while (1) {
        adc_select_input(0);
        uint16_t y = adc_read();

        adc_select_input(1);
        uint16_t x = adc_read();

        update_display(x, y);
        sleep_ms(200);
    }
}