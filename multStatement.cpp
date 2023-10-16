#include "multStatement.hpp"
using namespace std;

multStatement::multStatement(string name, string value)
    : varName(name), subVal(value)   //Contructor initialization list
{}

void multStatement::execute(ProgramState * state, std::ostream &outf)
{
    int val;
    try{
        val = state->getValue(subVal);  //If you are multiplying by the value of another variable
    }
    catch(string notVariable){
        val = stoi(subVal); //If you are multiplying by an integer directly
    }
    state->mult(varName, val); 
    state->increment();
}

multStatement::~multStatement()
{}