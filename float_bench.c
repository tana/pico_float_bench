#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/time.h"

#define N 4000

void benchmark();
void generate_gaussian(float* x, size_t n);
float calc_mean(float* x, size_t n);
float calc_variance(float* x, float mean, size_t n);

void benchmark()
{
    float x[N];
    absolute_time_t start_time, end_time;

    start_time = get_absolute_time();
    generate_gaussian(x, N);
    end_time = get_absolute_time();
    printf("generate_gaussian: %lld us\n", absolute_time_diff_us(start_time, end_time));

    start_time = get_absolute_time();
    float mean = calc_mean(x, N);
    end_time = get_absolute_time();
    printf("calc_mean: %lld us\n", absolute_time_diff_us(start_time, end_time));

    start_time = get_absolute_time();
    float variance = calc_variance(x, mean, N);
    end_time = get_absolute_time();
    printf("calc_variance: %lld us\n", absolute_time_diff_us(start_time, end_time));

    printf("mean = %f, variance = %f\n", mean, variance);
}

void generate_gaussian(float* x, size_t n)
{
    for (size_t i = 0; i < n / 2; i++) {
        // Generate two gaussian random numbers
        // using Box-Muller transformation
        //  See: https://mathworld.wolfram.com/Box-MullerTransformation.html
        float random1 = (float)rand() / (float)RAND_MAX;
        float random2 = (float)rand() / (float)RAND_MAX;
        float sqrt_part = sqrtf(-2 * logf(random1));
        float angle_part = 2 * M_PI * random2;
        x[2 * i] = sqrt_part * cosf(angle_part);
        x[2 * i + 1] = sqrt_part * sinf(angle_part);
    }
}

float calc_mean(float* x, size_t n)
{
    float mean = 0;
    for (size_t i = 0; i < n; i++) {
        mean = (i * mean + x[i]) / (i + 1);
    }
    return mean;
}

float calc_variance(float* x, float mean, size_t n)
{
    float variance = 0;
    for (size_t i = 0; i < n; i++) {
        float x_minus_mean = x[i] - mean;
        variance = (i * variance + x_minus_mean * x_minus_mean) / (i + 1);
    }
    return variance;
}

int main()
{
    stdio_init_all();

    for (;;) {
        benchmark();
        sleep_ms(10000);
    }

    return 0;
}