# ESP32-P4 Waveshare 7-inch Display Screen Test

This repository contains a screen test sketch for the **Waveshare ESP32-P4-WIFI6 7-inch Touch Display Development Board**.

## Display Specifications

- **Resolution**: 1024 × 600 pixels
- **Panel**: 7" IPS touch display
- **Interface**: MIPI DSI LCD
- **Color Depth**: RGB565, RGB666, RGB888 supported
- **Touch**: GT911 capacitive touch controller (5-point)

## Hardware Setup

1. Connect the display board to your computer via USB-C (for programming/debugging)
2. Ensure adequate power supply (the board may require external power for full brightness)
3. Connect via the USB TO UART Type-C port for serial monitoring

## Software Requirements

### Arduino IDE Setup

1. **Install ESP32 Board Support**:
   - Go to `File` → `Preferences`
   - Add to Additional Board Manager URLs:
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Go to `Tools` → `Board` → `Boards Manager`
   - Search for "ESP32" and install the latest version

2. **Install ESP32-P4 Support**:
   - ESP32-P4 support may require ESP-IDF or a specific board package
   - Check Waveshare's documentation for their BSP/board package

3. **Install Display Library**:
   - Option A: Use Waveshare BSP (recommended)
     - Install from: https://components.espressif.com/components/waveshare/esp32_p4_platform
   - Option B: Use ESP-IDF display drivers
   - Option C: Use a compatible Arduino display library

### Library Installation

The sketch requires one of the following display libraries:

1. **Waveshare ESP32-P4 Platform BSP** (Recommended)
   ```
   Component Registry: waveshare/esp32_p4_platform
   ```

2. **ESP-IDF Display Drivers**
   - Usually included with ESP32-P4 board support

3. **Custom Library**
   - Check Waveshare's GitHub: https://github.com/waveshareteam/ESP32-display-support

## Usage

1. **Open the Sketch**:
   - Open `screen_test.ino` in Arduino IDE

2. **Configure Display Library**:
   - Uncomment the appropriate `#include` statement at the top of the file
   - Adjust initialization code in `initDisplay()` function
   - Implement the drawing functions based on your library's API

3. **Configure Pins** (if needed):
   - Check Waveshare's wiki/schematic for exact pin mappings
   - Update I2C pins if backlight control uses different pins
   - Update reset/backlight control pins if needed

4. **Select Board**:
   - Go to `Tools` → `Board` → Select your ESP32-P4 board
   - Set appropriate upload speed and port

5. **Upload and Run**:
   - Upload the sketch
   - Open Serial Monitor at 115200 baud
   - Watch the display cycle through test patterns

## Test Patterns

The sketch includes 9 different test patterns that cycle every 3 seconds:

1. **Solid Colors**: Cycles through Red, Green, Blue, White, Black
2. **Color Bars**: Vertical bars of 8 primary colors
3. **Gradient**: Horizontal gradient from red to blue
4. **Text**: Displays text information about the board
5. **Geometric Shapes**: Rectangles, circles, and lines
6. **Moving Pattern**: Animated moving bars
7. **Checkerboard**: Black and white checkerboard pattern
8. **Color Wheel**: Radial color wheel pattern
9. **Info Screen**: System information display

## Customization

### Adjust Test Duration

Change `TEST_DURATION` constant:
```cpp
const unsigned long TEST_DURATION = 3000; // milliseconds
```

### Modify Colors

Update color definitions:
```cpp
#define COLOR_RED     0xF800  // RGB565 format
```

### Add Custom Tests

Add new test cases in the `loop()` switch statement and implement the test function.

## Troubleshooting

### Display Not Initializing

1. **Check Power**: Ensure adequate power supply (may need external power)
2. **Check Connections**: Verify all display connections are secure
3. **Check Library**: Ensure correct display library is installed and included
4. **Check Pins**: Verify pin configurations match your hardware

### Backlight Not Working

- Backlight I2C address: `0x45`, Register: `0xAB`
- Check I2C pin connections (SDA/SCL)
- Verify I2C address is correct for your board revision

### Blank Screen

1. Check serial output for error messages
2. Verify display initialization succeeded
3. Try adjusting backlight brightness manually
4. Check if display requires specific initialization sequence

### Compilation Errors

1. Ensure ESP32-P4 board support is installed
2. Verify display library is compatible with ESP32-P4
3. Check that all required libraries are installed

## Notes

- The exact pin mappings and initialization sequence depend on your specific board revision
- Refer to Waveshare's wiki for detailed pinout: https://www.waveshare.net/wiki/ESP32-P4-WIFI6-Touch-LCD-7B
- Some functions are placeholders - you'll need to implement them based on your display library's API
- MIPI DSI displays require specific timing parameters that may need adjustment

## Resources

- **Waveshare Wiki**: https://www.waveshare.net/wiki/ESP32-P4-WIFI6-Touch-LCD-7B
- **Waveshare BSP**: https://components.espressif.com/components/waveshare/esp32_p4_platform
- **ESP-IDF Documentation**: https://docs.espressif.com/projects/esp-idf/en/latest/
- **Product Page**: Check Waveshare's product page for latest documentation

## License

This code is provided as-is for testing and development purposes.


