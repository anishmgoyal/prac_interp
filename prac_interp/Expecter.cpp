#include "Main.h"

#include "Expecter.h"

namespace Prac
{

	void Expecter::expect(std::vector<Token>::const_iterator& it, ReservedKeyword keyword)
	{
		Token tk = *it;
		switch (tk.getType())
		{
		case IDENTIFIER:
		case WORD:
			break;
		default:
			throw EXPECTED_KEYWORD_NOT_FOUND;
		}

		ReservedKeyword keyword2 = getKeyword(tk.getValue());
		if (keyword != keyword2)
		{
			throw EXPECTED_KEYWORD_NOT_FOUND;
		}
	}

	void Expecter::expectOne(std::vector<Token>::const_iterator& it,
		const std::vector<ReservedKeyword>& keywords)
	{
		const Token& tk = *it;
		switch (tk.getType())
		{
		case IDENTIFIER:
		case WORD:
			break;
		default:
			throw EXPECTED_KEYWORD_NOT_FOUND;
		}

		ReservedKeyword keyword = getKeyword(tk.getValue());
		for (auto it2 = keywords.begin(); it2 != keywords.end(); ++it2)
		{
			if (*it2 == keyword)
			{
				return;
			};
		}
		throw EXPECTED_KEYWORD_NOT_FOUND;
	}

	void Expecter::expectSemicolon(std::vector<Token>::const_iterator& it)
	{
		Token tk = *it;
		if (tk.getType() != SEMICOLON)
		{
			throw EXPECTED_SEMICOLON_NOT_FOUND;
		}
	}

}