#ifndef ArithmeticOpNode_H
#define ArithmeticOpNode_H

#include "Main.h"

#include "IExpressionNode.h"
#include "WrapUtil.h"

namespace Prac
{
	enum ArithmeticOp
	{
		OP_ADD,
		OP_SUBTRACT,
		OP_MULTIPLY,
		OP_DIVIDE,
		OP_MODULUS,
		OP_BITWISEAND,
		OP_BITWISEOR,
		OP_BITWISEXOR,
		OP_BITWISERIGHT,
		OP_BITWISELEFT,
	};

	template <class T, ArithmeticOp OP> class ArithmeticOpNode : public IExpressionNode
	{

	private:
		IExpressionNode *m_lterm;
		IExpressionNode *m_rterm;

	public:
		ArithmeticOpNode(IExpressionNode *lterm, IExpressionNode *rterm)
			: m_lterm(lterm), m_rterm(rterm) { }

		~ArithmeticOpNode()
		{
			delete m_lterm;
			delete m_rterm;
		}

		Data *evaluate(Scope *scope)
		{
			Data *ldata = m_lterm->evaluate(scope);
			Data *rdata = m_rterm->evaluate(scope);

			T lterm = WrapUtil::unwrapValue<T>(ldata);
			T rterm = WrapUtil::unwrapValue<T>(rdata);

			T output = ArithmeticUtil<T, OP>::applyOperation(lterm, rterm);
			WrapUtil::wrapValue<T>(ldata, output);

			destroyData(rdata);
			return ldata;
		}
	};

	template<class T, ArithmeticOp OP> class ArithmeticUtil
	{
	public:
		static T applyOperation(T lterm, T rterm);
	};

	const std::string *ArithmeticUtil<const std::string *, OP_ADD>::applyOperation(
		const std::string *lterm, const std::string *rterm);

	template<class T> class ArithmeticUtil<T, OP_ADD>
	{
	public:
		static T applyOperation(T lterm, T rterm)
		{
			return lterm + rterm;
		}
	};

	template<class T> class ArithmeticUtil<T, OP_SUBTRACT>
	{
	public:
		static T applyOperation(T lterm, T rterm)
		{
			return lterm - rterm;
		}
	};

	template<class T> class ArithmeticUtil<T, OP_MULTIPLY>
	{
	public:
		static T applyOperation(T lterm, T rterm)
		{
			return lterm * rterm;
		}
	};

	template<class T> class ArithmeticUtil<T, OP_DIVIDE>
	{
	public:
		static T applyOperation(T lterm, T rterm)
		{
			return lterm / rterm;
		}
	};

	template<class T> class ArithmeticUtil<T, OP_MODULUS>
	{
	public:
		static T applyOperation(T lterm, T rterm)
		{
			return lterm % rterm;
		}
	};

	template<class T> class ArithmeticUtil<T, OP_BITWISEAND>
	{
	public:
		static T applyOperation(T lterm, T rterm)
		{
			return lterm & rterm;
		}
	};

	template<class T> class ArithmeticUtil<T, OP_BITWISEOR>
	{
	public:
		static T applyOperation(T lterm, T rterm)
		{
			return lterm | rterm;
		}
	};

	template<class T> class ArithmeticUtil<T, OP_BITWISEXOR>
	{
	public:
		static T applyOperation(T lterm, T rterm)
		{
			return lterm ^ rterm;
		}
	};

	template<class T> class ArithmeticUtil<T, OP_BITWISERIGHT>
	{
	public:
		static T applyOperation(T lterm, T rterm)
		{
			return lterm >> rterm;
		}
	};

	template<class T> class ArithmeticUtil<T, OP_BITWISELEFT>
	{
	public:
		static T applyOperation(T lterm, T rterm)
		{
			return lterm << rterm;
		}
	};
}

#endif