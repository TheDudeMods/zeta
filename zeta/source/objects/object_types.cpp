#include <objects/object_types.h>
#include <tag_files/tag_definitions.h>

TAG_ENUM(object_type_enum, k_number_of_object_types)
{
	{ "biped", _object_type_biped },
	{ "vehicle", _object_type_vehicle },
	{ "weapon", _object_type_weapon },
	{ "equipment", _object_type_equipment },
	{ "terminal", _object_type_terminal },
	{ "projectile", _object_type_projectile },
	{ "scenery", _object_type_scenery },
	{ "machine", _object_type_machine },
	{ "control", _object_type_control },
	{ "sound_scenery", _object_type_sound_scenery },
	{ "crate", _object_type_crate },
	{ "creature", _object_type_creature },
	{ "giant", _object_type_giant },
	{ "effect_scenery", _object_type_effect_scenery },
};
