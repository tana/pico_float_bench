# Float benchmark on Raspberry Pi Pico

## Methods
The benchmark tasks are:
1. Generate 4000 Gaussian random numbers using Box-Muller method.
2. Calculate mean of them.
3. Calculate variance of them.

## Results
| Board | Generation [us] | Mean calculation [us] | Variance calculation [us] |
| :-- | --: | --: | --: |
| Raspberry Pi Pico | 49081 | 11560 | 17100 |
| ESP32-DevKitC | 

