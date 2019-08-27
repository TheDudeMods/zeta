#pragma once

#include <cseries/cseries.h>

/* ---------- types */

template <long const k_maximum_count>
class c_static_string final
{
	static_assert(k_maximum_count > 0 && k_maximum_count <= k_maximum_string_size);

private:
	char m_string[k_maximum_count];

public:
	c_static_string()
	{
		clear();
	}

	c_static_string(const char *s) :
		c_static_string()
	{
		assert(s);
		set(s);
	}

	char *get_buffer()
	{
		return m_string;
	}

	char const *get_string() const
	{
		return m_string;
	}

	char const *get_buffer() const
	{
		return m_string;
	}

	static unsigned long max_length()
	{
		return k_maximum_count;
	}

	unsigned long length() const
	{
		return csstrlen(reinterpret_cast<char const *>(m_string));
	}

	bool is_empty() const
	{
		return csstrnlen(m_string, k_maximum_count) == 0;
	}

	bool starts_with(char const *s) const
	{
		assert(s);
		return csstrncmp(s, m_string, strnlen_s(s, k_maximum_count)) == 0;
	}

	c_static_string<k_maximum_count> &clear()
	{
		assert(csmemset(m_string, 0, k_maximum_count));
		return *this;
	}

	c_static_string<k_maximum_count> &set(char const *s)
	{
		assert(s);
		assert(csstrnzcpy(m_string, s, k_maximum_count));
		return *this;
	}

	c_static_string<k_maximum_count> &append(char const *s)
	{
		assert(s);
		assert(csstrnzcat(m_string, s, k_maximum_count));
		return *this;
	}

	c_static_string<k_maximum_count> &remove_all(char c)
	{
		static char temporary[k_maximum_count];

		assert(csstrnzcpy(temporary, m_string, k_maximum_count));

		unsigned long old_length = length();
		unsigned long new_length = 0;
		
		for (unsigned long i = 0; i < old_length; i++)
			if (temporary[i] != c)
				m_string[new_length++] = temporary[i];

		m_string[new_length] = '\0';

		return *this;
	}

	c_static_string<k_maximum_count> &replace(char old_value, char new_value)
	{
		unsigned long total_length = length();

		for (unsigned long i = 0; i < total_length; i++)
			if (m_string[i] == old_value)
				m_string[i] = new_value;

		return *this;
	}

	c_static_string<k_maximum_count> &strip_leading(char c)
	{
		unsigned long total_length = length();
		unsigned long strip_length = 0;

		while (strip_length < total_length && m_string[strip_length] == c)
			strip_length++;

		if (strip_length > 0)
		{
			assert(csmemmove(m_string, m_string + strip_length, k_maximum_count - strip_length));
			m_string[total_length - strip_length] = '\0';
		}

		return *this;
	}

	c_static_string<k_maximum_count> &strip_trailing(char c)
	{
		unsigned long total_length = length();

		while (total_length > 0 && m_string[total_length - 1] == c)
			m_string[total_length--] = '\0';

		return *this;
	}

	c_static_string<k_maximum_count> &to_lower()
	{
		unsigned long total_length = length();

		for (unsigned long i = 0; i < total_length; i++)
			m_string[i] = ascii_tolower(m_string[i]);

		return *this;
	}

	c_static_string<k_maximum_count> &to_upper()
	{
		unsigned long total_length = length();

		for (unsigned long i = 0; i < total_length; i++)
			m_string[i] = ascii_toupper(m_string[i]);

		return *this;
	}

	operator char *()
	{
		return m_string;
	}

	operator char const *() const
	{
		return m_string;
	}
};
