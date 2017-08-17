#ifndef BooleanOpNode_H
#define BooleanOpNode_H

#include "Main.h"

#include "IExpressionNode.h"

namespace Prac
{

	enum BooleanOp
	{
		OP_GT, 
		OP_GE,
		OP_LT,
		OP_LE,
		OP_EQUALS,
		OP_NE,
		OP_AND,
		OP_OR,
	};

	template <class T, BooleanOp OP> class BooleanOpNode : public IExpressionNode
	{
		
	private:
		IExpressionNode *m_lterm;
		IExpressionNode *m_rterm;

		bool applyOperation(T lterm, T rterm);

	public:
		BooleanOpNode(IExpressionNode *lterm, IExpressionNode *rterm)
			: m_lterm(lterm), m_rterm(rterm) {}

		~BooleanOpNode()
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

			bool output = BooleanUtil<T, OP>::applyOperation(lterm, rterm);
			setDataBool(ldata, output);

			destroyData(rdata);
			return ldata;
		}

	};
	
	template <class T, BooleanOp OP> class BooleanUtil
	{
	public:
		static bool applyOperation(T lterm, T rterm);
	};

	bool BooleanUtil<const std::string *, OP_EQUALS>::
		applyOperation(const std::string *lterm, const std::string *rterm);
	bool BooleanUtil<bool, OP_AND>::applyOperation(bool lterm, bool rterm);
	bool BooleanUtil<bool, OP_OR>::applyOperation(bool lterm, bool rterm);

	template <class T> class BooleanUtil<T, OP_GT>
	{
	public:
		static bool applyOperation(T lterm, T rterm)
		{
			return lterm > rterm;
		}
	};

	template <class T> class BooleanUtil<T, OP_GE>
	{
	public:
		static bool applyOperation(T lterm, T rterm)
		{
			return lterm >= rterm;
		}
	};

	template <class T> class BooleanUtil<T, OP_LT>
	{
	public:
		static bool applyOperation(T lterm, T rterm)
		{
			return lterm < rterm;
		}
	};

	template <class T> class BooleanUtil<T, OP_LE>
	{
	public:
		static bool applyOperation(T lterm, T rterm)
		{
			return lterm <= rterm;
		}
	};

	template <class T> class BooleanUtil<T, OP_EQUALS>
	{
	public:
		static bool applyOperation(T lterm, T rterm)
		{
			return lterm == rterm;
		}
	};

	template <class T> class BooleanUtil<T, OP_NE>
	{
	public:
		static bool applyOperation(T lterm, T rterm)
		{
			return lterm != rterm;
		}
	};

}

#endif