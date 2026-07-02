#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#include <math.h>
#include "motor.h"
#include "pins.h"

int main() {
    stdio_init_all();

    //pin initialization
    if (cyw43_arch_init()) {
        return -1; // failed to init WiFi chip
    }

    // gpio_init(LED_LF);
    // gpio_set_dir(LED_LF, GPIO_OUT);

    gpio_set_function(LED_LF, GPIO_FUNC_PWM);
    int amplitude = 200;
    int base = 200;
    int wrap = 999;
    float f = 0.1;

    uint slice = pwm_gpio_to_slice_num(LED_LF);
    pwm_set_clkdiv(slice, 125.0f);
    pwm_set_wrap(slice, wrap);
    // pwm_set_gpio_level(slice, 250);
    // pwm_set_chan_level(slice, PWM_CHAN_A, 250);
    // Set initial B output high for three cycles before dropping
    // pwm_set_chan_level(slice, PWM_CHAN_B, 500);
    pwm_set_enabled(slice, true);
    
    int c = 0;

    while (true) {
        // printf("HELLO\r\n");
        int level = amplitude * sinf(c * f) + base;
        pwm_set_chan_level(slice, PWM_CHAN_A, level);
        c++;
        sleep_ms(50);

        // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        // // gpio_put(LED_LF, 1);
        // sleep_ms(1000);

        // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        // // gpio_put(LED_LF, 0);
        // sleep_ms(500);
    }
}