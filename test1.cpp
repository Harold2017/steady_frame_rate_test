#include <chrono>
#include <thread>
#include <iostream>

static inline std::chrono::steady_clock::duration GetTime()
{
    return std::chrono::steady_clock::now().time_since_epoch();
}

static inline long long ToMS(std::chrono::steady_clock::duration const& dur)
{
     return std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
}

// not stable as Windows multimedia timer
int main()
{
    using namespace std::literals::chrono_literals;

    while (true)
    {
        auto start_ticks = GetTime();

        // frame function
        std::cout << ToMS(start_ticks) << '\n';

        auto end_ticks = GetTime();
        auto cost_ticks = end_ticks - start_ticks;
        auto wait_ticks = 5ms - cost_ticks;  // 5ms interval

        if (wait_ticks <= 0ms) continue;  // timeout

        if (wait_ticks > 1ms) std::this_thread::sleep_for(wait_ticks - 1ms);  // sleep if > 1ms, Sleep in ms

        auto next_ticks = start_ticks + 5ms;

        while (GetTime() < next_ticks) { }  // do nothing, wait
    }

    return 0;
}