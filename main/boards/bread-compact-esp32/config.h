#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

#include <driver/gpio.h>

#define AUDIO_INPUT_SAMPLE_RATE  16000
#define AUDIO_OUTPUT_SAMPLE_RATE 24000

// Duplex I2S mode (mic and speaker share BCLK and WS), so SIMPLEX is disabled
// #define AUDIO_I2S_METHOD_SIMPLEX

#ifdef AUDIO_I2S_METHOD_SIMPLEX

#define AUDIO_I2S_MIC_GPIO_WS   GPIO_NUM_25
#define AUDIO_I2S_MIC_GPIO_SCK  GPIO_NUM_26
#define AUDIO_I2S_MIC_GPIO_DIN  GPIO_NUM_32

#define AUDIO_I2S_SPK_GPIO_DOUT GPIO_NUM_33
#define AUDIO_I2S_SPK_GPIO_BCLK GPIO_NUM_14
#define AUDIO_I2S_SPK_GPIO_LRCK GPIO_NUM_27

#else

// STEMbotix PCB: mic and speaker on one shared I2S bus
#define AUDIO_I2S_GPIO_WS   GPIO_NUM_19
#define AUDIO_I2S_GPIO_BCLK GPIO_NUM_18
#define AUDIO_I2S_GPIO_DIN  GPIO_NUM_23
#define AUDIO_I2S_GPIO_DOUT GPIO_NUM_5

#endif

#define BOOT_BUTTON_GPIO        GPIO_NUM_0
#define TOUCH_BUTTON_GPIO       GPIO_NUM_NC
#define ASR_BUTTON_GPIO         GPIO_NUM_NC
#define BUILTIN_LED_GPIO        GPIO_NUM_2

#define ML307_RX_PIN            GPIO_NUM_16
#define ML307_TX_PIN            GPIO_NUM_17

// TODO: change these two if your PCB's OLED is on different pins
#define DISPLAY_SDA_PIN GPIO_NUM_4
#define DISPLAY_SCL_PIN GPIO_NUM_15
#define DISPLAY_WIDTH   128

#if CONFIG_OLED_SSD1306_128X32
#define DISPLAY_HEIGHT  32
#elif CONFIG_OLED_SSD1306_128X64 || CONFIG_OLED_SH1106_128X64
#define DISPLAY_HEIGHT  64
#else
#error "OLED display type is not selected"
#endif

#define DISPLAY_MIRROR_X true
#define DISPLAY_MIRROR_Y true

#endif // _BOARD_CONFIG_H_


