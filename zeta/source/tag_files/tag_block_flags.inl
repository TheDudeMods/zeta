#pragma once

template <typename t_element, typename t_flags>
class c_tag_block_flags
{
private:
	t_flags m_flags;

public:
	c_tag_block_flags(t_flags flags) : m_flags(flags) {}
	c_tag_block_flags() : c_tag_block_flags(t_flags()) {}
	c_tag_block_flags(const c_tag_block_flags<t_element, t_flags> &other) : c_tag_block_flags(other.m_flags) {}

	bool operator==(t_flags other) const { return m_flags == other; }
	bool operator!=(t_flags other) const { return !(*this == other); }

	bool operator==(const c_tag_block_flags<t_element, t_flags> &other) const { return m_flags == other.m_flags; }
	bool operator!=(const c_tag_block_flags<t_element, t_flags> &other) const { return !(*this == other); }

	operator t_flags() const { return m_flags; }
};
static_assert(sizeof(c_tag_block_flags<void, long>) == sizeof(long));
