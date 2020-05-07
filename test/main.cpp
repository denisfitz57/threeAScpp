#include "threeAS-task.hpp"
#include <testcpplite/testcpplite.hpp>
#include <functional>

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

void run(Task &task) { task.run(); }

void frameUpdate(Task &task) { task.frameUpdate(); }

void keyPressed(Task &task, int key) { task.keyPressed(key); }

void testTask(const std::function<void(Task &, FrameworkStub &)> &f) {
    FrameworkStub framework;
    Task task{framework};
    f(task, framework);
}

void taskEntersEventLoop(testcpplite::TestResult &result) {
    testTask([&](Task &task, FrameworkStub &framework) {
        run(task);
        assertTrue(result, framework.eventLoopEntered());
    });
}

void frameUpdateShowsInstructions(testcpplite::TestResult &result) {
    testTask([&](Task &task, FrameworkStub &framework) {
        frameUpdate(task);
        assertEqual(result, instructions, framework.displayedText());
    });
}

void frameUpdateAfterSpacebarDoesNotShowInstructions(
    testcpplite::TestResult &result) {
    testTask([&](Task &task, FrameworkStub &framework) {
        keyPressed(task, ' ');
        frameUpdate(task);
        assertFalse(result, framework.textDisplayed());
    });
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
