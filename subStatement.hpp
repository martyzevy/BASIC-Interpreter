#include "Statement.h"

class subStatement: public Statement {
    std::string varName;
    std::string subVal;
    public:
        subStatement(std::string name, std::string num);
        virtual void execute(ProgramState * state, std::ostream &outf); //Override pure virtual function
        ~subStatement();
};

