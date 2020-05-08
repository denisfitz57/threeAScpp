#ifndef THREEAS_TIMER_HPP_
#define THREEAS_TIMER_HPP_

#include <chrono>
#include <functional>

namespace three_as {
struct Interval {};

class MonotonicTimer {
  public:
    virtual ~MonotonicTimer() = default;
    virtual auto elapsed() -> std::chrono::milliseconds = 0;
    virtual void start() = 0;
};

class Timer {
  public:
    Timer(MonotonicTimer &);
    void frameUpdate();
    void invokeAfter(std::chrono::milliseconds, std::function<void()>);

  private:
    std::function<void()> callback{};
    std::chrono::milliseconds timeToWait{};
    MonotonicTimer &monotonic;
    bool running{};
};
}

#endif
