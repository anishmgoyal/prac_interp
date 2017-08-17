#include "Main.h"

#include <string>

#include "VariableNode.h"

namespace Prac
{
	Data *VariableNode::evaluate(Scope *scope)
	{
		return cloneData(scope->getValue(m_varname));
	}
}