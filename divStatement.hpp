#include "Statement.h"
#include "ProgramState.h"

class divStatement: public Statement 
{
    std::string varName;
    std::string divVal; //The divisor
    public:
        divStatement(std::string name, std::string num);
        virtual void execute(ProgramState * state, std::ostream &outf); 
        ~divStatement();  
};