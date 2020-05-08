#ifndef THREEAS_TEST_TIMER_HPP_
#define THREEAS_TEST_TIMER_HPP_

#include <testcpplite/testcpplite.hpp>

namespace three_as {
void timerConstructorSubscribesToFrameUpdate(testcpplite::TestResult &);
void timerInvokeAfterCallsbackWhenTime(testcpplite::TestResult &);
void timerInvokeAfterDoesNotCallsbackWhenNotTime(testcpplite::TestResult &);
void timerInvokeAfterCallsbackWhenPastTime(testcpplite::TestResult &);
void timerInvokeAfterDoesNotCallsbackTwice(testcpplite::TestResult &);
void timerInvokeAfterStartsMonotonic(testcpplite::TestResult &);
void timerInvokeAfterInCallback(testcpplite::TestResult &);
}

#endif
