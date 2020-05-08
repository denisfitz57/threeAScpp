#include "Timer.hpp"
#include "threeAS-Timer.hpp"
#include <functional>
#include <chrono>
#include <utility>

using std::literals::chrono_literals::operator""ms;

namespace three_as {
namespace {
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

void testTimer(const std::function<void(Timer &, MonotonicTimerStub &)> &f) {
    MonotonicTimerStub monotonic;
    Timer timer{monotonic};
    f(timer, monotonic);
}

void check(Timer &s) { s.check(); }

void invokeAfter(
    Timer &timer, std::chrono::milliseconds s, std::function<void()> f) {
    timer.invokeAfter(s, std::move(f));
}

void setElapsed(MonotonicTimerStub &monotonic, std::chrono::milliseconds s) {
    monotonic.setElapsed(s);
}

auto timerCallsAfterWhenElapsed(Timer &timer, MonotonicTimerStub &monotonic,
    std::chrono::milliseconds after, std::chrono::milliseconds elapsed)
    -> bool {
    bool called{};
    invokeAfter(timer, after, [&]() { called = true; });
    setElapsed(monotonic, elapsed);
    check(timer);
    return called;
}
}

void timerInvokeAfterCallsbackWhenTime(testcpplite::TestResult &result) {
    testTimer([&](Timer &timer, MonotonicTimerStub &monotonic) {
        assertTrue(
            result, timerCallsAfterWhenElapsed(timer, monotonic, 1ms, 1ms));
    });
}

void timerInvokeAfterDoesNotCallsbackWhenNotTime(
    testcpplite::TestResult &result) {
    testTimer([&](Timer &timer, MonotonicTimerStub &monotonic) {
        assertFalse(
            result, timerCallsAfterWhenElapsed(timer, monotonic, 2ms, 1ms));
    });
}

void timerInvokeAfterCallsbackWhenPastTime(testcpplite::TestResult &result) {
    testTimer([&](Timer &timer, MonotonicTimerStub &monotonic) {
        assertTrue(
            result, timerCallsAfterWhenElapsed(timer, monotonic, 1ms, 2ms));
    });
}

void timerInvokeAfterDoesNotCallsbackTwice(testcpplite::TestResult &result) {
    testTimer([&](Timer &timer, MonotonicTimerStub &monotonic) {
        int count{};
        invokeAfter(timer, 1ms, [&]() { ++count; });
        setElapsed(monotonic, 1ms);
        check(timer);
        check(timer);
        assertEqual(result, 1, count);
    });
}

void timerInvokeAfterStartsMonotonic(testcpplite::TestResult &result) {
    testTimer([&](Timer &timer, MonotonicTimerStub &monotonic) {
        invokeAfter(timer, {}, {});
        assertTrue(result, monotonic.started());
    });
}

void timerInvokeAfterInCallback(testcpplite::TestResult &result) {
    testTimer([&](Timer &timer, MonotonicTimerStub &monotonic) {
        bool called{};
        invokeAfter(timer, 1ms,
            [&]() { invokeAfter(timer, 1ms, [&]() { called = true; }); });
        setElapsed(monotonic, 1ms);
        check(timer);
        assertFalse(result, called);
        check(timer);
        assertTrue(result, called);
    });
}
}
