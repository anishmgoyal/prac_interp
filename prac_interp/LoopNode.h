#ifndef LoopNode_H
#define LoopNode_H

#include "Main.h"

#include "IEvaluatorNode.h"
#include "IExpressionNode.h"
#include "Scope.h"
#include <iostream>

namespace Prac
{

	class LoopNode : public IEvaluatorNode
	{

	private:
		IExpressionNode *m_condition;
		IEvaluatorNode *m_child;

	public:
		LoopNode(IEvaluatorNode *prev, IEvaluatorNode *next,
			IExpressionNode *condition, IEvaluatorNode *child)
			: IEvaluatorNode(prev, next), m_condition(condition), m_child(child) {}

		~LoopNode()
		{
			delete m_condition;
			delete m_child;
		}

		void evaluate(Scope *scope) const;

	};

}

#endif