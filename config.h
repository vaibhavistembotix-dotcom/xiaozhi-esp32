#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

#include <driver/gpio.h>

// Stembotix Playmate V2 (ESP32-WROOM-32E, 16MB)
// INMP441 mic and MAX98357A amp SHARE BCLK/WS -> Duplex I2S, same rate both ways
#define AUDIO_INPUT_SAMPLE_RATE  24000
#define AUDIO_OUTPUT_SAMPLE_RATE 24000

#define AUDIO_I2S_GPIO_BCLK GPIO_NUM_18
#define AUDIO_I2S_GPIO_WS   GPIO_NUM_19
#define AUDIO_I2S_GPIO_DIN  GPIO_NUM_23   // INMP441 SD  -> ESP32
#define AUDIO_I2S_GPIO_DOUT GPIO_NUM_5    // ESP32 -> MAX98357A DIN

#define BOOT_BUTTON_GPIO    GPIO_NUM_0

// No OLED on Playmate (the 42x WS2812B matrix on IO4 is not used as a display here)

#endif // _BOARD_CONFIG_H_
