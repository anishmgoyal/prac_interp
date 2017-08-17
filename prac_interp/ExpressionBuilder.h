#ifndef EXPRESSION_BUILDER_H
#define EXPRESSION_BUILDER_H

#include "Main.h"

#include <unordered_set>
#include <vector>

#include "ArithmeticOpNode.h"
#include "BooleanOpNode.h"
#include "IExpressionNode.h"
#include "UnitaryOpNode.h"
#include "Token.h"

namespace Prac
{

	struct ExpressionNodeContainer
	{
		IExpressionNode *node;
		std::string type;
	};

	class ExpressionBuilder
	{

	private:

		template <ArithmeticOp OP> static ExpressionNodeContainer
			buildArithmeticOpNode(
			ExpressionNodeContainer *left, ExpressionNodeContainer *right);

		template <BooleanOp OP> static ExpressionNodeContainer
			buildBooleanOpNode(
			ExpressionNodeContainer *left, ExpressionNodeContainer *right,
			const std::string& widerType);

	public:
		static ExpressionNodeContainer buildExpression(
			std::vector<Token>::const_iterator& it, Scope *scope);
		static ExpressionNodeContainer buildExpressionLogicAnd(
			std::vector<Token>::const_iterator& it, Scope *scope);
		static ExpressionNodeContainer buildExpressionLogicEq(
			std::vector<Token>::const_iterator& it, Scope *scope);
		static ExpressionNodeContainer buildExpressionNumericComp(
			std::vector<Token>::const_iterator& it, Scope *scope);
		static ExpressionNodeContainer buildExpressionArithOp(
			std::vector<Token>::const_iterator& it, Scope *scope,
			const std::vector<std::unordered_set<TokenType>>& operatorLists,
			unsigned int operatorListOffset);
		static ExpressionNodeContainer buildExpressionSingle(
			std::vector<Token>::const_iterator& it, Scope *scope);
		static ExpressionNodeContainer buildExpressionAtomic(
			std::vector<Token>::const_iterator& it, Scope *scope);

		static ExpressionNodeContainer buildCastNode(
			ExpressionNodeContainer source, const std::string& targetType);
	};

	template <ArithmeticOp OP> ExpressionNodeContainer
		ExpressionBuilder::buildArithmeticOpNode(
		ExpressionNodeContainer *left, ExpressionNodeContainer *right)
	{
		IExpressionNode *node = NULL;

		if (!TypeCheck::areCompatibleArithmetic(left->type, right->type, OP))
		{
			throw INVALID_OPERANDS;
		}

		const std::string& widerType = TypeCheck::getWider(left->type, right->type);

		*left = buildCastNode(*left, widerType);
		*right = buildCastNode(*right, widerType);

		if (widerType == "character")
		{
			node = new ArithmeticOpNode<char, OP>(left->node, right->node);
			return ExpressionNodeContainer{ node, widerType };
		}
		else if (widerType == "integer")
		{
			node = new ArithmeticOpNode<long long, OP>(left->node, right->node);
			return ExpressionNodeContainer{ node, widerType };
		}
		else if (widerType == "number")
		{
			switch (OP)
			{
			case OP_ADD:
				node = new ArithmeticOpNode<double, OP_ADD>(left->node, right->node);
				break;
			case OP_SUBTRACT:
				node = new ArithmeticOpNode<double, OP_SUBTRACT>(left->node, right->node);
				break;
			case OP_MULTIPLY:
				node = new ArithmeticOpNode<double, OP_MULTIPLY>(left->node, right->node);
				break;
			case OP_DIVIDE:
				node = new ArithmeticOpNode<double, OP_DIVIDE>(left->node, right->node);
				break;
			default:
				throw INVALID_OPERANDS;
			}
			return ExpressionNodeContainer{ node, widerType };
		}
		else if (widerType == "Type String" && OP == OP_ADD)
		{
			node = new ArithmeticOpNode<const std::string *, OP_ADD>(left->node, right->node);
			return ExpressionNodeContainer{ node, widerType };
		}
		throw INVALID_OPERANDS;
	}

	template <BooleanOp OP> ExpressionNodeContainer
		ExpressionBuilder::buildBooleanOpNode(
		ExpressionNodeContainer *left, ExpressionNodeContainer *right,
		const std::string& widerType)
	{
		IExpressionNode *node = NULL;
		if (widerType == "character")
		{
			node = new BooleanOpNode<char, OP>(left->node, right->node);
			return ExpressionNodeContainer{ node, "boolean" };
		}
		else if (widerType == "integer")
		{
			node = new BooleanOpNode<long long, OP>(left->node, right->node);
			return ExpressionNodeContainer{ node, "boolean" };
		}
		else if (widerType == "number")
		{
			node = new BooleanOpNode<double, OP>(left->node, right->node);
			return ExpressionNodeContainer{ node, "boolean" };
		}
		throw INVALID_OPERANDS;
	}

}

#endif