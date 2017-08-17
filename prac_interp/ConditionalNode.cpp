#include "Main.h"

#include "ConditionalNode.h"

namespace Prac
{
	void runIEvaluatorNode(Scope *parentScope, const IEvaluatorNode *node)
	{
		Scope scope (parentScope);
		do
		{
			node->evaluate(&scope);
		} while ((node = node->getNext()) != NULL);
	}

	void ConditionalNode::evaluate(Scope *scope) const
	{
		Data *condition = m_condition->evaluate(scope);
		if (condition->choice != dcBool)
		{
			throw CONDITION_IS_NOT_BOOLEAN;
		}

		if (condition->data.asBoolean == true)
		{
			runIEvaluatorNode(scope, m_child1);
		}
		else if (m_child2 != NULL)
		{
			runIEvaluatorNode(scope, m_child2);
		}

		destroyData(condition);
	}

}