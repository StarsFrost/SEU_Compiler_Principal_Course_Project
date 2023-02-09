#pragma once
#include<iostream>
#include<map>
#include<vector>
#include<array>
#include<stack>
using namespace std;

class token
{
public:
	string id;
	string value;

	token() = default;
	token(string i, string v) : id(i), value(v) {};
};

class automata
{
public: 
	int state;
	map<int, map<string, int>> pattern;
	int workStatus;

public:
	automata() : state(0), workStatus(0) {}
	virtual ~automata() = default;
};

class finiteAutomata : public automata
{
public:
	string token;
	array<string, 30> reserved = { "if","else", "while", "do", "true", "false","break", "(", ")", "<", "<=", "=", "==", ">", ">=","!=","%","*","+","-","/","++","--","||","&&", "|", "&" ,";", "{", "}"};
	array<int, 6> acc = { 1, 2, 3, 5, 8, 11 };

public:
	finiteAutomata();

	void init();

	void loadPattern();

	string tokenType();

	string charType(char c);

	int testAcc();

	int testReserved();

	void read(char c);
};

class stateTokenPair
{
public:
	int s;
	token t;
	stateTokenPair() = default;
	stateTokenPair(int s, token t) : s(s), t(t){}
};

class pushdownAutomata : public automata
{
public:
	vector<stateTokenPair> pStack;
	map<int, stateTokenPair> reduceTable;
	bool forward = false;

public:

	pushdownAutomata() { loadPattern(); }

	void read(token t);

	void reduction(int i);

	void exec(int i, token t);

	void loadPattern();
	
	void init();

	void printParser();
};