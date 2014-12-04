#ifndef SICXEPARSER_H_INCLUDED
#define SICXEPARSER_H_INCLUDED



#include "hashTable.h"

#include "parser.h"

class sicxeParser : public parser {
    private :
    char reg[7] ;
    bool isReg(char g);
public :
bool isHex(string a);
sicxeParser();
int evaluator (hashTable* opTable , hashTable* symbolTable , hashTable* directiveTable,int &locationCounter) ;
friend class sicAssembler ;
};



#endif // SICXEPARSER_H_INCLUDED
