#ifndef TIME_HPP
#define TIME_HPP

#include <Qt>
#include <QDataStream>

#include <chrono>

// QT_BEGIN_NAMESPACE
// class QDataStream;
// QT_END_NAMESPACE

namespace bm {

using TimerType    = std::chrono::steady_clock;
using TimePoint    = std::chrono::time_point<TimerType>;
using Milliseconds = std::chrono::milliseconds;

inline QDataStream& operator<<(QDataStream& stream, const Milliseconds& ms)
{
    stream << ms.count();

    return stream;
}

inline TimePoint createDelay(const Milliseconds& delay)
{
    return TimerType::now() + delay;
}

} // namespace bm

#endif // TIME_HPP
