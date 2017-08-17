#include "InputNode.h"

#include "Main.h"

#include <algorithm>
#include <iostream>

namespace Prac
{

	void InputNode<char>::evaluate(Scope *scope) const
	{
		char c;
		std::cin.get(c);

		if (c != '\n')
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		
		Data *d = new Data();
		setDataChar(d, c);
		scope->setValue(m_varname, d);
	}

	void InputNode<long long>::evaluate(Scope *scope) const
	{
		long long i;
		while (!(std::cin >> i))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter a valid integer: " << std::flush;
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		Data *d = new Data();
		setDataInt(d, i);
		scope->setValue(m_varname, d);
	}

	void InputNode<bool>::evaluate(Scope *scope) const
	{
		std::string tmp;
		std::cin >> tmp;

		std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		while (tmp != "true" && tmp != "false")
		{
			std::cout << "Please enter 'true' or 'false': " << std::flush;
			std::cin >> tmp;
			std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		}

		Data *d = new Data();
		if (tmp == "true")
		{
			setDataBool(d, true);
		}
		else
		{
			setDataBool(d, false);
		}
		scope->setValue(m_varname, d);
	}

	void InputNode<double>::evaluate(Scope *scope) const
	{
		double n;
		while (!(std::cin >> n))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter a valid number: " << std::flush;
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		Data *d = new Data();
		setDataNum(d, n);
		scope->setValue(m_varname, d);
	}

	void InputNode<const std::string *>::evaluate(Scope *scope) const
	{
		std::string *str = new std::string();
		std::getline(std::cin, *str);

		Data *d = new Data();
		setDataStr(d, str);
		scope->setValue(m_varname, d);
	}

}