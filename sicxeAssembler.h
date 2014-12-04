#ifndef SICXEASSEMBLER_H_INCLUDED
#define SICXEASSEMBLER_H_INCLUDED

#include "assembler.h"
#include <string>
#include "sicxeParser.h"
#include <fstream>
#include "Instruction.h"
#include "sicxeObcode.h"


using namespace std ;
class sicxeAssembler : public assembler {

private :
sicxeParser *pars ;
string a[32];
sicxeObcode objectCode;
string instructionList[5];
string ob ;
int firstLoc;
string temp;


public :
sicxeAssembler(){}
sicxeAssembler (std::string fileName);
void assemble () ;
~sicxeAssembler();
friend class sicxeParser;
void tokens(string interInput);
int findIna(string b , char c);

};

#endif // SICXEASSEMBLER_H_INCLUDED
