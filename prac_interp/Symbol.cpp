#include "Main.h"

#include <string>

#include "Symbol.h"
#include "Data.h"

namespace Prac
{

	Symbol::Symbol(std::string type)
		: m_type(type)
	{
		m_flags = SYM_UNDEFINED;
		m_data = NULL;
	}

	const std::string& Symbol::getType()
	{
		return m_type;
	}

	Data *Symbol::getData()
	{
		return m_data;
	}

	void Symbol::setData(Data *data)
	{
		// Remove undefined flag if it's there,
		// then set data
		m_flags = m_flags & ~SYM_UNDEFINED;

		if (m_data != NULL)
		{
			destroyData(m_data);
		}

		m_data = data;
	}

	bool Symbol::isUndefined()
	{
		return ((m_flags & SYM_UNDEFINED) == SYM_UNDEFINED);
	}

}