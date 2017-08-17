#ifndef CastNode_H
#define CastNode_H

#include "Main.h"

#include <string>

#include "IExpressionNode.h"

namespace Prac
{

	template <class FROM, class TO> class CastNode : public IExpressionNode
	{

	private:
		IExpressionNode *m_child;

	public:
		CastNode<FROM, TO>(IExpressionNode *child) : m_child(child) {}

		~CastNode()
		{
			delete m_child;
		}

		Data *evaluate(Scope *scope)
		{
			Data *d = m_child->evaluate(scope);
			if (d == NULL)
			{
				return NULL;
			}
			TO value = CastUtil<FROM, TO>::castValue(d);
			WrapUtil::wrapValue<TO>(d, value);
			return d;
		}
	};

	template<class FROM, class TO> class CastUtil
	{
	public:
		static TO castValue(Data *d);
	};

	const std::string *CastUtil<long long, const std::string *>::castValue(Data *d);
	const std::string *CastUtil<double, const std::string*>::castValue(Data *d);
	const std::string *CastUtil<char, const std::string *>::castValue(Data *d);
	const std::string *CastUtil<bool, const std::string *>::castValue(Data *d);

	template <class TO> class CastUtil<long long, TO>
	{
	public:
		static TO castValue(Data *d)
		{
			return (TO)d->data.asInteger;
		}
	};

	template <class TO> class CastUtil<double, TO>
	{
	public:
		static TO castValue(Data *d)
		{
			return (TO)d->data.asNumber;
		}
	};

	template <class TO> class CastUtil<char, TO>
	{
	public:
		static TO castValue(Data *d)
		{
			return (TO)d->data.asCharacter;
		}
	};

}

#endif