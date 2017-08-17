#ifndef IExpressionNode_H
#define IExpressionNode_H

#include "Main.h"

#include <string>

#include "Scope.h"
#include "Symbol.h"

namespace Prac
{

	class IExpressionNode
	{
	public:
		virtual ~IExpressionNode() { }
		virtual Data *evaluate(Scope *scope) = 0;
	};

}

#endif