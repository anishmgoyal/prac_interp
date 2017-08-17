#include "Main.h"

#include "AssignNode.h"

namespace Prac
{

	void AssignNode::evaluate(Scope *scope) const
	{
		Data *result = m_child->evaluate(scope);
		scope->setValue(m_varname, result);
	}

}