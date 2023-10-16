#include "returnStatement.hpp"
using namespace std;

void returnStatement::execute(ProgramState * state, std::ostream &outf){
    state->popReturn(); //popReturn will move the counter to what was on top of the stack and then pop from the top of the stack
}

returnStatement::~returnStatement()
{}