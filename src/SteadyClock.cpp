#include "threeAS-SteadyClock.hpp"

namespace three_as {
auto SteadyClock::elapsed() -> std::chrono::milliseconds {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - startTime);
}

void SteadyClock::start() { startTime = std::chrono::steady_clock::now(); }
}
