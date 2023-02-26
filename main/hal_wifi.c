#include "hal.h"
#include "freertos/event_groups.h"

static EventGroupHandle_t s_wifi_event_group; /* EVENT GROUP */

#define WIFI_CONNECTED_BIT  BIT0
#define WIFI_FAIL_BIT       BIT1

/**
 * @brief Wifi AP/STA Init
 */
void wifi_init(WifiMode wifi_mode)
{
    s_wifi_event_group = xEventGroupCreate();
    
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
            .listen_interval = 0,
            .pmf_cfg = {
                .capable = true,
                .required = false
            },
        };

        esp_wifi_set_config(WIFI_IF_STA, (wifi_config_t *) &wifi_sta_config);
        esp_wifi_set_mode(WIFI_MODE_STA);

        esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID,       wifi_sta_event_handler, NULL, NULL);   
        esp_event_handler_instance_register(IP_EVENT,   IP_EVENT_STA_GOT_IP,    wifi_sta_event_handler, NULL, NULL);
        // esp_event_handler_instance_register(SC_EVENT,   ESP_EVENT_ANY_ID,       wifi_sta_event_handler, NULL, NULL);
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

        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
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
        else 
        {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
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

/**
 * Wifi Scan
*/
void wifi_scan(void)
{
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    uint16_t ap_count   = 0;
    uint16_t number     = ESP_SCAN_LIST_SIZE;
    wifi_ap_record_t ap_info[ESP_SCAN_LIST_SIZE];

    memset(ap_info, 0, sizeof(ap_info));

    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_start();
    esp_wifi_scan_start(NULL, true);
    esp_wifi_scan_get_ap_records(&number, ap_info);
    esp_wifi_scan_get_ap_num(&ap_count);

    ESP_LOGI(TAG_SCAN, "Total APs scanned = %u", ap_count);

    for (int i = 0; (i < ESP_SCAN_LIST_SIZE) && (i < ap_count); i++)
    {
        ESP_LOGI(TAG_SCAN, "SSID \t\t%s", ap_info[i].ssid);
        ESP_LOGI(TAG_SCAN, "RSSI \t\t%d", ap_info[i].rssi);

        print_auth_mode(ap_info[i].authmode);

        if (ap_info[i].authmode != WIFI_AUTH_WEP) {
            print_cipher_type(ap_info[i].pairwise_cipher, ap_info[i].group_cipher);
        }

        ESP_LOGI(TAG_SCAN, "Channel \t\t%d\n", ap_info[i].primary);
    }

}