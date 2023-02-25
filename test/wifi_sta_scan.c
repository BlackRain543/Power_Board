// 【注意】：wifi_scan_handle变量是一个Task的句柄，
// 可通过xTaskCreate在创建任务时获得
// 也可通过xTaskGetCurrentTaskHandle()等FreeRTOS API获取
TaskHandle_t wifi_scan_handle;	
// 上边的这个变量储存了创建的wifi扫描任务句柄
// 对应下边示例的函数 task_wifi_scan(void *arg)


void wifi_event_handler(void *arg, esp_event_base_t eventBase, int32_t eventID, void *eventData){
    
    ...
    
    if(eventBase == WIFI_EVENT){
        if(eventID == WIFI_EVENT_STA_START){
            // printf("WiFi 已启动");

			// 向WiFi扫描任务发送任务通知，通知WiFi启动成功，可以开始扫描了 (这里的任务通知相当于一个二值信号量)
            xTaskNotifyGive(wifi_scan_handle);	
        }
    }
}


void task_wifi_scan(void *arg){
	// 等待来自event_handler发来的任务通知，在等到通知之前，此任务进入阻塞状态。知道接收到WiFi启动成功的通知之后才开始往下执行。
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    uint16_t num;
    wifi_ap_record_t records[8];

    esp_wifi_scan_start(NULL, true);
    esp_wifi_scan_get_ap_num(&num);
    if(num > 8){
        num = 8;	// if 的目的是如果扫描到了8个以上的WiFi，则只保留前8个
    }
    esp_wifi_scan_get_ap_records(&num, records);
    if(num > 8){
        num = 8;	// if 的目的同上
    }

	// 这个for循环是用来将RSSI信号强度，转换成信号等级。
	// 如 rssi_level == 5 时，表示WiFi满格
    for(int i = 0; i < num; i++){
        uint8_t rssi_level = 0;
        switch (records[i].rssi) {
            case -100 ... -88:
                rssi_level = 1; break;
            case -87 ... -77:
                rssi_level = 2; break;
            case -76 ... -66:
                rssi_level = 3; break;
            case -65 ... -55:
                rssi_level = 4; break;
            default:
                if(records[i].rssi < -100){
                    rssi_level = 0;
                }else{
                    rssi_level = 5;
                }
                break;
        }

	// 逐条打印扫描到的WiFi
        printf("—————【第 %2d 个WiFi】———————\n", i+1);
        printf("WiFi名称: %s\n", records[i].ssid);
        printf("信号强度: %d格\n", rssi_level);
        printf("WiFi: 安全类型: %d\n\n", records[i].authmode);
    }

    vTaskDelete(NULL);
}
