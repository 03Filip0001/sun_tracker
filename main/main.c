#include "main.h"

#include "esp_log.h"

void app_main(void)
{
    esp_log_level_set(MAIN_1_TAG, ESP_LOG_INFO);
    esp_log_level_set(MAIN_2_TAG, ESP_LOG_INFO);

    ESP_LOGI(MAIN_1_TAG, "Creating task for 2nd core...");
    xTaskCreatePinnedToCore(app_wifi, "app_wifi", 4096, NULL, 0, NULL, CORE_ID_1);
    ESP_LOGI(MAIN_1_TAG, "Task 2 created on core %d", CORE_ID_1);

    ESP_LOGI(MAIN_1_TAG, "Starting infinite task on core %d", CORE_ID_0);
    while(1){
        
        ESP_LOGI("Core 1", "Running...");
        
        delay(500);
    }
}

void app_wifi(){
    ESP_LOGI(MAIN_2_TAG, "Task started on core %d", CORE_ID_1);

    ESP_LOGI(MAIN_2_TAG, "Starting infinite task on core %d", CORE_ID_1);
    while(1){

        ESP_LOGI("Core 2", "Running...");

        delay(1000);
    }
}