#ifndef Symbol_H
#define Symbol_H

#include "Main.h"

#include <string>
#include "Data.h"

namespace Prac
{

	const int SYM_UNDEFINED = 1;

	class Symbol
	{

	private:
		std::string m_type;
		Data *m_data;
		int m_flags;

	public:
		Symbol(std::string type);
		~Symbol()
		{
			destroyData(m_data);
		}
	
		const std::string& getType();

		Data *getData();
		void setData(Data *data);

		bool isUndefined();
	};

}

#endif