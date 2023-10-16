#include "Statement.h"
#include "ProgramState.h"

class gosubStatement: public Statement
{
    private:
        int originLine;
        int destinationLine;
    public:
        gosubStatement(int originLine, int destinationLine);    
        virtual void execute(ProgramState* state, std::ostream &outf);  //Override pure virtual function
        ~gosubStatement();
};
