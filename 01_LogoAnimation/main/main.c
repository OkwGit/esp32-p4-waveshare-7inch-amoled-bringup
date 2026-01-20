#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "lvgl.h"
#include "bsp/esp-bsp.h"
#include "bsp/display.h"
#include "bsp_board_extra.h"

static const char *TAG = "LogoAnimation";

#define FADE_IN_DURATION_MS    2000
#define FADE_STEPS            100
#define FADE_DELAY_MS          (FADE_IN_DURATION_MS / FADE_STEPS)

static lv_obj_t *label = NULL;

static void fade_in_animation_task(void *pvParameters)
{
    uint8_t opacity = 0;
    uint8_t target_opacity = 255;
    
    ESP_LOGI(TAG, "Starting fade-in animation...");
    
    for (int step = 0; step <= FADE_STEPS; step++) {
        opacity = (uint8_t)((step * 255) / FADE_STEPS);
        
        if (label != NULL) {
            lv_obj_set_style_opa(label, opacity, LV_PART_MAIN);
            lv_obj_invalidate(label);
        }
        
        vTaskDelay(pdMS_TO_TICKS(FADE_DELAY_MS));
    }
    
    ESP_LOGI(TAG, "Fade-in animation complete!");
    vTaskDelete(NULL);
}

void app_main(void)
{
    ESP_LOGI(TAG, "Initializing display...");
    
    bsp_display_cfg_t cfg = {
        .lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG(),
        .buffer_size = BSP_LCD_DRAW_BUFF_SIZE,
        .double_buffer = BSP_LCD_DRAW_BUFF_DOUBLE,
        .flags = {
            .buff_dma = true,
            .buff_spiram = false,
            .sw_rotate = false,
        }
    };
    
    lv_display_t *disp = bsp_display_start_with_config(&cfg);
    if (disp == NULL) {
        ESP_LOGE(TAG, "Display initialization failed!");
        return;
    }
    
    bsp_display_backlight_on();
    ESP_LOGI(TAG, "Display initialized successfully");
    
    lv_obj_t *scr = lv_scr_act();
    
    lv_obj_set_style_bg_color(scr, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, LV_PART_MAIN);
    
    label = lv_label_create(scr);
    lv_label_set_text(label, "test text");
    lv_obj_set_style_text_color(label, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_40, LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    
    lv_obj_set_style_opa(label, 0, LV_PART_MAIN);
    
    ESP_LOGI(TAG, "Label created, starting fade-in animation");
    
    xTaskCreate(
        fade_in_animation_task,
        "fade_in_task",
        4096,
        NULL,
        5,
        NULL
    );
    
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10));
        lv_task_handler();
    }
}

