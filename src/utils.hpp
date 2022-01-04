#ifndef UTILS_HPP
#define UTILS_HPP

#include <QDataStream>

#include <vector>

namespace bm {

template<typename Type>
QDataStream& operator<<(QDataStream& stream, const std::vector<Type>& vector)
{
    stream << vector.size();
    for (const auto& element : vector) {
        stream << element;
    }

    return stream;
}

template<typename Type>
QDataStream& operator>>(QDataStream& stream, std::vector<Type>& vector)
{
    size_t size = 0;
    stream >> size;
    vector.resize(size);
    for (auto& element : vector) {
        stream >> element;
    }

    return stream;
}

} // namespace bm

#endif // UTILS_HPP
