
#include "Clause.h"
#include <string>

#include "Resolution.h"

int main()
{
	std::string clauseTest = "1 2 -3 -4 5 5 -3";
	Clause test(clauseTest, clauseTest.length());
	test.Print();
	printf("\n");

	Resolution testFormula("1 2 3; 1 2 -3; 1 -2 3; 1 -2 -3; -1 2 3; -1 2 -3; -1 -2 3; -1 -2 -3");
	testFormula.Print();

	scanf_s("/n");
}