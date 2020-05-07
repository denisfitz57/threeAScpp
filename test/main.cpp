#include "threeAS-task.hpp"
#include <testcpplite/testcpplite.hpp>

namespace three_as {
namespace {
class FrameworkStub : public Framework {
  public:
    auto eventLoopEntered() const -> bool { return eventLoopEntered_; }

    void eventLoop() override { eventLoopEntered_ = true; }

    auto displayedText() -> std::string { return displayedText_; }

    void display(const std::string &s) override { displayedText_ = s; }

  private:
    std::string displayedText_;
    bool eventLoopEntered_{};
};

void taskEntersEventLoop(testcpplite::TestResult &result) {
    FrameworkStub framework;
    runTask(framework);
    assertTrue(result, framework.eventLoopEntered());
}

void frameUpdateShowsInstructions(testcpplite::TestResult &result) {
    FrameworkStub framework;
    frameUpdate(framework);
    assertEqual(result, instructions, framework.displayedText());
}
}
}

#include <testcpplite/testcpplite.hpp>
#include <iostream>

namespace three_as {
int main() {
    return testcpplite::test(
        {{taskEntersEventLoop, "taskEntersEventLoop"},
            {frameUpdateShowsInstructions, "frameUpdateShowsInstructions"}},
        std::cout);
}
}

int main() { return three_as::main(); }
