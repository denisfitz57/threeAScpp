#include "threeAS-task.hpp"

namespace three_as {
void Task::runTask(Framework &framework) { framework.eventLoop(); }

void Task::frameUpdate(Framework &framework) {
    if (!keyPressed_)
        framework.display(instructions);
}

void Task::keyPressed(Framework &, int key) { keyPressed_ = true; }
}
