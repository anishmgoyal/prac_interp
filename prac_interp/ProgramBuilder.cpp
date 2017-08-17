#include "Main.h"

#include "ProgramBuilder.h"

#include "Expecter.h"

#include "AssignNode.h"
#include "ConditionalNode.h"
#include "DeclareNode.h"
#include "ExpressionBuilder.h"
#include "InputNode.h"
#include "LoopNode.h"
#include "PrintNode.h"
#include "Scope.h"

namespace Prac
{

	IEvaluatorNode *ProgramBuilder::buildProgram(const std::string& program)
	{
		Tokenizer tkzr(program);
		std::vector<Token> tokens;
		
		Token *tk;
		while ((tk = tkzr.nextToken()) != NULL)
		{
			tokens.push_back(*tk);
			delete tk;
		}

		return buildProgram(tokens);
	}

	IEvaluatorNode *ProgramBuilder::buildProgram(const std::vector<Token>& tokens)
	{
		IEvaluatorNode *startNode = NULL;
		IEvaluatorNode *endNode = NULL;

		Scope scope;

		for (auto it = tokens.begin(); it != tokens.end(); it++)
		{
			const Token& tk = *it;

			if (tk.getType() != IDENTIFIER)
			{
				throw INVALID_START_OF_STATEMENT;
			}

			ReservedKeyword keyword = getKeyword(tk.getValue());
			IEvaluatorNode *next = NULL;

			bool expectSemicolon = true;

			switch (keyword)
			{
			case KEY_ASSIGN:
				next = buildAssignNode(++it, &scope);
				break;
			case KEY_DECLARE:
				next = buildDeclareNode(++it, &scope);
				break;
			case KEY_GET:
				next = buildInputNode(++it, &scope);
				break;
			case KEY_WHILE:
				next = buildWhileNode(tokens, ++it, &scope);
				expectSemicolon = false;
				break;
			case KEY_IF:
				next = buildConditionalNode(tokens, ++it, &scope);
				expectSemicolon = false;
				break;
			case KEY_PRINT:
				next = buildPrintNode(++it, &scope);
				break;
			default:
				throw INVALID_START_OF_STATEMENT;
			}

			if (startNode == NULL)
			{
				startNode = next;
				endNode = next;
			}
			else
			{
				next->setPrev(endNode);
				endNode->setNext(next);
				endNode = next;
			}

			if (it != tokens.end() && expectSemicolon)
			{
				Expecter::expectSemicolon(it);
			}

		}

		return startNode;
	}

	IEvaluatorNode *ProgramBuilder::buildDeclareNode(std::vector<Token>::const_iterator& it, Scope *scope)
	{
		const Token& varIdentifier = *it++;
		if (varIdentifier.getType() != IDENTIFIER)
		{
			throw INVALID_IDENTIFIER;
		}
		if (getKeyword(varIdentifier.getValue()) != NONE)
		{
			throw KEYWORD_AS_IDENTIFIER;
		}

		const std::string& varname = varIdentifier.getValue();

		ReservedKeyword keyword = getKeyword(*it);

		Expecter::expectOne(it++, { KEY_AS, KEY_OF });

		if (keyword == KEY_AS)
		{
			Expecter::expectOne(it++, { KEY_A, KEY_AN });
		}

		Token varType = *it++;
		// check for typename is one of the defined, or "Type X"

		if (varType.getType() != IDENTIFIER && varType.getType() != PROPIDENTIFIER)
		{
			throw INVALID_TYPENAME;
		}

		ReservedKeyword type = getKeyword(varType.getValue());

		switch (type)
		{
		case TYPE_INTEGER:
			scope->createVariable(varname, "integer");
			return new DeclareNode(NULL, NULL, varname, "integer");
		case TYPE_NUMBER:
			scope->createVariable(varname, "number");
			return new DeclareNode(NULL, NULL, varname, "number");
		case TYPE_CHARACTER:
			scope->createVariable(varname, "character");
			return new DeclareNode(NULL, NULL, varname, "character");
		case TYPE_BOOLEAN:
			scope->createVariable(varname, "boolean");
			return new DeclareNode(NULL, NULL, varname, "boolean");
		case TYPE_TYPE:
			break;
		default:
			throw INVALID_TYPENAME;
		}

		varType = *it++;
		if (varType.getType() != PROPIDENTIFIER)
		{
			throw INVALID_TYPENAME;
		}

		if (getKeyword(varType.getValue()) != NONE)
		{
			throw KEYWORD_AS_IDENTIFIER;
		}

		scope->createVariable(varname, "Type " + varType.getValue());
		return new DeclareNode(NULL, NULL, varname, "Type " + varType.getValue());
	}

