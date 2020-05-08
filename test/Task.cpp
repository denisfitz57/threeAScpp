#include "Task.hpp"
#include "threeAS-Task.hpp"
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

    auto listener() -> Listener * { return listener_; }

    void subscribe(Listener *s) override { listener_ = s; }

    void frameUpdate() { listener_->frameUpdate(); }

    void keyPressed(int c) { listener_->keyPressed(c); }

  private:
    std::string displayedText_;
    Listener *listener_{};
    bool textDisplayed_{};
    bool eventLoopEntered_{};
};

void run(Task &task) { task.run(); }

void frameUpdate(FrameworkStub &framework) { framework.frameUpdate(); }

void keyPressed(FrameworkStub &framework, int key) {
    framework.keyPressed(key);
}

void testTask(const std::function<void(Task &, FrameworkStub &)> &f) {
    FrameworkStub framework;
    Task task{framework};
    f(task, framework);
}
}

void taskConstructorSubscribesToEvents(testcpplite::TestResult &result) {
    testTask([&](Task &task, FrameworkStub &framework) {
        assertTrue(result, &task == framework.listener());
    });
}

void runningTaskEntersEventLoop(testcpplite::TestResult &result) {
    testTask([&](Task &task, FrameworkStub &framework) {
        run(task);
        assertTrue(result, framework.eventLoopEntered());
    });
}

void taskFrameUpdateShowsInstructions(testcpplite::TestResult &result) {
    testTask([&](Task &, FrameworkStub &framework) {
        frameUpdate(framework);
        assertEqual(result, instructions, framework.displayedText());
    });
}

void taskFrameUpdateAfterSpacebarDoesNotShowInstructions(
    testcpplite::TestResult &result) {
    testTask([&](Task &, FrameworkStub &framework) {
        keyPressed(framework, ' ');
        frameUpdate(framework);
        assertFalse(result, framework.textDisplayed());
    });
}
}
