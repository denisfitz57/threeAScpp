#include "Timer.hpp"
#include "threeAS-timer.hpp"

namespace three_as {
namespace {
class ScreenStub : public Screen {
  public:
    auto listener() -> Listener * { return listener_; }

    void subscribe(Listener *s) { listener_ = s; }

  private:
    Listener *listener_{};
};
}
void timerConstructorSubscribesToFrameUpdate(testcpplite::TestResult &result) {
    ScreenStub screen;
    Timer timer{screen};
    assertTrue(result, &timer == screen.listener());
}
}
