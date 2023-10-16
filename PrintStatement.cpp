// PrintStatement.cpp:
#include "PrintStatement.h"
using namespace std;
#include <fstream>
#include <iostream> 

PrintStatement::PrintStatement(std::string variableName)
	: m_variableName( variableName )
{}


void PrintStatement::execute(ProgramState * state, std::ostream &outf){
	state->print(m_variableName, outf);
	state->increment();	//Move to the next line
}

PrintStatement::~PrintStatement()
{}
