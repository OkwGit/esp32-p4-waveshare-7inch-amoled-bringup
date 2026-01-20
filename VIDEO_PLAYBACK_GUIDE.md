# ESP32-P4 视频播放测试指南

## ⚠️ 重要限制

**ESP32-P4 不支持直接播放 MP4 文件！**

- ✅ **支持格式：MJPEG** (Motion JPEG)
- ❌ **不支持：MP4, H.264, H.265 等**

**原因：** ESP32-P4 有 JPEG 硬件解码器，但没有 H.264/H.265 视频解码器。

## 准备工作

### 1. 转换视频格式（MP4 → MJPEG）

你需要使用 **ffmpeg** 将 MP4 转换为 MJPEG 格式。

#### Windows 安装 ffmpeg：

1. **下载 ffmpeg：**
   - 访问：https://ffmpeg.org/download.html
   - 或直接下载：https://www.gyan.dev/ffmpeg/builds/
   - 下载 "ffmpeg-release-essentials.zip"

2. **解压并添加到系统路径：**
   - 解压到 `C:\ffmpeg` 或任意位置
   - 将 `bin` 文件夹路径添加到系统环境变量 PATH
   - 或在命令行中直接使用完整路径

3. **验证安装：**
   ```bash
   ffmpeg -version
   ```

#### 转换视频命令：

```bash
ffmpeg -i YOUR_VIDEO.mp4 -vcodec mjpeg -q:v 2 -vf "scale=1024:600" -acodec copy OUTPUT.mjpeg
```

**参数说明：**
- `-i YOUR_VIDEO.mp4` - 输入文件
- `-vcodec mjpeg` - 视频编码为 MJPEG
- `-q:v 2` - 视频质量（2-5，数字越小质量越高，文件越大）
- `-vf "scale=1024:600"` - 缩放至屏幕分辨率（1024x600）
- `-acodec copy` - 音频直接复制（或使用 `-an` 移除音频）
- `OUTPUT.mjpeg` - 输出文件名

**示例：**
```bash
ffmpeg -i test_video.mp4 -vcodec mjpeg -q:v 2 -vf "scale=1024:600" -an test_video.mjpeg
```

**注意：** MJPEG 文件会比较大，因为是无损压缩格式。

### 2. 准备 SD 卡

1. **格式化 SD 卡为 FAT32 格式**
2. **将转换后的 `.mjpeg` 文件复制到 SD 卡根目录**
3. **插入 SD 卡到开发板的 TF 卡槽**

## 运行视频播放示例

### 1. 进入示例目录

```bash
cd "C:\Users\test\Downloads\ESP32-P4-WIFI6-Touch-LCD-7B-3871b0b23777c14de90cbac2f8d9adbf40c03022\ESP32-P4-WIFI6-Touch-LCD-7B-3871b0b23777c14de90cbac2f8d9adbf40c03022\examples\ESP-IDF\11_esp_brookesia_phone"
```

### 2. 设置目标

```bash
idf.py set-target esp32p4
```

### 3. 配置项目（重要！）

```bash
idf.py menuconfig
```

**必须配置：**

1. 进入 `Example Configurations`
2. 选择 `Enable SD Card` - **必须启用！**
3. 保存并退出（按 `S` 保存，然后 `Q` 退出）

### 4. 编译项目

```bash
idf.py build
```

**注意：** 这个示例比较大，编译可能需要较长时间（5-10分钟）。

### 5. 烧录并运行

```bash
idf.py -p COMx flash monitor
```

### 6. 使用视频播放器

1. **启动后**，屏幕会显示类似 Android 的界面
2. **插入 SD 卡**（如果还没插入）
3. **找到 "Video Player" 应用图标**，点击打开
4. **选择视频文件**并播放

## 预期结果

- ✅ 屏幕显示视频内容
- ✅ 可以播放、暂停、停止
- ✅ 显示播放进度条

## 常见问题

### 1. 找不到视频文件

- 确认 SD 卡格式为 FAT32
- 确认文件扩展名为 `.mjpeg`
- 确认文件在 SD 卡根目录（不是子文件夹）

### 2. 视频播放卡顿

- **降低视频质量：** 使用 `-q:v 5`（更大的数字）
- **降低分辨率：** 使用 `-vf "scale=800:480"` 或更小
- **移除音频：** 使用 `-an` 参数

### 3. 视频播放器应用不显示

- 确认已启用 SD 卡支持（menuconfig）
- 确认 SD 卡已插入
- 检查串口日志是否有错误

### 4. 编译错误

- 确保 ESP-IDF 版本 >= v5.4
- 运行 `idf.py install-deps` 安装依赖
- 检查网络连接（需要下载组件）

### 5. 文件太大

MJPEG 文件通常比 MP4 大很多。如果文件太大：

- 降低质量：`-q:v 5`
- 降低帧率：`-r 15`（15 fps）
- 缩短视频时长

**示例（低质量、低帧率）：**
```bash
ffmpeg -i input.mp4 -vcodec mjpeg -q:v 5 -r 15 -vf "scale=1024:600" -an output.mjpeg
```

## 快速转换脚本（Windows）

创建一个批处理文件 `convert_video.bat`：

```batch
@echo off
echo Converting MP4 to MJPEG for ESP32-P4...
echo.

if "%1"=="" (
    echo Usage: convert_video.bat input.mp4
    exit /b 1
)

set INPUT=%1
set OUTPUT=%~n1.mjpeg

echo Input: %INPUT%
echo Output: %OUTPUT%
echo.

ffmpeg -i "%INPUT%" -vcodec mjpeg -q:v 2 -vf "scale=1024:600" -an "%OUTPUT%"

echo.
echo Conversion complete!
pause
```

**使用方法：**
```bash
convert_video.bat your_video.mp4
```

## 性能优化建议

1. **视频分辨率：** 使用 1024x600 或更小
2. **帧率：** 15-20 fps 通常足够流畅
3. **质量：** `-q:v 3-4` 是质量和文件大小的平衡点
4. **音频：** 如果不需要，使用 `-an` 移除音频

## 下一步

如果视频播放成功，可以：
- 测试不同的视频文件
- 调整视频质量和分辨率
- 尝试其他示例（如 `09_lvgl_demo_v8` 或 `10_lvgl_demo_v9`）


