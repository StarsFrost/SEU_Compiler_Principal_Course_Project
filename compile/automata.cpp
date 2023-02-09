#include"automata.h"
finiteAutomata::finiteAutomata() { loadPattern(); }

void finiteAutomata::init() { workStatus = state = 0; token.clear(); }

void finiteAutomata::loadPattern()
{
	pattern[0]["l"] = 1;
	pattern[0]["s"] = 2;
	pattern[0]["d"] = 3;
	pattern[0]["\""] = 10;
	pattern[1]["l"] = 1;
	pattern[2]["s"] = 2;
	pattern[3]["d"] = 3;
	pattern[3]["."] = 4;
	pattern[3]["e"] = 6;
	pattern[4]["d"] = 5;
	pattern[5]["d"] = 5;
	pattern[5]["e"] = 6;
	pattern[6]["d"] = 8;
	pattern[6]["+"] = 7;
	pattern[6]["-"] = 7;
	pattern[7]["d"] = 8;
	pattern[8]["d"] = 8;
	pattern[10]["\""] = 11;
	pattern[10]["l"] = 10;
}

string finiteAutomata::tokenType()
{
	string r;
	switch (state)
	{
	case 1: r = "id";
		break;
	case 2: r = "space";
		break;
	case 3: r = "digit";
		break;
	case 5: r = "digit";
		break;
	case 8: r = "digit";
		break;
	case 11: r = "string";
		break;
	default:
		break;
	}
	return r;
}

string finiteAutomata::charType(char c)
{
	if ((state == 3 || state == 5) && (c == 'e' || c == 'E')) return "e";
	if (state == 10 && c != '"') return "l";
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_') return "l"; // letter or _
	if (c >= '0' && c <= '9') return "d"; //digit
	if (c == ' ' || c == '\n') return "s"; //space or enter
	else return string(1, c);
}

int finiteAutomata::testAcc()
{
	auto iter = find(acc.begin(), acc.end(), state);
	if (iter != acc.end())
		return 1;
	else
		return 0;
}

int finiteAutomata::testReserved()
{
	auto iter = find(reserved.begin(), reserved.end(), token);
	if (iter != reserved.end())
		return 1;
	else
		return 0;
}

void finiteAutomata::read(char c)
{
	token.push_back(c);
	if (testReserved() && state == 0)
		state = 9;
	if (state == 9)
	{
		if (!testReserved())
			workStatus = 2;
	}
	else{
		map<string, int>::iterator iter = pattern[state].find(charType(c));
		if (iter != pattern[state].end())
			state = iter->second;
		else
		{
			if (testAcc())
			{
				token.pop_back();
				if (testReserved())
					workStatus = 2;
				else
					workStatus = 1;
			}
			else
				workStatus = 3;
		}
	}
}

void pushdownAutomata::reduction(int i)
{
	stateTokenPair rule = reduceTable[i];
	for (int j = rule.s; j > 0; j--)
	{
		pStack.pop_back();
	}
	state = pStack.back().s;
	read(rule.t);
	forward = false;
}

void pushdownAutomata::exec(int i, token t)
{
	if (i == 0) { reduction(0); forward = true; workStatus = 1; return; }
	if (i > 0) 
	{ 
		state = i;
		stateTokenPair tmp(state, t);
		pStack.push_back(tmp);
		forward = true;
		return; 
	}
	if (i < 0) { reduction(i); return; }
}

void pushdownAutomata::read(token t)
{
	forward = false;
	map<string, int>::iterator iter = pattern[state].find(t.id);
	if (iter != pattern[state].end())
	{
		exec(iter->second, t);
	}
	else
	{
		cout << "something wrong";
		forward = true;
		return;
	}
}
void pushdownAutomata::init()
{
	workStatus = state = 0;
	pStack.clear();
	pStack.push_back(stateTokenPair(0, token("$", "null")));
}
void pushdownAutomata::printParser()
{
	for (auto iter = pStack.begin(); iter != pStack.end(); iter++)
	{
		if (iter->t.value == "null")
			cout << iter->t.id;
		else
		{
			cout << iter->t.value;
		}
	}
	cout << endl;
}

