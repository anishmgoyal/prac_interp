#include "Main.h"

#include <string>

#include "StaticNode.h"

namespace Prac
{

	Data *StaticNode<long long>::evaluate(Scope *scope)
	{
		Data *d = new Data();
		setDataInt(d, m_constant);
		return d;
	}

	Data *StaticNode<std::map<std::string, DataUnion>>::evaluate(Scope *scope)
	{
		Data *d = new Data();
		std::map<std::string, DataUnion> *clone = new std::map<std::string, DataUnion>(m_constant);
		setDataMap(d, clone);
		return d;
	}

	Data *StaticNode<double>::evaluate(Scope *scope)
	{
		Data *d = new Data();
		setDataNum(d, m_constant);
		return d;
	}

	Data *StaticNode<char>::evaluate(Scope *scope)
	{
		Data *d = new Data();
		setDataChar(d, m_constant);
		return d;
	}

	Data *StaticNode<bool>::evaluate(Scope *scope)
	{
		Data *d = new Data();
		setDataBool(d, m_constant);
		return d;
	}

	Data *StaticNode<std::string>::evaluate(Scope *scope)
	{
		Data *d = new Data();
		std::string *copy = new std::string(m_constant);
		setDataStr(d, copy);
		return d;
	}
}