#include "Statement.h"
#include "ProgramState.h"

class ifStatement: public Statement
{
    private:
        std::string variable;
        std::string operation;
        int val;    //The value the variable is being compared to
        int line;   //The line number to go to if the condition is true
    public:
        ifStatement(std::string var, std::string op, int value, int lineNumber);
        virtual void execute(ProgramState * state, std::ostream &outf);
        ~ifStatement();
};

