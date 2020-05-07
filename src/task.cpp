#include "threeAS-Task.hpp"

namespace three_as {
Task::Task(Framework &framework) : framework{framework} {}

void Task::run() { framework.eventLoop(); }

void Task::frameUpdate() {
    if (!keyPressed_)
        framework.display(instructions);
}

void Task::keyPressed(int key) { keyPressed_ = true; }
}
