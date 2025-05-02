#include "hal_temp.h"

float adc_to_celsius(float tensao) {
    return 27.0f - ((tensao - 0.706f) / 0.001721f);
}
