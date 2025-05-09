#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "drivers/ssd1306/ssd1306.h"
#include "include/galton.h"
#include "include/hal_i2c.h"
#include "include/display.h"

ssd1306_t display;

void init_i2c_display() {

    hal_i2c_init();
    ssd1306_init(&display, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0x3C, i2c1);;
    ssd1306_clear(&display);
    ssd1306_show(&display);

}

int main() {
    stdio_init_all();
    init_i2c_display();

    while (true) {
        galton_tick();
        display_render();
        sleep_ms(50);
    }

    return 0;
}
