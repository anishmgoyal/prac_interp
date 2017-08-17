#include "Main.h"

#include "ExpressionBuilder.h"

#include <sstream>

#include "ArithmeticOpNode.h"
#include "BooleanOpNode.h"
#include "BuildConstants.h"
#include "CastNode.h"
#include "Expecter.h"
#include "UnitaryOpNode.h"
#include "StaticNode.h"
#include "TypeCheck.h"
#include "VariableNode.h"

namespace Prac
{

	std::vector<std::unordered_set<TokenType>> operatorLists
	{
		{ PLUS, MINUS },
		{ MUL, DIV, MOD },
		{ BITWISERIGHT, BITWISELEFT },
		{ BITWISEAND, BITWISEOR, BITWISEXOR }
	};

	ExpressionNodeContainer ExpressionBuilder::buildExpression(
		std::vector<Token>::const_iterator& it, Scope *scope)
	{
		ExpressionNodeContainer left = buildExpressionLogicAnd(it, scope);

		const Token& tk = *it;
		if (getKeyword(tk) == KEY_OR)
		{
			ExpressionNodeContainer right = buildExpression(++it, scope);
			if (left.type != "boolean" || right.type != "boolean")
			{
				throw INVALID_OPERANDS;
			}

			BooleanOpNode<bool, OP_OR> *newNode = new BooleanOpNode<bool, OP_OR>(left.node, right.node);
			return ExpressionNodeContainer { newNode, "boolean" };
		}

		return left;
	}

	ExpressionNodeContainer ExpressionBuilder::buildExpressionLogicAnd(
		std::vector<Token>::const_iterator& it, Scope *scope)
	{
		ExpressionNodeContainer left = buildExpressionLogicEq(it, scope);

		const Token& tk = *it;
		if (getKeyword(tk) == KEY_AND)
		{
			ExpressionNodeContainer right = buildExpressionLogicAnd(++it, scope);
			if (left.type != "boolean" || right.type != "boolean")
			{
				throw INVALID_OPERANDS;
			}

			BooleanOpNode<bool, OP_AND> *newNode = new BooleanOpNode<bool, OP_AND>(left.node, right.node);
			return ExpressionNodeContainer { newNode, "boolean" };
		}

		return left;
	}

	ExpressionNodeContainer ExpressionBuilder::buildExpressionLogicEq(
		std::vector<Token>::const_iterator& it, Scope *scope)
	{
		ExpressionNodeContainer left = buildExpressionNumericComp(it, scope);

		const Token& tk = *it;
		ReservedKeyword keyword = getKeyword(tk);
		if (keyword != KEY_EQUALS && keyword != KEY_DOESNT)
		{
			return left;
		}

		if (keyword == KEY_DOESNT)
		{
			Expecter::expect(++it, KEY_EQUAL);
		}

		ExpressionNodeContainer right = buildExpressionLogicEq(++it, scope);

		if (!TypeCheck::areCompatibleEquality(left.type, right.type))
		{
			throw INVALID_OPERANDS;
		}

		const std::string& widerType = TypeCheck::getWider(left.type, right.type);

		left = buildCastNode(left, widerType);
		right = buildCastNode(right, widerType);

		if (keyword == KEY_EQUALS)
		{
			IExpressionNode *node = NULL;
			if (widerType == "boolean")
			{
				node = new BooleanOpNode<bool, OP_EQUALS>(left.node, right.node);
			}
			else if (widerType == "character")
			{
				node = new BooleanOpNode<char, OP_EQUALS>(left.node, right.node);
			}
			else if (widerType == "integer")
			{
				node = new BooleanOpNode<long long, OP_EQUALS>(left.node, right.node);
			}
			else if (widerType == "number")
			{
				node = new BooleanOpNode<double, OP_EQUALS>(left.node, right.node);
			}
			else if (widerType == "Type String")
			{
				node = new BooleanOpNode<const std::string *, OP_EQUALS>(left.node, right.node);
			}
			return ExpressionNodeContainer{ node, "boolean" };
		}

		if (keyword == KEY_DOESNT)
		{

			IExpressionNode *node = NULL;
			if (widerType == "boolean")
			{
				node = new BooleanOpNode<bool, OP_NE>(left.node, right.node);
			}
			else if (widerType == "character")
			{
				node = new BooleanOpNode<char, OP_NE>(left.node, right.node);
			}
			else if (widerType == "integer")
			{
				node = new BooleanOpNode<long long, OP_NE>(left.node, right.node);
			}
			else if (widerType == "number")
			{
				node = new BooleanOpNode<double, OP_NE>(left.node, right.node);
			}
			else if (widerType == "Type String")
			{
				node = new BooleanOpNode<const std::string *, OP_NE>(left.node, right.node);
			}
			return ExpressionNodeContainer{ node, "boolean" };
		}
		throw INVALID_OPERANDS;
	}

