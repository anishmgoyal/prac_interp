#include "Main.h"

#include "CastNode.h"
#include "WrapUtil.h"

#include <sstream>

namespace Prac
{

	const std::string *CastUtil<long long, const std::string *>::castValue(Data *d)
	{
		std::stringstream ss;
		ss << d->data.asInteger;
		return new std::string(ss.str());
	}

	const std::string *CastUtil<double, const std::string*>::castValue(Data *d)
	{
		std::stringstream ss;
		ss << d->data.asNumber;
		return new std::string(ss.str());
	}

	const std::string *CastUtil<char, const std::string *>::castValue(Data *d)
	{
		return new std::string(1, d->data.asCharacter);
	}

	const std::string *CastUtil<bool, const std::string *>::castValue(Data *d)
	{
		if (d->data.asBoolean)
		{
			return new std::string("true");
		}
		return new std::string("false");
	}

}