#pragma once

#include "Clause.h"
#include <string>

class Resolution
{
public:
	Resolution(std::string input);
	Resolution(Resolution* input);
	~Resolution();

	static Resolution* Resolve(Resolution* formula); //deletes original Formula
	
	//bool isInvalid();
	void Print();
private:
	int numberOfClauses;

	int clausesLength = 0;
	Clause** clauses;

	clauseList newClauses;

	bool deleteClauses = true;
	bool isValid;
};