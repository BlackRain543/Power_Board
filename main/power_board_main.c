#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"

#include "esp_log.h"

#include "sdkconfig.h"

#define LED_PIN_NUM     GPIO_NUM_20
#define LED_PIN_NUM_2   GPIO_NUM_21


static const char *TAG = "example";

// static uint32_t cnt = 0;
bool status = 1;
int val[4];

void app_main(void)
{
    gpio_config_t ioConfig = {
		.pin_bit_mask = (1ull << 20) | (1ull << 21)| (1ull << 5) | (1ull << 6) | (1ull << 7),
		.mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE
	};

	//传入gpio_config_t指针
	gpio_config(&ioConfig);

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_1,ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_3,ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_4,ADC_ATTEN_DB_11);


    gpio_set_level(5, 0);
    gpio_set_level(6, 0);
    gpio_set_level(7, 0);


    while (1)
    {   
        // gpio_set_level(5, status);
        // gpio_set_level(6, status);
        // gpio_set_level(7, status);
        val[0] = adc1_get_raw(ADC1_CHANNEL_0);
        val[1] = adc1_get_raw(ADC1_CHANNEL_1);
        val[2] = adc1_get_raw(ADC1_CHANNEL_3);
        val[3] = adc1_get_raw(ADC1_CHANNEL_4);
        // v = val[1]* 2500.00/4095.00;
        ESP_LOGI(TAG, "%f,%f,%f,%f", val[0]/4095.0*2.95*35.0, val[1]/4095.0*2.95*11.0, val[2]/4095.0*2.95*2.5, val[3]/4095.0*2.95/0.001/50.0);
        // cnt++;
        // if(cnt % 30 == 0){
        //     status = !status;
        // }
        status = !status;
        vTaskDelay(50);
        gpio_set_level(LED_PIN_NUM,  status);
        gpio_set_level(LED_PIN_NUM_2,!status);
        // vTaskDelay(50);

        // gpio_set_level(LED_PIN_NUM, 1);
        // gpio_set_level(LED_PIN_NUM_2, 0);
        // vTaskDelay(50);
    }
}
