#ifndef INSTRUCTION_H_INCLUDED
#define INSTRUCTION_H_INCLUDED

#include <iostream>
#include <string>

using namespace std ;
class Instruction
{
private :
string input ;
    string label ;
    string mnemonic ;
    string operand ;
    string symbol ;
 int errorFlag ;
public :


    void read () ;
    void write (string output, int locationCounter) ;
    Instruction();
    ~Instruction(){}
    friend class parser;
friend class sicParser;
friend class sicxeParser ;
};


#endif // INSTRUCTION_H_INCLUDED
