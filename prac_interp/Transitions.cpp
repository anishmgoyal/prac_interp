#include "Main.h"

#include "Transitions.h"

namespace Prac
{

	int passall(int c)
	{
		return (int)true;
	}

	Transition startTransitions[]
	{
		{ CHAR, 'm', NULL, MOD0 },
		{ FN, '\0', isupper, PROPIDENTIFIER },
		{ FN, '\0', islower, IDENTIFIER },
		{ FN, '\0', isdigit, INTEGER },
		{ CHAR, ';', NULL, SEMICOLON, finishFlag },
		{ CHAR, '-', NULL, MINUS, finishFlag },
		{ CHAR, '(', NULL, OPENPARENTH, finishFlag },
		{ CHAR, ')', NULL, CLOSEPARENTH, finishFlag },
		{ CHAR, '{', NULL, OPENBRACKET, finishFlag },
		{ CHAR, '}', NULL, CLOSEBRACKET, finishFlag },
		{ CHAR, '&', NULL, BITWISEAND, finishFlag },
		{ CHAR, '|', NULL, BITWISEOR, finishFlag },
		{ CHAR, '^', NULL, BITWISEXOR, finishFlag },
		{ CHAR, '/', NULL, DIV, finishFlag },
		{ CHAR, '*', NULL, MUL, finishFlag },
		{ CHAR, '+', NULL, PLUS, finishFlag },
		{ CHAR, '>', NULL, GT },
		{ CHAR, '<', NULL, LT },
		{ CHAR_IGNORECHAR, '"', NULL, STRING },
		{ IGNORE, '\0', NULL, START }
	};

	Transition mod0Transitions[]
	{
		{ CHAR, 'o', NULL, MOD1 },
		{ FN, '\0', isalnum, IDENTIFIER },
		{ CHAR, '\'', NULL, WORD },
		{ NIL, '\0', NULL, IDENTIFIER, finishFlag },
	};

	Transition mod1Transitions[]
	{
		{ CHAR, 'd', NULL, MOD },
		{ FN, '\0', isalnum, IDENTIFIER },
		{ CHAR, '\'', NULL, WORD },
		{ NIL, '\0', NULL, IDENTIFIER, finishFlag },
	};

	Transition modTransitions[]
	{
		{ FN, '\0', isalnum, IDENTIFIER },
		{ CHAR, '\'', NULL, WORD },
		{ NIL, '\0', NULL, MOD, finishFlag },
	};

	Transition identifierTransitions[]
	{
		{ FN, '\0', isalnum, IDENTIFIER },
		{ CHAR, '\'', NULL, WORD },
		{ NIL, '\0', NULL, IDENTIFIER, finishFlag }
	};

	Transition wordTransitions[]
	{
		{ FN, '\0', isalpha, WORD },
		{ NIL, '\0', NULL, WORD, finishFlag }
	};

	Transition propIdentifierTransitions[]
	{
		{ FN, '\0', isalnum, PROPIDENTIFIER },
		{ NIL, '\0', NULL, PROPIDENTIFIER, finishFlag }
	};

	Transition integerTransitions[]
	{
		{ FN, '\0', isdigit, INTEGER },
		{ CHAR, 'd', NULL, DIMENSION, finishFlag },
		{ NIL, '\0', NULL, INTEGER, finishFlag }
	};

	Transition gtTransitions[]
	{
		{ CHAR, '>', NULL, BITWISERIGHT, finishFlag },
		{ CHAR, '=', NULL, GE, finishFlag },
		{ NIL, '\0', NULL, GT, finishFlag }
	};

	Transition ltTransitions[]
	{
		{ CHAR, '<', NULL, BITWISELEFT, finishFlag },
		{ CHAR, '=', NULL, LE, finishFlag },
		{ NIL, '\0', NULL, LT, finishFlag }
	};

	Transition stringTransitions[]
	{
		{ CHAR, '\\', NULL, STRINGNOTERM },
		{ CHAR, '\n', NULL, STRINGSKIPWHITESPACE },
		{ CHAR_IGNORECHAR, '"', NULL, STRING, finishFlag },
		{ FN, '\0', passall, STRING }
	};

	Transition stringNoTermTransitions[]
	{
		{ FN, '\0', passall, STRING }
	};

	Transition stringSkipWhitespaceTransitions[]
	{
		{ CHAR_IGNORECHAR, '"', NULL, STRING },
		{ IGNORE, '\0', isspace, STRINGSKIPWHITESPACE },
		{ NIL, '\0', NULL, INVALID }
	};

	std::map<TokenType, Transition *> transitions
	{
		{ START, startTransitions },
		{ IDENTIFIER, identifierTransitions },
		{ WORD, wordTransitions },
		{ PROPIDENTIFIER, propIdentifierTransitions },
		{ MOD0, mod0Transitions },
		{ MOD1, mod1Transitions },
		{ MOD, modTransitions },
		{ INTEGER, integerTransitions },
		{ GT, gtTransitions },
		{ LT, ltTransitions },
		{ STRING, stringTransitions },
		{ STRINGNOTERM, stringNoTermTransitions },
		{ STRINGSKIPWHITESPACE, stringSkipWhitespaceTransitions },
	};

}