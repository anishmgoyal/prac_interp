#include "Main.h"

#include <string>
#include <sstream>

#include "Token.h"
#include "Tokenizer.h"
#include "Transitions.h"

namespace Prac
{

	Token *Tokenizer::nextToken()
	{

		TokenType state = START;
		int flags = 0;
		std::stringstream token;

		if (m_pos >= m_data.length())
		{
			return NULL;
		}

		char c = m_data[m_pos++];
		bool endIsNull = false;

		while (m_pos <= m_data.length())
		{

			// We assume that the transition table is there.
			// If not, the transitions have been encoded incorrectly.
			Transition *trans = transitions[state];

			bool transitioned = false;

			for (int i = 0; !transitioned; i++)
			{
				switch (trans[i].type)
				{

				case IGNORE:
					flags = trans[i].flags;
					state = trans[i].state;
					transitioned = true;
					break;

				case FN:
					if (trans[i].func(c))
					{
						token << c;
						flags = trans[i].flags;
						state = trans[i].state;
						transitioned = true;
					}
					break;

				case CHAR:
					if (trans[i].c == c)
					{
						token << c;
						flags = trans[i].flags;
						state = trans[i].state;
						transitioned = true;
					}
					break;

				case FN_IGNORECHAR:
					if (trans[i].func(c))
					{
						flags = trans[i].flags;
						state = trans[i].state;
						transitioned = true;
					}
					break;

				case CHAR_IGNORECHAR:
					if (trans[i].c == c)
					{
						flags = trans[i].flags;
						state = trans[i].state;
						transitioned = true;
					}
					break;

				case NIL:
					endIsNull = true;
					flags = trans[i].flags; 
					state = trans[i].state;
					transitioned = true;
					break;
				}
			}

			if ((flags & finishFlag) == finishFlag)
			{
				break;
			}

			if (m_pos < m_data.length())
			{
				c = m_data[m_pos++];
			}
			else
			{
				m_pos++;
			}
		}

		if (state == START)
		{
			return NULL;
		}

		if ((flags & finishFlag) != finishFlag)
		{
			state = Token::resolveTokenIncomplete(state);
			if (state == INVALID)
			{
				throw INVALID_STATE;
			}
		}

		if (endIsNull)
		{
			m_pos--;
		}

		return new Token(state, token.str());

	}

}