#include "common_inc.h"
#include "freertos_inc.h"
#include "hal.h"

char udp_cmd = '0';

void app_main(void)
{
    HAL_Init();
    
    wifi_init(WIFI_STA);
    // wifi_smartconfig();
    freertos_tasks_create();

    all_tasks_memory_info_print();

    // buzzer_PlayMusic("Startup");
    
    // buzzer_PlayMusic("DeviceInsert");

    while (1)
    {      
        switch(udp_cmd)
        {
            case 'a':
                buzzer_PlayMusic("DeviceInsert");
                break;
            // case 'b':
            //     buzzer_PlayMusic("Test");
            //     break;
        //     case 'c':
        //         buzzer_PlayMusic("Error");
        //         break;
        //     case 'd':
        //         buzzer_PlayMusic("Connect");
        //         break;  
        //     case 'e':
        //         buzzer_PlayMusic("UnstableConnect");
        //         break; 
        //     case 'f':
        //         buzzer_PlayMusic("BattChargeStart");
        //         break; 
        //     case 'g':
        //         buzzer_PlayMusic("DeviceInsert");
        //         break; 
        //     case 'h':
        //         buzzer_PlayMusic("DevicePullout");
        //         break; 
        //     case 'i':
        //         buzzer_PlayMusic("NoOperationWarning");
        //         break; 
            default:
                break;
        }

        // status = !status;

        vTaskDelay(2000); 
    }
}