	IEvaluatorNode *ProgramBuilder::buildAssignNode(std::vector<Token>::const_iterator& it, Scope *scope)
	{
		// Get the expression built as a node
		ExpressionNodeContainer node = ExpressionBuilder::buildExpression(it, scope);
		
		// Expecting the keyword 'to'
		Expecter::expect(it++, KEY_TO);
		
		// Get the variable name
		const Token& tk = *it++;

		if (tk.getType() != IDENTIFIER)
		{
			throw EXPECTED_IDENTIFIER_NOT_FOUND;
		}

		if (getKeyword(tk.getValue()) != NONE)
		{
			throw KEYWORD_AS_IDENTIFIER;
		}

		const std::string& vartype = scope->getType(tk.getValue());
		if (vartype != node.type)
		{
			throw TYPES_DONT_MATCH;
		}

		return new AssignNode(NULL, NULL, tk.getValue(), node.node);
	}

	IEvaluatorNode *ProgramBuilder::buildPrintNode(std::vector<Token>::const_iterator& it, Scope *scope)
	{
		ExpressionNodeContainer node = ExpressionBuilder::buildExpression(it, scope);
		if (node.type != "Type String")
		{
			node = ExpressionBuilder::buildCastNode(node, "Type String");
		}
		return new PrintNode(NULL, NULL, node.node);
	}

	IEvaluatorNode *ProgramBuilder::buildInputNode(std::vector<Token>::const_iterator& it, Scope *scope)
	{
		// Check for a / an. These are not required though.
		ReservedKeyword aOrAn = getKeyword(*it);
		if (aOrAn == KEY_A || aOrAn == KEY_AN)
		{
			++it;
		}

		const Token& typeTk = *it;
		if (typeTk.getType() != IDENTIFIER)
		{
			throw EXPECTED_IDENTIFIER_NOT_FOUND;
		}

		Token tk = *++it;
		bool requireUser = false;
		if (getKeyword(tk) == KEY_FROM)
		{
			tk = *++it;
			requireUser = true;
			if (getKeyword(tk) == KEY_THE)
			{
				tk = *++it;
			}
		}

		if (getKeyword(tk) == KEY_USER)
		{
			tk = *++it;
		}
		else if (requireUser)
		{
			throw EXPECTED_KEYWORD_NOT_FOUND;
		}

		Expecter::expect(it, KEY_AND);
		Expecter::expect(++it, KEY_STORE);

		tk = *++it;
		if (getKeyword(tk) == KEY_IT)
		{
			tk = *++it;
		}

		Expecter::expect(it, KEY_IN);

		const Token& varTk = *++it;

		if (varTk.getType() != IDENTIFIER)
		{
			throw EXPECTED_IDENTIFIER_NOT_FOUND;
		}

		std::string varname = varTk.getValue();
		std::string type = typeTk.getValue();

		++it;

		if (type == "string")
		{
			type = "Type String";
		}

		if (scope->getType(varname) != type)
		{
			throw INVALID_OPERANDS;
		}

		if (type == "boolean")
		{
			return new InputNode<bool>(NULL, NULL, varname);
		}
		else if (type == "character")
		{
			return new InputNode<char>(NULL, NULL, varname);
		}
		else if (type == "integer")
		{
			return new InputNode<long long>(NULL, NULL, varname);
		}
		else if (type == "number")
		{
			return new InputNode<double>(NULL, NULL, varname);
		}
		else if (type == "Type String")
		{
			return new InputNode<const std::string *>(NULL, NULL, varname);
		}
		throw UNSUPPORTED_OPERATION;
	}

