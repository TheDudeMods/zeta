#include <game/game_powerups.h>

/* ---------- definitions */

TAG_ENUM(
	multiplayer_powerup_flavor_enum,
	k_number_of_multiplayer_powerup_flavors)
{
	{ "red", _multiplayer_powerup_flavor_red },
	{ "blue", _multiplayer_powerup_flavor_blue },
	{ "yellow", _multiplayer_powerup_flavor_yellow },
	{ "custom", _multiplayer_powerup_flavor_custom }
};
