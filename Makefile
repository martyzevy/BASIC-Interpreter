CXX = g++
CPPFLAGS = -g -Wall -std=c++11

all: Interpreter

Interpreter: Interpreter.cpp ProgramState.o Statement.cpp addStatement.o divStatement.o gotoStatement.o ifStatement.o multStatement.o returnStatement.o subStatement.o LetStatement.o PrintStatement.o printallStatement.o gosubStatement.o
	$(CXX) $(CPPFLAGS) $^ -o $@

ProgramState.o: ProgramState.cpp ProgramState.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

Statement.o: Statement.cpp Statement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

addStatement.o: addStatement.cpp addStatement.hpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

divStatement.o: divStatement.cpp divStatement.hpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

gotoStatement.o: gotoStatement.cpp gotoStatement.hpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

ifStatement.o: ifStatement.cpp ifStatement.hpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

multStatement.o: multStatement.cpp multStatement.hpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

returnStatement.o: returnStatement.cpp returnStatement.hpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

subStatement.o: subStatement.cpp subStatement.hpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

LetStatement.o: LetStatement.cpp LetStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

PrintStatement.o: PrintStatement.cpp PrintStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

printallStatement.o: printallStatement.cpp printallStatement.hpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

gosubStatement.o: gosubStatement.cpp gosubStatement.hpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *.o Interpreter