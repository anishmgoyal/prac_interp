#ifndef Transitions_H
#define Transitions_H

#include "Main.h"

#include <array>
#include <cctype>
#include <map>
#include <string>
#include "Token.h"

namespace Prac
{
	enum TransitionType
	{
		NIL,
		FN,
		CHAR,
		FN_IGNORECHAR,
		CHAR_IGNORECHAR,
		IGNORE
	};

	typedef struct
	{
		TransitionType type;
		char c;
		int(*func)(int);
		TokenType state;
		int flags;
	} Transition;

	extern std::map<TokenType, Transition *> transitions;

}

#endif