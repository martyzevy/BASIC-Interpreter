#include "printallstatement.hpp"
using namespace std;

printallStatement::printallStatement()
{}  //Nothing necessary here

void printallStatement::execute(ProgramState* state, std::ostream &outf){
    state->printAll(outf);  //Calls ProgramState printAll function
    state->increment();
}

printallStatement::~printallStatement()
{}   