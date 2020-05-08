#include "Timer.hpp"
#include "threeAS-Timer.hpp"
#include <functional>
#include <chrono>
#include <utility>

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

    auto started() const -> bool { return started_; }

    void start() override { started_ = true; }

  private:
    std::chrono::milliseconds elapsed_{};
    bool started_{};
};

void testTimer(
    const std::function<void(Timer &, ScreenStub &, MonotonicTimerStub &)> &f) {
    ScreenStub screen;
    MonotonicTimerStub monotonic;
    Timer timer{screen, monotonic};
    f(timer, screen, monotonic);
}

void frameUpdate(ScreenStub &s) { s.frameUpdate(); }

void invokeAfter(
    Timer &timer, std::chrono::milliseconds s, std::function<void()> f) {
    timer.invokeAfter(s, std::move(f));
}

void setElapsed(MonotonicTimerStub &monotonic, std::chrono::milliseconds s) {
    monotonic.setElapsed(s);
}

auto timerCallsAfterWhenElapsed(Timer &timer, ScreenStub &screen,
    MonotonicTimerStub &monotonic, std::chrono::milliseconds after,
    std::chrono::milliseconds elapsed) -> bool {
    bool called{};
    invokeAfter(timer, after, [&]() { called = true; });
    setElapsed(monotonic, elapsed);
    frameUpdate(screen);
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
            invokeAfter(timer, 1ms, [&]() { ++count; });
            setElapsed(monotonic, 1ms);
            frameUpdate(screen);
            frameUpdate(screen);
            assertEqual(result, 1, count);
        });
}

void timerInvokeAfterStartsMonotonic(testcpplite::TestResult &result) {
    testTimer([&](Timer &timer, ScreenStub &, MonotonicTimerStub &monotonic) {
        invokeAfter(timer, {}, {});
        assertTrue(result, monotonic.started());
    });
}

void timerInvokeAfterInCallback(testcpplite::TestResult &result) {
    testTimer(
        [&](Timer &timer, ScreenStub &screen, MonotonicTimerStub &monotonic) {
            bool called{};
            invokeAfter(timer, 1ms,
                [&]() { invokeAfter(timer, 1ms, [&]() { called = true; }); });
            setElapsed(monotonic, 1ms);
            frameUpdate(screen);
            assertFalse(result, called);
            frameUpdate(screen);
            assertTrue(result, called);
        });
}
}
