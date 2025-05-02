#include "hal_led.h"
#include "led_embutido.h"

static bool estado_led = false;

bool hal_led_init(void) {
    return led_embutido_init();
}

void hal_led_toggle(void) {
    if (estado_led) {
        led_embutido_off();
        estado_led = false;
    } else {
        led_embutido_on();
        estado_led = true;
    }
}
