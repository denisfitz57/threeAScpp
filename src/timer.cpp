#include "threeAS-timer.hpp"
#include <utility>

namespace three_as {
Timer::Timer(Screen &screen, MonotonicTimer &) { screen.subscribe(this); }

void Timer::frameUpdate() { callback(); }

void Timer::invokeAfter(std::chrono::milliseconds, std::function<void()> f) {
    callback = std::move(f);
}
}
