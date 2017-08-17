#include "Main.h"

#include <map>
#include <string>

#include "Scope.h"
#include "Symbol.h"

namespace Prac
{

	void Scope::createVariable(std::string varname, std::string vartype)
	{
		auto it = m_values.find(varname);
		if (it != m_values.end())
		{
			throw VARIABLE_ALREADY_EXISTS;
		}
		m_values.insert(std::make_pair(varname, Symbol(vartype)));
	}

	Data *Scope::getValue(std::string varname)
	{
		auto it = m_values.find(varname);
		if (it != m_values.end())
		{
			if (it->second.isUndefined())
			{
				throw VARIABLE_IS_UNDEFINED;
			}
			return it->second.getData();
		}
		
		
		if (m_parent != NULL)
		{
			return m_parent->getValue(varname);
		}

		throw VARIABLE_DOES_NOT_EXIST;
	}

	std::string Scope::getType(std::string varname)
	{
		auto it = m_values.find(varname);
		if (it != m_values.end())
		{
			return it->second.getType();
		}

		if (m_parent != NULL)
		{
			return m_parent->getType(varname);
		}

		throw VARIABLE_DOES_NOT_EXIST;
	}

	void Scope::setValue(std::string varname, Data *value)
	{
		auto it = m_values.find(varname);
		if (it != m_values.end())
		{
			it->second.setData(value);
		}
		else if (m_parent != NULL)
		{
			m_parent->setValue(varname, value);
		}
		else
		{
			throw VARIABLE_DOES_NOT_EXIST;
		}
	}

	void Scope::reset()
	{
		m_values.clear();
	}

}