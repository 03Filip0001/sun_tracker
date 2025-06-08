#ifndef __INC_CREDENTIALS_H
#define __INC_CREDENTIALS_H

#include <stdint.h>

// WiFi credentials
extern const char* const WIFI_SSID;
extern const char* const WIFI_PASS;

// Server credentials
extern const char* const    SERVER_IP;
extern const uint16_t       SERVER_PORT; 

#define MAIN_1_TAG "Main (core 1)"
#define MAIN_2_TAG "Main (core 2)"

#define WIFI_TAG "WiFi"

#endif