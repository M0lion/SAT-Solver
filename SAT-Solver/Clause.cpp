#include "Clause.h"

Clause::Clause(std::string input, int inputLength)
{
	length = 0;
	for (int i = 0; i < inputLength; i++)
	{
		if (isdigit(input[i]))
		{
			length++;
		}
	}

	char* lit = new char[2];
	lit[1] = 0;

	literals = new int[length];
	int reader = 0;
	for (int i = 0; i < length; i++)
	{
		if (input[reader] == ' ')
			reader++;

		bool neg = false;
		if (input[reader] == '-')
		{
			neg = true;
			reader++;
		}

		lit[0] = input[reader];
		literals[i] = atoi(lit);
		if (neg)
			literals[i] *= -1;

		reader++;
	}

	delete(lit);
}

Clause::~Clause()
{
	delete(literals);
}

void Clause::Print()
{
	for (int i = 0; i < length; i++)
	{
		printf("%d ", literals[i]);
	}
}

clauseList Clause::getResolvents(Clause* clause)
{
	clauseList resolvents;
	resolvents.reserve(length * clause->length);
	for (int i = 0; i < length; i++)
	{

	}
}