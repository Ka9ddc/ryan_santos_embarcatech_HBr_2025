#ifndef HAL_I2C_H
#define HAL_I2C_H

#include "hardware/i2c.h"

void hal_i2c_init();

i2c_inst_t* hal_get_i2c_instance();

#endif
