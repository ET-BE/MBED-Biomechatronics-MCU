#include "mbed.h"
#include "states/control.h"

using namespace std::chrono;

Timer t;

int main()
{
    t.start();

    Control machine;

    while (true) {

        auto next = t.elapsed_time() + machine.getLooptime();

        machine.run();

        // Busy wait untill the looptime (including execution) has passed
        while (t.elapsed_time() < next) {}
    }
}
