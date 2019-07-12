#pragma once

#include <cseries/cseries.h>
#include <math/real_math.h>
#include <tag_files/tag_groups.h>

/* ---------- constants */

enum
{
    k_camera_track_group_tag = 'trak',
    k_maximum_number_of_camera_track_control_points = 2000
};

/* ---------- enumerators */

enum e_camera_track_flags
{
    _camera_track_lens_enabled_bit,
    k_number_of_camera_track_flags
};

/* ---------- structures */

struct s_camera_track_control_point
{
    real_point3d position;
    real_quaternion orientation;
};
static_assert(sizeof(s_camera_track_control_point) == 0x1C);

struct s_camera_track_definition
{
    c_flags<e_camera_track_flags, byte> flags;
    char : 8;
    short : 16;
    c_tag_block<s_camera_track_control_point> control_points;
};
static_assert(sizeof(s_camera_track_definition) == 0x10);
