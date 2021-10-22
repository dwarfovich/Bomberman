#ifndef BM_CAMPAIGN_HPP
#define BM_CAMPAIGN_HPP

#include <QString>

#include <vector>

namespace bm {

namespace campaign_ns {
inline const std::vector<QString> levels { "test_map.json", "test_map_2.json" };
}

class Campaign
{
public:
    Campaign();

private:
    size_t currentLevel_ = 0;
};

} // namespace bm

#endif // BM_CAMPAIGN_HPP
