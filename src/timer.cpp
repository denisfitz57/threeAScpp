#include "threeAS-Timer.hpp"
#include <utility>

namespace three_as {
Timer::Timer(MonotonicTimer &monotonic) : monotonic{monotonic} {}

void Timer::check() {
    if (running && monotonic.elapsed() >= timeToWait) {
        running = false;
        callback();
    }
}

void Timer::invokeAfter(std::chrono::milliseconds t, std::function<void()> f) {
    monotonic.start();
    timeToWait = t;
    callback = std::move(f);
    running = true;
}
}
