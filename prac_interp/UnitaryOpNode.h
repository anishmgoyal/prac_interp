#ifndef UnitaryOpNode_H
#define UnitaryOpNode_H

#include "Main.h"

#include "IExpressionNode.h"

namespace Prac
{

	enum UnitaryOp
	{
		OP_NOT,
		OP_COMPLEMENT,
		OP_NEGATIVE,
	};

	template <class T, UnitaryOp OP> class UnitaryOpNode : public IExpressionNode
	{
		
	private:
		IExpressionNode *m_child;

	public:
		UnitaryOpNode(IExpressionNode *child) : m_child(child) {}

		~UnitaryOpNode()
		{
			delete m_child;
		}

		Data *evaluate(Scope *scope)
		{
			Data *d = m_child->evaluate(scope);
			T value = WrapUtil::unwrapValue<T>(d);

			T output = UnitaryUtil<T, OP>::applyOperation(value);
			WrapUtil::wrapValue<T>(d, output);

			return d;
		}
	};

	template <class T, UnitaryOp OP> class UnitaryUtil
	{
	public:
		static T applyOperation(T value);
	};


	bool UnitaryUtil<bool, OP_NOT>::applyOperation(bool value);

	template <class T> class UnitaryUtil<T, OP_COMPLEMENT>
	{
	public:
		static T applyOperation(T value)
		{
			return ~value;
		}
	};

	template <class T> class UnitaryUtil<T, OP_NEGATIVE>
	{
	public:
		static T applyOperation(T value)
		{
			return -value;
		}
	};

}

#endif