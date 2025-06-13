#include "wifi.h"

bool __WIFI_CONNECTED = false;

esp_err_t init_wifi(const char* const ssid, const char* const pass){
    ESP_LOGI(WIFI_TAG, "Initializing WiFi...");

    ESP_LOGI(WIFI_TAG, "Initializing nvs flash");
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);    
    
    ESP_LOGI(WIFI_TAG, "Initializing netif and event loop");
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    ESP_LOGI(WIFI_TAG, "Creating default configuration");
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t conf = {
        .sta = {
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
            .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
            .sae_h2e_identifier = "",
        }
    };

    memcpy(&conf.sta.ssid, ssid, strlen(ssid));
    memcpy(&conf.sta.password, pass, strlen(pass));

    ESP_LOGI(WIFI_TAG, "Setting mode");
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &conf));

    ESP_LOGI(WIFI_TAG, "Starting WiFi...");
    ESP_ERROR_CHECK(esp_wifi_start());

    wifi_connect();

    return ESP_OK;
}

esp_err_t wifi_connect(){
    ESP_LOGI(WIFI_TAG, "Connecting...");
    esp_err_t err = esp_wifi_connect();

    return err;
}

esp_err_t check_wifi_conn(){
    wifi_ap_record_t ap_info;
    esp_err_t err = esp_wifi_sta_get_ap_info(&ap_info);

    ESP_LOGI(WIFI_TAG, "Checking WiFi connection...");

    if(err == ESP_OK){
        __WIFI_CONNECTED = true;
        ESP_LOGI(WIFI_TAG, "Connected");
    }else{
        __WIFI_CONNECTED = false;
        ESP_LOGI(WIFI_TAG, "Not connected, trying to reconnect...");
        wifi_connect();
    }

    return err;
}