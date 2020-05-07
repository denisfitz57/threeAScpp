#ifndef THREEAS_TEST_TASK_HPP_
#define THREEAS_TEST_TASK_HPP_

#include <testcpplite/testcpplite.hpp>

namespace three_as {
void runningTaskEntersEventLoop(testcpplite::TestResult &result);
void taskFrameUpdateShowsInstructions(testcpplite::TestResult &result);
void taskFrameUpdateAfterSpacebarDoesNotShowInstructions(
    testcpplite::TestResult &result);
}

#endif
