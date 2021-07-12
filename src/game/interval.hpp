#ifndef INTERVAL_HPP
#define INTERVAL_HPP

namespace bm {

template<typename BaseType, BaseType Min, BaseType Max>
class Interval
{
public:
    Interval& operator=(BaseType value)
    {
        setValue(value);
        return *this;
    }

         operator BaseType() { return value_; }
    bool setValue(BaseType value)
    {
        if (value >= Min && value <= Max) {
            value_ = value;
            return true;
        } else {
            return false;
        }
    }

    BaseType min() const { return Min; }
    BaseType max() const { return Max; }

private:
    BaseType value_;
};

template<int Min, int Max>
using IntervalInt = Interval<int, Min, Max>;

} // namespace bm

#endif // INTERVAL_HPP
