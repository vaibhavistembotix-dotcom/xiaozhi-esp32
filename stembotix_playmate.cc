#include "wifi_board.h"
#include "codecs/no_audio_codec.h"
#include "application.h"
#include "button.h"
#include "config.h"
#include "display/display.h"

#include <esp_log.h>

#define TAG "StembotixPlaymate"

// Stembotix Playmate V2: no OLED, I2S mic + amp on shared BCLK/WS.
class StembotixPlaymateBoard : public WifiBoard {
private:
    Button boot_button_;
    Display* display_ = nullptr;

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

public:
    StembotixPlaymateBoard() : WifiBoard(), boot_button_(BOOT_BUTTON_GPIO) {
        display_ = new NoDisplay();
        InitializeButtons();
        ESP_LOGI(TAG, "Playmate board ready");
    }

    virtual AudioCodec* GetAudioCodec() override {
        static NoAudioCodecDuplex audio_codec(AUDIO_INPUT_SAMPLE_RATE, AUDIO_OUTPUT_SAMPLE_RATE,
            AUDIO_I2S_GPIO_BCLK, AUDIO_I2S_GPIO_WS, AUDIO_I2S_GPIO_DOUT, AUDIO_I2S_GPIO_DIN);
        return &audio_codec;
    }

    virtual Display* GetDisplay() override {
        return display_;
    }
};

DECLARE_BOARD(StembotixPlaymateBoard);
