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
| Board | Generation [us] | Mean calculation [us] | Variance calculation [us] |
| :-- | --: | --: | --: |
| Raspberry Pi Pico | 49081 | 11560 | 17100 |
| ESP32-DevKitC | 11965 | 3217 | 3334 |
| Seeeduino Xiao | 679416 | 83082 | 113193 |

