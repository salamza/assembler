#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <string>
#include <iostream>
#include "hashTable.h"
#include "Instruction.h"
using namespace std;

class parser
{
private :

public :
    parser();
    void lexicalAnalyzer (hashTable* opTable , hashTable* symbolTable , hashTable* directiveTable , string fileName , int &locationCounter);
    virtual ~parser();
    protected :
    int findIn (string b , char c) ;
    string instructionList[7] ;
        virtual int evaluator (hashTable* opTable , hashTable* symbolTable , hashTable* directiveTable ,int &locationCounter){return 0;}
        Instruction *instruction ;
        bool isInt(string a);

    friend int main () ;
};

#endif // PARSER_H_INCLUDED
