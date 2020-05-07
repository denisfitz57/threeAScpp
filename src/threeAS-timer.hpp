#ifndef THREEAS_TIMER_HPP_
#define THREEAS_TIMER_HPP_

#include <chrono>
#include <functional>
#include <utility>

namespace three_as {
class Screen {
  public:
    class Listener {
      public:
        virtual ~Listener() = default;
        virtual void frameUpdate() = 0;
    };
    virtual ~Screen() = default;
    virtual void subscribe(Listener *) = 0;
};

struct Interval {};

class MonotonicTimer {
  public:
    virtual ~MonotonicTimer() = default;
};

class Timer : public Screen::Listener {
  public:
    Timer(Screen &screen, MonotonicTimer &) { screen.subscribe(this); }

    void frameUpdate() override { callback(); }

    void invokeAfter(std::chrono::milliseconds, std::function<void()> f) {
        callback = std::move(f);
    }

  private:
    std::function<void()> callback{};
};
}

#endif