	IEvaluatorNode *ProgramBuilder::buildConditionalNode(const std::vector<Token>& tokens,
		std::vector<Token>::const_iterator& it, Scope *scope)
	{
		ExpressionNodeContainer condition = ExpressionBuilder::buildExpression(it, scope);
		if (condition.type != "boolean")
		{
			throw NON_BOOLEAN_CONDITIONAL;
		}

		const Token& openBracket = *it;
		if (openBracket.getType() != OPENBRACKET)
		{
			throw EXPECTED_OPENBRACKET_NOT_FOUND;
		}

		if (it != tokens.end())
		{
			++it;
		}
		else
		{
			throw UNEXPECTED_END;
		}

		IEvaluatorNode *child1 = buildBody(tokens, it, scope);
		IEvaluatorNode *child2 = NULL;

		if (it != tokens.end())
		{
			++it;
		}
		
		if (it == tokens.end())
		{
			--it;
			return new ConditionalNode(NULL, NULL, condition.node, child1, NULL);
		}

		const Token& otherwiseToken = *it;
		if (getKeyword(otherwiseToken) == KEY_OTHERWISE)
		{
			const Token& decider = *++it;
			if (decider.getType() == OPENBRACKET)
			{
				child2 = buildBody(tokens, ++it, scope);
			}
			else if (getKeyword(decider) == KEY_IF)
			{
				child2 = buildConditionalNode(tokens, ++it, scope);
			}
			else
			{
				throw EXPECTED_OTHERWISE_BRANCH_NOT_FOUND;
			}
		}
		else
		{
			--it;
		}
		return new ConditionalNode(NULL, NULL, condition.node, child1, child2);
	}

	IEvaluatorNode *ProgramBuilder::buildWhileNode(const std::vector<Token>& tokens,
		std::vector<Token>::const_iterator& it, Scope *scope)
	{
		ExpressionNodeContainer condition = ExpressionBuilder::buildExpression(it, scope);
		if (condition.type != "boolean")
		{
			throw NON_BOOLEAN_CONDITIONAL;
		}

		const Token& openBracket = *it;
		if (openBracket.getType() != OPENBRACKET)
		{
			throw EXPECTED_OPENBRACKET_NOT_FOUND;
		}

		if (it != tokens.end())
		{
			++it;
		}

		IEvaluatorNode *child = buildBody(tokens, it, scope);

		return new LoopNode(NULL, NULL, condition.node, child);
	}

	IEvaluatorNode *ProgramBuilder::buildBody(const std::vector<Token>& tokens,
		std::vector<Token>::const_iterator& it, Scope *parentScope)
	{
		IEvaluatorNode *startNode = NULL;
		IEvaluatorNode *endNode = NULL;

		Scope scope(parentScope);

		bool expectSemicolon = true;

		for (; it != tokens.end(); it++)
		{
			const Token& tk = *it;

			if (tk.getType() == CLOSEBRACKET)
			{
				break;
			}

			if (tk.getType() != IDENTIFIER)
			{
				throw INVALID_START_OF_STATEMENT;
			}

			ReservedKeyword keyword = getKeyword(tk.getValue());
			IEvaluatorNode *next = NULL;

			switch (keyword)
			{
			case KEY_ASSIGN:
				next = buildAssignNode(++it, &scope);
				break;
			case KEY_DECLARE:
				next = buildDeclareNode(++it, &scope);
				break;
			case KEY_WHILE:
				next = buildWhileNode(tokens, ++it, &scope);
				expectSemicolon = false;
				break;
			case KEY_IF:
				next = buildConditionalNode(tokens, ++it, &scope);
				expectSemicolon = false;
				break;
			case KEY_PRINT:
				next = buildPrintNode(++it, &scope);
				break;
			default:
				throw INVALID_START_OF_STATEMENT;
			}

			if (startNode == NULL)
			{
				startNode = next;
				endNode = next;
			}
			else
			{
				next->setPrev(endNode);
				endNode->setNext(next);
				endNode = next;
			}

			if (it != tokens.end() && expectSemicolon)
			{
				Expecter::expectSemicolon(it);
			}
		}

		return startNode;
	}

}