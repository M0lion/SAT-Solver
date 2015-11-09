#pragma once

#include "Clause.h"
#include <string>

class Formula
{
public:
	Formula(std::string input);
	~Formula();

	bool SAT(Assignment* a = nullptr);

	Bool getValue(Assignment* a);
	void Print();
private:
	int numberOfClauses;

	clauseList clauses;

	int varRange = 0;
};