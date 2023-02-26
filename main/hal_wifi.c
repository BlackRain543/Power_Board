#include "hal.h"

/**
 * @brief Wifi AP/STA Init
 */
void wifi_init(WifiMode wifi_mode)
{
    esp_netif_init();
    esp_event_loop_create_default();

    /* 默认配置:初始化wifi驱动 */
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    /* STA Mode */
    if(wifi_mode == WIFI_STA)
    {
        esp_netif_create_default_wifi_sta();

        wifi_sta_config_t wifi_sta_config = {
            .ssid       = ESP_STA_WIFI_SSID,
            .password   = ESP_STA_WIFI_PASS,
            .channel    = ESP_STA_WIFI_CHANNEL,
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
            .pmf_cfg = {
                .capable = true,
                .required = false
            },
        };
        
        /* 向系统注册两组事件 */
        esp_wifi_set_mode(WIFI_MODE_STA);
        esp_wifi_set_config(WIFI_IF_STA, (wifi_config_t *) &wifi_sta_config);

        esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID,       wifi_sta_event_handler, NULL, NULL);   
        esp_event_handler_instance_register(IP_EVENT,   IP_EVENT_STA_GOT_IP,    wifi_sta_event_handler, NULL, NULL);
    }
    /* AP Mode */
    if(wifi_mode == WIFI_AP)
    {
        esp_netif_create_default_wifi_ap();

        wifi_ap_config_t wifi_ap_config = {
                .ssid           = ESP_AP_WIFI_SSID,
                .ssid_len       = strlen(ESP_AP_WIFI_SSID),
                .channel        = ESP_AP_WIFI_CHANNEL,
                .password       = ESP_AP_WIFI_PASS,
                .max_connection = ESP_AP_STA_CONN,
                .authmode       = WIFI_AUTH_WPA_WPA2_PSK,
        };

        if (strlen(ESP_AP_WIFI_PASS) == 0) 
        {
            wifi_ap_config.authmode = WIFI_AUTH_OPEN;
        }

        esp_wifi_set_mode(WIFI_MODE_AP);
        esp_wifi_set_config(ESP_IF_WIFI_AP, (wifi_config_t *)&wifi_ap_config);

        esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID,   wifi_ap_event_handler,  NULL,NULL);
        
        ESP_LOGI(TAG_WIFI_AP, "Wifi_Softap Finished. SSID:%s Password:%s Channel:%d",
                                ESP_AP_WIFI_SSID, 
                                ESP_AP_WIFI_PASS, 
                                ESP_AP_WIFI_CHANNEL);
        
    }

    esp_wifi_start();

}

/**
 * @brief WiFi Sta Handler
 * @param arg 
 * @param event_base 
 * @param event_id 
 * @param event_data 
 */
static void wifi_sta_event_handler( void* arg, esp_event_base_t event_base, 
                                    int32_t event_id, void* event_data) {
    
    static uint8_t s_retry_num = 0;

    /* WIFI STA */
    // Start to Connect
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) 
    {
        esp_wifi_connect();
        ESP_LOGI(TAG_WIFI_STA, "Start Connect...");
    }

    // Connect Success and Got IP
    if(event_base  == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) 
    {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG_WIFI_STA, "Got IP: " IPSTR,  IP2STR(&event->ip_info.ip));
    }

    // Try to Connect
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        if (s_retry_num < ESP_STA_MAXIMUM_RETRY) 
        {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG_WIFI_STA, "%d times: retry to connect to the AP",s_retry_num);
        } 

        ESP_LOGI(TAG_WIFI_STA,"connect to the AP fail");
    }

}

/**
 * @brief WiFi Ap Handler
 * @param arg 
 * @param event_base 
 * @param event_id 
 * @param event_data 
 */
static void wifi_ap_event_handler( void* arg, esp_event_base_t event_base, 
                                    int32_t event_id, void* event_data) {

    /* WIFI AP */
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG_WIFI_AP, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } 

    if (event_id == WIFI_EVENT_AP_STADISCONNECTED) 
    {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG_WIFI_AP, "station "MACSTR" leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }

}