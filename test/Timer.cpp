#include "Timer.hpp"
#include "threeAS-timer.hpp"
#include <functional>

namespace three_as {
namespace {
class ScreenStub : public Screen {
  public:
    auto listener() -> Listener * { return listener_; }

    void subscribe(Listener *s) override { listener_ = s; }

    void frameUpdate() { listener_->frameUpdate(); }

  private:
    Listener *listener_{};
};

class MonotonicTimerStub : public MonotonicTimer {
  public:
    void setElapsed(std::chrono::milliseconds t) { elapsed_ = t; }

    auto elapsed() -> std::chrono::milliseconds { return elapsed_; }

  private:
    std::chrono::milliseconds elapsed_{};
};

void testTimer(
    const std::function<void(Timer &, ScreenStub &, MonotonicTimerStub &)> &f) {
    ScreenStub screen;
    MonotonicTimerStub monotonic;
    Timer timer{screen, monotonic};
    f(timer, screen, monotonic);
}
}

void timerConstructorSubscribesToFrameUpdate(testcpplite::TestResult &result) {
    testTimer([&](Timer &timer, ScreenStub &screen, MonotonicTimerStub &) {
        assertTrue(result, &timer == screen.listener());
    });
}

void timerInvokeAfterCallsbackWhenTime(testcpplite::TestResult &result) {
    testTimer(
        [&](Timer &timer, ScreenStub &screen, MonotonicTimerStub &monotonic) {
            bool called{};
            timer.invokeAfter(
                std::chrono::milliseconds{1}, [&]() { called = true; });
            monotonic.setElapsed(std::chrono::milliseconds{1});
            screen.frameUpdate();
            assertTrue(result, called);
        });
}
}
