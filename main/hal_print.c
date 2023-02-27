#include "hal.h"

void esp_chip_info_print(void){
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    /* idf + chip info*/
    ESP_LOGI(TAG_GENERAL,"IDF Version: %s",esp_get_idf_version());
    ESP_LOGI(TAG_GENERAL,"CPU model: %d",   chip_info.model);
    ESP_LOGI(TAG_GENERAL,"CPU features: %d",chip_info.features);
    ESP_LOGI(TAG_GENERAL,"CPU cores: %d",   chip_info.cores);
    ESP_LOGI(TAG_GENERAL,"CPU version: %d", chip_info.revision);
}

/**
 * @brief Get Single Task Size
*/
void task_memory_info_print(TaskHandle_t taskHandle,int taskMem){
    int waterMark = uxTaskGetStackHighWaterMark(taskHandle);

    ESP_LOGI(TAG_GENERAL,"Task Memory: %d B",taskMem - waterMark);
}

/**
 * @brief Print auth mode -- [wifi scan]
*/
void print_auth_mode(int authmode)
{
    switch (authmode) {
        case WIFI_AUTH_OPEN:
            ESP_LOGI(TAG_SCAN, "Authmode \tWIFI_AUTH_OPEN");
            break;
        case WIFI_AUTH_OWE:
            ESP_LOGI(TAG_SCAN, "Authmode \tWIFI_AUTH_OWE");
            break;
        case WIFI_AUTH_WEP:
            ESP_LOGI(TAG_SCAN, "Authmode \tWIFI_AUTH_WEP");
            break;
        case WIFI_AUTH_WPA_PSK:
            ESP_LOGI(TAG_SCAN, "Authmode \tWIFI_AUTH_WPA_PSK");
            break;
        case WIFI_AUTH_WPA2_PSK:
            ESP_LOGI(TAG_SCAN, "Authmode \tWIFI_AUTH_WPA2_PSK");
            break;
        case WIFI_AUTH_WPA_WPA2_PSK:
            ESP_LOGI(TAG_SCAN, "Authmode \tWIFI_AUTH_WPA_WPA2_PSK");
            break;
        case WIFI_AUTH_WPA2_ENTERPRISE:
            ESP_LOGI(TAG_SCAN, "Authmode \tWIFI_AUTH_WPA2_ENTERPRISE");
            break;
        case WIFI_AUTH_WPA3_PSK:
            ESP_LOGI(TAG_SCAN, "Authmode \tWIFI_AUTH_WPA3_PSK");
            break;
        case WIFI_AUTH_WPA2_WPA3_PSK:
            ESP_LOGI(TAG_SCAN, "Authmode \tWIFI_AUTH_WPA2_WPA3_PSK");
            break;
        default:
            ESP_LOGI(TAG_SCAN, "Authmode \tWIFI_AUTH_UNKNOWN");
            break;
    }
}

/**
 * @brief Print cipher type -- [wifi scan]
*/
void print_cipher_type(int pairwise_cipher, int group_cipher)
{
    switch (pairwise_cipher) {
        case WIFI_CIPHER_TYPE_NONE:
            ESP_LOGI(TAG_SCAN, "Pairwise Cipher \tWIFI_CIPHER_TYPE_NONE");
            break;
        case WIFI_CIPHER_TYPE_WEP40:
            ESP_LOGI(TAG_SCAN, "Pairwise Cipher \tWIFI_CIPHER_TYPE_WEP40");
            break;
        case WIFI_CIPHER_TYPE_WEP104:
            ESP_LOGI(TAG_SCAN, "Pairwise Cipher \tWIFI_CIPHER_TYPE_WEP104");
            break;
        case WIFI_CIPHER_TYPE_TKIP:
            ESP_LOGI(TAG_SCAN, "Pairwise Cipher \tWIFI_CIPHER_TYPE_TKIP");
            break;
        case WIFI_CIPHER_TYPE_CCMP:
            ESP_LOGI(TAG_SCAN, "Pairwise Cipher \tWIFI_CIPHER_TYPE_CCMP");
            break;
        case WIFI_CIPHER_TYPE_TKIP_CCMP:
            ESP_LOGI(TAG_SCAN, "Pairwise Cipher \tWIFI_CIPHER_TYPE_TKIP_CCMP");
            break;
        default:
            ESP_LOGI(TAG_SCAN, "Pairwise Cipher \tWIFI_CIPHER_TYPE_UNKNOWN");
            break;
    }

    switch (group_cipher) {
        case WIFI_CIPHER_TYPE_NONE:
            ESP_LOGI(TAG_SCAN, "Group Cipher \tWIFI_CIPHER_TYPE_NONE");
            break;
        case WIFI_CIPHER_TYPE_WEP40:
            ESP_LOGI(TAG_SCAN, "Group Cipher \tWIFI_CIPHER_TYPE_WEP40");
            break;
        case WIFI_CIPHER_TYPE_WEP104:
            ESP_LOGI(TAG_SCAN, "Group Cipher \tWIFI_CIPHER_TYPE_WEP104");
            break;
        case WIFI_CIPHER_TYPE_TKIP:
            ESP_LOGI(TAG_SCAN, "Group Cipher \tWIFI_CIPHER_TYPE_TKIP");
            break;
        case WIFI_CIPHER_TYPE_CCMP:
            ESP_LOGI(TAG_SCAN, "Group Cipher \tWIFI_CIPHER_TYPE_CCMP");
            break;
        case WIFI_CIPHER_TYPE_TKIP_CCMP:
            ESP_LOGI(TAG_SCAN, "Group Cipher \tWIFI_CIPHER_TYPE_TKIP_CCMP");
            break;
        default:
            ESP_LOGI(TAG_SCAN, "Group Cipher \tWIFI_CIPHER_TYPE_UNKNOWN");
            break;
    }
}