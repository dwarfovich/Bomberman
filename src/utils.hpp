#ifndef UTILS_HPP
#define UTILS_HPP

#include <QDataStream>

namespace bm {

template<typename Type1, typename Type2>
QDataStream& operator<<(QDataStream& stream, std::pair<Type1, Type2>& pair)
{
    stream << pair.first;
    stream << pair.second;

    return stream;
}

} // namespace bm

#endif // UTILS_HPP
