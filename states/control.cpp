#include "mbed.h"
#include "control.h"
#include <cstdint>

// Constructor
Control::Control() :
    StateMachine(0),
    sw2(SW2), sw3(SW3),
    a0(A0), a1(A1),
    led_green(LED_GREEN), led_red(LED_RED), led_blue(LED_BLUE) {
    
    setLooptime(250.0f); // Default rate
}

// Destructor
Control::~Control() {
    if (scope) {
        delete scope;
    }
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

    static I2C i2c(I2C_SDA, I2C_SCL);
    static MPU6050 imu(&i2c);

    if (isInit()) {

        setLooptime(250.0f);

        led_red = led_blue = 1;
        led_green = 0;

        i2c.frequency(400000); // 400 kHz

        scope = new Scope(6); // Create scope instance
        // Constructor will hang untill USB connection is made

        const uint8_t whoami = imu.readByte(WHO_AM_I_MPU6050);
        if (whoami != 0x68) {
            setState(IDLE);
            return; // Abort current state
        }

        imu.setAScale(AFS_16G);
        imu.setGScale(GFS_2000DPS);

        imu.reset();  // Reset registers to default
        imu.init();
        imu.calibrate_basic(250); // Do internal calibration

        led_red = led_blue = 0;
        led_green = 1;

        ThisThread::sleep_for(100ms); // Make sure program is caught up
    }

    // Create destination variables (static in case imu fails for one loop)
    static float a[3] = {0.0f}, g[3] = {0.0f}, temp = 0.0f;

    // Check if data is ready
    const uint8_t is_ready = imu.readByte(INT_STATUS) & 0x01;
    if (is_ready) {

        imu.readData(a, g, &temp);

        scope->set(0, a, 3);
        scope->set(3, g, 3);

    }

    scope->send();
}

// ------------- EMG -------------

void Control::state_emg() {

    if (isInit()) {

        setLooptime(750.0f);

        led_red = led_blue = 1;
        led_green = 0;

        scope = new Scope(2); // Create scope instance
        // Constructor will hang untill USB connection is made

        led_red = led_green = 0;
        led_blue = 1;
    }

    scope->set(0, a0.read());
    scope->set(1, a1.read());
    //scope->set(0, 1 - sw2.read());
    //scope->set(1, 1 - sw3.read());
    scope->send();
}

// ------------- IDLE -------------

void Control::state_idle() {

    // Blink red LED
    led_blue = led_green = 1;
    led_red.write(blink(1000));

}
