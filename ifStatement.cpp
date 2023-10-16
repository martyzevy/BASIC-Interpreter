#include "ifStatement.hpp"
using namespace std;

ifStatement::ifStatement(string var, string op, int value, int lineNumber)
    : variable(var), operation(op), val(value), line(lineNumber)    //val is the integer we are comparing the variable to
{}

void ifStatement::execute(ProgramState * state, std::ostream &outf)
{
    //First we must check if the variable in question has already been initialized
    int varVal;
    try{
        varVal = state->getValue(variable);
    }
    catch(string noVar){
        //If the variable doesn't exist we initialize it to zero
        state->updateVar(variable, 0);
        varVal = 0;
    }

    /*First, we identify the type of operation, then we can test whether the line is in bounds. If it is out of bounds,
    we print an error statement, and updateLine will change counter to m_numlines, causing the program to terminate*/
    if (operation == "<"){
        if (varVal < val){
            try{
                state->updateLine(line);
            }
            catch(string illegal){
                outf << "Illegal jump instruction" << endl;
            }
        }
        else state->increment();
    }

    else if (operation == "<="){
        if (varVal <= val){
            try{
                state->updateLine(line);
            }
            catch(string illegal){
                outf << "Illegal jump instruction" << endl;
            }
        }
        else state->increment();
    }

    else if (operation == ">"){
        if (varVal > val){
            try{
                state->updateLine(line);
            }
            catch(string illegal){
                outf << "Illegal jump instruction" << endl;
            }
        }
        else state->increment();
    }

    else if (operation == ">="){
        if (varVal >= val){
            try{
                state->updateLine(line);
            }
            catch(string illegal){
                outf << "Illegal jump instruction" << endl;
            }
        }
        else state->increment();
    }

    else if (operation == "="){
        if (varVal == val){
            try{
                state->updateLine(line);
            }
            catch(string illegal){
                outf << "Illegal jump instruction" << endl;
            }
        }
        else state->increment();
    }

    //The only remaining operation is '!='
    else{
        if (varVal != val){
            try{
                state->updateLine(line);
            }
            catch(string illegal){
                outf << "Illegal jump instruction" << endl;
            }
        }
        else state->increment();
    }
}

ifStatement::~ifStatement()  
{}  