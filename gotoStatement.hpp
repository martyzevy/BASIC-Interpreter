#include "Statement.h"
#include "ProgramState.h"

class gotoStatement: public Statement
{
    int line;
    public:
        gotoStatement(int lineNumber);  
        virtual void execute(ProgramState * state, std::ostream &outf); //Overrides pure virtual function in abstract Statement class
        ~gotoStatement();
};