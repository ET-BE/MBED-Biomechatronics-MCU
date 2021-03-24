#include "mbed.h"
#include "control.h"

// Constructor
Control::Control() :
    StateMachine(0),
    button1(SW2) {
    
}

// State selection
void Control::run_state() {
    switch (getState()) {
        case IMU:
            state_imu();
            return;
        case IMU_IDLE:
            state_imu_idle();
            return;
        case EMG:
            state_emg();
            return;
        case EMG_IDLE:
            state_emg_idle();
            return;
    }
}

// ------------- IMU -------------

void Control::state_imu() {

    if (isInit()) {
        printf("State IMU\n\r");
    }

    const bool button = !button1.read();

    if (button) {
        setState(IMU_IDLE);
    }
}

void Control::state_imu_idle() {

    if (isInit()) {
        printf("State IMU-IDLE\n\r");
    }

    if (getStateTime() > 5000) {
        setState(EMG);
    }
}

// ------------- EMG -------------

void Control::state_emg() {

    if (isInit()) {
        printf("State EMG\n\r");
    }
}

void Control::state_emg_idle() {

}
