#include "Main.h"

#include "LoopNode.h"

namespace Prac
{
	void runIEvaluatorNodeIteration(Scope *scope, const IEvaluatorNode *node)
	{
		do
		{
			node->evaluate(scope);
		} while ((node = node->getNext()) != NULL);
	}

	void LoopNode::evaluate(Scope *scope) const
	{
		Data *condition = m_condition->evaluate(scope);
		if (condition->choice != dcBool)
		{
			throw CONDITION_IS_NOT_BOOLEAN;
		}

		Scope smallerScope (scope);

		while (condition->data.asBoolean == true)
		{
			destroyData(condition);
			runIEvaluatorNodeIteration(&smallerScope, m_child);

			condition = m_condition->evaluate(scope);
			if (condition->data.asBoolean == true)
			{
				smallerScope.reset();
			}
		}

		destroyData(condition);
	}
}