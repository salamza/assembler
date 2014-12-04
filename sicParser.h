#ifndef SICPARSER_H_INCLUDED
#define SICPARSER_H_INCLUDED

#include "hashTable.h"

#include "parser.h"

class sicParser : public parser {
public :
bool isHex(string a);
sicParser();
int evaluator (hashTable* opTable , hashTable* symbolTable , hashTable* directiveTable,int &locationCounter) ;
friend class sicAssembler ;
bool hexa(string a);
};

#endif // SICPARSER_H_INCLUDED
