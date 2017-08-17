#include "Main.h"

#include "WrapUtil.h"

namespace Prac
{

	template<> static void WrapUtil::wrapValue<long long>
		(Data *data, long long value)
	{
		setDataInt(data, value);
	}

	template<> static long long WrapUtil::unwrapValue<long long>
		(Data *data)
	{
		return data->data.asInteger;
	}

	template<> static void WrapUtil::wrapValue<double>
		(Data *data, double value)
	{
		setDataNum(data, value);
	}

	template<> static double WrapUtil::unwrapValue<double>
		(Data *data)
	{
		return data->data.asNumber;
	}

	template<> static void WrapUtil::wrapValue<char>
		(Data *data, char value) 
	{
		setDataChar(data, value);
	}

	template<> static char WrapUtil::unwrapValue<char>
		(Data *data)
	{
		return data->data.asCharacter;
	}

	template<> static void WrapUtil::wrapValue<bool>
		(Data *data, bool value) 
	{
		setDataBool(data, value);
	}

	template<> static bool WrapUtil::unwrapValue<bool>
		(Data *data)
	{
		return data->data.asBoolean;
	}

	template<> static void WrapUtil::wrapValue<const std::string *>
		(Data *data, const std::string *value)
	{
		setDataStr(data, value);
	}

	template<> static const std::string *WrapUtil::unwrapValue<const std::string *>
		(Data *data)
	{
		return data->data.asString;
	}
}