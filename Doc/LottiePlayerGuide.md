# ESP32 Lottie 动画播放指南

本文档旨在指导如何在 ESP32 项目中使用 `esp_rlottie` 库结合 LVGL 来播放 Lottie 动画。

## 1. Lottie 动画文件处理

为了在资源受限的嵌入式系统上高效地加载和播放 Lottie 动画，推荐将 Lottie JSON 文件转换为 C 语言的头文件（`.h`），并将其作为 `uint8_t` 数组编译到固件中。

### 1.1. 转换工具

LVGL 提供了一个 Python 脚本 `scripts/tohex.py` 用于此转换。

### 1.2. 转换步骤

后续将补充详细的转换命令和示例。

## 2. 在代码中播放 Lottie

### 2.1. 引入动画数据

```c
// 引入由 JSON 文件转换而来的 C 数组
extern const uint8_t your_lottie_animation[];
```

### 2.2. 创建 Lottie 对象

使用 `lv_rlottie_create_from_raw` 函数从内存数据创建动画。

```c
// 在 LVGL 父对象上创建 Lottie 动画
lv_obj_t * lottie = lv_rlottie_create_from_raw(lv_screen_active(), width, height, (const char *)your_lottie_animation);
lv_obj_center(lottie); // 将动画居中显示
```

---
*本文档将随着开发进度持续更新。*