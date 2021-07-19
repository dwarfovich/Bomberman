#include "timer_queue.hpp"

namespace bm {

TimerQueue::TimerQueue()
{
    connect(&timer_, &QTimer::timeout, this, &TimerQueue::onTimeout);
}

void TimerQueue::addEvent(const TimePoint& time, std::unique_ptr<TimerEvent> event)
{
    auto inserted = events_.insert({ time, std::move(event) });
    if (inserted == events_.cbegin() || !timer_.isActive()) {
        restart();
    }
}

void TimerQueue::restart()
{
    if (events_.empty()) {
        return;
    }

    timer_.stop();
    const auto& nextEvent = events_.cbegin()->first;
    const auto& delay     = nextEvent - TimerType::now();
    if (delay.count() <= 0) {
        onTimeout();
    } else {
        using std::chrono::duration_cast;
        using std::chrono::milliseconds;
        timer_.start(duration_cast<milliseconds>(delay));
    }
}

void TimerQueue::onTimeout()
{
    const auto& iter = events_.cbegin();
    if (iter != events_.cend()) {
        iter->second->doWork();
        events_.erase(iter);
        if (events_.empty()) {
            timer_.stop();
        } else {
            restart();
        }
    }
}

} // namespace bm
