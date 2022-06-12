#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 5105)

#pragma comment(lib,"winmm.lib")
#include <windows.h>

#include <iostream>

// ms
static inline double GetTicks()
{
    LARGE_INTEGER ticks, frequency;
    if (!QueryPerformanceCounter(&ticks))
    {
        return timeGetTime();  // timeGetTime() has lower time resolution (1ms if timeBeginPeriod(1))
    }
    return double(ticks.QuadPart) * 1000. / double(frequency.QuadPart);  // ms
}

// https://docs.microsoft.com/en-us/windows/win32/multimedia/multimedia-timers
int main()
{
    timeBeginPeriod(1);  // request 1ms timer resolution

    while (true)
    {
        auto start_ticks = timeGetTime();

        // frame function
        std::cout << start_ticks << '\n';

        auto end_ticks = timeGetTime();
        auto cost_ticks = end_ticks - start_ticks;
        auto wait_ticks = 5 - cost_ticks;  // 5ms interval

        if (wait_ticks <= 0) continue;  // timeout

        if (wait_ticks > 1) Sleep(wait_ticks - 1);  // sleep if > 1ms, Sleep in ms

        auto next_ticks = start_ticks + 5;

        while (timeGetTime() < next_ticks) { }  // do nothing, wait
    }
    
    timeEndPeriod(1);

    return 0;
}
