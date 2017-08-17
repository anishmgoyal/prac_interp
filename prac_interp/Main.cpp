#include "Main.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Token.h"
#include "Tokenizer.h"

#include "ProgramBuilder.h"

void runProgram()
{
	std::ifstream codeFile;
	codeFile.open("prog1.prac", std::ios::in);

	std::string data((std::istreambuf_iterator<char>(codeFile)),
		std::istreambuf_iterator<char>());

	codeFile.close();

	const Prac::IEvaluatorNode *program;

#ifndef _DEBUG
	try
	{
#endif
		program = Prac::ProgramBuilder::buildProgram(data);
#ifndef _DEBUG
	}
	catch (...)
	{
		std::cout << "Failed to build program." << std::endl;
		return;
	}
#endif

	Prac::Scope scope;

	auto node = program;

	while (node != NULL)
	{
#ifndef _DEBUG
		try
		{
#endif
			node->evaluate(&scope);
#ifndef _DEBUG
		}
		catch (...)
		{
			std::cout << "Execution error while trying to run program." << std::endl;
			delete program;
			return;
		}
#endif

		node = node->getNext();
	}

	delete program;
}

int main()
{

	#ifdef _DEBUG
		_CrtMemState s1;
		_CrtMemCheckpoint(&s1);
	#endif

	runProgram();

	#ifdef _DEBUG
		_CrtMemDumpAllObjectsSince(&s1);
	#endif

	std::getline(std::cin, std::string());

	return 0;
}