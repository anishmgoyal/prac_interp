#ifndef AssignNode_H
#define AssignNode_H

#include "Main.h"

#include <string>

#include "IEvaluatorNode.h"
#include "IExpressionNode.h"

namespace Prac
{

	class AssignNode : public IEvaluatorNode
	{

	private:
		std::string m_varname;
		IExpressionNode *m_child;

	public:
		AssignNode(IEvaluatorNode *prev, IEvaluatorNode *next, 
			const std::string& varname, IExpressionNode *child) 
			: IEvaluatorNode(prev, next), m_varname(varname), m_child(child) {}

		~AssignNode()
		{
			delete m_child;
		}

		void evaluate(Scope *scope) const;

	};

}

#endif