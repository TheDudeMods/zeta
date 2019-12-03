#include <camera/camera_track.h>

/* ---------- definitions */

TAG_ENUM(
    camera_track_flags_enum,
    k_number_of_camera_track_flags)
{
    { "lens_enabled", _camera_track_lens_enabled_bit }
};

TAG_PAD(
    _field_char_integer,
    camera_track_post_flags_padding,
    3);

TAG_BLOCK(
    camera_track_control_point_block,
    sizeof(s_camera_track_control_point),
    k_maximum_number_of_camera_track_control_points)
{
    { _field_real_point3d, "position" },
    { _field_real_quaternion, "orientation" },
    { _field_terminator }
};

TAG_GROUP(
    camera_track_group,
    k_camera_track_group_tag,
    sizeof(s_camera_track_definition))
{
    { _field_byte_flags, "flags", &camera_track_flags_enum },
    { _field_padding, "post_flags_padding", &camera_track_post_flags_padding },
    { _field_block, "control_points", &camera_track_control_point_block },
    { _field_terminator }
};
