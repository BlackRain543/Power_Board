#include "hal.h"

int32_t  duration = 0;
uint32_t freq = 0;
uint8_t  channels_resolution[LEDC_CHANNELS] = {0};

/**
 * @brief buzzer play tone
 */
void buzzer_tone(uint32_t _freq, int32_t _duration){
    if (_duration == 0)
    {
        ledcWriteTone(LEDC_CHANNEL, _freq);
    } 
    else
    {
        freq        = _freq;
        duration    = _duration;
    }
}

/**
 * @brief bledc change fduty
 */
void ledcWrite(uint8_t channel, uint32_t duty)
{
    if(channel >= LEDC_CHANNELS){
        return;
    }

    uint32_t max_duty   = (1 << channels_resolution[channel]) - 1;

    if((duty == max_duty) && (max_duty != 1)){
        duty = max_duty + 1;
    }

    ledc_set_duty(LEDC_MODE, LEDC_TIMER, duty);
    ledc_update_duty(LEDC_MODE, LEDC_TIMER);
}

/**
 * @brief ledc change freq
 */
uint32_t ledcWriteTone(uint8_t channel, uint32_t freq)
{
    if(channel >= LEDC_CHANNELS)
    {
        return 0;
    }

    if(!freq)
    {
        ledcWrite(channel, 0);
        return 0;
    }

    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = 10,
        .freq_hz          = freq, 
        .clk_cfg          = LEDC_DEFAULT_CLK
    };

    if(ledc_timer_config(&ledc_timer) != ESP_OK)
    {
        ESP_LOGE("Buzzer", "LedcSetup Failed!");
        return 0;
    }

    channels_resolution[channel] = 10;

    uint32_t res_freq = ledc_get_freq(LEDC_MODE,LEDC_TIMER);
    ledcWrite(channel, 0x01FF);

    return res_freq;
}

/**
 * @brief Buzzer Play Music
 */
MusicNode_t* Cur_Music;
uint8_t      Music_Length = 0;

bool buzzer_PlayMusic(const char* name){
    bool retval = false;

    for (uint8_t i = 0; i < sizeof(MusicList) / sizeof(MusicList[0]); i++)
    {
        if (strcmp(name, MusicList[i].name) == 0)
        {
            Cur_Music    =  MusicList[i].mc;
            Music_Length =  MusicList[i].length;

            retval = true;
            break;
        }
    }

    return retval;
}