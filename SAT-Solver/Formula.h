#pragma once

#include "Clause.h"
#include <string>

class Formula
{
public:
	Formula(std::string input);
	Formula(Formula* input);
	~Formula();

	static Formula* Resolve(Formula* formula); //deletes original Formula
	
	bool SAT(Assignment* a = nullptr);

	Bool getValue(Assignment* a);
	void Print();
private:
	int numberOfClauses;

	int clausesLength = 0;
	Clause** clauses;

	clauseList newClauses;

	bool deleteClauses = true;
	bool isValid;

	int varRange = 0;
};