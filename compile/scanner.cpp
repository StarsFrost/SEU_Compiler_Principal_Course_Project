#include"scanner.h"

scanner::scanner(string s): code(s)
{
	front = end = code.begin();
}

token scanner::getNextToken()
{
	automata.init();
	end = front;
	while (!automata.workStatus && end != code.end())
	{
		automata.read(*end);
		if (automata.workStatus)
			break;
		end++;
	}
	if (automata.workStatus == 1)
		if (automata.tokenType() == "space")
		{
			forward(true);  return getNextToken();
		}
		else
			return token(automata.tokenType(), string(front, end));
	if (automata.workStatus == 2)
		return token(string(front, end), "null");
	if (automata.workStatus == 3 && *end != '$')
	{
		end++;
		cout << "something wrong" << endl;
	}
	if (automata.workStatus == 3 && *end == '$')
	{
		front = end;
		exit(0);
	}
}

void scanner::forward(bool f)
{
	if (f)
		front = end;
}

bool scanner::atEnd()
{
	if (*front == '$')
		return true;
	else return false;
}