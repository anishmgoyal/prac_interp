#ifndef InputNode_H
#define InputNode_H

#include "IEvaluatorNode.h"
#include "Scope.h"

namespace Prac
{

	template <class T> class InputNode : public IEvaluatorNode
	{
		
	private:
		std::string m_varname;

	public:
		InputNode(IEvaluatorNode *prev, IEvaluatorNode *next,
			const std::string& varname) : IEvaluatorNode(prev, next), m_varname(varname) {}

		void evaluate(Scope *scope) const;

	};

}

#endif