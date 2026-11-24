#include "wifi_board.h"
#include "codecs/no_audio_codec.h"
#include "display/oled_display.h"
#include "application.h"
#include "button.h"
#include "config.h"

#include <esp_log.h>
#include <driver/gpio.h>
#include <driver/i2c_master.h>
#include <esp_lcd_panel_ops.h>
#include <esp_lcd_panel_vendor.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define TAG "StembotixC3Mini"

class StembotixC3MiniBoard : public WifiBoard {
private:
    Button boot_button_;
    i2c_master_bus_handle_t i2c_bus_ = nullptr;
    esp_lcd_panel_io_handle_t panel_io_ = nullptr;
    esp_lcd_panel_handle_t panel_ = nullptr;
    Display* display_ = nullptr;

    // MAX98357A SD pin: keep the amp enabled
    void InitializeAmp() {
        gpio_config_t io_conf = {};
        io_conf.pin_bit_mask = 1ULL << AUDIO_AMP_SD_GPIO;
        io_conf.mode = GPIO_MODE_OUTPUT;
        gpio_config(&io_conf);
        gpio_set_level(AUDIO_AMP_SD_GPIO, 1);
    }

    void InitializeDisplay() {
        // Hardware reset of the OLED (RES wired to GPIO0)
        gpio_config_t rst_conf = {};
        rst_conf.pin_bit_mask = 1ULL << DISPLAY_RST_PIN;
        rst_conf.mode = GPIO_MODE_OUTPUT;
        gpio_config(&rst_conf);
        gpio_set_level(DISPLAY_RST_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(20));
        gpio_set_level(DISPLAY_RST_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(50));

        i2c_master_bus_config_t bus_config = {};
        bus_config.i2c_port = I2C_NUM_0;
        bus_config.sda_io_num = DISPLAY_SDA_PIN;
        bus_config.scl_io_num = DISPLAY_SCL_PIN;
        bus_config.clk_source = I2C_CLK_SRC_DEFAULT;
        bus_config.glitch_ignore_cnt = 7;
        bus_config.flags.enable_internal_pullup = 1;
        if (i2c_new_master_bus(&bus_config, &i2c_bus_) != ESP_OK) {
            ESP_LOGE(TAG, "I2C bus init failed, running without display");
            display_ = new NoDisplay();
            return;
        }

        // Don't hang if the OLED is missing or loose: probe first, fall back to NoDisplay
        if (i2c_master_probe(i2c_bus_, DISPLAY_I2C_ADDR, 200) != ESP_OK) {
            ESP_LOGW(TAG, "OLED not found at 0x%02X, running without display", DISPLAY_I2C_ADDR);
            display_ = new NoDisplay();
            return;
        }

        esp_lcd_panel_io_i2c_config_t io_config = {};
        io_config.dev_addr = DISPLAY_I2C_ADDR;
        io_config.scl_speed_hz = 100 * 1000;
        io_config.control_phase_bytes = 1;
        io_config.dc_bit_offset = 6;
        io_config.lcd_cmd_bits = 8;
        io_config.lcd_param_bits = 8;
        io_config.on_color_trans_done = nullptr;
        io_config.user_ctx = nullptr;
        io_config.flags.dc_low_on_data = 0;
        io_config.flags.disable_control_phase = 0;
        if (esp_lcd_new_panel_io_i2c(i2c_bus_, &io_config, &panel_io_) != ESP_OK) {
            display_ = new NoDisplay();
            return;
        }

        // SSD1309 128x64 is command-compatible with the SSD1306 driver
        esp_lcd_panel_dev_config_t panel_config = {};
        panel_config.reset_gpio_num = GPIO_NUM_NC;   // already reset above
        panel_config.bits_per_pixel = 1;
        esp_lcd_panel_ssd1306_config_t ssd1306_config = {
            .height = static_cast<uint8_t>(DISPLAY_HEIGHT),
        };
        panel_config.vendor_config = &ssd1306_config;

        if (esp_lcd_new_panel_ssd1306(panel_io_, &panel_config, &panel_) != ESP_OK ||
            esp_lcd_panel_reset(panel_) != ESP_OK ||
            esp_lcd_panel_init(panel_) != ESP_OK) {
            ESP_LOGE(TAG, "Failed to initialize display");
            display_ = new NoDisplay();
            return;
        }
        esp_lcd_panel_disp_on_off(panel_, true);
        display_ = new OledDisplay(panel_io_, panel_, DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y);
    }

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
    StembotixC3MiniBoard() : WifiBoard(), boot_button_(BOOT_BUTTON_GPIO) {
        InitializeAmp();
        InitializeDisplay();
        InitializeButtons();
    }

    virtual AudioCodec* GetAudioCodec() override {
        static NoAudioCodecSimplex audio_codec(AUDIO_INPUT_SAMPLE_RATE, AUDIO_OUTPUT_SAMPLE_RATE,
            AUDIO_I2S_SPK_GPIO_BCLK, AUDIO_I2S_SPK_GPIO_LRCK, AUDIO_I2S_SPK_GPIO_DOUT,
            AUDIO_I2S_MIC_GPIO_SCK, AUDIO_I2S_MIC_GPIO_WS, AUDIO_I2S_MIC_GPIO_DIN);
        return &audio_codec;
    }

    virtual Display* GetDisplay() override {
        return display_;
    }
};

DECLARE_BOARD(StembotixC3MiniBoard);
