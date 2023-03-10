#include "freertos_inc.h"

extern char udp_cmd;
extern EventGroupHandle_t s_wifi_event_group;

TaskHandle_t udp_server_task_handle;	
TaskHandle_t smartconfig_task_handle;	
TaskHandle_t adc_task_handle;	
TaskHandle_t buzzer_task_handle;
TaskHandle_t music_task_handle;	
TaskHandle_t led_task_handle;	

void freertos_tasks_create(void)
{
    xTaskCreate(udp_server_task,    "udp_server_task"       , 4096, (void*)AF_INET, 2,  &udp_server_task_handle);
    xTaskCreate(adc_getvalue_task,  "adc_task"              , 768,  NULL, 1,            &adc_task_handle);
    xTaskCreate(buzzer_task,        "buzzer_task"           , 512,  NULL, 2,            &buzzer_task_handle);
    xTaskCreate(music_task,         "music_task"            , 512,  NULL, 2,            &music_task_handle);
    xTaskCreate(led_task,           "led_task"              , 512,  NULL, 5,            &led_task_handle);
}

void all_tasks_memory_info_print(void){
    task_memory_info_print(udp_server_task_handle,  4096);
    // task_memory_info_print(smartconfig_task_handle,4096);
    task_memory_info_print(adc_task_handle,         768);
    task_memory_info_print(buzzer_task_handle,      512);
    task_memory_info_print(music_task_handle,       512);
    task_memory_info_print(led_task_handle,         512);
}

/**
 * @brief Wifi Smartconfig Task
 */
void smartconfig_task(void *pvParameters)
{
    EventBits_t uxBits;
    ESP_ERROR_CHECK( esp_smartconfig_set_type(SC_TYPE_ESPTOUCH) );
    smartconfig_start_config_t cfg = SMARTCONFIG_START_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_smartconfig_start(&cfg) );

    while (1) {
        uxBits = xEventGroupWaitBits(s_wifi_event_group, WIFI_CONNECTED_BIT | ESPTOUCH_DONE_BIT, true, false, portMAX_DELAY);
        if(uxBits & WIFI_CONNECTED_BIT) {
            ESP_LOGI(TAG_SMARTCONFIG, "WiFi Connected to ap");
        }
        if(uxBits & ESPTOUCH_DONE_BIT) {
            ESP_LOGI(TAG_SMARTCONFIG, "smartconfig over");
            esp_smartconfig_stop();
            vTaskDelete(NULL);
        }
    }
}

/**
 * @brief ADC Task
 */
void adc_getvalue_task(void *pvParameters)
{
    
    /* ADC Values */
    static uint16_t AdcRawVal[4] = {};

    static float Adc_Voltage_5V     = 0;
    static float Adc_Voltage_19V    = 0;
    static float Adc_Voltage_VIN    = 0;
    static float Adc_Current        = 0;

    static bool  Adc_Print          = 0;

    for (;;)
    {
        AdcRawVal[0]    = adc1_get_raw(ADC1_CHANNEL_0);
        AdcRawVal[1]    = adc1_get_raw(ADC1_CHANNEL_1);
        AdcRawVal[2]    = adc1_get_raw(ADC1_CHANNEL_3);
        AdcRawVal[3]    = adc1_get_raw(ADC1_CHANNEL_4);

        Adc_Voltage_5V  = AdcRawVal[2] * ADC2VAL * AMP_5V;
        Adc_Voltage_19V = AdcRawVal[1] * ADC2VAL * AMP_19V;
        Adc_Voltage_VIN = AdcRawVal[0] * ADC2VAL * AMP_VIN;
        Adc_Current     = AdcRawVal[3] * ADC2VAL / RESISTANCE / AMP_CUR;

        if(Adc_Print)
        {
            ESP_LOGI(TAG_GENERAL, "ADC: %4.2f, %4.2f, %4.2f, %6.2f",
                                Adc_Voltage_5V,     Adc_Voltage_19V,
                                Adc_Voltage_VIN,    Adc_Current);
        }     
        vTaskDelay(1);
    }
}

/**
 * @brief Buzzer Task
 */
extern int32_t  duration;
extern uint32_t freq;
    
void buzzer_task(void *pvParameters)
{
    for (;;)
    {
        if (duration > 0)
        {
            ledcWriteTone(LEDC_CHANNEL,freq);
            vTaskDelay(duration);
            ledcWriteTone(LEDC_CHANNEL,0);
            duration = 0;
        }
        
        vTaskDelay(10);
    }
}

extern uint8_t Music_Length;
extern MusicNode_t* Cur_Music;
/**
 * @brief Music Task
 */
void music_task(void *pvParameters)
{
    static uint8_t current_pos = 0;

    for (;;)
    {   
        while(current_pos < Music_Length){

            buzzer_tone(Cur_Music[current_pos].Freq, Cur_Music[current_pos].Time);
            vTaskDelay(Cur_Music[current_pos].Time + 11);
            current_pos++;

            if(current_pos == Music_Length)
            {
                buzzer_tone(0, 0);
                current_pos = 0;
                Music_Length = 0;
                break;
            }
        }

        vTaskDelay(10);
    }
}

extern char udp_cmd;
/**
 * @brief Led Task
 */
