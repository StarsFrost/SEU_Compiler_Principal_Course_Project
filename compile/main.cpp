#include"parser.h"
#include <fstream>
#include <sstream>
using namespace std;

string readFromFile(string path)
{
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
            << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

ostream& operator<<(ostream& o, token t) {
	o << "<" << t.id << ", " << t.value << ">";
	return o;
}

void main()
{
    string code = readFromFile("test2.txt");
    scanner s(code);
    parser p(&s);
    p.parse();
    /////////////////////Test for scaner/////////////////////////
	 /*
    string code = readFromFile("test.txt");
    scanner s(code);
    while (!s.atEnd())
	{
        token t = s.getNextToken();
        s.forward(true);
        cout << "(" << t.id << ", " << t.value << ")" << endl;
	}
    */
}