#include "Statement.h"
#include "ProgramState.h"

class multStatement: public Statement {
    std::string varName;
    std::string subVal;
    public:
        multStatement(std::string name, std::string value);
        virtual void execute(ProgramState * state, std::ostream &outf); //Override pure virtual function
        ~multStatement();
};