#ifndef __FREERTOS_INC_H__
#define __FREERTOS_INC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common_inc.h"
#include "hal.h"

// List of Tasks
/*--------------------------------- System Tasks -------------------------------------*/
void freertos_tasks_create(void);

void adc_getvalue_task(void *pvParameters);
void udp_server_task(void *pvParameters);
void buzzer_task(void* argument);
void music_task(void *pvParameters);
void led_task(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif