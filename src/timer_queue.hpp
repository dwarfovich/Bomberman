#ifndef TIMERQUEUE_HPP
#define TIMERQUEUE_HPP

#include "time.hpp"
#include "timer_event.hpp"

#include <QObject>
#include <QTimer>

#include <map>
#include <chrono>

namespace bm {

class TimerQueue : public QObject
{
    Q_OBJECT
public:
    TimerQueue();
    ~TimerQueue()                 = default;
    TimerQueue(const TimerQueue&) = delete;
    TimerQueue(TimerQueue&&)      = delete;
    TimerQueue& operator=(const TimerQueue&) = delete;
    TimerQueue& operator=(TimerQueue&&) = delete;

    void addEvent(const TimePoint& time, std::unique_ptr<TimerEvent> event);

private slots:
    void onTimeout();

private:
    void restart();

private:
    using EventsMap = std::multimap<TimePoint, std::unique_ptr<TimerEvent>>;
    QTimer    timer_;
    EventsMap events_;
};

}

#endif // TIMERQUEUE_HPP
