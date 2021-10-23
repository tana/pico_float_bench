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
| Board | Chip | Arch | Clock [MHz] | FPU | Generation [us] | Mean calculation [us] | Variance calculation [us] |
| :-- | :-- | :-- | --: | :-- | --: | --: | --: |
| [Raspberry Pi Pico](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) | RP2040 | Cortex-M0+ | 133 | No | 49081 | 11560 | 17100 |
| [ESP32-DevKitC](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-devkitc.html) | ESP32 | Xtensa LX6 | 240 | Yes | 11965 | 3217 | 3334 |
| [Seeeduino Xiao](https://wiki.seeedstudio.com/Seeeduino-XIAO/) | ATSAMD21G18A-MU | Cortex-M0+ | 48 | No | 679416 | 83082 | 113193 |

