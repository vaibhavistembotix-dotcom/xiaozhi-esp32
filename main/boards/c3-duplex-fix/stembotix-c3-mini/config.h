#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

#include <driver/gpio.h>

// Stembotix ESP32-C3 Super Mini voice board
// The ESP32-C3 has only ONE I2S port, so mic and speaker must share BCLK and WS (Duplex I2S).
// WIRING (changed from the Arduino sketch):
//   INMP441 SCK -> GPIO5  (same pin as MAX98357A BCLK)
//   INMP441 WS  -> GPIO6  (same pin as MAX98357A LRC)
//   INMP441 SD  -> GPIO10, L/R -> GND
//   MAX98357A DIN -> GPIO7, SD (enable) -> GPIO3
#define AUDIO_INPUT_SAMPLE_RATE  24000
#define AUDIO_OUTPUT_SAMPLE_RATE 24000

#define AUDIO_I2S_GPIO_BCLK GPIO_NUM_5
#define AUDIO_I2S_GPIO_WS   GPIO_NUM_6
#define AUDIO_I2S_GPIO_DIN  GPIO_NUM_10   // INMP441 SD -> ESP32
#define AUDIO_I2S_GPIO_DOUT GPIO_NUM_7    // ESP32 -> MAX98357A DIN
#define AUDIO_AMP_SD_GPIO   GPIO_NUM_3    // amp enable: HIGH = on

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
