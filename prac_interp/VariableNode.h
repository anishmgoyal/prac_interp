#ifndef VariableNode_H
#define VariableNode_H

#include "Main.h"

#include <string>

#include "IExpressionNode.h"
#include "Scope.h"

namespace Prac
{

	class VariableNode : public IExpressionNode
	{

	private:
		std::string m_varname;

	public:
		VariableNode(const std::string& varname) : m_varname(varname) { }

		~VariableNode() { }

		Data *evaluate(Scope *scope);
	};

}

#endif