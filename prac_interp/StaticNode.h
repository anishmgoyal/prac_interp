#ifndef StaticNode_H
#define StaticNode_H

#include "Main.h"

#include <string>

#include "IExpressionNode.h"
#include "Scope.h"

namespace Prac
{

	const std::string typeInteger = "integer";
	const std::string typeNumber = "number";
	const std::string typeCharacter = "character";
	const std::string typeBoolean = "boolean";
	const std::string typeString = "Type String";

	template<class T> class StaticNode : public IExpressionNode
	{

	private:
		const T m_constant;

	public:
		StaticNode(const T constant) : m_constant(constant) {}

		~StaticNode() { }

		Data *evaluate(Scope *scope);
	};

	Data *StaticNode<long long>::evaluate(Scope *scope);
	Data *StaticNode<std::map<std::string, DataUnion>>::evaluate(Scope *scope);
	Data *StaticNode<double>::evaluate(Scope *scope);
	Data *StaticNode<char>::evaluate(Scope *scope);
	Data *StaticNode<bool>::evaluate(Scope *scope);
	Data *StaticNode<std::string>::evaluate(Scope *scope);

}

#endif