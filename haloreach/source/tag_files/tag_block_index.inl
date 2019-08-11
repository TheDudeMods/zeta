#pragma once

#include <cache/cache_files.h>

template <typename t_element, typename t_index>
class c_tag_block_index
{
private:
	t_index m_index;

public:
	inline c_tag_block_index(t_index index) : m_index(index) {}
	inline c_tag_block_index() : c_tag_block_index(t_index()) {}
	inline c_tag_block_index(const c_tag_block_index<t_element, t_index> &other) : c_tag_block_index(other.m_index) {}

	inline bool operator==(t_index other) const { return m_index == other; }
	inline bool operator!=(t_index other) const { return !(*this == other); }

	inline bool operator==(const c_tag_block_index<t_element, t_index> &other) const { return m_index == other.m_index; }
	inline bool operator!=(const c_tag_block_index<t_element, t_index> &other) const { return !(*this == other); }

	inline bool try_resolve(c_cache_file_reach *file, c_tag_block<t_element> *block, t_element **out_element)
	{
		if (!block || !out_element)
			return false;
		return block->try_get_element(file, m_index, out_element);
	}

	inline t_element *resolve(c_cache_file_reach *file, c_tag_block<t_element> *block)
	{
		if (!block)
			return nullptr;
		return block->get_element(file, m_index);
	}

	inline operator t_index() const { return m_index; }
	inline operator bool() const { return m_index != (t_index)NONE; }
};
static_assert(sizeof(c_tag_block_index<void, long>) == sizeof(long));
