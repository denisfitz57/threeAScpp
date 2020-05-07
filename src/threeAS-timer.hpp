#ifndef THREEAS_TIMER_HPP_
#define THREEAS_TIMER_HPP_

#include <chrono>
#include <functional>

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
    Timer(Screen &, MonotonicTimer &);
    void frameUpdate() override;
    void invokeAfter(std::chrono::milliseconds, std::function<void()>);

  private:
    std::function<void()> callback{};
};
}

#endif
