#include <string>
#include <fstream>

#include "Formula.h"

int main(char* args[], int argc)
{
	std::string input = "cnf_test.txt";

	std::ifstream infile(input);

	if (!infile.is_open())
	{
		printf("couldn't open '%s'!\n", input);
		return 0;
	}

	std::string line;
	while (std::getline(infile, line))
	{
		Formula formula(line);
		if (formula.SAT())
		{
			printf("%s\n", line.c_str());
		}
	}

	scanf_s("/n");
}