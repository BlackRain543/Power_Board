#include "common_inc.h"
#include "freertos_inc.h"
#include "hal.h"

char udp_cmd = 0;

uint16_t Startup[3][2] = 
{
    {M1, 80},
    {M6, 80},
    {M3, 80},
};

/*连接成功音*/
uint16_t Connect[3][2]=
{
    {H1, 80},
    {H2, 80},
    {H3, 80},
};

void app_main(void)
{
    HAL_Init();
    freertos_tasks_create();

    bool status = 0;


    while (1)
    {   
        switch(udp_cmd)
        {
            case 'a':
                buzzer_PlayMusic("Startup");
                break;
            case 'b':
                buzzer_PlayMusic("Shutdown");
                break;
            case 'c':
                buzzer_PlayMusic("Error");
                break;
            case 'd':
                buzzer_PlayMusic("Connect");
                break;  
            case 'e':
                buzzer_PlayMusic("UnstableConnect");
                break; 
            case 'f':
                buzzer_PlayMusic("BattChargeStart");
                break; 
            case 'g':
                buzzer_PlayMusic("DeviceInsert");
                break; 
            case 'h':
                buzzer_PlayMusic("DevicePullout");
                break; 
            case 'i':
                buzzer_PlayMusic("NoOperationWarning");
                break; 
            default:
                break;
        }
        status = !status;
        gpio_set_level(LED1_PIN,status);
        vTaskDelay(1000);
                
    }
}



