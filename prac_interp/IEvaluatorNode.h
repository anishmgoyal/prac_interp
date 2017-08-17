#ifndef IEvaluatorNode_H
#define IEvaluatorNode_H

#include "Main.h"

#include "Scope.h"

namespace Prac
{
	enum RuntimeExceptions
	{
		CONDITION_IS_NOT_BOOLEAN,
	};

	class IEvaluatorNode
	{
		
	private:
		IEvaluatorNode *m_prev;
		IEvaluatorNode *m_next;

	public:
		IEvaluatorNode(IEvaluatorNode *prev, IEvaluatorNode *next)
			: m_prev(prev), m_next(next) {}

		virtual ~IEvaluatorNode()
		{
			if (m_next != NULL)
			{
				delete m_next;
			}
		}

		virtual void evaluate(Scope *scope) const = 0;

		void setPrev(IEvaluatorNode *prev);
		const IEvaluatorNode *getPrev() const;

		void setNext(IEvaluatorNode *next);
		const IEvaluatorNode *getNext() const;

	};

}

#endif