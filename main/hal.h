#ifndef __HAL_H__
#define __HAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common_inc.h"
#include "TonePlayer/MusicCode.h"

void HAL_Init(void);

void nvs_init(void);
void gpio_init(void);
void adc_init(void);
void buzzer_init(void);

void buzzer_tone(uint32_t _freq, int32_t _duration);
bool buzzer_PlayMusic(const char* name);
void ledcWrite(uint8_t channel, uint32_t duty);
uint32_t ledcWriteTone(uint8_t channel, uint32_t freq);

void wifi_init(WifiMode wifi_mode);

static void wifi_sta_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
static void wifi_ap_event_handler (void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
                                                                        
#ifdef __cplusplus
}
#endif

#endif