// LetStatement.cpp:
#include "LetStatement.h"
#include <iostream>
#include <fstream>
using namespace std;

LetStatement::LetStatement(string variableName, int value)
	: m_variableName( variableName ), m_value( value )
{}


// The LetStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
void LetStatement::execute(ProgramState * state, ostream &outf){
	state->updateVar(m_variableName, m_value);	//Will create or override a variable
	state->increment();
}

LetStatement::~LetStatement()
{}