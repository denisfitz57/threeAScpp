#include "threeAS-timer.hpp"
#include <utility>

namespace three_as {
Timer::Timer(Screen &screen, MonotonicTimer &monotonic) : monotonic{monotonic} {
    screen.subscribe(this);
}

void Timer::frameUpdate() {
    if (monotonic.elapsed() >= timeToWait)
        callback();
}

void Timer::invokeAfter(std::chrono::milliseconds t, std::function<void()> f) {
    timeToWait = t;
    callback = std::move(f);
}
}
