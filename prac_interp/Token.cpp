#include "Main.h"

#include "Token.h"

namespace Prac
{
	TokenType Token::getType() const
	{
		return m_type;
	}

	std::string Token::getValue() const
	{
		return m_value;
	}

	// If a token is found at the end of the file, determine
	// whether or not it is valid, as well as whether or not it
	// has to be interpreted differently than the tokenizer
	// originally interpreted it.
	TokenType Token::resolveTokenIncomplete(TokenType type)
	{
		switch (type)
		{
		case INVALID:				return INVALID;
		case START:					return START;
		case IDENTIFIER:			return IDENTIFIER;
		case WORD:					return WORD;
		case PROPIDENTIFIER:		return PROPIDENTIFIER;
		case INTEGER:				return INTEGER;
		case DIMENSION:				return DIMENSION;
		case MINUS:					return MINUS;
		case STRING:				return INVALID;
		case STRINGNOTERM:			return INVALID;
		case STRINGSKIPWHITESPACE:	return INVALID;
		case SEMICOLON:				return SEMICOLON;
		case OPENPARENTH:			return OPENPARENTH;
		case CLOSEPARENTH:			return CLOSEPARENTH;
		case OPENBRACKET:			return OPENBRACKET;
		case CLOSEBRACKET:			return CLOSEBRACKET;
		case BITWISEAND:			return BITWISEAND;
		case BITWISEOR:				return BITWISEOR;
		case BITWISEXOR:			return BITWISEXOR;
		case DIV:					return DIV;
		case MUL:					return MUL;
		case PLUS:					return PLUS;
		case GT:					return GT;
		case GE:					return GE;
		case BITWISERIGHT:			return BITWISERIGHT;
		case LT:					return LT;
		case LE:					return LE;
		case BITWISELEFT:			return BITWISELEFT;
		case MOD0:					return IDENTIFIER;
		case MOD1:					return IDENTIFIER;
		case MOD:					return MOD;
		default:					throw - 1; // If this is reached, programmer error.
		}
	}
}