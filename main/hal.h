#ifndef __HAL_H__
#define __HAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common_inc.h"
#include "TonePlayer/MusicCode.h"
#include "freertos_inc.h"

/* Init */
void HAL_Init(void);

void nvs_init(void);
void gpio_init(void);
void adc_init(void);
void buzzer_init(void);

/* Func */
void buzzer_tone(uint32_t _freq, int32_t _duration);
bool buzzer_PlayMusic(const char* name);
void ledcWrite(uint8_t channel, uint32_t duty);
uint32_t ledcWriteTone(uint8_t channel, uint32_t freq);

/* Print */
void esp_chip_info_print(void);
void task_memory_info_print(TaskHandle_t taskHandle,int taskMem);
void print_auth_mode(int authmode);
void print_cipher_type(int pairwise_cipher, int group_cipher);

/* Wifi */
void wifi_init(WifiMode wifi_mode);
void wifi_scan(void);
void wifi_smartconfig(void);

static void wifi_sta_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
static void wifi_ap_event_handler (void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
static void wifi_smartconfig_event_handler( void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

#ifdef __cplusplus
}
#endif

#endif