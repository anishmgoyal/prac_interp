#ifndef WrapUtil_H
#define WrapUtil_H

#include "Main.h"

#include "Data.h"

namespace Prac
{

	class WrapUtil
	{

	public:

		template<class T> static void wrapValue(Data *data, T value);
		template<class T> static T unwrapValue(Data *data);

	};

	template<> static void WrapUtil::wrapValue<long long>
		(Data *data, long long value);
	template<> static void WrapUtil::wrapValue<double>
		(Data *data, double value);
	template<> static void WrapUtil::wrapValue<char>
		(Data *data, char value);
	template<> static void WrapUtil::wrapValue<bool>
		(Data *data, bool value);
	template<> static void WrapUtil::wrapValue<const std::string *>
		(Data *data, const std::string *value);
		
	template<> static long long WrapUtil::unwrapValue<long long>
		(Data *data);
	template<> static double WrapUtil::unwrapValue<double>
		(Data *data);
	template<> static char WrapUtil::unwrapValue<char>
		(Data *data);
	template<> static bool WrapUtil::unwrapValue<bool>
		(Data *data);	
	template<> static const std::string *WrapUtil::unwrapValue<const std::string *>
		(Data *data);

}

#endif