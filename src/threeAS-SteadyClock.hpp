#ifndef THREEAS_STEADYCLOCK_HPP_
#define THREEAS_STEADYCLOCK_HPP_

#include "threeAS-timer.hpp"
#include <chrono>

namespace three_as {
class SteadyClock : public MonotonicTimer {
  public:
    auto elapsed() -> std::chrono::milliseconds override;
    void start() override;

  private:
    std::chrono::time_point<std::chrono::steady_clock> startTime{};
};
}

#endif
