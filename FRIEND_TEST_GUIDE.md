# 朋友测试指南 - ESP32-P4 Waveshare 7寸显示屏

## 前提条件

1. **已安装 ESP-IDF v5.1 或更高版本**
2. **已设置好 ESP-IDF 环境**（能运行 `idf.py` 命令）
3. **开发板已连接**（USB 线连接到电脑）

## 快速开始

### 方法 1：测试 LogoAnimation（渐入文字动画）

#### 1. 进入项目目录

```bash
cd "C:\Users\test\Downloads\esp32-p4-waveshare-7inch-amoled-bringup-main\01_LogoAnimation"
```

#### 2. 设置目标并编译

```bash
idf.py set-target esp32p4
idf.py build
```

#### 3. 烧录并运行

```bash
idf.py -p COMx flash monitor
```

**替换 `COMx` 为实际的串口号**（如 COM3, COM4, COM5 等）

#### 预期效果：
- 屏幕显示黑色背景
- "test text" 文字在屏幕中心
- 文字从透明逐渐淡入，2秒后完全显示

---

### 方法 2：测试基础显示（07_color_panel）

#### 1. 进入示例目录

```bash
cd "C:\Users\test\Downloads\esp32-p4-waveshare-7inch-amoled-bringup-main\ESP32-P4-WIFI6-Touch-LCD-7B-main\examples\ESP-IDF\07_color_panel"
```

#### 2. 设置目标并编译

```bash
idf.py set-target esp32p4
idf.py build
```

#### 3. 烧录并运行

```bash
idf.py -p COMx flash monitor
```

#### 预期效果：
- 屏幕显示垂直彩色条纹（硬件测试图案）
- 这是最简单的显示测试

---

### 方法 3：测试 LVGL 显示（08_lvgl_display_panel）

#### 1. 进入示例目录

```bash
cd "C:\Users\test\Downloads\esp32-p4-waveshare-7inch-amoled-bringup-main\ESP32-P4-WIFI6-Touch-LCD-7B-main\examples\ESP-IDF\08_lvgl_display_panel"
```

#### 2. 设置目标并编译

```bash
idf.py set-target esp32p4
idf.py build
```

#### 3. 烧录并运行

```bash
idf.py -p COMx flash monitor
```

#### 预期效果：
- 屏幕显示彩色填充（红、绿、蓝、白）
- 可以触摸屏幕画点

---

## 如何找到串口（COM 端口）

### Windows 方法：

1. **设备管理器：**
   - 按 `Win + X`，选择"设备管理器"
   - 展开"端口 (COM 和 LPT)"
   - 找到 "USB Serial Port" 或 "Silicon Labs CP210x" 等
   - 记住 COM 号（如 COM3, COM4）

2. **自动检测：**
   ```bash
   idf.py flash monitor
   ```
   系统会尝试自动检测端口

---

## 常见问题

### 1. 找不到串口

**解决方法：**
- 检查 USB 线是否连接
- 检查设备管理器中的端口
- 尝试不同的 USB 端口
- 安装 USB 驱动（如果需要）

### 2. 编译错误

**解决方法：**
```bash
# 安装依赖
idf.py install-deps

# 清理并重新编译
idf.py fullclean
idf.py build
```

### 3. 屏幕黑屏

**可能原因：**
- 背光没有打开
- 显示初始化失败
- 电源不足

**检查方法：**
- 查看串口输出是否有错误信息
- 确认串口显示初始化成功的日志

### 4. 编译时间很长

**正常现象：**
- 首次编译需要下载依赖组件（5-10分钟）
- 后续编译会快很多（1-2分钟）

---

## 推荐测试顺序

1. **第一步：** 运行 `07_color_panel`（最简单，验证显示链路）
2. **第二步：** 运行 `01_LogoAnimation`（测试自定义代码）
3. **第三步：** 运行 `08_lvgl_display_panel`（测试 LVGL 和触摸）

---

## 快速命令参考

```bash
# 设置目标
idf.py set-target esp32p4

# 编译
idf.py build

# 烧录
idf.py -p COMx flash

# 监视串口
idf.py -p COMx monitor

# 烧录并监视（一步完成）
idf.py -p COMx flash monitor

# 清理构建
idf.py fullclean
```

---

## 需要帮助？

如果遇到问题，请提供：
1. 串口输出的完整日志
2. 错误信息截图
3. 使用的命令和路径

---

## 项目结构说明

```
esp32-p4-waveshare-7inch-amoled-bringup-main/
├── 01_LogoAnimation/          # 自定义渐入文字动画
├── ESP32-P4-WIFI6-Touch-LCD-7B-main/
│   └── examples/ESP-IDF/
│       ├── 07_color_panel/    # 基础显示测试
│       ├── 08_lvgl_display_panel/  # LVGL 显示测试
│       └── ...
├── serial_test.ino            # Arduino 串口测试
├── i2c_scanner.ino            # I2C 扫描工具
└── ...
```

---

**祝测试顺利！** 🚀

