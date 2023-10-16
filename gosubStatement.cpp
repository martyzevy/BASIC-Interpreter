#include "gosubStatement.hpp"

gosubStatement::gosubStatement(int origin, int destination)
    : originLine(origin), destinationLine(destination)
{}

void gosubStatement::execute(ProgramState * state, std::ostream &outf){
    state->updateLine(destinationLine); 
    state->pushReturn(originLine);  //Store the line we came from. Will get pushed on the stack for LIFO
}

gosubStatement::~gosubStatement()
{}