#include "mbed.h"
#include "control.h"

// Constructor
Control::Control() :
    StateMachine(0),
    sw2(SW2), sw3(SW3),
    led_green(LED_GREEN), led_red(LED_RED), led_blue(LED_BLUE) {
    
    setLooptime(250.0f); // Default rate
}

// State selection
void Control::run_state() {
    switch (getState()) {
        case INIT:
            state_init();
            return;
        case IMU:
            state_imu();
            return;
        case EMG:
            state_emg();
            return;
        case IDLE:
            state_idle();
            return;
    }
}

void Control::setLooptime(float fs) {
    looptime = std::chrono::duration<float>(1.0f / fs);
}

const std::chrono::duration<float>& Control::getLooptime() const {
    return looptime;
}

bool Control::blink(int dt) const {
    return getStateTime() % (2*dt) > dt;
}

// ------------- INIT -------------

void Control::state_init() {

    static int button1 = 0, button2 = 0;

    if (isInit()) {

        printf("State: INIT\n\r");

        button1 = button2 = 0;
        led_green = led_red = 1; // Off
    }

    // Blink blue LED
    led_blue.write(blink(250));

    // Debounce and delay (buttons are pulled up)
    if (!sw2.read()) {
        button1++;
    } else {
        button1 = 0;
    }

    if (!sw3.read()) {
        button2++;
    } else {
        button2 = 0;
    }

    const int lim = 100;

    if (button1 >= lim) {
        setState(IMU);
    }
    if (button2 >= lim) {
        setState(EMG);
    }
}

// ------------- IMU -------------

void Control::state_imu() {

    if (isInit()) {

        printf("State: IMU\n\r");

        setLooptime(250.0f);

        led_red = led_blue = 0;
        led_green = 1;
    }
}

// ------------- EMG -------------

void Control::state_emg() {

    if (isInit()) {

        printf("State: EMG\n\r");

        setLooptime(750.0f);

        led_red = led_green = 0;
        led_blue = 1;
    }
}

// ------------- IDLE -------------

void Control::state_idle() {

    // Blink red LED
    led_blue = led_green = 1;
    led_red.write(blink(500));

}
