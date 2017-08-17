#include "Main.h"

#include "ArithmeticOpNode.h"
#include "WrapUtil.h"

namespace Prac
{

	const std::string *ArithmeticUtil<const std::string *, OP_ADD>::applyOperation(
		const std::string *lterm, const std::string *rterm)
	{
		std::string l = *lterm;
		std::string r = *rterm;

		std::string *ret = new std::string(l + r);
		return ret;
	}

}