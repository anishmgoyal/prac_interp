#ifndef PrintNode_H
#define PrintNode_H

#include "Main.h"

#include "IEvaluatorNode.h"
#include "IExpressionNode.h"

namespace Prac
{

	class PrintNode : public IEvaluatorNode
	{

	private:
		IExpressionNode *m_child;

	public:
		PrintNode(IEvaluatorNode *prev, IEvaluatorNode *next, IExpressionNode *child)
			: IEvaluatorNode(prev, next), m_child(child) {}

		~PrintNode()
		{
			delete m_child;
		}

		void evaluate(Scope *scope) const;

	};

}

#endif