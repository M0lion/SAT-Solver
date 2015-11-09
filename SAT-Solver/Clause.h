#pragma once
#include <string>
#include <vector>
#include "Assignment.h"

class Clause;
typedef std::vector<Clause*> clauseList;

class Clause
{
public:
	Clause(std::string input, int inputLength);
	~Clause();
	void Print();

	bool Contains(int lit);

	Bool getValue(Assignment* a);

	int unassignedLiterals(Assignment* a);
	int unassignedLiteral(Assignment* a);

	Bool hasVar(int var);

	int varRange = 0;
private:
	int length;
	int* literals;
};