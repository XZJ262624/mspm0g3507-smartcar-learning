# MSPM0G3507 灰度循迹智能车

基于 **TI MSPM0G3507 + Code Composer Studio（CCS）** 的嵌入式智能车项目。从 PWM、串口和电机驱动逐步迭代到编码器反馈、PID 与灰度循迹。

本仓库以 `M0G3507_7_Tracking` 作为完整循迹版本。

## 功能与代码

| 模块 | 文件 |
| --- | --- |
| 启动与外设配置 | `firmware/main.c`、`firmware/main.syscfg` |
| 八路数字灰度循迹 | `firmware/Hardware/Tracking.c` |
| 电机、PWM、编码器 | `firmware/Hardware/Motor.c`、`PWM.c`、`Encoder.c` |
| 定时控制、按键、OLED | `firmware/Hardware/` |
| 时钟与基础支持 | `firmware/System/` |

## 开发环境

以下版本来自工程配置：CCS 的 Theia 工程格式、TI Arm Clang **4.0.3.LTS**、MSPM0 SDK **2.05.01.00**、SysConfig **1.24.0**，目标器件 **MSPM0G3507**，调试器配置 **XDS110**。

## 导入与运行

1. 安装 CCS 及以上 SDK、编译器和 SysConfig。
2. 使用 CCS 的工程导入功能选择 `firmware/`；目录包含 `.project`、`.cproject`、`.ccsproject`。
3. 在工程属性中确认 SDK 与 SysConfig 能被发现，打开 `main.syscfg` 检查目标芯片和引脚。
4. 构建工程，由 SysConfig 生成 `ti_msp_dl_config.c/.h` 和链接配置；这些生成文件无需从旧 `Debug/` 目录复制。
5. 根据电机方向、编码器和灰度传感器重新校准参数，再下载到板上运行。

## 版本与复现说明

开发过程见 [docs/DEVELOPMENT.md](docs/DEVELOPMENT.md)。发布副本清除了 IDE 缓存、编译输出和无效的旧电脑绝对包含路径，保留固件算法。原项目没有包含外部 SDK；复现时需独立安装。未进行实车测试。

## 来源与许可

保留原文件作者及第三方声明。TI SDK 为外部依赖，按其自身许可使用；本次归档未为原创代码新增许可证。

## 发布验证

已从发布副本重新生成 SysConfig 配置，并完成全部应用源码、生成代码和启动文件的编译与链接，无编译警告。详见 [验证记录](docs/VALIDATION.md)。
