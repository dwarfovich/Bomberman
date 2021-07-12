#ifndef TIMERQUEUE_HPP
#define TIMERQUEUE_HPP

#include <QObject>
#include <QTimer>

#include <map>
#include <chrono>

using TimerType = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<TimerType>;

class TimerEvent
{
public:
    virtual ~TimerEvent()       = default;
    virtual void doWork() const = 0;
};

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

#endif // TIMERQUEUE_HPP
