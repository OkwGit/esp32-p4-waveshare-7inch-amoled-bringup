# 快速启动指南

## 运行步骤

### 1. 进入项目目录

```bash
cd "C:\Users\oxpas\Documents\GitHub\esp32-p4-waveshare-7inch-amoled-bringup\01_LogoAnimation"
```

### 2. 设置目标

```bash
idf.py set-target esp32p4
```

### 3. 编译

```bash
idf.py build
```

### 4. 烧录并运行

```bash
idf.py -p COMx flash monitor
```

## 预期效果

- 屏幕显示黑色背景
- "test text" 文字在屏幕中心
- 文字从透明逐渐淡入，2秒后完全显示
- 动画完成后文字保持可见

## 自定义修改

### 修改文字内容

编辑 `main/main.c` 第 58 行：
```c
lv_label_set_text(label, "你的文字");
```

### 修改动画时长

编辑 `main/main.c` 第 10 行：
```c
#define FADE_IN_DURATION_MS    2000  // 改为你想要的毫秒数
```

### 修改文字颜色

编辑 `main/main.c` 第 60 行：
```c
lv_obj_set_style_text_color(label, lv_color_white(), LV_PART_MAIN);
// 可选: lv_color_red(), lv_color_green(), lv_color_blue(), lv_color_yellow()
```

### 修改字体大小

编辑 `main/main.c` 第 61 行：
```c
lv_obj_set_style_text_font(label, &lv_font_montserrat_40, LV_PART_MAIN);
// 可选大小: 12, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40
```

## 故障排除

### 编译错误：找不到 bsp_extra

确保路径正确，bsp_extra 组件应该在：
```
ESP32-P4-WIFI6-Touch-LCD-7B-main/examples/ESP-IDF/08_lvgl_display_panel/components/bsp_extra
```

### 屏幕黑屏

- 检查串口输出是否有错误
- 确认背光已打开（代码中有 `bsp_display_backlight_on()`）
- 检查显示初始化是否成功

### 文字不显示

- 检查 LVGL 是否正常初始化
- 查看串口日志中的错误信息
- 确认字体已正确配置

