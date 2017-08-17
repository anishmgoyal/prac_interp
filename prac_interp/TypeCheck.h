#ifndef TypeCheck_H
#define TypeCheck_H

#include "Main.h"

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

#include "ArithmeticOpNode.h"
#include "BooleanOpNode.h"
#include "ConditionalNode.h"

namespace Prac
{

	class TypeCheck
	{
	private:
		static bool areCompatible(const std::string& typeA, const std::string& typeB,
			const std::unordered_map<std::string, std::vector<std::string>>& typeMap);
		static bool isBitwise(ArithmeticOp op);
	public:
		static bool areCompatibleEquality(const std::string& typeA, const std::string& typeB);
		static bool areCompatibleComparison(const std::string& typeA, const std::string& typeB);
		static bool areCompatibleArithmetic(const std::string& typeA, const std::string& typeB, ArithmeticOp op);
		static const std::string& getWider(const std::string& typeA, const std::string& typeB);
	};

}

#endif