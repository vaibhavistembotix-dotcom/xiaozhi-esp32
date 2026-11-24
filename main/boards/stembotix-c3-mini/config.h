#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

#include <driver/gpio.h>

// Stembotix ESP32-C3 Super Mini voice board (from STEM_AI_ESP32C3_OLED_SPEAKER_CLARITY_V6.ino)
// Mic and speaker are on separate I2S pins -> Simplex I2S
#define AUDIO_INPUT_SAMPLE_RATE  16000
#define AUDIO_OUTPUT_SAMPLE_RATE 24000

// INMP441 mic (L/R -> GND = left slot)
#define AUDIO_I2S_MIC_GPIO_SCK  GPIO_NUM_4
#define AUDIO_I2S_MIC_GPIO_WS   GPIO_NUM_1
#define AUDIO_I2S_MIC_GPIO_DIN  GPIO_NUM_10

// MAX98357A speaker amp
#define AUDIO_I2S_SPK_GPIO_BCLK GPIO_NUM_5
#define AUDIO_I2S_SPK_GPIO_LRCK GPIO_NUM_6
#define AUDIO_I2S_SPK_GPIO_DOUT GPIO_NUM_7
#define AUDIO_AMP_SD_GPIO       GPIO_NUM_3   // amp enable: HIGH = on

// SSD1309 128x64 OLED, I2C, address 0x3D, RES on GPIO0
// NOTE: GPIO20/21 are the C3's UART0 pins, so the console MUST be USB-Serial-JTAG (set in config.json)
#define DISPLAY_SDA_PIN   GPIO_NUM_21
#define DISPLAY_SCL_PIN   GPIO_NUM_20
#define DISPLAY_RST_PIN   GPIO_NUM_0
#define DISPLAY_I2C_ADDR  0x3D
#define DISPLAY_WIDTH     128
#define DISPLAY_HEIGHT    64
#define DISPLAY_MIRROR_X  false
#define DISPLAY_MIRROR_Y  false

// Super Mini on-board BOOT button (free, because the OLED SCL is on GPIO20, not GPIO9)
#define BOOT_BUTTON_GPIO  GPIO_NUM_9

#endif // _BOARD_CONFIG_H_
