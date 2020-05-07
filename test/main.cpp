#include "Timer.hpp"
#include "Task.hpp"
#include <testcpplite/testcpplite.hpp>
#include <iostream>

namespace three_as {
int main() {
    return testcpplite::test(
        {{runningTaskEntersEventLoop, "runningTaskEntersEventLoop"},
            {taskFrameUpdateShowsInstructions,
                "taskFrameUpdateShowsInstructions"},
            {taskFrameUpdateAfterSpacebarDoesNotShowInstructions,
                "taskFrameUpdateAfterSpacebarDoesNotShowInstructions"},
            {timerConstructorSubscribesToFrameUpdate,
                "timerConstructorSubscribesToFrameUpdate"},
            {timerInvokeAfterCallsbackWhenTime,
                "timerInvokeAfterCallsbackWhenTime"},
            {timerInvokeAfterDoesNotCallsbackWhenNotTime,
                "timerInvokeAfterDoesNotCallsbackWhenNotTime"},
            {timerInvokeAfterCallsbackWhenPastTime,
                "timerInvokeAfterCallsbackWhenPastTime"},
            {timerInvokeAfterDoesNotCallsbackTwice,
                "timerInvokeAfterDoesNotCallsbackTwice"}},
        std::cout);
}
}

int main() { return three_as::main(); }
