#include "threeAS-task.hpp"
#include <testcpplite/testcpplite.hpp>

namespace three_as {
namespace {
class FrameworkStub : public Framework {
  public:
    auto eventLoopEntered() const -> bool { return eventLoopEntered_; }

    void eventLoop() override { eventLoopEntered_ = true; }

    auto displayedText() -> std::string { return displayedText_; }

    void display(const std::string &s) override {
        textDisplayed_ = true;
        displayedText_ = s;
    }

    auto textDisplayed() const -> bool { return textDisplayed_; }

  private:
    std::string displayedText_;
    bool textDisplayed_{};
    bool eventLoopEntered_{};
};

void runTask(Task &task, Framework &framework) { task.runTask(framework); }

void frameUpdate(Task &task, Framework &framework) {
    task.frameUpdate(framework);
}

void keyPressed(Task &task, Framework &framework, int key) {
    task.keyPressed(framework, key);
}

void taskEntersEventLoop(testcpplite::TestResult &result) {
    Task task;
    FrameworkStub framework;
    runTask(task, framework);
    assertTrue(result, framework.eventLoopEntered());
}

void frameUpdateShowsInstructions(testcpplite::TestResult &result) {
    Task task;
    FrameworkStub framework;
    frameUpdate(task, framework);
    assertEqual(result, instructions, framework.displayedText());
}

void frameUpdateAfterSpacebarDoesNotShowInstructions(
    testcpplite::TestResult &result) {
    Task task;
    FrameworkStub framework;
    keyPressed(task, framework, ' ');
    frameUpdate(task, framework);
    assertFalse(result, framework.textDisplayed());
}
}
}

#include <testcpplite/testcpplite.hpp>
#include <iostream>

namespace three_as {
int main() {
    return testcpplite::test(
        {{taskEntersEventLoop, "taskEntersEventLoop"},
            {frameUpdateShowsInstructions, "frameUpdateShowsInstructions"},
            {frameUpdateAfterSpacebarDoesNotShowInstructions,
                "frameUpdateAfterSpacebarDoesNotShowInstructions"}},
        std::cout);
}
}

int main() { return three_as::main(); }