	ExpressionNodeContainer ExpressionBuilder::buildExpressionNumericComp(
		std::vector<Token>::const_iterator& it, Scope *scope)
	{
		ExpressionNodeContainer left = buildExpressionArithOp(it, scope, operatorLists, 0);

		const Token& op = *it;
		
		if (op.getType() != GE && op.getType() != GT && op.getType() != LE && op.getType() != LT)
		{
			return left;
		}

		ExpressionNodeContainer right = buildExpressionNumericComp(++it, scope);

		if (!TypeCheck::areCompatibleComparison(left.type, right.type))
		{
			throw INVALID_OPERANDS;
		}

		const std::string& widerType = TypeCheck::getWider(left.type, right.type);

		left = buildCastNode(left, widerType);
		right = buildCastNode(right, widerType);

		if (op.getType() == GT)
		{
			return buildBooleanOpNode<OP_GT>(&left, &right, widerType);
		}
		else if (op.getType() == GE)
		{
			return buildBooleanOpNode<OP_GE>(&left, &right, widerType);
		}
		else if (op.getType() == LT)
		{
			return buildBooleanOpNode<OP_LT>(&left, &right, widerType);
		}
		else
		{
			return buildBooleanOpNode<OP_LE>(&left, &right, widerType);
		}

		throw INVALID_OPERANDS;
	}

	ExpressionNodeContainer ExpressionBuilder::buildExpressionArithOp(
		std::vector<Token>::const_iterator& it, Scope *scope,
		const std::vector<std::unordered_set<TokenType>>& operatorLists,
		unsigned int operatorListOffset)
	{
		ExpressionNodeContainer left;
		if (operatorListOffset < operatorLists.size() - 1)
		{
			left = buildExpressionArithOp(it, scope, operatorLists, operatorListOffset + 1);
		}
		else
		{
			left = buildExpressionSingle(it, scope);
		}

		Token op = *it;

		bool isCurrentOp = false;
		const std::unordered_set<TokenType>& opList = operatorLists[operatorListOffset];
		auto opIt = opList.find(op.getType());
		if (opIt != opList.end())
		{
			isCurrentOp = true;
		}

		while (isCurrentOp)
		{

			ExpressionNodeContainer right;
			if (operatorListOffset < operatorLists.size() - 1)
			{
				right = buildExpressionArithOp(++it, scope, operatorLists, operatorListOffset + 1);
			}
			else
			{
				right = buildExpressionSingle(++it, scope);
			}

			switch (op.getType())
			{
			case PLUS:
				left = buildArithmeticOpNode<OP_ADD>(&left, &right);
				break;
			case MINUS:
				left = buildArithmeticOpNode<OP_SUBTRACT>(&left, &right);
				break;
			case MUL:
				left = buildArithmeticOpNode<OP_MULTIPLY>(&left, &right);
				break;
			case DIV:
				left = buildArithmeticOpNode<OP_DIVIDE>(&left, &right);
				break;
			case MOD:
				left = buildArithmeticOpNode<OP_MODULUS>(&left, &right);
				break;
			case BITWISEAND:
				left = buildArithmeticOpNode<OP_BITWISEAND>(&left, &right);
				break;
			case BITWISELEFT:
				left = buildArithmeticOpNode<OP_BITWISELEFT>(&left, &right);
				break;
			case BITWISEOR:
				left = buildArithmeticOpNode<OP_BITWISEOR>(&left, &right);
				break;
			case BITWISERIGHT:
				left = buildArithmeticOpNode<OP_BITWISERIGHT>(&left, &right);
				break;
			case BITWISEXOR:
				left = buildArithmeticOpNode<OP_BITWISEXOR>(&left, &right);
				break;
			default:
				throw INVALID_OPERANDS;
			}

			op = *it;
			isCurrentOp = false;
			for (auto it2 = opList.begin(); it2 != opList.end(); ++it2)
			{
				if (*it2 == op.getType())
				{
					isCurrentOp = true;
					break;
				}
			}
		}
		return left;
	}

	ExpressionNodeContainer ExpressionBuilder::buildExpressionSingle(
		std::vector<Token>::const_iterator& it, Scope *scope)
	{
		Token tk = *it;
		if (tk.getType() == MINUS)
		{
			ExpressionNodeContainer child = buildExpressionSingle(++it, scope);
			if (child.type == "character")
			{
				IExpressionNode *node = new UnitaryOpNode<char, OP_NEGATIVE>(child.node);
				return ExpressionNodeContainer{ node, "character" };
			}
			else if (child.type == "integer")
			{
				IExpressionNode *node = new UnitaryOpNode<long long, OP_NEGATIVE>(child.node);
				return ExpressionNodeContainer{ node, "integer" };
			}
			else if (child.type == "number")
			{
				IExpressionNode *node = new UnitaryOpNode<double, OP_NEGATIVE>(child.node);
				return ExpressionNodeContainer{ node, "number" };
			}
			throw INVALID_OPERANDS;
		}
		else if (getKeyword(tk) == KEY_NOT)
		{
			ExpressionNodeContainer child = buildExpressionSingle(++it, scope);
			if (child.type == "boolean")
			{
				IExpressionNode *node = new UnitaryOpNode<bool, OP_NOT>(child.node);
				return ExpressionNodeContainer{ node, "boolean" };
			}
			else if (child.type == "character")
			{
				IExpressionNode *node = new UnitaryOpNode<char, OP_COMPLEMENT>(child.node);
				return ExpressionNodeContainer{ node, "character" };
			}
			else if (child.type == "integer")
			{
				IExpressionNode *node = new UnitaryOpNode<long long, OP_COMPLEMENT>(child.node);
				return ExpressionNodeContainer{ node, "integer" };
			}
			throw INVALID_OPERANDS;
		}
		return buildExpressionAtomic(it, scope);
	}

