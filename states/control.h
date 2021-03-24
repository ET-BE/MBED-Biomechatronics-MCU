#ifndef CONTROL_H
#define CONTROL_H

#include "state_machine.h"
#include "mbed-scope/scope.h"
#include "mpu6050/MPU6050.h"

/**
 * Main state machine class of this program
 */
class Control : public StateMachine {

public:
    enum State {
        INIT = 0,
        IMU,
        EMG,
        IDLE,
    };

    /**
     * Constructor
     */
    Control();

    /**
     * Choose the right state function based on current state
     */
    void run_state() override;

    /**
     * Return the chrono duration of a loop
     *
     * Based on internal framerate
     */
    const std::chrono::duration<float>& getLooptime() const;

private:

    void state_init();
    void state_imu();
    void state_emg();
    void state_idle();

    /**
     * Set looptime based on frequency
     */
    void setLooptime(float fs);

    /**
     * Return alternating true and false, based on state time
     *
     * @param dt Period of blink frequency
     */
    bool blink(int dt) const;

    std::chrono::duration<float> looptime;

    DigitalIn sw2, sw3; /// Buttons
    DigitalOut led_green, led_red, led_blue; /// LEDs

    Scope* scope; /// Pointer to scope
    MPU6050* mpu; /// Pointer to MPU

};

#endif // CONTROL_H