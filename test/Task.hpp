#ifndef THREEAS_TEST_TASK_HPP_
#define THREEAS_TEST_TASK_HPP_

#include <testcpplite/testcpplite.hpp>

namespace three_as {
void taskEntersEventLoop(testcpplite::TestResult &result);
void frameUpdateShowsInstructions(testcpplite::TestResult &result);
void frameUpdateAfterSpacebarDoesNotShowInstructions(
    testcpplite::TestResult &result);
}

#endif
