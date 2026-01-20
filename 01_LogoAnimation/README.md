# Logo Animation - Text Fade In

This example demonstrates a simple text fade-in animation on the ESP32-P4 Waveshare 7-inch display.

## Features

- **Text Display**: Shows "test text" in the center of the screen
- **Fade-in Animation**: Text gradually fades in over 2 seconds
- **LVGL Based**: Uses LVGL graphics library for rendering

## Hardware Requirements

- ESP32-P4-WIFI6-Touch-LCD-7B development board
- 7-inch 1024x600 display

## Build and Flash

### 1. Set Target

```bash
cd 01_LogoAnimation
idf.py set-target esp32p4
```

### 2. Build

```bash
idf.py build
```

### 3. Flash and Monitor

```bash
idf.py -p COMx flash monitor
```

## Expected Result

- Screen starts with black background
- "test text" appears in the center
- Text gradually fades in from transparent to fully visible over 2 seconds
- Animation completes and text remains visible

## Customization

### Change Text

Edit `main/main.c`:
```c
lv_label_set_text(label, "Your Text Here");
```

### Change Animation Duration

Edit `main/main.c`:
```c
#define FADE_IN_DURATION_MS    2000  // Change to desired duration in milliseconds
```

### Change Text Color

Edit `main/main.c`:
```c
lv_obj_set_style_text_color(label, lv_color_white(), LV_PART_MAIN);
// Change to: lv_color_red(), lv_color_green(), lv_color_blue(), etc.
```

### Change Font Size

Edit `main/main.c`:
```c
lv_obj_set_style_text_font(label, &lv_font_montserrat_40, LV_PART_MAIN);
// Available sizes: 12, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40
```

## Project Structure

```
01_LogoAnimation/
├── CMakeLists.txt          # Main project CMake file
├── sdkconfig.defaults      # Default configuration
├── README.md               # This file
└── main/
    ├── CMakeLists.txt      # Main component CMake file
    ├── idf_component.yml   # Component dependencies
    └── main.c              # Main application code
```

## Notes

- The animation uses LVGL's opacity feature for smooth fading
- The fade-in is implemented in a separate FreeRTOS task
- Screen resolution is 1024x600 pixels
- Text is centered both horizontally and vertically

