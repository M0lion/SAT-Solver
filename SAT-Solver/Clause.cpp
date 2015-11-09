#include "Clause.h"
#include <sstream>

Clause::Clause(std::string input, int inputLength)
{
	length = 0;
	bool foundLiteral = false;
	for (int i = 0; i < inputLength; i++)
	{
		if (isdigit(input[i]))
		{
			if (!foundLiteral)
			{
				length++;
				foundLiteral = true;
			}
		}
		else if (input[i] == ' ')
			foundLiteral = false;
	}

	char* lit = new char[100];
	for (int i = 0; i < 100; i++)
	{
		lit[i] = '\0';
	}
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
		
		int j = 0;
		while (input[reader] != ' ' && reader < input.length())
		{
			if (j == 99)
			{
				throw "variable too big!";
			}

			lit[j] = input[reader];

			j++;
			reader++;
		}

		literals[i] = atoi(lit);
		if (abs(literals[i]) > varRange)
			varRange = abs(literals[i]);
		if (neg)
			literals[i] *= -1;
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

bool Clause::Contains(int lit)
{
	for (int i = 0; i < length; i++)
	{
		if (literals[i] == lit)
			return true;
	}

	return false;
}

Bool Clause::getValue(Assignment* a)
{
	if (length == 0)
		return 1;

	Bool value = -1;

	for (int i = 0; i < length; i++)
	{
		if (a->getValue(literals[i]) == 0)
			value = 0;
		else if (a->getValue(literals[i]) == 1)
			return 1;
	}

	return value;
}

int Clause::unassignedLiterals(Assignment * a)
{
	int res = 0;
	for (int i = 0; i < length; i++)
	{
		if (a->getValue(literals[i]) == 0)
			res++;
	}
	return res;
}

int Clause::unassignedLiteral(Assignment * a)
{
	for (int i = 0; i < length; i++)
	{
		if (a->getValue(literals[i]) == 0)
			return literals[i];
	}
	return 0;
}

Bool Clause::hasVar(int var)
{
	for (int i = 0; i < length; i++)
	{
		if (literals[i] == var)
			return 1;
		else if (literals[i] == var * -1)
			return -1;
	}

	return 0;
}
