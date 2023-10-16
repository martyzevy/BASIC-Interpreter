// Interpreter.cpp
#include "Statement.h"
#include "LetStatement.h"
#include "addStatement.hpp"
#include "subStatement.hpp"
#include "multStatement.hpp"
#include "divStatement.hpp"
#include "gotoStatement.hpp"
#include "gosubStatement.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <stack>
#include <map> 
#include <iostream>
#include "ifStatement.hpp"
#include "returnStatement.hpp"
#include "PrintStatement.h"
#include "printallstatement.hpp"

using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement *> & program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);

int main()
{
        cout << "Enter BASIC program file name: ";
        string filename;
        getline(cin, filename);
        ifstream infile(filename.c_str());
        if (!infile)
        {
                cout << "Cannot open " << filename << "!" << endl;
                return 1;
        }
        interpretProgram(infile, cout);
}



void parseProgram(istream &inf, vector<Statement *> & program)
{
	program.push_back(NULL);
	
	string line;
	while( ! inf.eof() )
	{
		getline(inf, line);
		program.push_back( parseLine( line ) );
	}
}


Statement * parseLine(string line)
{
	Statement * statement;	
	stringstream ss;
	string type;
	string var;
	int val;

	ss << line;

	int lineNum;	//Store the line number
	ss >> lineNum;
	ss >> type;
	
	if ( type == "LET" )
	{
		ss >> var;
		ss >> val;
		// Note:  Because the project spec states that we can assume the file
		//	  contains a syntactically legal program, we know that
		//	  any line that begins with "LET" will be followed by a space
		//	  and then a variable and then an integer value.
		statement = new LetStatement(var, val);		
	}

	else if (type == "PRINT"){
		ss >> var;
		statement = new PrintStatement(var);	
	}

	else if (type == "PRINTALL") statement = new printallStatement();	

	/*For the Add, Sub, Mult and Divide statements, we read in a string and not an integer because
	we might be adding/subtracting/multiplying/dividing by the value of another variable
	instead of an integer. If it is an integer, we will use stoi inside the execute function*/
	else if (type == "ADD"){
		string value;	
		ss >> var >> value;
		statement = new addStatement(var, value);	
	}
	else if (type == "SUB"){
		string value;	
		ss >> var >> value;
		statement = new subStatement(var, value);	
	}
	else if (type == "MULT"){
		string value;	
		ss >> var >> value;
		statement = new multStatement(var, value);	
	}
	else if (type == "DIV"){
		string value;
		ss >> var >> value;
		statement = new divStatement(var, value);	
	}

	else if (type == "GOTO"){
		ss >> val;	
		statement = new gotoStatement(val);
	}

	else if (type == "IF"){
		ss >> var;
		string operation;	
		ss >> operation;	
		ss >> val;
		string then;
		ss >> then;	 		//Skip over "THEN" and store in temp variable that won't be used
		int gotoLine;
		ss >> gotoLine;
		statement = new ifStatement(var, operation, val, gotoLine);	
	}

	else if (type == "GOSUB"){
		int dest;
		ss >> dest;
		statement = new gosubStatement(lineNum, dest);	
	}

	/*returnStatement::execute will pop off the stack. No data members needed since
	we stored the gosubStatement's originLine when we pushed on the stack.*/
	else if (type == "RETURN") statement = new returnStatement();

	/*for both "END" and "." we terminate the program. Instead of creating a class for
	these commands, just put a nullptr in the vector and when interpretProgram encounters
	a nullptr, it will stop interpreting and the program will end. */
	else return nullptr;
	
	return statement;
}


void interpretProgram(istream& inf, ostream& outf)
{
	vector<Statement *> program;
	parseProgram( inf, program );
	ProgramState* basic = new ProgramState(program.size());

	/*Since the order in which a BASIC program is run is not necessarily sequential, 
	we always call basic->getLine(), which returns the line the program is supposed to run
	now. Everytime we execute a line, the program counter is updated so that getLine() will
	return the right result. The counter defaults at 1. The fist pointer in the program vector
	in nullptr, so it makes sense to start at index 1, which is the first line in the BASIC program.*/

	while (program[basic->getLine()]){ 
		program[basic->getLine()]->execute(basic, outf);	//execute is virtual, so this is dynamic binding. 
	}

	//De-allocate memmory 
	for (unsigned  i = 0; i < program.size(); i++){
		if (program[i]) delete program[i];
	}
	delete basic;
}
