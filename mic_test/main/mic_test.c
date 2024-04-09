#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "esp_system.h"
#include <math.h>  // Include the math library

// Define the I2S number to be used
#define I2S_NUM (I2S_NUM_0)

// I2S configuration for INMP441 microphone
i2s_config_t i2s_config = {
    .mode = I2S_MODE_MASTER | I2S_MODE_RX,
    .sample_rate = 44100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = 1024,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
};

// I2S pin configuration
i2s_pin_config_t pin_config = {
    .bck_io_num = 6, // Bit Clock
    .ws_io_num = 5,  // Word Select
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = 4  // Data in
};

void app_main() {
    // Install and start i2s driver
    i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM, &pin_config);

    // Buffer to read data into
    size_t bytes_read;
    uint8_t i2s_read_buff[1024];

    // Variables for calculating RMS
    double rms = 0;
    int count = 0;

    while (1) {
        // Read data from the I2S peripheral
        i2s_read(I2S_NUM, &i2s_read_buff, sizeof(i2s_read_buff), &bytes_read, portMAX_DELAY);
        
        // Calculate RMS
        for (int i = 0; i < sizeof(i2s_read_buff) / sizeof(int32_t); i++) {
            int32_t sample = ((int32_t *)i2s_read_buff)[i];
            rms += sample * sample;
            count++;
        }

        // Print RMS value every 1000 iterations
        if (count >= 1000) {
            rms = sqrt(rms / count);
            printf("\rRMS: %f", rms);  // Use \r to return to the start of the line
            fflush(stdout);  // Flush the output buffer to ensure the line is printed immediately
            rms = 0;
            count = 0;
        }
    }
}