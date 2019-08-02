#define WIN32_LEAN_AND_MEAN
#include <d3d11.h>

#include <geometry/vertex_definitions.h>

/* ---------- private globals */

static D3D11_INPUT_ELEMENT_DESC g_world_vertex_elements[4] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R16G16_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R16G16B16A16_SNORM, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT", 0, DXGI_FORMAT_R16G16B16A16_SNORM, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_rigid_vertex_elements[4] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R16G16_UNORM, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R16G16B16A16_SNORM, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT", 0, DXGI_FORMAT_R16G16B16A16_SNORM, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_skinned_vertex_elements[6] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R16G16_UNORM, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R16G16B16A16_SNORM, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT", 0, DXGI_FORMAT_R16G16B16A16_SNORM, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "BLENDINDICES", 0, DXGI_FORMAT_R8G8B8A8_UINT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "BLENDWEIGHT", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_flat_world_vertex_elements[4] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R16G16_FLOAT, 0, 0x10, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R16G16B16A16_SNORM, 0, 0x14, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT", 0, DXGI_FORMAT_R16G16B16A16_SNORM, 0, 0x1C, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_flat_rigid_vertex_elements[4] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R16G16_UNORM, 0, 0x10, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R16G16B16A16_SNORM, 0, 0x14, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT", 0, DXGI_FORMAT_R16G16B16A16_SNORM, 0, 0x1C, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_flat_skinned_vertex_elements[6] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R16G16_UNORM, 0, 0x10, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R16G16B16A16_SNORM, 0, 0x14, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT", 0, DXGI_FORMAT_R16G16B16A16_SNORM, 0, 0x1C, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "BLENDINDICES", 0, DXGI_FORMAT_R8G8B8A8_UINT, 0, 0x2E, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "BLENDWEIGHT", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 0x28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_screen_vertex_elements[3] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_B8G8R8A8_UNORM, 0, 0x10, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_debug_vertex_elements[2] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_B8G8R8A8_UNORM, 0, 0x0C, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_transparent_vertex_elements[3] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0x0C, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_B8G8R8A8_UNORM, 0, 0x14, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_chud_vertex_simple_elements[2] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_chud_vertex_fancy_elements[3] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_B8G8R8A8_UNORM, 0, 0x0C, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0x10, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_decorator_vertex[7] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0x0C, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0x14, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "POSITION", 1, DXGI_FORMAT_R32_UINT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "COLOR", 2, DXGI_FORMAT_R8G8B8A8_UINT, 1, 4, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "NORMAL", 1, DXGI_FORMAT_R8G8B8A8_SNORM, 1, 8, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "COLOR", 1, DXGI_FORMAT_R8G8B8A8_UNORM, 1, 0x0C, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
};

