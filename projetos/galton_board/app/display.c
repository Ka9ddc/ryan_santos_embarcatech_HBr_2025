#include "include/display.h"
#include "drivers/ssd1306/ssd1306.h"
#include "include/galton.h"

extern ssd1306_t display;

void display_render() {
    ssd1306_clear(&display);
    desenhar_histograma();
    desenhar_bolas();
    desenhar_contador();
    ssd1306_show(&display);
}

void desenhar_histograma() {
    int* hist = galton_get_histograma();

    for (int i = 0; i < NUM_CANALETAS; i++) {
        int altura = hist[i];
        if (altura > DISPLAY_HEIGHT) altura = DISPLAY_HEIGHT;
        int x_inicio = i * (DISPLAY_WIDTH / NUM_CANALETAS);

        for (int y = DISPLAY_HEIGHT - 1; y >= DISPLAY_HEIGHT - altura; y--) {
            for (int x = 0; x < (DISPLAY_WIDTH / NUM_CANALETAS); x++) {
                ssd1306_draw_pixel(&display, x_inicio + x, y);
            }
        }
    }
}

void desenhar_bolas() {
    Bola* bolas = galton_get_bolas();
    for (int i = 0; i < MAX_BOLAS; i++) {
        if (bolas[i].ativa) {
            ssd1306_draw_pixel(&display, bolas[i].x, bolas[i].y);
        }
    }
}

void desenhar_contador() {
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "Total: %d", galton_get_total_bolas());
    ssd1306_draw_string(&display, 0, 0, 1, buffer);
}
