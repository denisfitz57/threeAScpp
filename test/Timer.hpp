#ifndef THREEAS_TEST_TIMER_HPP_
#define THREEAS_TEST_TIMER_HPP_

#include <testcpplite/testcpplite.hpp>

namespace three_as {
void timerConstructorSubscribesToFrameUpdate(testcpplite::TestResult &);
void timerInvokeAfterCallsbackWhenTime(testcpplite::TestResult &);
void timerInvokeAfterDoesNotCallsbackWhenNotTime(testcpplite::TestResult &);
}

#endif
