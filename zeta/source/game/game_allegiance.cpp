#include <game/game_allegiance.h>
#include <tag_files/tag_groups.h>

/* ---------- definitions */

TAG_ENUM(
    campaign_team_enum,
    k_number_of_campaign_teams)
{
    { "default", _campaign_team_default },
    { "player", _campaign_team_player },
    { "human", _campaign_team_human },
    { "covenant", _campaign_team_covenant },
    { "brute", _campaign_team_brute },
    { "mule", _campaign_team_mule },
    { "spare", _campaign_team_spare },
    { "covenant_player", _campaign_team_covenant_player },
};
