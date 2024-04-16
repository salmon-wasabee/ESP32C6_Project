#ifndef MIC_TEST_H
#define MIC_TEST_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "esp_system.h"
#include "esp_http_client.h"
#include "math.h"
#include <app_wifi.h>

// extern const uint8_t google_cloud_cert_pem_start[] asm("_binary_google_cloud_cert_pem_start");

// char* extract_transcribed_text(char* response);
// esp_http_client_handle_t init_http_client();
extern double db;
extern char db_str[20];
void mic_main();


#endif // MIC_TEST_H