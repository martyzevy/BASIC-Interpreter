#include "Statement.h"
#include "ProgramState.h"

class returnStatement: public Statement{
    public:
        //Default constructor is OK for this class
        virtual void execute(ProgramState * state, std::ostream &outf);
        ~returnStatement();
};