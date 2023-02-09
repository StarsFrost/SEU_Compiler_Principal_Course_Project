#pragma once
#include"automata.h"
using namespace std;

class scanner
{
public:
	string code;
	finiteAutomata automata;
	string::iterator front;
	string::iterator end;

public:
	scanner(string s);

	token getNextToken();

	bool atEnd();

	void forward(bool f);

};