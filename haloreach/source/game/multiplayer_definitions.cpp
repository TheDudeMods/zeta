#include <game/multiplayer_definitions.h>
#include <tag_files/tag_groups.h>

/* ---------- definitions */

TAG_ENUM(
	multiplayer_team_designator_enum,
	k_number_of_multiplayer_team_designators + 1)
{
	{ "none", _multiplayer_team_none },
	{ "red", _multiplayer_team_red },
	{ "blue", _multiplayer_team_blue },
	{ "green", _multiplayer_team_green },
	{ "orange", _multiplayer_team_orange },
	{ "purple", _multiplayer_team_purple },
	{ "gold", _multiplayer_team_gold },
	{ "brown", _multiplayer_team_brown },
	{ "pink", _multiplayer_team_pink },
	{ "white", _multiplayer_team_white },
	{ "black", _multiplayer_team_black },
	{ "zombie", _multiplayer_team_zombie },
	{ "gray", _multiplayer_team_gray },
};
