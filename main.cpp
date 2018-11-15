#include <iostream>
#include <string>
using namespace std;
#include "token.h"
#include "parser.h"

void main(int argc, char* argv[]) {
	parser p;
	if (argc < 2)
		cout << "No file name given on command line\n";
	else {
		string fn = argv[1];
		p.parse(fn);
	}
	system("pause");
}
