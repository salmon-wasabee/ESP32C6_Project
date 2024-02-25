#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#ifdef CONFIG_BLINK_LED_RMT
#include "led_strip.h"
#endif
#include "dht.h"
#include "u8g2_esp32_hal.h"
#include "u8g2.h"

static const char *TAG = "example";

// Define your OLED pins here
#define OLED_CLOCK_PIN 22
#define OLED_DATA_PIN  21

// Initialize the OLED display structure
u8g2_t u8g2;

#ifdef CONFIG_BLINK_LED_RMT
static led_strip_handle_t led_strip;
#endif

static uint8_t s_led_state = 0;
static int color_index = 0; // New variable to keep track of the current color

#ifdef CONFIG_BLINK_LED_RMT

// Function to blink addressable LED with different colors
static void blink_led(void) {
    /* Define colors for the RGB spectrum */
    uint32_t colors[7][3] = {
        {255, 0, 0},    // Red
        {255, 127, 0},  // Orange
        {255, 255, 0},  // Yellow
        {0, 255, 0},    // Green
        {0, 0, 255},    // Blue
        {75, 0, 130},   // Indigo
        {148, 0, 211}   // Violet
    };

    if (s_led_state) {
        led_strip_set_pixel(led_strip, 0, colors[color_index][0], colors[color_index][1], colors[color_index][2]);
        led_strip_refresh(led_strip);
    } else {
        led_strip_clear(led_strip);
    }
    color_index = (color_index + 1) % 7;
}

// Configuration for addressable LED
static void configure_led(void) {
    ESP_LOGI(TAG, "Configuring addressable LED");
    led_strip_config_t strip_config = {
        .strip_gpio_num = CONFIG_BLINK_GPIO,
        .max_leds = 1,
    };
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000,
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    led_strip_clear(led_strip);
}

#elif CONFIG_BLINK_LED_GPIO

// Function to blink a regular LED
static void blink_led(void) {
    gpio_set_level(CONFIG_BLINK_GPIO, s_led_state);
}

// Configuration for regular LED
static void configure_led(void) {
    ESP_LOGI(TAG, "Configuring GPIO LED");
    gpio_reset_pin(CONFIG_BLINK_GPIO);
    gpio_set_direction(CONFIG_BLINK_GPIO, GPIO_MODE_OUTPUT);
}

#endif

// Function to initialize and blink the OLED display
void oled_blink_task(void *pvParameter) {
    // OLED display initialization
    u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
    u8g2_esp32_hal.sda = OLED_DATA_PIN;
    u8g2_esp32_hal.scl = OLED_CLOCK_PIN;
    u8g2_esp32_hal_init(u8g2_esp32_hal);
    u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8g2_esp32_i2c_byte_cb, u8g2_esp32_gpio_and_delay_cb);
    u8x8_SetI2CAddress(&u8g2.u8x8,0x78);
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);

    while(1) {
        // Blink the OLED screen
        u8g2_ClearBuffer(&u8g2);
        u8g2_SendBuffer(&u8g2);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        u8g2_SetDrawColor(&u8g2, 1);
        u8g2_DrawBox(&u8g2, 0, 26, 128, 12); // Draw a horizontal line in the middle
        u8g2_SendBuffer(&u8g2);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void) {
    // Read temperature and humidity data (if needed)
    float humidity, temperature;
    dht_read_float_data(DHT_TYPE_DHT11, 10, &humidity, &temperature);

    // Configure the LED (regular or addressable)
    configure_led();

    // Create a task for blinking the OLED display
    xTaskCreate(&oled_blink_task, "oled_blink_task", 4096, NULL, 5, NULL);

    // Main loop to blink the LED
    while (1) {
        ESP_LOGI(TAG, "Turning the LED %s!", s_led_state ? "ON" : "OFF");
        blink_led();
        s_led_state = !s_led_state;
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}
