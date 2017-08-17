#ifndef Expecter_H
#define Expecter_H

#include "Main.h"

#include <vector>

#include "BuildConstants.h"
#include "Tokenizer.h"

namespace Prac
{

	class Expecter
	{
	public:
		static void expect(std::vector<Token>::const_iterator& it, ReservedKeyword keyword);
		static void expectOne(std::vector<Token>::const_iterator& it, 
			const std::vector<ReservedKeyword>& keywords);
		static void expectSemicolon(std::vector<Token>::const_iterator& it);
	};

}

#endif