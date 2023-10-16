#include "addStatement.hpp"
using namespace std;

addStatement::addStatement(string name, string num) 
    : varName(name), addVal(num)   
{}

void addStatement::execute(ProgramState * state, ostream &outf){
    int add;
    try{
        add = state->getValue(addVal);  //If we are adding by the value of another variable
    }
    catch(string noVar){    
        add = stoi(addVal); //We are adding an integer directly, not the value of a variable
    }
	state->add(varName, add);  
    state->increment(); 
}

addStatement::~addStatement()
{}