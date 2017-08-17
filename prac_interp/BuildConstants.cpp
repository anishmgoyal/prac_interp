#include "Main.h"

#include "BuildConstants.h"

#include <unordered_map>

#include "Token.h"

namespace Prac
{

	std::unordered_map<std::string, ReservedKeyword> keyMap
	{
		{ "a", KEY_A },
		{ "an", KEY_AN },
		{ "and", KEY_AND },
		{ "as", KEY_AS },
		{ "assign", KEY_ASSIGN },
		{ "declare", KEY_DECLARE },
		{ "doesn't", KEY_DOESNT },
		{ "equal", KEY_EQUAL },
		{ "equals", KEY_EQUALS },
		{ "false", KEY_FALSE },
		{ "from", KEY_FROM },
		{ "get", KEY_GET },
		{ "if", KEY_IF },
		{ "in", KEY_IN },
		{ "it", KEY_IT },
		{ "newline", KEY_NEWLINE },
		{ "not", KEY_NOT },
		{ "of", KEY_OF },
		{ "or", KEY_OR },
		{ "otherwise", KEY_OTHERWISE },
		{ "print", KEY_PRINT },
		{ "store", KEY_STORE },
		{ "the", KEY_THE },
		{ "to", KEY_TO },
		{ "true", KEY_TRUE },
		{ "user", KEY_USER },
		{ "while", KEY_WHILE },

		{ "integer", TYPE_INTEGER },
		{ "number", TYPE_NUMBER },
		{ "character", TYPE_CHARACTER },
		{ "boolean", TYPE_BOOLEAN },
		{ "Type", TYPE_TYPE },
	};

	ReservedKeyword getKeyword(const Token& token)
	{
		if (token.getType() != IDENTIFIER && token.getType() != WORD)
		{
			return NONE;
		}
		return getKeyword(token.getValue());
	}

	ReservedKeyword getKeyword(const std::string& str)
	{
		auto it = keyMap.find(str);
		if (it == keyMap.end())
		{
			return NONE;
		}
		return it->second;
	}

}