	ExpressionNodeContainer ExpressionBuilder::buildExpressionAtomic(
		std::vector<Token>::const_iterator& it, Scope *scope)
	{
		const Token& tk = *it;
		const std::string& tokenValue = tk.getValue();

		IExpressionNode *node = NULL;

		ExpressionNodeContainer child;
		std::stringstream ss;
		long long val;

		const ReservedKeyword keywordType = getKeyword(tk);
		switch (keywordType)
		{
		case KEY_FALSE:
			node = new StaticNode<bool>(false);
			++it;
			return ExpressionNodeContainer{ node, "boolean" };
		case KEY_NEWLINE:
			node = new StaticNode<std::string>("\n");
			++it;
			return ExpressionNodeContainer{ node, "Type String" };
		case KEY_TRUE:
			node = new StaticNode<bool>(true);
			++it;
			return ExpressionNodeContainer{ node, "boolean" };
		case NONE:
			break;
		default:
			throw KEYWORD_AS_IDENTIFIER;
		}

		switch (tk.getType())
		{
		case OPENPARENTH:
			child = buildExpression(++it, scope);
			if (it->getType() != CLOSEPARENTH)
			{
				throw EXPECTED_CLOSEPARENTH_NOT_FOUND;
			}
			++it;
			return child;

		case STRING:
			for (unsigned int i = 0; i < tokenValue.size(); i++)
			{
				if (tokenValue[i] != '\\')
				{
					ss << tokenValue[i];
				}
				else
				{
					if (i == tokenValue.size() - 1)
					{
						throw INVALID_ESCAPE_CHAR_USAGE;
					}

					switch (tokenValue[i + 1])
					{
					case '"':
					case '\\':
						ss << tokenValue[i + 1];
						i++;
						break;
					case 'n':
						ss << '\n';
						i++;
						break;
					case 't':
						ss << '\t';
						i++;
						break;
					default:
						throw INVALID_ESCAPE_CHAR_USAGE;
					}
				}
			}
			node = new StaticNode<std::string>(ss.str());
			++it;
			return ExpressionNodeContainer{ node, "Type String" };

		case INTEGER:
			val = std::stoll(tk.getValue());
			node = new StaticNode<long long>(val);
			++it;
			return ExpressionNodeContainer{ node, "integer" };

		case IDENTIFIER:
			if (getKeyword(tokenValue) != NONE)
			{
				throw KEYWORD_AS_IDENTIFIER;
			}
			const std::string& vartype = scope->getType(tokenValue);
			node = new VariableNode(tokenValue);
			++it;
			return ExpressionNodeContainer{ node, vartype };
		}
		throw UNSUPPORTED_OPERATION;
	}
	
	ExpressionNodeContainer ExpressionBuilder::buildCastNode(
		ExpressionNodeContainer source, const std::string& targetType)
	{
		if (source.type == targetType)
		{
			return source;
		}

		if (source.type == "boolean")
		{
			if (targetType == "Type String")
			{
				CastNode<bool, const std::string *> *caster = new
					CastNode<bool, const std::string *>(source.node);
				return ExpressionNodeContainer{ caster, targetType };
			}
		}
		else if (source.type == "character")
		{
			if (targetType == "integer")
			{
				CastNode<char, long long> *caster = new
					CastNode<char, long long>(source.node);
				return ExpressionNodeContainer{ caster, targetType };
			}
			else if (targetType == "number")
			{
				CastNode<char, double> *caster = new
					CastNode<char, double>(source.node);
				return ExpressionNodeContainer{ caster, targetType };
			}
			else if (targetType == "Type String")
			{
				CastNode<char, const std::string *> *caster = new
					CastNode<char, const std::string *>(source.node);
				return ExpressionNodeContainer{ caster, targetType };
			}
		}
		else if (source.type == "integer")
		{
			if (targetType == "number")
			{
				CastNode<long long, double> *caster = new
					CastNode<long long, double>(source.node);
				return ExpressionNodeContainer{ caster, targetType };
			}
			else if (targetType == "Type String")
			{
				CastNode<long long, const std::string *> *caster = new
					CastNode<long long, const std::string *>(source.node);
				return ExpressionNodeContainer{ caster, targetType };
			}
		}
		else if (source.type == "number")
		{
			if (targetType == "Type String")
			{
				CastNode<double, const std::string *> *caster = new
					CastNode<double, const std::string *>(source.node);
				return ExpressionNodeContainer{ caster, targetType };
			}
		}

		throw INVALID_OPERANDS;
	}

}