#include "mbed.h"
#include "states/control.h"

const float fs = 10.0f;

int main()
{
    printf("Starting...\n\r");

    Control machine;

    using namespace std::chrono;

    while (true) {

        machine.run();

        auto next = Kernel::Clock::now() + machine.getLooptime();

        while (Kernel::Clock::now() < next) {}
    }
}
