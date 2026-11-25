#include "wifi_board.h"
#include "codecs/no_audio_codec.h"
#include "application.h"
#include "button.h"
#include "config.h"
#include "led_control_esp32.h"
#include "led/circular_strip.h"

#include <esp_log.h>

#define TAG "StembotixPlaymate"

class StembotixPlaymateBoard : public WifiBoard {
private:
    Button boot_button_;
    CircularStrip* led_strip_ = nullptr;

    void InitializeButtons() {
        boot_button_.OnClick([this]() {
            auto& app = Application::GetInstance();
            if (app.GetDeviceState() == kDeviceStateStarting) {
                EnterWifiConfigMode();
                return;
            }
            app.ToggleChatState();
        });
    }

    void InitializeLeds() {
        led_strip_ = new CircularStrip(LED_STRIP_GPIO, LED_STRIP_COUNT);
        new LedStripControl(led_strip_);
    }

public:
    StembotixPlaymateBoard() : boot_button_(BOOT_BUTTON_GPIO) {
        InitializeButtons();
        InitializeLeds();
    }

    virtual Led* GetLed() override {
        return led_strip_;
    }

    virtual AudioCodec* GetAudioCodec() override {
        static NoAudioCodecDuplex audio_codec(AUDIO_INPUT_SAMPLE_RATE, AUDIO_OUTPUT_SAMPLE_RATE,
            AUDIO_I2S_GPIO_BCLK, AUDIO_I2S_GPIO_WS, AUDIO_I2S_GPIO_DOUT, AUDIO_I2S_GPIO_DIN);
        return &audio_codec;
    }
};

DECLARE_BOARD(StembotixPlaymateBoard);
