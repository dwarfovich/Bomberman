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

    QString mapForCampaignLevel(int level) const
    {
        if (level >= 0 && static_cast<size_t>(level) < campaign_ns::levels.size()) {
            return campaign_ns::levels[level];
        } else {
            return {};
        }
    }
};

} // namespace bm

#endif // BM_CAMPAIGN_HPP
