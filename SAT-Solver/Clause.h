#pragma once
#include <string>
#include <vector>

class Clause;
typedef std::vector<Clause*> clauseList;

class Clause
{
public:
	Clause(std::string input, int inputLength);
	~Clause();
	void Print();

	clauseList getResolvents(Clause* clause);
private:
	Clause(Clause* A, Clause* B, int lit);
	int length;
	int* literals;
};