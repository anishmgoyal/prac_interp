#include "Main.h"

#include "UnitaryOpNode.h"
#include "WrapUtil.h"

#include <iostream>

namespace Prac
{

	bool UnitaryUtil<bool, OP_NOT>::applyOperation(bool value)
	{
		return !value;
	}

}