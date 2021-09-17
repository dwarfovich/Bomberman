#ifndef TIMER_EVENT_H
#define TIMER_EVENT_H

namespace bm {

class TimerEvent
{
public:
    virtual ~TimerEvent() = default;

    virtual void doWork() const = 0;
};

} // namespace bm

#endif // TIMER_EVENT_H
