#ifndef DeclareNode_H
#define DeclareNode_H

#include "Main.h"

#include <string>

#include "IEvaluatorNode.h"
#include "Scope.h"

namespace Prac
{

	class DeclareNode : public IEvaluatorNode
	{

	private:
		std::string m_varname;
		std::string m_vartype;

	public:
		DeclareNode(IEvaluatorNode *prev, IEvaluatorNode *next,
			std::string varname, std::string vartype) 
			: IEvaluatorNode(prev, next), m_varname(varname), m_vartype(vartype) {}
		
		void evaluate(Scope *scope) const;

	};

}

#endif