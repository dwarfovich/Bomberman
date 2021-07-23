#ifndef BM_MOVE_PROCESSOR_HPP
#define BM_MOVE_PROCESSOR_HPP

#include "map.hpp"

#include <QObject>

namespace bm {

class MoveProcessor : public QObject
{
    Q_OBJECT

public:
    MoveProcessor(const Map& map = {});

    void addObject(const std::shared_ptr<MovingObject>& object);
    void deleteObject(const std::shared_ptr<MovingObject>& object);
    void performMovement(double timeDelta);

signals:
    void objectIndexChanged(const std::shared_ptr<MovingObject>& object, size_t newIndex);
    void characterMoved(const std::shared_ptr<MovingObject>& object);

private:
    const Map&                                 map_;
    std::vector<std::shared_ptr<MovingObject>> objects_;
};

} // namespace bm

#endif // BM_MOVE_PROCESSOR_HPP
