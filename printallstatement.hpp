#include "Statement.h"
#include "ProgramState.h"
#include <iostream>

class printallStatement: public Statement
{	
    public:
        printallStatement();
        void execute(ProgramState* state, std::ostream &outf);  
        ~printallStatement();   //Need to specify destructor because Statement destructor is virtual
};