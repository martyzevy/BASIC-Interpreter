// ProgramState.h
//
// CS 104
//
// The ProgramState class encapsulates the state of an executing Facile
// program.  The state of a BASIC program consists of three parts:
//
//    * The program counter, which specifies the line number of the
//      statement that will execute next.
//    * A map, as explained by the problem writeup.
//    * A stack of integers, which is used to hold return lines for GOSUB
//      statements.
//
// We've provided you a start on this class, but you'll need to add methods
// to it as you go along.  In particular, you'll need methods to access and
// modify the state; these methods will be called primarily by the various
// execute() methods in the Statement subclasses, to allow the execution of
// a statement to change the state of a program.  For example, executing a
// GOTO statement will cause the program counter to be changed.

#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED

#include <stack>
#include <map> 
#include <string>
#include <queue>
#include <iostream>
#include <fstream>
#include <ostream>	

class ProgramState
{
	public:
		ProgramState(int numLines);
		void updateVar(std::string varName, int val);	//Creates new variable or overides existing one
		void add(std::string varName, int val);
		void sub(std::string varName, int val);
		void mult(std::string varName, int val);
		void div(std::string varName, int val);
		void updateLine(int line);						//Changes the program counter to a custom int
		void increment();								//Moves program counter to the next sequential line
		int getLine();									//Returns the current state of program counter
		int getValue(std::string variable);				//Get the value of any variable
		void pushReturn(int returnLine);				//For GOSUB statements
		void popReturn();								//When you reach a RETURN statement
		void print(std::string variable, std::ostream &outf);
		void printAll(std::ostream &outf);
		
	private:
		int m_numLines;
		std::stack<int> returns;			//Will store the line to go back to when you encounter a RETURN
		std::map<std::string, int> data;	//Stores all variables
		int counter;						//Current line the program should run
};

#endif
