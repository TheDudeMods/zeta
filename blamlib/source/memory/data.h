/*
DATA.H
*/

#pragma once

#include <cseries/cseries.h>

/* ---------- classes */

class BLAMAPI c_datum
{
protected:
	void *m_address;

public:
	virtual word get_identifier() const = 0;
	virtual void set_identifier(word identifier) = 0;
};

template <typename t_datum>
class BLAMAPI c_data_array
{
protected:
	void *m_address;

public:
	virtual c_datum &get_datum(long index) const = 0;
	virtual void set_datum(long index, c_datum &datum) = 0;
};

template <typename t_datum>
class BLAMAPI c_data_iterator
{
protected:
	void *m_address;
};
