#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#include "tusb.h"

#include <math.h>
#include "motor.h"
#include "led.h"
#include "pins.h"

// uint8_t motor_input_buffer[8] = {0};
float motor_input_buffer[2] = {0};

    //LED init
    LED lf;
    LED lb;
    LED rf;
    LED rb;

    //Motor Init
    Motor m_lf;
    Motor m_lb;
    Motor m_rf;
    Motor m_rb;

int main() {
    stdio_init_all();
    tusb_init();

    //pin initialization
    if (cyw43_arch_init()) {
        return -1; // failed to init WiFi chip
    }

    initLED(&lf, LED_LF);
    initLED(&lb, LED_LB);
    initLED(&rf, LED_RF);
    initLED(&rb, LED_RB);

    initMotor(&m_lf, LFen, LFin1, LFin2);
    initMotor(&m_lb, LBen, LBin1, LBin2);
    initMotor(&m_rf, RFen, RFin1, RFin2);
    initMotor(&m_rb, RBen, RBin1, RBin2);



    while (true) {
        tud_task();

        //apply changes to motor inputs
        float left = motor_input_buffer[0];
        float right = motor_input_buffer[1];
        setMotor(&m_lf, left);
        setMotor(&m_lb, left);
        setMotor(&m_rf, right);
        setMotor(&m_rb, right);
    }
}

// get usb msgs
void tud_cdc_rx_cb(uint8_t itf)
{
    uint32_t total = tud_cdc_available();
    // total should be 2f = 8bytes
    tud_cdc_read(motor_input_buffer, total);
}

