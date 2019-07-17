#include <tag_files/tag_definitions.h>
#include <camera/camera_track.h>
#include <objects/object_definitions.h>
#include <objects/scenery.h>
#include <objects/crates.h>
#include <devices/devices.h>
#include <devices/device_controls.h>
#include <devices/device_machines.h>
#include <items/items.h>
#include <items/projectiles.h>
#include <units/unit_definitions.h>

/* ---------- code */

s_tag_group_definition *tag_group_definition_get(
	tag group_tag)
{
	char tag_string[5];

	switch (group_tag)
	{
	case k_camera_track_group_tag:
		extern s_tag_group_definition camera_track_group;
		return &camera_track_group;

	case k_control_group_tag:
		extern s_tag_group_definition control_group;
		return &control_group;

	case k_crate_group_tag:
		extern s_tag_group_definition crate_group;
		return &crate_group;

	case k_device_group_tag:
		extern s_tag_group_definition device_group;
		return &device_group;

	case k_item_group_tag:
		extern s_tag_group_definition item_group;
		return &item_group;

	case k_machine_group_tag:
		extern s_tag_group_definition machine_group;
		return &machine_group;

	case k_object_group_tag:
		extern s_tag_group_definition object_group;
		return &object_group;

	case k_projectile_group_tag:
		extern s_tag_group_definition projectile_group;
		return &projectile_group;

	case k_scenery_group_tag:
		extern s_tag_group_definition scenery_group;
		return &scenery_group;

	case k_unit_group_tag:
		extern s_tag_group_definition unit_group;
		return &unit_group;

	default:
		return nullptr;
	}
}
