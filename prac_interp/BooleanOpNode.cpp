#include "Main.h"

#include "BooleanOpNode.h"
#include "WrapUtil.h"

namespace Prac
{
	bool BooleanUtil<bool, OP_AND>::applyOperation(bool lterm, bool rterm)
	{
		return lterm && rterm;
	}

	bool BooleanUtil<bool, OP_OR>::applyOperation(bool lterm, bool rterm)
	{
		return lterm || rterm;
	}

	bool BooleanUtil<const std::string *, OP_EQUALS>
		::applyOperation(const std::string *lterm, const std::string *rterm)
	{
		return *lterm == *rterm;
	}
}