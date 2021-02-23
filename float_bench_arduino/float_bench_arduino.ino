#include <stdlib.h>
#include <math.h>

#define N 4000

void benchmark()
{
    // When N=4000, float x[N] crashes on ESP32.
    // Instead of a standard array init, we use malloc.
    float* x = (float*)malloc(N * sizeof(float));
    unsigned long start_time, end_time;

    start_time = micros();
    generate_gaussian(x, N);
    end_time = micros();
    Serial.print("generate_gaussian: ");
    Serial.print(end_time - start_time);
    Serial.println(" [us]");

    start_time = micros();
    float mean = calc_mean(x, N);
    end_time = micros();
    Serial.print("calc_mean: ");
    Serial.print(end_time - start_time);
    Serial.println(" [us]");

    start_time = micros();
    float variance = calc_variance(x, mean, N);
    end_time = micros();
    Serial.print("calc_variance: ");
    Serial.print(end_time - start_time);
    Serial.println(" [us]");

    Serial.print("mean = ");
    Serial.print(mean);
    Serial.print(", variance = ");
    Serial.println(variance);

    free(x);  // Because x is allocated by malloc
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

void setup() {
    Serial.begin(115200);
    // Wait until serial port becomes ready.
    // (For boards using internal USB controller to create virtual serial port)
    //  See: https://www.arduino.cc/reference/en/language/functions/communication/serial/ifserial/
    while (!Serial) {
    }
}

void loop() {
    benchmark();
    delay(10000);
}
