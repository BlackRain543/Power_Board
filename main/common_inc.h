#ifndef COMMON_INC_H
#define COMMON_INC_H

/* INCLUDE */
#include <stdio.h>

#include <string.h>
#include <sys/param.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "nvs_flash.h"

#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_mac.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#include "driver/gpio.h"
#include "driver/adc.h"

#include "sdkconfig.h"

/* GPIO */
#define EN_5V_PIN           GPIO_NUM_5
#define EN_19V_PIN          GPIO_NUM_6
#define EN_VIN_PIN          GPIO_NUM_7

#define LED1_PIN            GPIO_NUM_20
#define LED2_PIN            GPIO_NUM_21

#define BUZZER_PIN          GPIO_NUM_10

#define ADC_CH0_VIN_PIN     GPIO_NUM_0
#define ADC_CH1_19V_PIN     GPIO_NUM_1
#define ADC_CH3_5V_PIN      GPIO_NUM_3
#define ADC_CH4_CUR_PIN     GPIO_NUM_4

/* ADC */

#define ADC2VAL             0.0007203907203f
#define VAL2ADC             1388.1355932203f

#define RESISTANCE          0.001f
#define AMP_CUR             50.0f

#define AMP_5V              2.5f
#define AMP_19V             11.0f    
#define AMP_VIN             35.0f


/* UART*/
#define RXD_PIN             GPIO_NUM_20
#define TXD_PIN             GPIO_NUM_21

/* WIFI AP */
#define ESP_AP_PORT         8080

#define ESP_AP_WIFI_SSID      "ESP32C3_POWER_BOARD"
#define ESP_AP_WIFI_PASS      "12345678"
#define ESP_AP_WIFI_CHANNEL   1
#define ESP_AP_STA_CONN       4

#define ESP_AP_CONFIG_IPV4    192.168.4.1

/* WIFI STA*/
#define ESP_STA_WIFI_SSID      "CLEAR-LAB"
#define ESP_STA_WIFI_PASS      "RobotRobot"

        

#endif