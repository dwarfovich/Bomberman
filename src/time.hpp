#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

namespace bm {

using TimerType = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<TimerType>;
using Milliseconds = std::chrono::milliseconds;
//using Duration = std::chrono::duration<Milliseconds>;

inline TimePoint createDelay(const Milliseconds& delay){
    return TimerType::now() + delay;
}

}

#endif // TIME_HPP
