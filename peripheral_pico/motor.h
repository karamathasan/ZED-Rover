#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#define WRAP 999
#define SYS_CLK 125000000
#define CLK_DIV 125.0f

typedef struct Motor {
    uint en;
    uint in1;
    uint in2;
    uint slice;
    uint channel;
} Motor;

void initMotor(Motor * motor, uint en, uint in1, uint in2){
    uint slice = pwm_gpio_to_slice_num(en);
    uint channel = pwm_gpio_to_channel(en);
    gpio_set_function(en, GPIO_FUNC_PWM);

    pwm_set_clkdiv(slice, CLK_DIV);
    pwm_set_wrap(slice, WRAP);
    pwm_set_enabled(slice, true);

    gpio_init(in1);
    gpio_set_dir(in1, GPIO_OUT);
    gpio_init(in2);
    gpio_set_dir(in2, GPIO_OUT);

    motor->en = en;
    motor->in1 = in1;
    motor->in2 = in2;
    motor->slice = slice;
    motor->channel = channel;
}

float clamp(float value){
    return 1.0f * (value > 1.0f) + (value < -1.0f) + value * (value <= 1.0f && value >= -1.0f);
}

void setMotor(Motor * motor, float value){
    value = clamp(value);
    int dir = (value >= 0.0f) - (value < 0.0f);
    int level = dir * value * WRAP;

    if (dir >= 0){
        gpio_put(motor->in1, 1);
        gpio_put(motor->in2, 0);
    } else {
        gpio_put(motor->in1, 0);
        gpio_put(motor->in1, 1);
    }

    pwm_set_chan_level(motor->slice, motor->channel, level);
}

#endif