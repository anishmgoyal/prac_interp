#ifndef Scope_H
#define Scope_H

#include "Main.h"

#include <unordered_map>
#include <string>

#include "Symbol.h"

namespace Prac
{

	enum ScopeException
	{
		VARIABLE_ALREADY_EXISTS,
		VARIABLE_IS_UNDEFINED,
		VARIABLE_DOES_NOT_EXIST,
	};

	class Scope
	{

	private:
		std::unordered_map<std::string, Symbol> m_values;
		Scope *m_parent;

	public:
		Scope() : m_values(), m_parent(NULL) {}
		Scope(Scope *parent) : m_values(), m_parent(parent) {}

		void createVariable(std::string varname, std::string vartype);

		Data *getValue(std::string varname);
		void setValue(std::string varname, Data *value);

		std::string getType(std::string varname);

		void reset();

	};

}

#endif