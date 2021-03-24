#include "mbed.h"
#include "states/control.h"

const float fs = 10.0f;

int main()
{
    printf("Starting...\n\r");

    Control machine;

    //using namespace std::chrono;
    //using Framerate = duration<steady_clock::rep, std::ratio<1, 10>>;
    //auto next = Kernel::Clock::now() + Framerate{1};


    while (true) {

        machine.run();

        //while (Kernel::Clock::now() < next) {}
        //next += Framerate{1};

        ThisThread::sleep_for(100ms);
    }
}
