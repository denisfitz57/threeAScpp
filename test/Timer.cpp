#include "Timer.hpp"
#include "threeAS-timer.hpp"
#include <functional>
#include <chrono>

using std::literals::chrono_literals::operator""ms;

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

    auto elapsed() -> std::chrono::milliseconds override { return elapsed_; }

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

auto timerCallsAfterWhenElapsed(Timer &timer, ScreenStub &screen,
    MonotonicTimerStub &monotonic, std::chrono::milliseconds after,
    std::chrono::milliseconds elapsed) -> bool {
    bool called{};
    timer.invokeAfter(after, [&]() { called = true; });
    monotonic.setElapsed(elapsed);
    screen.frameUpdate();
    return called;
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
            assertTrue(result,
                timerCallsAfterWhenElapsed(timer, screen, monotonic, 1ms, 1ms));
        });
}

void timerInvokeAfterDoesNotCallsbackWhenNotTime(
    testcpplite::TestResult &result) {
    testTimer(
        [&](Timer &timer, ScreenStub &screen, MonotonicTimerStub &monotonic) {
            assertFalse(result,
                timerCallsAfterWhenElapsed(timer, screen, monotonic, 2ms, 1ms));
        });
}

void timerInvokeAfterCallsbackWhenPastTime(testcpplite::TestResult &result) {
    testTimer(
        [&](Timer &timer, ScreenStub &screen, MonotonicTimerStub &monotonic) {
            assertTrue(result,
                timerCallsAfterWhenElapsed(timer, screen, monotonic, 1ms, 2ms));
        });
}

void timerInvokeAfterDoesNotCallsbackTwice(testcpplite::TestResult &result) {
    testTimer(
        [&](Timer &timer, ScreenStub &screen, MonotonicTimerStub &monotonic) {
            int count{};
            timer.invokeAfter(1ms, [&]() { ++count; });
            monotonic.setElapsed(1ms);
            screen.frameUpdate();
            screen.frameUpdate();
            assertEqual(result, 1, count);
        });
}
}
