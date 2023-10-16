//Add Statement Class
#include "Statement.h"
#include "ProgramState.h"

class addStatement: public Statement 
{
    std::string varName;
    std::string addVal;

    public:
        addStatement(std::string name, std::string num);
        virtual void execute(ProgramState * state, std::ostream &outf); //Override execute function
        ~addStatement();   
};


