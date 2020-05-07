#include "threeAS-task.hpp"

namespace three_as {
void runTask(Framework &framework) { framework.eventLoop(); }

void frameUpdate(Framework &framework) { framework.display(instructions); }
}
