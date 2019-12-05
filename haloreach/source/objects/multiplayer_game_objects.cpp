#include <objects/multiplayer_game_objects.h>

/* ---------- definitions */

TAG_ENUM(
	multiplayer_object_type_enum,
	k_number_of_multiplayer_object_types)
{
	{ "ordinary", _multiplayer_object_type_ordinary },
	{ "weapon", _multiplayer_object_type_weapon },
	{ "grenade", _multiplayer_object_type_grenade },
	{ "projectile", _multiplayer_object_type_projectile },
	{ "powerup", _multiplayer_object_type_powerup },
	{ "equipment", _multiplayer_object_type_equipment },
	{ "ammo_pack", _multiplayer_object_type_ammo_pack },
	{ "light_land_vehicle", _multiplayer_object_type_light_land_vehicle },
	{ "heavy_land_vehicle", _multiplayer_object_type_heavy_land_vehicle },
	{ "flying_vehicle", _multiplayer_object_type_flying_vehicle },
	{ "turret", _multiplayer_object_type_turret },
	{ "device", _multiplayer_object_type_device },
	{ "teleporter_2_way", _multiplayer_object_type_teleporter_2_way },
	{ "teleporter_sender", _multiplayer_object_type_teleporter_sender },
	{ "teleporter_receiver", _multiplayer_object_type_teleporter_receiver },
	{ "player_spawn_location", _multiplayer_object_type_player_spawn_location },
	{ "player_respawn_zone", _multiplayer_object_type_player_respawn_zone },
	{ "secondary_objective", _multiplayer_object_type_secondary_objective },
	{ "primary_objective", _multiplayer_object_type_primary_objective },
	{ "named_location_area", _multiplayer_object_type_named_location_area },
	{ "danger_zone", _multiplayer_object_type_danger_zone },
	{ "fireteam_1_respawn_zone", _multiplayer_object_type_fireteam_1_respawn_zone },
	{ "fireteam_2_respawn_zone", _multiplayer_object_type_fireteam_2_respawn_zone },
	{ "fireteam_3_respawn_zone", _multiplayer_object_type_fireteam_3_respawn_zone },
	{ "fireteam_4_respawn_zone", _multiplayer_object_type_fireteam_4_respawn_zone },
	{ "safe_volume", _multiplayer_object_type_safe_volume },
	{ "kill_volume", _multiplayer_object_type_kill_volume },
	{ "cinematic_camera_position", _multiplayer_object_type_cinematic_camera_position },
};

TAG_ENUM(
	multiplayer_object_teleporter_flags_enum,
	k_number_of_multiplayer_object_teleporter_flags)
{
	{ "disallow_players", _multiplayer_object_teleporter_disallow_players_bit },
	{ "allow_light_land_vehicles", _multiplayer_object_teleporter_allow_light_land_vehicles_bit },
	{ "allow_heavy_land_vehicles", _multiplayer_object_teleporter_allow_heavy_land_vehicles_bit },
	{ "allow_flying_vehicles", _multiplayer_object_teleporter_allow_flying_vehicles_bit },
	{ "allow_projectiles", _multiplayer_object_teleporter_allow_projectiles_bit }
};

TAG_ENUM(
	multiplayer_object_flags_enum,
	k_number_of_multiplayer_object_flags)
{
	{ "only_render_in_editor", _multiplayer_object_only_render_in_editor_bit },
	{ "phased_physics_in_forge", _multiplayer_object_phased_physics_in_forge_bit },
	{ "valid_initial_player_spawn", _multiplayer_object_valid_initial_player_spawn_bit },
	{ "fixed_boundary_orientation", _multiplayer_object_fixed_boundary_orientation_bit },
	{ "candy_monitor_should_ignore", _multiplayer_object_candy_monitor_should_ignore_bit },
	{ "inherit_owning_team_color", _multiplayer_object_inherit_owning_team_color_bit },
	{ "boundary_volume_doesnt_kill_immediately", _multiplayer_object_boundary_volume_doesnt_kill_immediately_bit },
	{ "only_collision_in_editor", _multiplayer_object_only_collision_in_editor_bit },
	{ "only_physics_in_editor", _multiplayer_object_only_physics_in_editor_bit },
	{ "force_render_in_forge", _multiplayer_object_force_render_in_forge_bit },
	{ "respawn_player_spawn", _multiplayer_object_respawn_player_spawn_bit },
	{ "fallback_player_spawn", _multiplayer_object_fallback_player_spawn_bit },
};

TAG_ENUM(
	multiplayer_object_boundary_shape_enum,
	k_number_of_multiplayer_object_boundary_shapes)
{
	{ "none", _multiplayer_object_boundary_shape_none },
	{ "sphere", _multiplayer_object_boundary_shape_sphere },
	{ "cylinder", _multiplayer_object_boundary_shape_cylinder },
	{ "box", _multiplayer_object_boundary_shape_box }
};

TAG_ENUM(
	multiplayer_object_spawn_timer_type_enum,
	k_number_of_multiplayer_object_spawn_timer_types)
{
	{ "starts_on_death", _multiplayer_object_spawn_timer_starts_on_death },
	{ "starts_on_disturbance", _multiplayer_object_spawn_timer_starts_on_disturbance }
};

TAG_STRUCT(
	multiplayer_object_boundary_shader_struct,
	sizeof(s_multiplayer_object_boundary_shader_definition))
{
	{ _field_tag_reference, "standard_shader" },
	{ _field_tag_reference, "opaque_shader" },
	{ _field_terminator }
};

TAG_ARRAY(
	_field_struct,
	multiplayer_object_boundary_shaders_array,
	k_number_of_multiplayer_object_boundary_shapes,
	&multiplayer_object_boundary_shader_struct);

TAG_PAD(
	_field_char_integer,
	multiplayer_object_post_teleporter_padding,
	1);

TAG_BLOCK(
	multiplayer_object_definition_block,
	sizeof(s_multiplayer_object_definition),
	k_maximum_number_of_multiplayer_object_definitions)
{
	{ _field_short_enum, "type", &multiplayer_object_type_enum },
	{ _field_byte_flags, "teleporter_passability", &multiplayer_object_teleporter_flags_enum },
	{ _field_pad, "post_teleporter_padding", &multiplayer_object_post_teleporter_padding },
	{ _field_real, "boundary_width" },
	{ _field_real, "boundary_length" },
	{ _field_real, "boundary_top" },
	{ _field_real, "boundary_bottom" },
	{ _field_char_enum, "boundary_shape", &multiplayer_object_boundary_shape_enum },
	{ _field_char_enum, "spawn_timer_type", &multiplayer_object_spawn_timer_type_enum },
	{ _field_short_integer, "default_spawn_time" },
	{ _field_short_integer, "default_abandon_time" },
	{ _field_word_flags, "flags", &multiplayer_object_flags_enum },
	{ _field_real, "normal_weight" },
	{ _field_string_id, "boundary_center_marker" },
	{ _field_string_id, "spawned_object_marker_name" },
	{ _field_tag_reference, "spawned_object" },
	{ _field_string_id, "nyi_boundary_material" },
	{ _field_array, "boundary_shaders", &multiplayer_object_boundary_shaders_array },
	{ _field_terminator }
};
