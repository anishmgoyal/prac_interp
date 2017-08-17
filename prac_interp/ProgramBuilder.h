#ifndef ProgramBuilder_H
#define ProgramBuilder_H

#include "Main.h"

#include "BuildConstants.h"
#include "IEvaluatorNode.h"
#include "Tokenizer.h"

#include <vector>

namespace Prac
{

	class ProgramBuilder
	{

	private:
		static IEvaluatorNode *buildDeclareNode(std::vector<Token>::const_iterator& it, Scope *scope);
		static IEvaluatorNode *buildAssignNode(std::vector<Token>::const_iterator& it, Scope *scope);
		static IEvaluatorNode *buildPrintNode(std::vector<Token>::const_iterator& it, Scope *scope);
		static IEvaluatorNode *buildInputNode(std::vector<Token>::const_iterator& it, Scope *scope);

		static IEvaluatorNode *buildConditionalNode(const std::vector<Token>& tokens,
			std::vector<Token>::const_iterator& it, Scope *scope);
		static IEvaluatorNode *buildWhileNode(const std::vector<Token>& tokens,
			std::vector<Token>::const_iterator& it, Scope *scope);

		static IEvaluatorNode *buildBody(const std::vector<Token>& tokens,
			std::vector<Token>::const_iterator& it, Scope *parentScope);

	public:
		static IEvaluatorNode *buildProgram(const std::string& program);
		static IEvaluatorNode *buildProgram(const std::vector<Token>& tokens);

	};

}

#endif