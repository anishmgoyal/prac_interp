#ifndef Token_H
#define Token_H

#include "Main.h"

#define finishFlag 1024

#include <string>

namespace Prac
{

	enum TokenType
	{
		
		// General states
		INVALID = 0,
		START,
		IDENTIFIER,
		WORD,
		PROPIDENTIFIER,
		INTEGER,
		DIMENSION,
		MINUS,
		STRING,
		STRINGNOTERM,
		STRINGSKIPWHITESPACE,

		// Symbol states
		SEMICOLON = 128,
		OPENPARENTH,
		CLOSEPARENTH,
		OPENBRACKET,
		CLOSEBRACKET,
		BITWISEAND,
		BITWISEOR,
		BITWISEXOR,
		DIV,
		MUL,
		PLUS,
		GT,
		GE,
		BITWISERIGHT,
		LT,
		LE,
		BITWISELEFT,

		// Keyword builder states
		MOD0,
		MOD1,
		MOD,

	};

	class Token
	{
		
	private:
		TokenType m_type;
		std::string m_value;

	public:
		Token(TokenType type, std::string value) : m_type(type), m_value(value) {}

		TokenType getType() const;
		std::string getValue() const;

		static TokenType resolveTokenIncomplete(TokenType type);

	};

}

#endif