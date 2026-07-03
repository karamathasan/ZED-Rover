#ifndef LED_H
#define LED_H

#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#define WRAP 999
#define SYS_CLK 125000000
#define CLK_DIV 125.0f

typedef struct LED {
    uint pin;
    uint on;
} LED;

void initLED(LED * led, uint pin){
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
    led->pin = pin;
    led->on = 0;
}

void LEDOn(LED * led){
    gpio_put(led->pin, 1);
    led->on = 1;
}

void LEDOff(LED * led){
    gpio_put(led->pin, 0);
    led->on = 0;
}

void toggleLED(LED * led){
    led->on = 1 - led->on;
    gpio_put(led->pin, led->on);
}

#endif