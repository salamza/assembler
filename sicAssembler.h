#ifndef SICASSEMBLER_H_INCLUDED
#define SICASSEMBLER_H_INCLUDED

#include "assembler.h"
#include "sicParser.h"
#include <fstream>
#include "Instruction.h"
#include <iomanip>
#include "obcode.h"
#include <string>

using namespace std ;
class sicAssembler : public assembler {

private :
sicParser *pars ;
string a[24];
string instructionList[5];
obcode objectCode;
string ob ;
string ob2 ;
int firstLoc;
string temp;
string temp2;

public :
void tokens(string interInput);
sicAssembler(){}
sicAssembler (std::string fileName);
void assemble () ;
~sicAssembler();
int findIna(string b , char c);
friend class sicParser;
};


#endif // SICASSEMBLER_H_INCLUDED
