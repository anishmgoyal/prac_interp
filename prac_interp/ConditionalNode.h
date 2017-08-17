#ifndef ConditionalNode_H
#define ConditionalNode_H

#include "Main.h"

#include "IEvaluatorNode.h"
#include "IExpressionNode.h"
#include "Scope.h"

namespace Prac
{

	class ConditionalNode : public IEvaluatorNode
	{

	private:
		IExpressionNode *m_condition;
		IEvaluatorNode *m_child1;
		IEvaluatorNode *m_child2;

	public:
		ConditionalNode(IEvaluatorNode *prev, IEvaluatorNode *next, 
			IExpressionNode *condition, IEvaluatorNode *child1, IEvaluatorNode *child2)
			: IEvaluatorNode(prev, next), m_condition(condition), m_child1(child1), m_child2(child2) {}

		~ConditionalNode()
		{
			delete m_condition;
			delete m_child1;
			if (m_child2 != NULL)
			{
				delete m_child2;
			}
		}

		void evaluate(Scope *scope) const;

	};

}

#endif