#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED
#include "hashTable.h"
#include <string>
#include <fstream>
#include "Instruction.h"
#include "parser.h"
#include "obcode.h"
class assembler {
protected :
int locationCounter ;
hashTable *opTable ;
hashTable *symbolTable ;
hashTable *directiveTable ;
string fileName ;
string intFile ;

public :
assembler(){}
virtual void assemble ()=0 ;
virtual ~assembler(){
delete opTable ;
delete symbolTable ;
delete directiveTable;
}
};

#endif // ASSEMBLER_H_INCLUDED
