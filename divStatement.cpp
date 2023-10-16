#include "divStatement.hpp"
using namespace std;

divStatement::divStatement(string name, string num)
    : varName(name), divVal(num)
{}

void divStatement::execute(ProgramState * state, std::ostream &outf){
    int divide;
    try{
        divide = state->getValue(divVal);   
    }
    //getValue throws exception if the variable doesn't exist, meaning you are dividing by an integer directly
    catch(string noVarExists){
        divide = stoi(divVal);  
    }

    //Program terminates if you try to divide by zero. Right before throwing exception, div will set counter to m_numlines
    try{
        state->div(varName, divide);
    }
    catch(int div0){    
        outf << "Divide by 0 exception" << endl;
        return;
    }
    state->increment(); 
}

divStatement::~divStatement()
{}