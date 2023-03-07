#include "hal.h"

void HAL_Init(void){
    
    nvs_init();
    gpio_init();
    adc_init();
    buzzer_init();

    

}

/** ------------------------------ INIT ------------------------------ **/
void nvs_init(void) {
    esp_err_t err = nvs_flash_init();

    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }

    ESP_ERROR_CHECK(err);
}

/**
 * @brief GPIO Init
 */
void gpio_init(void){
    gpio_config_t ioConfig = {
		.pin_bit_mask = (1ull << LED1_PIN) 
                    |   (1ull << LED2_PIN)
                    |   (1ull << BUZZER_PIN)
                    |   (1ull << EN_5V_PIN) 
                    |   (1ull << EN_19V_PIN) 
                    |   (1ull << EN_VIN_PIN),
		.mode         = GPIO_MODE_OUTPUT,
        .pull_up_en   = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
	};

	//传入gpio_config_t指针
	gpio_config(&ioConfig);

    LED1_OFF;
    LED2_OFF;

    EN_5V_OFF;
    EN_19V_OFF;
    EN_VIN_OFF;
}

/**
 * @brief ADC Init
 */
void adc_init(void){

    adc1_config_width(ADC_WIDTH_BIT_12);

    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_1, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);

}

/**
 * @brief Buzzer Init
 */
void buzzer_init(void){

    ledc_timer_config_t ledc_timer = {
        .speed_mode         = LEDC_MODE,
        .timer_num          = LEDC_TIMER,
        .duty_resolution    = LEDC_DUTY_RES,
        .freq_hz            = LEDC_FREQUENCY,
        .clk_cfg            = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    ledc_channel_config_t ledc_channel = {
        .speed_mode         = LEDC_MODE,
        .channel            = LEDC_CHANNEL,
        .timer_sel          = LEDC_TIMER,
        .intr_type          = LEDC_INTR_DISABLE,
        .gpio_num           = LEDC_OUTPUT_IO,
        .duty               = 0,
        .hpoint             = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

