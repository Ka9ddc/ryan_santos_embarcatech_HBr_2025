#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "ssd1306/ssd1306.h"

#define BUTTON_A 5
#define BUTTON_B 6

volatile bool counting = false;
volatile uint8_t counter = 0;
volatile uint8_t click_count = 0;

ssd1306_t disp;

// ATUALIZAR O DISPLAY COM OS NOVOS VALORES
void update_display() {
    char buffer[32];
    ssd1306_clear(&disp);
    sprintf(buffer, "Contador: %d", counter);
    ssd1306_draw_string(&disp, 0, 0, 1, buffer);
    sprintf(buffer, "Cliques B: %d", click_count);
    ssd1306_draw_string(&disp, 0, 16, 1, buffer);
    ssd1306_show(&disp);
}


// FUNÇÃO DE CALLBACK DA INTERRUPÇÃO
void gpio_callback(uint gpio, uint32_t events) {
    static absolute_time_t last_click_time = {0};

    if (gpio == BUTTON_A && (events & GPIO_IRQ_EDGE_FALL)) {
        counter = 9;
        click_count = 0;
        counting = true;
        update_display();
    }
    else if (gpio == BUTTON_B && (events & GPIO_IRQ_EDGE_FALL)) {
        absolute_time_t now = get_absolute_time();
        if (counting && absolute_time_diff_us(last_click_time, now) > 200000) {
            click_count++;
            last_click_time = now;
            update_display();
        }
    }
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

    // INCIALIZAÇÃO DOS BOTÕES
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    // INTERRUPÇÕES
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled(BUTTON_B, GPIO_IRQ_EDGE_FALL, true);

    update_display();

    // LOOP PRINCIPAL
    while (true) {
        if (counting) {
            sleep_ms(1000);
            if (counter > 0) {
                counter--;
                update_display();
            } else {
                counting = false;
                update_display();
            }
        } else {
            sleep_ms(100);
        }
    }
}