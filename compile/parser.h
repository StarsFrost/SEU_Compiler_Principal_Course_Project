#pragma once
#include"scanner.h"
#include<vector>

class parser
{
public:
	scanner* scan;
	pushdownAutomata pda;

public:
	parser(scanner* s);
	void parse();
};
