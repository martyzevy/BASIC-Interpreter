#include "subStatement.hpp"
using namespace std;

subStatement::subStatement(string name, string num)
    : varName(name), subVal(num)   
{}

void subStatement::execute(ProgramState * state, std::ostream &outf)
{
    int subtract;
    try{
        subtract = state->getValue(subVal); //When we are subtracting from the value of a variable
    }
    catch(string noVar){
        /*getValue throws exception when the variable does not exists
        In this case, we are subtracting from an integer directly*/
        subtract = stoi(subVal);
    }
    
    state->sub(varName, subtract);
    state->increment();
}

subStatement::~subStatement()
{}