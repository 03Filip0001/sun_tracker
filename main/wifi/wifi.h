#ifndef __INC_WIFI_H
#define __INC_WIFI_H

#include <string.h>

#include "esp_check.h"
#include "esp_log.h"

#include "nvs_flash.h"
#include "esp_wifi.h"

#include "utils/utils.h"
#include "credentials.h"

esp_err_t init_wifi(const char* const ssid, const char* const pass);
esp_err_t wifi_connect();
esp_err_t check_wifi_conn();

#endif