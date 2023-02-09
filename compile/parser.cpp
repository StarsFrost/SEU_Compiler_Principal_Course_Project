#include"parser.h"

parser::parser(scanner *s) : scan(s) {}

void parser::parse()
{
	pda.init();
	while(!scan->atEnd())
	{
		pda.init();
		while (!pda.workStatus)
		{
			token t = scan->getNextToken();
			if (t.id == "digit") t.id = "id";
			pda.read(t);
			pda.printParser();
			scan->forward(pda.forward);
		}
		cout << endl;
	}
}