void pushdownAutomata::loadPattern()
{
	pattern[0]["-"] = 2;
	pattern[0]["id"] = 4;
	pattern[0]["("] = 3;
	pattern[0]["E"] = 1;
	pattern[1]["+"] = 5;
	pattern[1]["-"] = 6;
	pattern[1]["*"] = 7;
	pattern[1]["/"] = 8;
	//pattern[1][";"] = 0;
	pattern[1]["="] = 16;
	pattern[2]["-"] = 2;
	pattern[2]["id"] = 4;
	pattern[2]["("] = 3;
	pattern[2]["E"] = 9;
	pattern[3]["-"] = 2;
	pattern[3]["id"] = 4;
	pattern[3]["("] = 3;
	pattern[3]["E"] = 10;
	pattern[4]["+"] = -1;
	pattern[4]["-"] = -1;
	pattern[4]["*"] = -1;
	pattern[4]["/"] = -1;
	pattern[4]["="] = -1;
	pattern[4]["id"] = -1;
	pattern[4]["("] = -1;
	pattern[4][")"] = -1;
	pattern[4]["E"] = -1;
	pattern[4][";"] = -1;
	pattern[5]["-"] = 2;
	pattern[5]["id"] = 4;
	pattern[5]["("] = 3;
	pattern[5]["E"] = 11;
	pattern[6]["-"] = 2;
	pattern[6]["id"] = 4;
	pattern[6]["("] = 3;
	pattern[6]["E"] = 12;
	pattern[7]["-"] = 2;
	pattern[7]["id"] = 4;
	pattern[7]["("] = 3;
	pattern[7]["E"] = 13;
	pattern[8]["-"] = 2;
	pattern[8]["id"] = 4;
	pattern[8]["("] = 3;
	pattern[8]["E"] = 14;
	pattern[9]["+"] = -2;
	pattern[9]["-"] = -2;
	pattern[9]["*"] = -2;
	pattern[9]["/"] = -2;
	pattern[9]["id"] = -2;
	pattern[9]["("] = -2;
	pattern[9][")"] = -2;
	pattern[9]["E"] = -2;
	pattern[9][";"] = -2;
	pattern[10]["+"] = 5;
	pattern[10]["-"] = 6;
	pattern[10]["*"] = 7;
	pattern[10]["/"] = 8;
	pattern[10]["id"] = 4;
	pattern[10]["("] = 3;
	pattern[10][")"] = 15;
	pattern[11]["+"] = -3;
	pattern[11]["-"] = -3;
	pattern[11]["*"] = 7;
	pattern[11]["/"] = 8;
	pattern[11]["id"] = 4;
	pattern[11]["("] = 3;
	pattern[11][")"] = -3;
	pattern[11][";"] = -3;
	pattern[12]["+"] = -4;
	pattern[12]["-"] = -4;
	pattern[12]["*"] = 7;
	pattern[12]["/"] = 8;
	pattern[12]["id"] = 4;
	pattern[12]["("] = 3;
	pattern[12][")"] = -4;
	pattern[12][";"] = -4;
	pattern[13]["+"] = -5;
	pattern[13]["-"] = -5;
	pattern[13]["*"] = -5;
	pattern[13]["/"] = -5;
	pattern[13]["id"] = -5;
	pattern[13]["("] = -5;
	pattern[13][")"] = -5;
	pattern[13][";"] = -5;
	pattern[14]["+"] = -6;
	pattern[14]["-"] = -6;
	pattern[14]["*"] = -6;
	pattern[14]["/"] = -6;
	pattern[14]["id"] = -6;
	pattern[14]["("] = -6;
	pattern[14][")"] = -6;
	pattern[14][";"] = -6;
	pattern[15]["+"] = -7;
	pattern[15]["-"] = -7;
	pattern[15]["*"] = -7;
	pattern[15]["/"] = -7;
	pattern[15]["id"] = -7;
	pattern[15]["("] = -7;
	pattern[15][";"] = -7;
	pattern[16]["-"] = 2;
	pattern[16]["id"] = 4;
	pattern[16]["("] = 3;
	pattern[16]["E"] = 17;
	pattern[17]["+"] = 5;
	pattern[17]["-"] = 6;
	pattern[17]["*"] = 7;
	pattern[17]["/"] = 8;
	pattern[17][";"] = 0;
	//pattern[1]["="] = 16;
	reduceTable[-1] = stateTokenPair(1, token("E", "null"));
	reduceTable[-2] = stateTokenPair(2, token("E", "null"));
	reduceTable[-3] = stateTokenPair(3, token("E", "null"));
	reduceTable[-4] = stateTokenPair(3, token("E", "null"));
	reduceTable[-5] = stateTokenPair(3, token("E", "null"));
	reduceTable[-6] = stateTokenPair(3, token("E", "null"));
	reduceTable[-7] = stateTokenPair(3, token("E", "null"));
	reduceTable[0] = stateTokenPair(3, token("E", "null"));
}