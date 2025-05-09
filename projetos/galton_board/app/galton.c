#include <stdlib.h>
#include "include/galton.h"

static int ticks = 0;
static int total_bolas = 0;
static int histograma[NUM_CANALETAS] = {0};
static Bola bolas[MAX_BOLAS];

int galton_get_total_bolas() {
    return total_bolas;
}

int* galton_get_histograma() {
    return histograma;
}

Bola* galton_get_bolas() {
    return bolas;
}

void galton_tick() {
    ticks++;

    if (ticks % 10 == 0) {
        for (int i = 0; i < MAX_BOLAS; i++) {
            if (!bolas[i].ativa) {
                inicializar_bola(&bolas[i]);
                total_bolas++;
                break;
            }
        }
    }

    for (int i = 0; i < MAX_BOLAS; i++) {
        if (bolas[i].ativa) {
            atualizar_bola(&bolas[i]);
            if (!bolas[i].ativa) {
                int canaleta = bolas[i].x / (DISPLAY_WIDTH / NUM_CANALETAS);
                if (canaleta >= 0 && canaleta < NUM_CANALETAS) {
                    histograma[canaleta]++;
                }
            }
        }
    }
}

void inicializar_bola(Bola* b) {
    b->x = DISPLAY_WIDTH / 2;
    b->y = 0;
    b->tick_proximo_pino = 0;
    b->ativa = true;
}

void atualizar_bola(Bola* b) {
    if (!b->ativa) return;

    b->y += 1;

    if (b->y % 8 == 0) {
        int dir = rand() % 2;
        b->x += (dir == 0) ? -4 : 4;
        if (b->x < 0) b->x = 0;
        if (b->x >= DISPLAY_WIDTH) b->x = DISPLAY_WIDTH - 1;
    }

    if (b->y >= DISPLAY_HEIGHT - 1) {
        b->ativa = false;
    }
}
