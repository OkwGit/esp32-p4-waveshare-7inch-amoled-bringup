# ESP-IDF 运行 07_color_panel 示例指南（朋友版本）

## 前置要求

1. **安装 ESP-IDF**
   - 下载并安装 ESP-IDF v5.1 或更高版本
   - 参考：https://docs.espressif.com/projects/esp-idf/en/latest/esp32p4/get-started/

2. **设置环境变量**
   - Windows: 运行 `install.bat` 和 `export.bat`（在 ESP-IDF 安装目录）
   - 或使用 ESP-IDF PowerShell/CMD 快捷方式

## 运行步骤

### 1. 打开 ESP-IDF 终端

**Windows:**
- 方法1: 使用 ESP-IDF PowerShell（推荐）
- 方法2: 使用 ESP-IDF CMD
- 方法3: 在普通 PowerShell/CMD 中运行：
  ```powershell
  # 进入 ESP-IDF 目录（根据你的安装路径调整）
  cd C:\Espressif\frameworks\esp-idf-v5.1
  .\install.bat esp32p4
  .\export.bat
  ```

### 2. 进入示例目录

```bash
cd "C:\Users\test\Downloads\ESP32-P4-WIFI6-Touch-LCD-7B-3871b0b23777c14de90cbac2f8d9adbf40c03022\ESP32-P4-WIFI6-Touch-LCD-7B-3871b0b23777c14de90cbac2f8d9adbf40c03022\examples\ESP-IDF\07_color_panel"
```

### 3. 设置目标芯片

```bash
idf.py set-target esp32p4
```

### 4. 配置项目（可选，通常使用默认配置即可）

```bash
idf.py menuconfig
```

**重要配置检查：**
- `Component config` → `LCD` → 确保 MIPI DSI 支持已启用
- `Component config` → `FreeRTOS` → 检查任务看门狗设置

如果不需要修改，直接跳过这一步。

### 5. 编译项目

```bash
idf.py build
```

**如果编译出错：**
- 确保已安装所有依赖：`idf.py install-deps`
- 检查 ESP-IDF 版本是否支持 ESP32-P4
- 确保网络连接正常（需要下载组件）

### 6. 连接开发板

- 使用 USB 线连接开发板到电脑
- 确认串口端口号（在设备管理器中查看）

### 7. 烧录程序

```bash
idf.py -p COMx flash
```

**Windows 串口示例：**
- `COM3`, `COM4`, `COM5` 等
- 如果不确定端口，运行 `idf.py -p COMx flash monitor` 会自动检测

### 8. 查看串口输出

```bash
idf.py -p COMx monitor
```

**或者一步完成烧录+监视：**
```bash
idf.py -p COMx flash monitor
```

**退出监视器：** 按 `Ctrl+]`

## 预期结果

如果一切正常，你应该看到：

1. **串口输出：**
   ```
   I (xxx) ek79007_test: Initialize LCD device
   I (xxx) ek79007_test: MIPI DSI PHY Powered on
   I (xxx) ek79007_test: Initialize MIPI DSI bus
   I (xxx) ek79007_test: Install panel IO
   I (xxx) ek79007_test: Install LCD driver of ek79007
   I (xxx) ek79007_test: Show color bar pattern drawn by hardware
   ```

2. **屏幕显示：**
   - 屏幕应该**亮起来**
   - 显示**垂直彩色条纹**（硬件生成的测试图案）
   - 这是最简单的验证：如果看到颜色，说明 MIPI DSI + 面板初始化成功！

## 代码说明

`app_main()` 函数会：
1. 初始化 LCD 设备（包括 MIPI DSI PHY 电源、总线、面板）
2. 显示硬件生成的垂直彩色条纹图案

**关键配置（在代码中）：**
- 分辨率：1024 x 600
- 颜色深度：24-bit (RGB888)
- Reset 引脚：GPIO 33
- 背光引脚：-1（未使用，可能通过 I2C 控制）
- MIPI DSI 通道数：2
- MIPI DSI PHY 电源：LDO 通道 3，2.5V

## 常见问题

### 1. 编译错误：找不到组件

```bash
idf.py install-deps
```

### 2. 找不到串口

- 检查 USB 驱动是否安装
- 检查设备管理器中的端口号
- 尝试不同的 USB 端口

### 3. 烧录失败

- 按住 BOOT 按钮，然后按 RESET，再松开 BOOT
- 或者使用 `idf.py -p COMx flash` 时自动进入下载模式

### 4. 屏幕仍然黑屏

**可能原因：**
- 背光没有打开（代码中 `TEST_PIN_NUM_BK_LIGHT = -1`，说明可能通过 I2C 控制）
- 电源不足（可能需要外部电源）
- 引脚配置不对（需要检查实际硬件）

**下一步：**
- 如果串口显示初始化成功但屏幕黑屏，需要找到背光控制方法
- 检查是否需要额外的背光初始化代码

### 5. 屏幕显示但颜色不对

- 检查 RGB 顺序配置
- 检查颜色深度设置

## 下一步

如果 `07_color_panel` 成功显示颜色：
- ✅ MIPI DSI 初始化正确
- ✅ 面板参数正确
- ✅ 显示链路工作正常

然后可以：
1. 继续测试背光控制（如果还没亮）
2. 运行 `08_lvgl_display_panel` 测试 LVGL
3. 运行 `09_lvgl_demo_v8` 或 `10_lvgl_demo_v9` 看完整演示

## 快速命令总结

```bash
# 1. 进入目录
cd "C:\Users\test\Downloads\ESP32-P4-WIFI6-Touch-LCD-7B-3871b0b23777c14de90cbac2f8d9adbf40c03022\ESP32-P4-WIFI6-Touch-LCD-7B-3871b0b23777c14de90cbac2f8d9adbf40c03022\examples\ESP-IDF\07_color_panel"

# 2. 设置目标
idf.py set-target esp32p4

# 3. 编译
idf.py build

# 4. 烧录并监视（替换 COMx 为你的端口）
idf.py -p COMx flash monitor
```

## 简化路径（可选）

如果路径太长，可以：

1. **使用短路径：**
   ```bash
   # 先进入父目录
   cd C:\Users\test\Downloads
   # 然后使用 Tab 键自动补全
   cd ESP32-P4-WIFI6-Touch-LCD-7B-3871b0b23777c14de90cbac2f8d9adbf40c03022\ESP32-P4-WIFI6-Touch-LCD-7B-3871b0b23777c14de90cbac2f8d9adbf40c03022\examples\ESP-IDF\07_color_panel
   ```

2. **或者直接复制完整路径到命令行：**
   - 在文件资源管理器中导航到 `07_color_panel` 文件夹
   - 在地址栏点击，复制完整路径
   - 在命令行输入 `cd ` 然后粘贴路径


