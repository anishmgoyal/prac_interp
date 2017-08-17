#include "Main.h"

#include <string>

#include "DeclareNode.h"
#include "Scope.h"

namespace Prac
{

	void DeclareNode::evaluate(Scope *scope) const
	{
		scope->createVariable(m_varname, m_vartype);
	}

}