#include "common_inc.h"

static const char *TAG_WIFI_STA = "Wifi_STA";
static const char *TAG_WIFI_AP  = "Wifi_AP";
static const char *TAG_GENERAL  = "ESP32_C3";

typedef enum{
    WIFI_STA = 0,
    WIFI_AP  = 1,
}WifiMode;

static uint16_t AdcRawVal[4] = {};

/** ---------- INIT ---------- **/
void Nvs_Init(void) {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
}

/**
 * @brief WiFi Sta Handler
 * @param arg 
 * @param event_base 
 * @param event_id 
 * @param event_data 
 */
static void Wifi_Sta_Event_Handler( void* arg, esp_event_base_t event_base, 
                                    int32_t event_id, void* event_data) {
    
    /* WIFI STA */
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    }

    if(event_base  == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG_WIFI_STA, "Got IP: " IPSTR,  IP2STR(&event->ip_info.ip));
    }

}

/**
 * @brief WiFi Ap Handler
 * @param arg 
 * @param event_base 
 * @param event_id 
 * @param event_data 
 */
static void Wifi_Ap_Event_Handler( void* arg, esp_event_base_t event_base, 
                                    int32_t event_id, void* event_data) {

    /* WIFI AP */
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG_WIFI_AP, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } 
    else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) 
    {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG_WIFI_AP, "station "MACSTR" leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }

}

/**
 * @brief Wifi Init
 */
void Wifi_Init(WifiMode wifi_mode)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    /* STA Mode */
    if(wifi_mode == WIFI_STA)
    {
        ESP_ERROR_CHECK(esp_netif_create_default_wifi_sta());

         wifi_config_t wifi_config = {
            .sta = {
                .ssid       = ESP_STA_WIFI_SSID,
                .password   = ESP_STA_WIFI_PASS,
            },
        };

        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
        ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, (wifi_config_t *) &wifi_config));


        ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID,       Wifi_Sta_Event_Handler, NULL, NULL));
        ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,   IP_EVENT_STA_GOT_IP,    Wifi_Sta_Event_Handler, NULL, NULL));

    }
    /* AP Mode */
    else if(wifi_mode == WIFI_AP)
    {
        ESP_ERROR_CHECK(esp_netif_create_default_wifi_ap());

        wifi_config_t wifi_config = {
            .ap = {
                .ssid           = ESP_AP_WIFI_SSID,
                .ssid_len       = strlen(ESP_AP_WIFI_SSID),
                .channel        = ESP_AP_WIFI_CHANNEL,
                .password       = ESP_AP_WIFI_PASS,
                .max_connection = ESP_AP_STA_CONN,
                .authmode       = WIFI_AUTH_WPA_WPA2_PSK
            },
        };

        ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                    ESP_EVENT_ANY_ID,
                                                    Wifi_Ap_Event_Handler,
                                                    NULL,
                                                    NULL));
        if (strlen(ESP_AP_WIFI_PASS) == 0) {
            wifi_config.ap.authmode = WIFI_AUTH_OPEN;
        }

        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
        ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));

        ESP_LOGI(TAG_WIFI_STA, "Wifi_Softap Finished. SSID:%s Password:%s Channel:%d",
                                ESP_AP_WIFI_SSID, 
                                ESP_AP_WIFI_PASS, 
                                ESP_AP_WIFI_CHANNEL);
    }
        

    ESP_ERROR_CHECK(esp_wifi_start());
}

/**
 * @brief GPIO Init
 */
void Gpio_Init(void){
    gpio_config_t ioConfig = {
		.pin_bit_mask = (1ull << LED1_PIN) 
                        | (1ull << LED2_PIN)
                        | (1ull << BUZZER_PIN)
                        | (1ull << EN_5V_PIN) 
                        | (1ull << EN_19V_PIN) 
                        | (1ull << EN_VIN_PIN),
		.mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
	};

	//传入gpio_config_t指针
	gpio_config(&ioConfig);
}

/**
 * @brief ADC Init
 */
void Adc_Init(void){
    
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_1,ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_3,ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_4,ADC_ATTEN_DB_11);

}

static void ADC_Getvalue_Task(void)
{
    static float Adc_Voltage_5V;
    static float Adc_Voltage_19V;
    static float Adc_Voltage_VIN;
    static float Adc_Current;

    AdcRawVal[0] = adc1_get_raw(ADC1_CHANNEL_0);
    AdcRawVal[1] = adc1_get_raw(ADC1_CHANNEL_1);
    AdcRawVal[2] = adc1_get_raw(ADC1_CHANNEL_3);
    AdcRawVal[3] = adc1_get_raw(ADC1_CHANNEL_4);

    Adc_Voltage_5V  = AdcRawVal[2] * ADC2VAL * AMP_5V;
    Adc_Voltage_19V = AdcRawVal[1] * ADC2VAL * AMP_19V;
    Adc_Voltage_VIN = AdcRawVal[0] * ADC2VAL * AMP_VIN;
    Adc_Current     = AdcRawVal[3] * ADC2VAL / RESISTANCE / AMP_CUR;

    ESP_LOGI(TAG_GENERAL, "ADC: %4.2f, %4.2f, %4.2f, %4.2f",
                                Adc_Voltage_5V,     Adc_Voltage_19V,
                                Adc_Voltage_VIN,    Adc_Current);
}


void app_main(void)
{
    Nvs_Init();
    Wifi_Init(WIFI_STA);
    Gpio_Init();
    Adc_Init();


    while (1)
    {   

        // vTaskDelay(50);
    }
}





