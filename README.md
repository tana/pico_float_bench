# Float benchmark on Raspberry Pi Pico
## Files
- `float_bench.c`: benchmark program for Raspberry Pi Pico
- `float_bench_arduino/` directory: benchmark program for Arduino-based environments, such as ESP32, for comparison.

## Methods
The benchmark tasks are:
1. Generate 4000 Gaussian random numbers using Box-Muller method.
2. Calculate mean of them.
3. Calculate variance of them.

## Results
| Board | Chip | Arch | Clock [MHz] | FPU | SDK | Generation [us] | Mean calculation [us] | Variance calculation [us] |
| :-- | :-- | :-- | --: | :-- | :-- | --: | --: | --: |
| [Raspberry Pi Pico](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) | RP2040 | Cortex-M0+ | 125[^1] | No | [Pico SDK](https://github.com/raspberrypi/pico-sdk) | 49081 | 11560 | 17100 |
| [Raspberry Pi Pico](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) | RP2040 | Cortex-M0+ | ?[^2] | No | [Arduino mbed core](https://blog.arduino.cc/2021/04/27/arduino-mbed-core-for-rp2040-boards/) | 248237 | 27350 | 36410 |
| [ESP32-DevKitC](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-devkitc.html) | ESP32 | Xtensa LX6 | 240 | Yes | Arduino | 11965 | 3217 | 3334 |
| [AtomS3](https://docs.m5stack.com/en/core/AtomS3) | ESP32-S3 | Xtensa LX7 | 240 | Yes | Arduino | 9369 | 1138 | 1278 |
| [M5Stamp C3](https://docs.m5stack.com/en/core/stamp_c3) | ESP32-C3 | RV32IMC | 160 | No | Arduino | 135386 | 13638 | 19240 |
| [Seeeduino Xiao](https://wiki.seeedstudio.com/Seeeduino-XIAO/) | ATSAMD21G18A-MU | Cortex-M0+ | 48 | No | Arduino | 679416 | 83082 | 113193 |
| [Nucleo F411RE](https://www.st.com/ja/evaluation-tools/nucleo-f411re.html) | STM32F411RE | Cortex-M4 | 100 | Yes | [STM32duino](https://github.com/stm32duino/Arduino_Core_STM32) | 16284 | 1014 | 1139 |

[^1]: Default clock frequency (see page 45 of [Raspberry Pi Pico C SDK document](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)). Max 133 MHz.
[^2]: See https://github.com/arduino/ArduinoCore-mbed/issues/221

Note: **Above values are results of a single measurement.**
"Mean calculation" and "Variance calculation" does not intend the mean/variance of results.
These are time spent to calculate mean and variance of 4000 Gaussian random numbers.

## Discussion
### Performance difference between Pi Pico SDK and Arduino Mbed Core
On Raspberry Pi Pico, Arduino version was slower than Pico SDK version despite the chip was the same.
It seems because of the difference of software float routines.
[Current version of Arduino Mbed Core does not use the optimized float routines built in RP2040](https://github.com/arduino/ArduinoCore-mbed/issues/325) (at the time of October 23, 2021).
However, it seems to be solved soon.
