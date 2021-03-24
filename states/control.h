#ifndef CONTROL_H
#define CONTROL_H

#include "state_machine.h"

/**
 * Main state machine class of this program
 */
class Control : public StateMachine {

public:
    enum State {
        IMU = 0,
        IMU_IDLE,
        EMG,
        EMG_IDLE
    };

    /**
     * Constructor
     */
    Control();

    /**
     * Choose the right state function based on current state
     */
    void run_state() override;

private:

    void state_imu();
    void state_imu_idle();
    void state_emg();
    void state_emg_idle();

    DigitalIn button1; /// State toggle button

};

#endif // CONTROL_H