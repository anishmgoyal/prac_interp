#include "Main.h"

#include "TypeCheck.h"

#include <unordered_map>
#include <unordered_set>

namespace Prac
{

	bool TypeCheck::areCompatible(const std::string& typeA, const std::string& typeB,
		const std::unordered_map<std::string, std::vector<std::string>>& typeMap)
	{
		auto it = typeMap.find(typeA);
		if (it == typeMap.end())
		{
			return false;
		}
		auto typeVec = it->second;

		for (auto it2 = typeVec.begin(); it2 != typeVec.end(); ++it2)
		{
			if (*it2 == typeB)
			{
				return true;
			}
		}
		return false;
	}

	const std::unordered_set<ArithmeticOp> bitwiseOperators
	{
		OP_BITWISEAND,
		OP_BITWISELEFT,
		OP_BITWISEOR,
		OP_BITWISERIGHT,
		OP_BITWISEXOR,
	};

	bool TypeCheck::isBitwise(ArithmeticOp op)
	{
		auto it = bitwiseOperators.find(op);
		if (it == bitwiseOperators.end())
		{
			return false;
		}
		return true;
	}

	std::unordered_map<std::string, std::vector<std::string>> equalityCompatible
	{
		{ "boolean", { "boolean", "Type String" } },
		{ "character", { "character", "integer", "number", "Type String" } },
		{ "integer", { "character", "integer", "number" } },
		{ "number", { "character", "integer", "number" } },
		{ "Type String", { "boolean", "character", "Type String" } }
	};

	bool TypeCheck::areCompatibleEquality(const std::string& typeA, const std::string& typeB)
	{
		return areCompatible(typeA, typeB, equalityCompatible);
	}

	std::unordered_map<std::string, std::vector<std::string>> comparisonCompatible
	{
		{ "character", { "character", "integer", "number" } },
		{ "integer", { "character", "integer", "number" } },
		{ "number", { "character", "integer", "number" } },
	};
	
	bool TypeCheck::areCompatibleComparison(const std::string& typeA, const std::string& typeB)
	{
		return areCompatible(typeA, typeB, comparisonCompatible);
	}

	const std::unordered_map<std::string, std::vector<std::string>> arithmeticCompatible
	{
		{ "character", { "character", "integer", "number" } },
		{ "integer", { "character", "integer", "number" } },
		{ "number", { "character", "integer", "number" } },
	};

	const std::unordered_map<std::string, std::vector<std::string>> bitwiseCompatible
	{
		{ "character", { "character", "integer" } },
		{ "integer", { "character", "integer" } },
	};

	const std::unordered_map<std::string, std::vector<std::string>> plusCompatible
	{
		{ "boolean", { "Type String" } },
		{ "character", { "character", "integer", "number", "Type String" } },
		{ "integer", { "character", "integer", "number", "Type String" } },
		{ "number", { "character", "integer", "number", "Type String" } },
		{ "Type String", { "boolean", "character", "integer", "number", "Type String" } },
	};

	bool TypeCheck::areCompatibleArithmetic(const std::string& typeA, const std::string& typeB, ArithmeticOp op)
	{
		if (op == OP_ADD)
		{
			return areCompatible(typeA, typeB, plusCompatible);
		}
		else if (isBitwise(op))
		{
			return areCompatible(typeA, typeB, bitwiseCompatible);
		}
		return areCompatible(typeA, typeB, arithmeticCompatible);
	}

	const std::vector<std::string> operatorWideness
	{
		"unknown",
		"boolean",
		"character",
		"integer",
		"number",
		"Type String"
	};

	const std::string& TypeCheck::getWider(const std::string& typeA, const std::string& typeB)
	{
		int widestFound = 0;
		int i = 0;
		for (auto it = operatorWideness.begin(); it != operatorWideness.end(); ++it)
		{
			const std::string& val = *it;
			if (val == typeA || val == typeB)
			{
				widestFound = i;
			}
			++i;
		}
		return operatorWideness[widestFound];
	}

}