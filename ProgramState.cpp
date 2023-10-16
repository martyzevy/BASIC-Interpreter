#include "ProgramState.h"
using namespace std;

/*Constructor initializes the counter to 1 because this is the first line, and because the first index in the 
program vector in Interpreter.cpp will be nullptr. Interpreter.cpp will always call execute on the statement 
index accossiated with the ProgramState counter*/
ProgramState::ProgramState(int numLines)
    : m_numLines(numLines), returns(), data(), counter(1)
{}

void ProgramState::updateVar(string varName, int val){
    data[varName] = val;   //Creates new variable with this value or overwrites value if it already exists
}

void ProgramState::add(string varName, int val){
    if (data.find(varName) == data.end()){
        updateVar(varName, 0);  //Variables default to 0 in BASIC
    }
    data[varName] += val;  
}

void ProgramState::sub(string varName, int val){
    data[varName] -= val;
}

void ProgramState::mult(string varName, int val){
    data[varName] *= val;
}

void ProgramState::div(std::string varName, int val){
    if (val == 0){
        counter = m_numLines;   
        throw 0;    //Trying to divide by zero should terminate the program
    }
    data[varName] /= val;
}

void ProgramState::updateLine(int line){
    //Check to make sure line is valid
    if (line < 1 || line > m_numLines){
        counter = m_numLines;   //The last line contains a "." Interpreter.cpp will see this and make the statement nullptr, which will terminate the program. 
        string illegal = "Illegal Jump Instruction";
        throw (illegal);
    }
    else counter = line;
}

int ProgramState::getLine(){
    return counter;
}

void ProgramState::increment(){
    counter++;
}

int ProgramState::getValue(string variable){
    //Check if variable exists
    string notVariable = "not found";
    if (data.find(variable) == data.end()){
        throw notVariable;
    }
    return data[variable];
}

void ProgramState::pushReturn(int returnLine){
    returns.push(returnLine + 1);   //1 more than the return line to prevent infinite loop within GOSUB
}

void ProgramState::popReturn(){
    //Check if returns is empty
    if (returns.empty()){
        counter = m_numLines;   //If you return and you were not inside a GOSUB, the program should terminate
        return;
    }
    counter = returns.top();
    returns.pop();
}

void ProgramState::print(string variable, ostream &outf){
    outf << data[variable] << endl;
}

void ProgramState::printAll(ostream &outf){
    //Auto will use iterator for Map
    for (auto it = data.begin(); it != data.end(); ++it){    
        outf << it->first << " " << it->second << endl; 
    }
}