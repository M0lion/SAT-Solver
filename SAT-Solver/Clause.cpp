#include "Clause.h"
#include <sstream>

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
		if (abs(literals[i]) > varRange)
			varRange = abs(literals[i]);
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

bool Clause::Contains(int lit)
{
	for (int i = 0; i < length; i++)
	{
		if (literals[i] == lit)
			return true;
	}

	return false;
}

clauseList Clause::getResolvents(Clause* clause)
{
	clauseList resolvents;
	resolvents.reserve(length * clause->length);
	for (int i = 0; i < length; i++)
	{
		if (clause->Contains(literals[i] * -1))
		{
			std::stringstream newClause;
			for (int j = 0; j < length; j++)
			{
				if (literals[j] != literals[i])
				{
					newClause << literals[j] << " ";
				}
			}
			for (int j = 0; j < clause->length; j++)
			{
				std::stringstream intToStr;
				intToStr << clause->literals[j];
				if (clause->literals[j] != literals[i] * -1 && newClause.str().find(intToStr.str()) != std::string::npos)
				{
					newClause << literals[j] << " ";
				}
			}
			std::string clauseString = newClause.str();
			resolvents.push_back(new Clause(clauseString, clauseString.length()));
		}
	}

	return resolvents;
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
