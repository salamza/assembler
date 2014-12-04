#include "parser.h"
#include "Instruction.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std ;

void parser::lexicalAnalyzer (hashTable* opTable , hashTable* symbolTable , hashTable* directiveTable , string fileName , int &locationCounter)
{
    int j=0 ;
    int i=0 ;
    int n=0 ;
    bool f=0  ;
    bool m=0 ;
    string b ;
    b.clear();
    ifstream mystream;
   string output = "outputfile.txt";
    mystream.open("testfile.txt");


    while (!mystream.eof())
    {
        instruction->label.clear() ;
        instruction->mnemonic.clear();
        instruction->operand.clear();
        instruction->symbol.clear();
        f=0 ;
        j=0;
        i=0 ;
        n=0 ;
        string c ;
        for (int i=0 ; i<7 ; i++ )
        {
            instructionList[i].clear();
        }
        getline (mystream , b , '\n');
        instruction->input = b ;
        int size = b.size() ;
        int u=parser::findIn(b,(char)39) ;
        if (u != -1)
        {
            instructionList[6] = b.substr(u,b.size());
        }
        for (i ; i<=size ; i++ )
        {
            f=0 ;
            if (b[i] ==' ' || i==size || b[i]==(char)0 || b[i]==(char)9 )
            {
                for (n; n<=i ; n++ )
                {
                    if(b[n]==' ' || b[n]==(char)0 || b[n]==(char)9) {}
                    else
                    {
                        instructionList[j].push_back(b[n]) ;

                        f = 1 ;
                    }
                }
                if (f==1)
                {
                    j++;
                }

                n=i ;
            }
            if (j==6)
            {
                n=i ;
                i=size+1 ;
            }
        }

        i=n ;
        int oldloc = locationCounter;
        int errorFlag=evaluator(opTable , symbolTable , directiveTable , locationCounter) ;
        instruction->errorFlag=errorFlag;
        instruction->input = b ;
        instruction->write(output,oldloc);

        if (errorFlag==15 || errorFlag==23) {
            m=1 ;
        break;
         }

         }
    if (!m){
        instruction->label.clear() ;
        instruction->mnemonic.clear();
        instruction->operand.clear();
    instruction->errorFlag=19 ;
    instruction->write(output,locationCounter);
    }

    mystream.close();
}

parser::parser ()
{
    instruction = new Instruction();
    for (int i=0 ; i<5 ; i++ )
    {
        instructionList[i].clear();
    }
}

int parser::findIn(string b , char c){
for (int i=0 ; i<b.size();i++){
if (b.at(i)==c) return i ;
}
return -1 ;
}

bool parser::isInt(string a){
for (int i=0 ; i<a.size();i++){
if ((a.at(i)<'0' || a.at(i)>'9')&& a.at(i)!=(char)0){return 0;}
}
return 1 ;
}




parser::~parser(){
delete instruction ;
}
