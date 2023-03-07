#ifndef __COMMON_INC_H__
#define __COMMON_INC_H__

#ifdef __cplusplus
    extern "C" {
#endif

/*---------------------------- C Scope ---------------------------*/
/* INCLUDE */
#include <stdio.h>
#include <string.h>
#include <sys/param.h>


#include "nvs_flash.h"

#include "esp_system.h"
#include "esp_event.h"
#include "esp_chip_info.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_mac.h"
#include "esp_smartconfig.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#include "driver/gpio.h"
#include "driver/adc.h"
#include "driver/ledc.h"

#include "sdkconfig.h"

typedef enum{
    OVER_CURRENT = 0,
    OVER_VOLTAGE_VIN = 1,
    OVER_VOLTAGE_5V  = 2,
    OVER_VOLTAGE_19V = 3,
    UBDER_OLTAGE_VIN = 4,
    UBDER_OLTAGE_5V  = 5,
    UBDER_OLTAGE_19V = 6,  

    WIFI_STA_CONNECT = 6, 
    WIFI_STA_DISCONNECT = 6, 

}PB_STATUS;

/* TAG */
#define  TAG_WIFI_STA       "Wifi_STA"
#define  TAG_WIFI_AP        "Wifi_AP"
#define  TAG_UDP            "Wifi_UDP"
#define  TAG_SCAN           "Wifi_SCAN"
#define  TAG_SMARTCONFIG    "Wifi_SMARTCONFIG"
#define  TAG_GENERAL        "ESP32_C3"

/* GPIO */
#define EN_5V_PIN           GPIO_NUM_5
#define EN_19V_PIN          GPIO_NUM_6
#define EN_VIN_PIN          GPIO_NUM_7

#define EN_5V_ON            gpio_set_level(EN_5V_PIN,0)
#define EN_5V_OFF           gpio_set_level(EN_5V_PIN,1)
#define EN_19V_ON           gpio_set_level(EN_19V_PIN,0)
#define EN_19V_OFF          gpio_set_level(EN_19V_PIN,1)
#define EN_VIN_ON           gpio_set_level(EN_VIN_PIN,0)
#define EN_VIN_OFF          gpio_set_level(EN_VIN_PIN,1)

#define LED1_PIN            GPIO_NUM_20
#define LED2_PIN            GPIO_NUM_21

#define SET_LED1(m)         gpio_set_level(LED1_PIN,m)
#define SET_LED2(m)         gpio_set_level(LED2_PIN,m)

#define LED1_ON             gpio_set_level(LED1_PIN,1)
#define LED1_OFF            gpio_set_level(LED1_PIN,0)
#define LED2_ON             gpio_set_level(LED2_PIN,1)
#define LED2_OFF            gpio_set_level(LED2_PIN,0)

#define BUZZER_PIN          GPIO_NUM_10
#define BUZZER_EN           1

#define ADC_CH0_VIN_PIN     GPIO_NUM_0
#define ADC_CH1_19V_PIN     GPIO_NUM_1
#define ADC_CH3_5V_PIN      GPIO_NUM_3
#define ADC_CH4_CUR_PIN     GPIO_NUM_4

/* PWM */
#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE

#define LEDC_OUTPUT_IO          (10) 
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_10_BIT           // Set duty resolution to 10 bits

#define LEDC_FREQUENCY          (4000)                      // Frequency in Hertz. Set frequency at 5 kHz
#define LEDC_DUTY               (512)                       // Set duty to 50%. ((2 ** 10) - 1) * 50% 
#define LEDC_CHANNELS           (SOC_LEDC_CHANNEL_NUM<<1)
#define LEDC_DEFAULT_CLK        LEDC_AUTO_CLK

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

/*---------------------------- PROTECT ---------------------------*/
#define VOLTAGE_VIN_MAX_LIMIT   56.0f   /* V */
#define VOLTAGE_VIN_MIN_LIMIT   20.0f

#define VOLTAGE_5V_MAX_LIMIT    6.0f    /* V */
#define VOLTAGE_5V_MIN_LIMIT    3.0f

#define VOLTAGE_19V_MAX_LIMIT   20.0f   /* V */
#define VOLTAGE_19V_MIN_LIMIT   16.0f

#define CURRENT_MAX_LIMIT       30.0f   /* A */
#define CURRENT_MIN_LIMIT

/*---------------------------- WIFI ---------------------------*/
typedef enum{
    WIFI_STA = 0,
    WIFI_AP  = 1,
}WifiMode;

#define ESP_PORT                8080
/* WIFI AP */
#define ESP_AP_WIFI_SSID        "POWER_BOARD"
#define ESP_AP_WIFI_PASS        "123456"
#define ESP_AP_WIFI_CHANNEL     1
#define ESP_AP_STA_CONN         4

#define ESP_AP_CONFIG_IPV4      192.168.4.1

/* WIFI STA */
// #define ESP_STA_WIFI_SSID       "CLEAR-LAB"
// #define ESP_STA_WIFI_PASS       "RobotRobot"
#define ESP_STA_WIFI_SSID       "Xiaomi_4EDC"
#define ESP_STA_WIFI_PASS       "123456+++abc"
#define ESP_STA_WIFI_CHANNEL    2
#define ESP_STA_MAXIMUM_RETRY   10

/* WIFI SCAN */
#define ESP_SCAN_LIST_SIZE      10

#define WIFI_CONNECTED_BIT  BIT0
#define WIFI_FAIL_BIT       BIT1
#define ESPTOUCH_DONE_BIT   BIT2

#ifdef __cplusplus
}
/*---------------------------- C++ Scope ---------------------------*/

#endif

#endif