void led_task(void *pvParameters){

    static int16_t  led_status = 0;
    static uint16_t cnt = 0;
    static uint16_t period = 1500;

    for (;;)
    {   
        led_status = udp_cmd;

        switch(led_status){
            case '0':   /* blink 1 times */
                if(cnt == 0)        LED1_ON;
                if(cnt == 100)      LED1_OFF;
                if(cnt >= period)   cnt = 0xFFFF;
                break;
            
            case '1':   /* blink 2 times */
                if(cnt == 0)        LED1_ON;
                if(cnt == 100)      LED1_OFF;
                if(cnt == 200)      LED1_ON;
                if(cnt == 300)      LED1_OFF;
                if(cnt >= period)   cnt = 0xFFFF;
                break;

            case '2':   /* blink 3 times */
                if(cnt == 0)        LED1_ON;
                if(cnt == 100)      LED1_OFF;
                if(cnt == 200)      LED1_ON;
                if(cnt == 300)      LED1_OFF;
                if(cnt == 400)      LED1_ON;
                if(cnt == 500)      LED1_OFF;
                if(cnt >= period)   cnt = 0xFFFF;
                break;

            case '3':
                if(cnt == 0)        LED1_ON;
                if(cnt == period/2) LED1_OFF;
                if(cnt >= period)   cnt = 0xFFFF;
                break;

            default:
                LED1_OFF;   
                LED2_OFF;
                break;
        }   

        cnt++;
        vTaskDelay(1);
    }
}

/**
 * @brief UDP Server Task
 */
void udp_server_task(void *pvParameters)
{
    char    rx_buffer[64]   = {};
    char    addr_str[64]    = {};
    int     addr_family     = (int)pvParameters;
    int     ip_protocol     = 0;
    struct  sockaddr_in6 dest_addr;

    for (;;)
    {

        if (addr_family == AF_INET) {
            struct sockaddr_in *dest_addr_ip4   = (struct sockaddr_in *)&dest_addr;
            dest_addr_ip4->sin_addr.s_addr      = htonl(INADDR_ANY);
            dest_addr_ip4->sin_family           = AF_INET;
            dest_addr_ip4->sin_port             = htons(ESP_PORT);
            ip_protocol = IPPROTO_IP;
        } 
        else if (addr_family == AF_INET6) 
        {
            bzero(&dest_addr.sin6_addr.un, sizeof(dest_addr.sin6_addr.un));
            dest_addr.sin6_family               = AF_INET6;
            dest_addr.sin6_port                 = htons(ESP_PORT);
            ip_protocol                         = IPPROTO_IPV6;
        }

        int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
        if (sock < 0) 
        {
            ESP_LOGE(TAG_UDP, "Unable to create socket: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG_UDP, "Socket created");

        #if defined(CONFIG_EXAMPLE_IPV4) && defined(CONFIG_EXAMPLE_IPV6)
            if (addr_family == AF_INET6) {
                // Note that by default IPV6 binds to both protocols, it is must be disabled
                // if both protocols used at the same time (used in CI)
                int opt = 1;
                setsockopt(sock, SOL_SOCKET,    SO_REUSEADDR,   &opt, sizeof(opt));
                setsockopt(sock, IPPROTO_IPV6,  IPV6_V6ONLY,    &opt, sizeof(opt));
            }
        #endif

        int err = bind(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

        if (err < 0)
        {
            ESP_LOGE(TAG_UDP, "Socket unable to bind: errno %d", errno);
        }
        else
        {
            ESP_LOGI(TAG_UDP, "Socket bound, port %d", ESP_PORT);
        }
        
        while (1) {

            ESP_LOGI(TAG_UDP, "Waiting for data");
            struct sockaddr_in6 source_addr; // Large enough for both IPv4 or IPv6

            socklen_t socklen   = sizeof(source_addr);
            int len             = recvfrom(sock, rx_buffer, sizeof(rx_buffer) - 1, 0, (struct sockaddr *)&source_addr, &socklen);

            // Error occurred during receiving
            if (len < 0) {
                ESP_LOGE(TAG_UDP, "Recvfrom failed: errno %d", errno);
                break;
            }

            // Data received
            else {
                // Get the sender's ip address as string
                if (source_addr.sin6_family == PF_INET)
                {
                    inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr.s_addr, addr_str, sizeof(addr_str) - 1);
                } 
                else if (source_addr.sin6_family == PF_INET6) 
                {
                    inet6_ntoa_r(source_addr.sin6_addr, addr_str, sizeof(addr_str) - 1);
                }

                rx_buffer[len] = 0;         // Null-terminate whatever we received and treat like a string...
                ESP_LOGI(TAG_UDP, "Received %d bytes from %s:", len, addr_str);
                ESP_LOGI(TAG_UDP, "%s", rx_buffer);

                udp_cmd = rx_buffer[0];
                buzzer_PlayMusic("Operation");

                int err = sendto(sock, rx_buffer, len, 0, (struct sockaddr *)&source_addr, sizeof(source_addr));
                if (err < 0) 
                {
                    ESP_LOGE(TAG_UDP, "Error occurred during sending: errno %d", errno);
                    break;
                }
            }
        }

        if (sock != -1) 
        {
            ESP_LOGE(TAG_UDP, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }
    }
    vTaskDelete(NULL);
}