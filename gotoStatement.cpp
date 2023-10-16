#include "gotoStatement.hpp"
using namespace std;

gotoStatement::gotoStatement(int lineNumber)
    : line(lineNumber)
{}

void gotoStatement::execute(ProgramState * state, std::ostream &outf){
     try{
          state->updateLine(line);
     }

     /*Exception for when line is less than 1 or bigger than the total number of lines. Program will terminate
     after catching exception because state->updateLine sets counter to m_numlines right before it throws exception*/
     catch(string illegal){     
          outf << "Illegal jump instruction" << endl;    
     }
}

gotoStatement::~gotoStatement()
{}