#ifndef GALTON_H
#define GALTON_H

#include <stdbool.h>

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define NUM_CANALETAS 16
#define MAX_BOLAS 10

typedef struct {
    int x;
    int y;
    int tick_proximo_pino;
    bool ativa;
} Bola;

void galton_tick();
Bola* galton_get_bolas();
int* galton_get_histograma();
int galton_get_total_bolas();

#endif
