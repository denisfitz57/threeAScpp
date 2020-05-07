#include "Timer.hpp"
#include "Task.hpp"
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
