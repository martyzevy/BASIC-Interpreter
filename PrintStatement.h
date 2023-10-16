#ifndef PRINT_STATEMENT_INCLUDED
#define PRINT_STATEMENT_INCLUDED

#include "Statement.h"
#include <iostream>
#include "ProgramState.h"

class PrintStatement: public Statement
{
	private:
		std::string m_variableName;
	public:
		PrintStatement(std::string variableName);
		void execute(ProgramState * state, std::ostream &outf);	//Overrides Statement pure virtual function
		~PrintStatement();
};

#endif
