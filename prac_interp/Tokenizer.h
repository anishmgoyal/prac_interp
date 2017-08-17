#ifndef Tokenizer_H
#define Tokenizer_H

#include "Main.h"

#include <string>
#include "Token.h"

namespace Prac
{

	enum TokenizerExceptions
	{
		INVALID_STATE,
	};

	class Tokenizer
	{

	private:
		std::string m_data;
		unsigned int m_pos;

	public:
		Tokenizer(const std::string& data) : m_data(data), m_pos(0) {}

		Token *nextToken();

	};

}

#endif