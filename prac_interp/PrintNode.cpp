#include "Main.h"

#include "PrintNode.h"

#include <iostream>

namespace Prac
{

	void PrintNode::evaluate(Scope *scope) const
	{
		Data *printVal = m_child->evaluate(scope);
		if (printVal == NULL)
		{
			std::cout << "(null)" << std::flush;
		}
		else
		{
			std::cout << *printVal->data.asString << std::flush;
			destroyData(printVal);
		}
	}

}