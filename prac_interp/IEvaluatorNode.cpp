#include "Main.h"

#include "IEvaluatorNode.h"

namespace Prac
{

	const IEvaluatorNode *IEvaluatorNode::getPrev() const
	{
		return m_prev;
	}

	void IEvaluatorNode::setPrev(IEvaluatorNode *prev)
	{
		m_prev = prev;
	}
	
	const IEvaluatorNode *IEvaluatorNode::getNext() const
	{
		return m_next;
	}

	void IEvaluatorNode::setNext(IEvaluatorNode *next)
	{
		m_next = next;
	}
}