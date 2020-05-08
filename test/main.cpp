#include "Timer.hpp"
#include <testcpplite/testcpplite.hpp>
#include <iostream>

namespace three_as {
static int main() {
    return testcpplite::test(
        {
            {timerInvokeAfterCallsbackWhenTime,
                "timerInvokeAfterCallsbackWhenTime"},
            {timerInvokeAfterDoesNotCallsbackWhenNotTime,
                "timerInvokeAfterDoesNotCallsbackWhenNotTime"},
            {timerInvokeAfterCallsbackWhenPastTime,
                "timerInvokeAfterCallsbackWhenPastTime"},
            {timerInvokeAfterDoesNotCallsbackTwice,
                "timerInvokeAfterDoesNotCallsbackTwice"},
            {timerInvokeAfterStartsMonotonic,
                "timerInvokeAfterStartsMonotonic"},
            {timerInvokeAfterInCallback, "timerInvokeAfterInCallback"},
        },
        std::cout);
}
}

int main() { return three_as::main(); }