static D3D11_INPUT_ELEMENT_DESC g_tiny_position_vertex_declaration[1] =
{
	{ "POSITION", 0, DXGI_FORMAT_R16G16B16A16_SNORM, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_patchy_fog_vertex_declaration[1] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_water_vertex_declaration[14] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "POSITION", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0x10, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "POSITION", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0x20, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "POSITION", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0x30, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "POSITION", 4, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0x40, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "POSITION", 5, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0x50, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "POSITION", 6, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0x60, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "POSITION", 7, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0x70, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0x80, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "TEXCOORD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0x90, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "TEXCOORD", 2, DXGI_FORMAT_R32G32_FLOAT, 1, 0x0A0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 3, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "NORMAL", 1, DXGI_FORMAT_R32G32_FLOAT, 3, 0x10, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "TEXCOORD", 3, DXGI_FORMAT_R32G32B32_FLOAT, 2, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_implicit_vertex_declaration[2] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0x0C, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_world_tessellated_vertex_declaration[4] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0x0C, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0x14, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0x20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_rigid_tessellated_vertex_declaration[4] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0x0C, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0x14, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0x20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_skinned_tessellated_vertex_declaration[6] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0x10, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0x18, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0x24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "BLENDINDICES", 0, DXGI_FORMAT_R8G8B8A8_UINT, 0, 0x34, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "BLENDWEIGHT", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 0x38, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_instance_imposter_vertex_declaration[2] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 0x0C, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_object_imposter_vertex_declaration[7] =
{
	{ "POSITION", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R16G16B16A16_FLOAT, 0, 4, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 1, DXGI_FORMAT_R8G8B8A8_UNORM, 2, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 2, DXGI_FORMAT_R8G8B8A8_UNORM, 2, 4, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 3, DXGI_FORMAT_R8G8B8A8_UNORM, 2, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 4, DXGI_FORMAT_R8G8B8A8_UNORM, 2, 0x0C, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 5, DXGI_FORMAT_R8G8B8A8_UNORM, 2, 0x10, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC g_light_volume_pre_vertex_elements[1] =
{
	{ "COLOR", 0, DXGI_FORMAT_R16G16B16A16_FLOAT, 0, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
};

static D3D11_INPUT_ELEMENT_DESC g_bink_vertex_declaration[2] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static s_vertex_definition g_vertex_definitions[k_number_of_vertex_types] =
{
	{ g_world_vertex_elements, 4 },
	{ g_rigid_vertex_elements, 4 },
	{ g_skinned_vertex_elements, 6 },
	{ nullptr, 0 },
	{ g_flat_world_vertex_elements, 4 },
	{ g_flat_rigid_vertex_elements, 4 },
	{ g_flat_skinned_vertex_elements, 6 },
	{ g_screen_vertex_elements, 3 },
	{ g_debug_vertex_elements, 2 },
	{ g_transparent_vertex_elements, 3 },
	{ nullptr, 0 },
	{ nullptr, 0 },
	{ nullptr, 0 },
	{ g_chud_vertex_simple_elements, 2 },
	{ g_chud_vertex_fancy_elements, 3 },
	{ g_decorator_vertex, 7 },
	{ g_tiny_position_vertex_declaration, 1 },
	{ g_patchy_fog_vertex_declaration, 1 },
	{ g_water_vertex_declaration, 14 },
	{ nullptr, 0 },
	{ g_implicit_vertex_declaration, 2 },
	{ nullptr, 0 },
	{ g_world_tessellated_vertex_declaration, 4 },
	{ g_rigid_tessellated_vertex_declaration, 4 },
	{ g_skinned_tessellated_vertex_declaration, 6 },
	{ nullptr, 0 },
	{ g_instance_imposter_vertex_declaration, 2 },
	{ g_object_imposter_vertex_declaration, 7 },
	{ g_rigid_vertex_elements, 4 },
	{ g_skinned_vertex_elements, 4 },
	{ g_light_volume_pre_vertex_elements, 1 },
	{ g_bink_vertex_declaration, 2 },
	//
	// TODO: finish
	//
};

/* ---------- code */

s_vertex_definition *vertex_definition_get(
	e_vertex_type type)
{
	if (type == NONE || type >= k_number_of_vertex_types)
		return nullptr;

	return &g_vertex_definitions[type];
}

bool vertex_definition_try_get_element(
	s_vertex_definition *definition,
	long element_index,
	void **out_address)
{
	assert(definition);
	assert(out_address);
	
	auto element_count = definition->element_count;

	if (!definition->elements || element_index < 0 || element_index >= definition->element_count)
	{
		*out_address = nullptr;
		return false;
	}
	else
	{
		*out_address = &((D3D11_INPUT_ELEMENT_DESC *)definition->elements)[element_index];
		return true;
	}
}

long vertex_element_get_size(
	void *element_address)
{
	assert(element_address);

	auto element = (D3D11_INPUT_ELEMENT_DESC *)element_address;

	switch (element->Format)
	{
	case DXGI_FORMAT_R32G32B32A32_TYPELESS:
		return 16;
	case DXGI_FORMAT_R32G32B32A32_FLOAT:
		return 16;
	case DXGI_FORMAT_R32G32B32A32_UINT:
		return 16;
	case DXGI_FORMAT_R32G32B32A32_SINT:
		return 16;
	case DXGI_FORMAT_R32G32B32_TYPELESS:
		return 12;
	case DXGI_FORMAT_R32G32B32_FLOAT:
		return 12;
	case DXGI_FORMAT_R32G32B32_UINT:
		return 12;
	case DXGI_FORMAT_R32G32B32_SINT:
		return 12;
	case DXGI_FORMAT_R16G16B16A16_TYPELESS:
		return 8;
	case DXGI_FORMAT_R16G16B16A16_FLOAT:
		return 8;
	case DXGI_FORMAT_R16G16B16A16_UNORM:
		return 8;
	case DXGI_FORMAT_R16G16B16A16_UINT:
		return 8;
	case DXGI_FORMAT_R16G16B16A16_SNORM:
		return 8;
	case DXGI_FORMAT_R16G16B16A16_SINT:
		return 8;
	case DXGI_FORMAT_R32G32_TYPELESS:
		return 8;
	case DXGI_FORMAT_R32G32_FLOAT:
		return 8;
	case DXGI_FORMAT_R32G32_UINT:
		return 8;
	case DXGI_FORMAT_R32G32_SINT:
		return 8;
	case DXGI_FORMAT_R32G8X24_TYPELESS:
		return 8;
	case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
		return 8;
	case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
		return 8;
	case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
		return 8;
	case DXGI_FORMAT_R10G10B10A2_TYPELESS:
		return 4;
	case DXGI_FORMAT_R10G10B10A2_UNORM:
		return 4;
	case DXGI_FORMAT_R10G10B10A2_UINT:
		return 4;
	case DXGI_FORMAT_R11G11B10_FLOAT:
		return 4;
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:
		return 4;
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		return 4;
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		return 4;
	case DXGI_FORMAT_R8G8B8A8_UINT:
		return 4;
	case DXGI_FORMAT_R8G8B8A8_SNORM:
		return 4;
	case DXGI_FORMAT_R8G8B8A8_SINT:
		return 4;
	case DXGI_FORMAT_R16G16_TYPELESS:
		return 4;
	case DXGI_FORMAT_R16G16_FLOAT:
		return 4;
	case DXGI_FORMAT_R16G16_UNORM:
		return 4;
	case DXGI_FORMAT_R16G16_UINT:
		return 4;
	case DXGI_FORMAT_R16G16_SNORM:
		return 4;
	case DXGI_FORMAT_R16G16_SINT:
		return 4;
	case DXGI_FORMAT_R32_TYPELESS:
		return 4;
	case DXGI_FORMAT_D32_FLOAT:
		return 4;
	case DXGI_FORMAT_R32_FLOAT:
		return 4;
	case DXGI_FORMAT_R32_UINT:
		return 4;
	case DXGI_FORMAT_R32_SINT:
		return 4;
	case DXGI_FORMAT_R24G8_TYPELESS:
		return 4;
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
		return 4;
	case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
		return 4;
	case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
		return 4;
	case DXGI_FORMAT_R8G8_TYPELESS:
		return 2;
	case DXGI_FORMAT_R8G8_UNORM:
		return 2;
	case DXGI_FORMAT_R8G8_UINT:
		return 2;
	case DXGI_FORMAT_R8G8_SNORM:
		return 2;
	case DXGI_FORMAT_R8G8_SINT:
		return 2;
	case DXGI_FORMAT_R16_TYPELESS:
		return 2;
	case DXGI_FORMAT_R16_FLOAT:
		return 2;
	case DXGI_FORMAT_D16_UNORM:
		return 2;
	case DXGI_FORMAT_R16_UNORM:
		return 2;
	case DXGI_FORMAT_R16_UINT:
		return 2;
	case DXGI_FORMAT_R16_SNORM:
		return 2;
	case DXGI_FORMAT_R16_SINT:
		return 2;
	case DXGI_FORMAT_R8_TYPELESS:
		return 1;
	case DXGI_FORMAT_R8_UNORM:
		return 1;
	case DXGI_FORMAT_R8_UINT:
		return 1;
	case DXGI_FORMAT_R8_SNORM:
		return 1;
	case DXGI_FORMAT_R8_SINT:
		return 1;
	case DXGI_FORMAT_A8_UNORM:
		return 1;
	case DXGI_FORMAT_R1_UNORM:
		return 1;
	case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
		return 4;
	case DXGI_FORMAT_R8G8_B8G8_UNORM:
		return 4;
	case DXGI_FORMAT_G8R8_G8B8_UNORM:
		return 4;
	case DXGI_FORMAT_B5G6R5_UNORM:
		return 2;
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		return 4;
	case DXGI_FORMAT_B8G8R8X8_UNORM:
		return 4;
	case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
		return 4;
	case DXGI_FORMAT_B8G8R8A8_TYPELESS:
		return 4;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
		return 4;
	case DXGI_FORMAT_B8G8R8X8_TYPELESS:
		return 4;
	case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
		return 4;
	case DXGI_FORMAT_AYUV:
		return 4;
	case DXGI_FORMAT_Y410:
		return 4;
	case DXGI_FORMAT_Y416:
		return 8;
	case DXGI_FORMAT_NV12:
		return 1;
	case DXGI_FORMAT_P010:
		return 2;
	case DXGI_FORMAT_P016:
		return 2;
	case DXGI_FORMAT_420_OPAQUE:
		return 1;
	case DXGI_FORMAT_YUY2:
		return 4;
	case DXGI_FORMAT_Y210:
		return 8;
	case DXGI_FORMAT_Y216:
		return 8;
	case DXGI_FORMAT_NV11:
		return 1;
	case DXGI_FORMAT_AI44:
		return 1;
	case DXGI_FORMAT_IA44:
		return 1;
	case DXGI_FORMAT_P8:
		return 1;
	case DXGI_FORMAT_A8P8:
		return 2;
	case DXGI_FORMAT_B4G4R4A4_UNORM:
		return 2;
	case DXGI_FORMAT_P208:
		return 1;
	case DXGI_FORMAT_V208:
		return 1;
	case DXGI_FORMAT_V408:
		return 2;
	case DXGI_FORMAT_FORCE_UINT:
		return 4;
	default:
		return NONE;
	}
}

bool vertex_element_next(
	s_vertex_definition *definition,
	void **element_address,
	void **data_address)
{
	assert(definition);
	assert(element_address);

	auto element_size = vertex_element_get_size(*element_address);

	if (element_size == NONE)
		return false;

	if (data_address)
		*(char **)data_address += element_size;

	(*(D3D11_INPUT_ELEMENT_DESC **)element_address)++;

	return true;
}
