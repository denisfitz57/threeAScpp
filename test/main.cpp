#include "threeAS-task.hpp"
#include <testcpplite/testcpplite.hpp>

namespace three_as {
namespace {
class FrameworkStub : public Framework {
  public:
    auto eventLoopEntered() const -> bool { return eventLoopEntered_; }

    void eventLoop() override { eventLoopEntered_ = true; }

  private:
    bool eventLoopEntered_{};
};

void taskEntersEventLoop(testcpplite::TestResult &result) {
    FrameworkStub framework;
    runTask(framework);
    assertTrue(result, framework.eventLoopEntered());
}
}
}

#include <testcpplite/testcpplite.hpp>
#include <iostream>

namespace three_as {
int main() {
    return testcpplite::test(
        {{taskEntersEventLoop, "taskEntersEventLoop"}}, std::cout);
}
}

int main() { return three_as::main(); }