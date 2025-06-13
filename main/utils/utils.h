#ifndef __INC_UTILS_H
#define __INC_UTILS_H

#include <stdint.h>
#include "freertos/FreeRTOS.h"

#define delayMS(ms) (vTaskDelay(pdMS_TO_TICKS(ms)) )

#endif