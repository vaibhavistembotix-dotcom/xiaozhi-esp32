#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

#include <driver/gpio.h>

// Stembotix Playmate (ESP32) - no display.
// INMP441 mic and MAX98357A amp share BCLK and WS -> Duplex I2S.

#define AUDIO_INPUT_SAMPLE_RATE  24000
#define AUDIO_OUTPUT_SAMPLE_RATE 24000

#define AUDIO_I2S_GPIO_BCLK GPIO_NUM_18
#define AUDIO_I2S_GPIO_WS   GPIO_NUM_19
#define AUDIO_I2S_GPIO_DIN  GPIO_NUM_23
#define AUDIO_I2S_GPIO_DOUT GPIO_NUM_5

#define BOOT_BUTTON_GPIO GPIO_NUM_0

// 42x WS2812B matrix on IO4
#define LED_STRIP_GPIO  GPIO_NUM_4
#define LED_STRIP_COUNT 42

#endif // _BOARD_CONFIG_H_
