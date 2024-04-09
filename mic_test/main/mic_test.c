#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "esp_system.h"
#include "esp_http_client.h"


extern const uint8_t google_cloud_cert_pem_start[] asm("_binary_google_cloud_cert_pem_start");

// Declare the extract_transcribed_text function
char* extract_transcribed_text(char* response) {
    // TODO: Implement this function
    return NULL;
}

#define I2S_NUM (I2S_NUM_0)

i2s_config_t i2s_config = {
    .mode = I2S_MODE_MASTER | I2S_MODE_RX,
    .sample_rate = 44100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,  // Use the non-deprecated format
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = 1024,
};

// I2S pin configuration
i2s_pin_config_t pin_config = {
    .bck_io_num = 6, // Bit Clock
    .ws_io_num = 5,  // Word Select
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = 4  // Data in
};

esp_http_client_handle_t init_http_client() {
    esp_http_client_config_t config = {
        .url = "https://speech.googleapis.com/v1/speech:recognize",
        .cert_pem = (const char *)google_cloud_cert_pem_start,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_header(client, "Authorization", "AIzaSyCve23uxvNmbn7NXutxKLsQs-T9ZxRY0-I");
    return client;
}

void app_main() {
    esp_http_client_handle_t client = init_http_client();
    i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM, &pin_config);

    // Buffer to read data into
    size_t bytes_read;
    uint8_t i2s_read_buff[1024];

    while (1) {
        // Read data from the I2S peripheral
        i2s_read(I2S_NUM, &i2s_read_buff, sizeof(i2s_read_buff), &bytes_read, portMAX_DELAY);
        
        // Send the audio data to a speech-to-text service
        esp_http_client_set_url(client, "https://speech.googleapis.com/v1/speech:recognize");
        esp_http_client_set_method(client, HTTP_METHOD_POST);
        esp_http_client_set_post_field(client, (const char *)i2s_read_buff, bytes_read);
        esp_http_client_perform(client);

        // Check the response status and read the response data
        if (esp_http_client_get_status_code(client) == 200) {
            int total_len = esp_http_client_get_content_length(client);
            char* response = malloc(total_len + 1);
            esp_http_client_read(client, response, total_len);

            // Extract the transcribed text from the response
            char* transcribed_text = extract_transcribed_text(response);

            // Print the transcribed text to the terminal
            printf("%s\n", transcribed_text);

            // Free the allocated memory
            free(response);
            free(transcribed_text);
        }
    }
}