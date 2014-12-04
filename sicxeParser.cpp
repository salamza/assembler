#include "sicxeParser.h"
#include "hashTable.h"
#include <string>

    sicxeParser::sicxeParser(){
        reg[0]='A';
        reg[1]='X';
        reg[2]='L';
        reg[3]='S';
        reg[4]='T';
        reg[5]='F';
        reg[6]='B';
        }

        bool sicxeParser::isHex(string a){
for (int i=0 ; i<a.size();i++){

if ((a.at(i)<'0' || a.at(i)>'9' )&& a.at(i)!='A'&& a.at(i)!='B'&& a.at(i)!='C'&& a.at(i)!='D'&& a.at(i)!='E'&& a.at(i)!='F'&& a.at(i)!=(char)0){return 0;}
}
if (strtol(a.c_str(),NULL,16) >= 1048576) return 0;
return 1 ;
}

bool sicxeParser::isReg(char g){
    for (int i=0 ; i<9 ; i++){
        if (reg[i]==g)return 1 ;
        }
        return 0 ;
    }

int sicxeParser::evaluator (hashTable* opTable , hashTable* symbolTable , hashTable* directiveTable , int &locationCounter)
{

    if (instructionList[0].empty())
    {
        return 0;
    }

    else if (instructionList[0].at(0)=='.')
    {
        return 9 ;
    }

    else if (opTable->getValue(instructionList[0])!=-2)
    {
        instruction->mnemonic = instructionList[0] ;
        if (instructionList[0] == "RSUB")
        {
            if (locationCounter==-1) locationCounter=3 ;
            else locationCounter =locationCounter+3 ;
            return 0 ;
        }

        if (instructionList[1].empty())
        {
            return 5;
        }
        if (opTable->getFormat(instructionList[0])==2){
            if (instructionList[0]=="CLEAR" || instructionList[0]=="TIXR"){
                            if (isReg(instructionList[1].at(0))){
                instruction->mnemonic = instructionList[0] ;
                instruction->operand = instructionList[1] ;
                if (locationCounter==-1) locationCounter=2 ;
                else locationCounter = locationCounter + 2 ;
                return 0 ;
                                }
                                else return 31 ;
                            }
            if (instructionList[1].size()==1 && instructionList[2].size()==1 && instructionList[3].size()==1){
                if (instructionList[2]=="," && isReg(instructionList[1].at(0))&&isReg(instructionList[3].at(0))){
                instruction->mnemonic = instructionList[0] ;
                instruction->operand = instructionList[1]+","+instructionList[3] ;
                if (locationCounter==-1) locationCounter=2 ;
                else locationCounter = locationCounter + 2 ;
                return 0 ;
                }
                else return 30 ;
                }

                else if (instructionList[1].size()==2 && instructionList[2].size()==1){
                    if (isReg(instructionList[1].at(0))&&instructionList[1].at(1)==',' &&isReg(instructionList[2].at(0))){
                       instruction->mnemonic = instructionList[0] ;
                instruction->operand = instructionList[1]+instructionList[2];
                if (locationCounter==-1) locationCounter=2 ;
                else locationCounter = locationCounter + 2 ;
                return 0 ;
                        }
                        else return 30 ;
                    }
                else if (instructionList[1].size()==1 && instructionList[2].size()==2){
                    if (isReg(instructionList[1].at(0))&&instructionList[2].at(0)==',' &&isReg(instructionList[2].at(1))){
                       instruction->mnemonic = instructionList[0] ;
                instruction->operand = instructionList[1]+instructionList[2];
                if (locationCounter==-1) locationCounter=2 ;
                else locationCounter = locationCounter + 2 ;
                return 0 ;
                        }
                        else return 30 ;
                    }
                    else if (instructionList[1].size()==3){
                        if (isReg(instructionList[1].at(0))&&instructionList[1].at(1)==','&&isReg(instructionList[1].at(2))){
                    instruction->mnemonic = instructionList[0] ;
                instruction->operand = instructionList[1];
                if (locationCounter==-1) locationCounter=2 ;
                else locationCounter = locationCounter + 2 ;
                return 0 ;
                            }
                            else return 30 ;
                        }
                    return 30 ;
            }
        if (instructionList[1].at(0)=='+'){return 24;}
        if (instructionList[1].size()==1 && (instructionList[1].at(0)=='@' || instructionList[1].at(0)=='#')){
            if (instructionList[2].empty()){return 25;}
            else if (instructionList[2].at(0)=='@' ||instructionList[2].at(0)=='@' ) return 24 ;
            else if (opTable->getValue(instructionList[2])!=-2|| directiveTable->getValue(instructionList[2])!=-2){return 26;}
            else {
                string g = instructionList[2];
                if (g=="A" ||g=="B" ||g=="X" ||g=="PC" ||g=="SW" ||g=="S" ||g=="L" ||g=="T" ||g=="F")return 6 ;
                else if (((int)g.at(0) <= (int)'9') &&((int)g.at(0) >=  (int)'0' )){
                    if (!isHex(g))return 4;
                    }
                instruction->mnemonic = instructionList[0] ;
                instruction->operand = instructionList[1]+instructionList[2];
                if (locationCounter==-1) locationCounter=3 ;
                else locationCounter = locationCounter+3 ;
                return 0 ;
                }
            }
            if ((instructionList[1].at(0)=='@')|| (instructionList[1].at(0)=='#')){
                string g ;
                g = instructionList[1].substr(1,instructionList[1].size()) ;
                if (opTable->getValue(g)!=-2|| directiveTable->getValue(g)!=-2) return 26 ;
                else if (g.at(0)=='@' || g.at(0)=='#') return 24;
                if (g=="A" ||g=="B" ||g=="X" ||g=="PC" ||g=="SW" ||g=="S" ||g=="L" ||g=="T" ||g=="F") return 6;
                else if (((int)g.at(0) <= (int)'9') &&((int)g.at(0) >=  (int)'0' )){
                    if (!isHex(g))return 4;
                    }

            if (locationCounter==-1) locationCounter=3 ;
            else locationCounter =locationCounter+3 ;
                instruction->mnemonic = instructionList[0];
                instruction->operand = instructionList[1] ;
                return 0 ;
                }
        if (!instructionList[2].empty())
        {
            if ((instructionList[1].at(instructionList[1].size()-1)== ',') && (instructionList[2].at(0)=='X'))
            {
                //opppo
                if (instructionList[2].size() !=1)
                {
                    instruction->operand=instructionList[1];

                    if (locationCounter==-1) locationCounter=3 ;
                    else locationCounter =locationCounter+3 ;
                    return 0 ;
                }
                else
                {
                    instruction->operand=instructionList[1]+"X" ;

                    if (locationCounter==-1) locationCounter=3 ;
                    else locationCounter =locationCounter+3 ;
                    return 0 ;
                }
            }


            if ((instructionList[2].at(0)== ',') && (instructionList[2].size()==2))
            {
                if (instructionList[2].at(1)=='X')
                {
                    instruction->operand=instructionList[1]+",X";         //Modifed By Same7

                    if (locationCounter==-1) locationCounter=3 ;
                    else locationCounter =locationCounter+3 ;
                    return 0;
                }
            }
        }
        if (!instructionList[3].empty() && !instructionList[2].empty())
        {
            if ((instructionList[2].at(0)== ',') && (instructionList[2].size()==1)&& instructionList[3].size()==1 && instructionList[3].at(0)=='X')
            {
                instruction->operand=instructionList[1]+",X";   //Modified By Same7

                if (locationCounter==-1) locationCounter=3 ;
                else locationCounter =locationCounter+3 ;
                return 0;
            }
        }
        if (opTable->getValue(instructionList[1]) != -2)
        {
            return 1;
        }
        if (directiveTable->getValue(instructionList[1]) != -2)
        {
            return 2;
        }
        if (instructionList[1].at(0) == '.')
        {
            return 3;
        }
        if (((int)instructionList[1].at(0) <= (int)'9') &&((int)instructionList[1].at(0) >=  (int)'0' ) )
        {
            return 4;
        }
        //register error ya ma3alm
        if (instructionList[1].size()==1)
        {
            if (instructionList[1].at(0)=='A' || instructionList[1].at(0)=='X' || instructionList[1].at(0)=='L' || instructionList[1].at(0)=='F' || instructionList[1].at(0)=='S'|| instructionList[1].at(0)=='T'|| instructionList[1].at(0)=='B' )
            {
                return 6;
            }
        }
        if (instructionList[1].size()==2)
        {
            if ((instructionList[1].at(0)=='P' &&instructionList[1].at(1)=='C' ) || (instructionList[1].at(0)=='S' &&instructionList[1].at(1)=='W' ))
            {
                return 6 ;
            }
        }
        instruction->operand = instructionList[1];

        if (locationCounter==-1) locationCounter=3 ;
        else locationCounter =locationCounter+3 ;
        return 0;
    }
    else if (instructionList[0].at(0)=='@' || instructionList[0].at(0)=='#') return 27;
/////////////////////////////////////////////////////////////////////////////////////////////////////
    else if (instructionList[0].at(0)=='+'){
        if (instructionList[0].size()==1){
            if (opTable->getValue(instructionList[1])==-2){return 27;}
            if (opTable->getFormat(instructionList[1])==2){return 29;}
            instruction->mnemonic = "+"+instructionList[1] ;
        if (instructionList[1] == "RSUB")
        {
            if (locationCounter==-1) locationCounter=4 ;
            else locationCounter =locationCounter+4 ;
            return 0 ;
        }
        if (instructionList[2].empty())
        {
            return 5;
        }
        if (instructionList[2].at(0)=='+'){return 24;}
        if (instructionList[2].size()==1 && (instructionList[2].at(0)=='@' || instructionList[2].at(0)=='#')){
            if (instructionList[3].empty()){return 25;}
            else if (instructionList[3].at(0)=='@' ||instructionList[3].at(0)=='@' ) return 24 ;
            else if (opTable->getValue(instructionList[3])!=-2|| directiveTable->getValue(instructionList[3])!=-2){return 26;}
            else {
                string g = instructionList[3];
                if (g=="A" ||g=="B" ||g=="X" ||g=="PC" ||g=="SW" ||g=="S" ||g=="L" ||g=="T" ||g=="F")return 6 ;
                else if (((int)g.at(0) <= (int)'9') &&((int)g.at(0) >=  (int)'0' )){
                    if (!isHex(g))return 4;
                    }
                instruction->mnemonic = "+"+instructionList[1] ;
                instruction->operand = instructionList[2]+instructionList[3];
                if (locationCounter==-1) locationCounter=4 ;
                else locationCounter = locationCounter+4 ;
                return 0 ;
                }
            }
            if ((instructionList[2].at(0)=='@')|| (instructionList[2].at(0)=='#')){
                string g ;
                g = instructionList[2].substr(1,instructionList[2].size()) ;
                if (opTable->getValue(g)!=-2|| directiveTable->getValue(g)!=-2) return 26 ;
                else if (g.at(0)=='@' || g.at(0)=='#') return 24;
                if (g=="A" ||g=="B" ||g=="X" ||g=="PC" ||g=="SW" ||g=="S" ||g=="L" ||g=="T" ||g=="F") return 6;
                else if (((int)g.at(0) <= (int)'9') &&((int)g.at(0) >=  (int)'0' )){
                    if (!isHex(g))return 4;
                    }

            if (locationCounter==-1) locationCounter=4 ;
            else locationCounter =locationCounter+4 ;
                instruction->mnemonic = "+"+instructionList[1];
                instruction->operand = instructionList[2] ;
                return 0 ;
                }
        if (!instructionList[3].empty())
        {
            if ((instructionList[2].at(instructionList[2].size()-1)== ',') && (instructionList[3].at(0)=='X'))
            {
                //opppo
                if (instructionList[3].size() !=1)
                {
                    instruction->operand=instructionList[2];

                    if (locationCounter==-1) locationCounter=4 ;
                    else locationCounter =locationCounter+4 ;
                    return 0 ;
                }
                else
                {
                    instruction->operand=instructionList[2]+"X" ;

                    if (locationCounter==-1) locationCounter=4 ;
                    else locationCounter =locationCounter+4 ;
                    return 0 ;
                }
            }


            if ((instructionList[3].at(0)== ',') && (instructionList[3].size()==2))
            {
                if (instructionList[3].at(1)=='X')
                {
                    instruction->operand=instructionList[2]+",X";         //Modifed By Same7

                    if (locationCounter==-1) locationCounter=4 ;
                    else locationCounter =locationCounter+4 ;
                    return 0;
                }
            }
        }
        if (!instructionList[4].empty() && !instructionList[3].empty())
        {
            if ((instructionList[3].at(0)== ',') && (instructionList[3].size()==1)&& instructionList[4].size()==1 && instructionList[4].at(0)=='X')
            {
                instruction->operand=instructionList[2]+",X";   //Modified By Same7

                if (locationCounter==-1) locationCounter=4 ;
                else locationCounter =locationCounter+4 ;
                return 0;
            }
        }
        if (opTable->getValue(instructionList[2]) != -2)
        {
            return 1;
        }
        if (directiveTable->getValue(instructionList[2]) != -2)
        {
            return 2;
        }
        if (instructionList[2].at(0) == '.')
        {
            return 3;
        }
        if (((int)instructionList[2].at(0) <= (int)'9') &&((int)instructionList[2].at(0) >=  (int)'0' ) )
        {
            return 4;
        }
        //register error ya ma3alm
        if (instructionList[2].size()==1)
        {
            if (instructionList[2].at(0)=='A' || instructionList[2].at(0)=='X' || instructionList[2].at(0)=='L' || instructionList[2].at(0)=='F' || instructionList[2].at(0)=='S'|| instructionList[2].at(0)=='T'|| instructionList[2].at(0)=='B' )
            {
                return 6;
            }
        }
        if (instructionList[2].size()==2)
        {
            if ((instructionList[2].at(0)=='P' &&instructionList[2].at(1)=='C' ) || (instructionList[2].at(0)=='S' &&instructionList[2].at(1)=='W' ))
            {
                return 6 ;
            }
        }
        instruction->operand = instructionList[2];

        if (locationCounter==-1) locationCounter=4 ;
        else locationCounter =locationCounter+4 ;
        return 0;
            }
            ///////////////////////////////////////////////

            instructionList[0] = instructionList[0].substr(1,instructionList[0].size());
            if (opTable->getValue(instructionList[0])==-2)return 27;
            if (opTable->getFormat(instructionList[0])==2){return 29;}
            instruction->mnemonic = "+"+instructionList[0] ;
        if (instructionList[0] == "RSUB")
        {
            if (locationCounter==-1) locationCounter=4 ;
            else locationCounter =locationCounter+4 ;
            return 0 ;
        }
        if (instructionList[1].empty())
        {
            return 5;
        }
        if (instructionList[1].at(0)=='+'){return 24;}
        if (instructionList[1].size()==1 && (instructionList[1].at(0)=='@' || instructionList[1].at(0)=='#')){
            if (instructionList[2].empty()){return 25;}
            else if (instructionList[2].at(0)=='@' ||instructionList[2].at(0)=='@' ) return 24 ;
            else if (opTable->getValue(instructionList[2])!=-2|| directiveTable->getValue(instructionList[2])!=-2){return 26;}
            else {
                string g = instructionList[2];
                if (g=="A" ||g=="B" ||g=="X" ||g=="PC" ||g=="SW" ||g=="S" ||g=="L" ||g=="T" ||g=="F")return 6 ;
                else if (((int)g.at(0) <= (int)'9') &&((int)g.at(0) >=  (int)'0' )){
                    if (!isHex(g))return 4;
                    }
                instruction->mnemonic = "+"+instructionList[0] ;
                instruction->operand = instructionList[1]+instructionList[2];
                if (locationCounter==-1) locationCounter=4 ;
                else locationCounter = locationCounter+4 ;
                return 0 ;
                }
            }
            if ((instructionList[1].at(0)=='@')|| (instructionList[1].at(0)=='#')){
                string g ;
                g = instructionList[1].substr(1,instructionList[1].size()) ;
                if (opTable->getValue(g)!=-2|| directiveTable->getValue(g)!=-2) return 26 ;
                else if (g.at(0)=='@' || g.at(0)=='#') return 24;
                if (g=="A" ||g=="B" ||g=="X" ||g=="PC" ||g=="SW" ||g=="S" ||g=="L" ||g=="T" ||g=="F") return 6;
                else if (((int)g.at(0) <= (int)'9') &&((int)g.at(0) >=  (int)'0' )){
                    if (!isHex(g))return 4;
                    }
                instruction->mnemonic = "+"+instructionList[0];
                instruction->operand = instructionList[1] ;
                return 0 ;
                }
        if (!instructionList[2].empty())
        {
            if ((instructionList[1].at(instructionList[1].size()-1)== ',') && (instructionList[2].at(0)=='X'))
            {
                //opppo
                if (instructionList[2].size() !=1)
                {
                    instruction->operand=instructionList[1];

                    if (locationCounter==-1) locationCounter=4 ;
                    else locationCounter =locationCounter+4 ;
                    return 0 ;
                }
                else
                {
                    instruction->operand=instructionList[1]+"X" ;

                    if (locationCounter==-1) locationCounter=4 ;
                    else locationCounter =locationCounter+4 ;
                    return 0 ;
                }
            }


            if ((instructionList[2].at(0)== ',') && (instructionList[2].size()==2))
            {
                if (instructionList[2].at(1)=='X')
                {
                    instruction->operand=instructionList[1]+",X";         //Modifed By Same7

                    if (locationCounter==-1) locationCounter=4 ;
                    else locationCounter =locationCounter+4 ;
                    return 0;
                }
            }
        }
        if (!instructionList[3].empty() && !instructionList[2].empty())
        {
            if ((instructionList[2].at(0)== ',') && (instructionList[2].size()==1)&& instructionList[3].size()==1 && instructionList[3].at(0)=='X')
            {
                instruction->operand=instructionList[1]+",X";   //Modified By Same7

                if (locationCounter==-1) locationCounter=4 ;
                else locationCounter =locationCounter+4 ;
                return 0;
            }
        }
        if (opTable->getValue(instructionList[1]) != -2)
        {
            return 1;
        }
        if (directiveTable->getValue(instructionList[1]) != -2)
        {
            return 2;
        }
        if (instructionList[1].at(0) == '.')
        {
            return 3;
        }
        if (((int)instructionList[1].at(0) <= (int)'9') &&((int)instructionList[1].at(0) >=  (int)'0' ) )
        {
            return 4;
        }
        //register error ya ma3alm
        if (instructionList[1].size()==1)
        {
            if (instructionList[1].at(0)=='A' || instructionList[1].at(0)=='X' || instructionList[1].at(0)=='L' || instructionList[1].at(0)=='F' || instructionList[1].at(0)=='S'|| instructionList[1].at(0)=='T'|| instructionList[1].at(0)=='B' )
            {
                return 6;
            }
        }
        if (instructionList[1].size()==2)
        {
            if ((instructionList[1].at(0)=='P' &&instructionList[1].at(1)=='C' ) || (instructionList[1].at(0)=='S' &&instructionList[1].at(1)=='W' ))
            {
                return 6 ;
            }
        }
        instruction->operand = instructionList[1];

        if (locationCounter==-1) locationCounter=4 ;
        else locationCounter =locationCounter+4 ;
        return 0;
        }

    // The Label in the first string ...
    else if ((directiveTable->getValue(instructionList[0])==-2) && (opTable->getValue(instructionList[0])==-2) && (symbolTable->getValue(instructionList[0])!=-2))
    {
        return 10;    //MODIFED BY ENG.SAMEH SALAMA EL Mo7trm
    }


    else if ((directiveTable->getValue(instructionList[0])==-2) && (opTable->getValue(instructionList[0])==-2))
    {
        instruction->label = instructionList[0] ;
        symbolTable->hash(instruction->label,locationCounter);
        if(instructionList[1].at(0)=='@' || instructionList[1].at(0)=='#') return 7;
        if (instructionList[1].at(0)=='+'){
        if (instructionList[1].size()==1){
            if (opTable->getValue(instructionList[2])==-2){return 7;}
            if (opTable->getFormat(instructionList[2])==2){return 29;}
            instruction->mnemonic = "+"+instructionList[2] ;
        if (instructionList[2] == "RSUB")
        {
            if (locationCounter==-1) locationCounter=4 ;
            else locationCounter =locationCounter+4 ;
            return 0 ;
        }
        if (instructionList[3].empty())
        {
            return 5;
        }
        if (instructionList[3].at(0)=='+'){return 24;}
        if (instructionList[3].size()==1 && (instructionList[3].at(0)=='@' || instructionList[3].at(0)=='#')){
            if (instructionList[4].empty()){return 25;}
            else if (instructionList[4].at(0)=='@' ||instructionList[4].at(0)=='@' ) return 24 ;
            else if (opTable->getValue(instructionList[4])!=-2|| directiveTable->getValue(instructionList[4])!=-2){return 26;}
            else {
                string g = instructionList[4];
                if (g=="A" ||g=="B" ||g=="X" ||g=="PC" ||g=="SW" ||g=="S" ||g=="L" ||g=="T" ||g=="F")return 6 ;
                else if (((int)g.at(0) <= (int)'9') &&((int)g.at(0) >=  (int)'0' )){
                    if (!isHex(g))return 4;
                    }
                instruction->mnemonic = "+"+instructionList[2] ;
                instruction->operand = instructionList[3]+instructionList[4];
                if (locationCounter==-1) locationCounter=4 ;
                else locationCounter = locationCounter+4 ;
                return 0 ;
                }
            }
            if ((instructionList[3].at(0)=='@')|| (instructionList[3].at(0)=='#')){
                string g ;
                g = instructionList[3].substr(1,instructionList[3].size()) ;
                if (opTable->getValue(g)!=-2|| directiveTable->getValue(g)!=-2) return 26 ;
                else if (g.at(0)=='@' || g.at(0)=='#') return 24;
                if (g=="A" ||g=="B" ||g=="X" ||g=="PC" ||g=="SW" ||g=="S" ||g=="L" ||g=="T" ||g=="F") return 6;
                else if (((int)g.at(0) <= (int)'9') &&((int)g.at(0) >=  (int)'0' )){
                    if (!isHex(g))return 4;
                    }

            if (locationCounter==-1) locationCounter=4 ;
            else locationCounter =locationCounter+4 ;
                instruction->mnemonic = "+"+instructionList[2];
                instruction->operand = instructionList[3] ;
                return 0 ;
                }
        if (!instructionList[4].empty())
        {
            if ((instructionList[3].at(instructionList[3].size()-1)== ',') && (instructionList[4].at(0)=='X'))
            {
                //opppo
                if (instructionList[4].size() !=1)
                {
                    instruction->operand=instructionList[3];

                    if (locationCounter==-1) locationCounter=4 ;
                    else locationCounter =locationCounter+4 ;
                    return 0 ;
                }
                else
                {
                    instruction->operand=instructionList[3]+"X" ;

                    if (locationCounter==-1) locationCounter=4 ;
                    else locationCounter =locationCounter+4 ;
                    return 0 ;
                }
            }


            if ((instructionList[4].at(0)== ',') && (instructionList[4].size()==2))
            {
                if (instructionList[4].at(1)=='X')
                {
                    instruction->operand=instructionList[3]+",X";         //Modifed By Same7

                    if (locationCounter==-1) locationCounter=4 ;
                    else locationCounter =locationCounter+4 ;
                    return 0;
                }
            }
        }
        if (!instructionList[5].empty() && !instructionList[4].empty())
        {
            if ((instructionList[4].at(0)== ',') && (instructionList[4].size()==1)&& instructionList[5].size()==1 && instructionList[5].at(0)=='X')
            {
                instruction->operand=instructionList[3]+",X";   //Modified By Same7

                if (locationCounter==-1) locationCounter=4 ;
                else locationCounter =locationCounter+4 ;
                return 0;
            }
        }
        if (opTable->getValue(instructionList[3]) != -2)
        {
            return 1;
        }
        if (directiveTable->getValue(instructionList[3]) != -2)
        {
            return 2;
        }
        if (instructionList[3].at(0) == '.')
        {
            return 3;
        }
        if (((int)instructionList[3].at(0) <= (int)'9') &&((int)instructionList[3].at(0) >=  (int)'0' ) )
        {
            return 4;
        }
        //register error ya ma3alm
        if (instructionList[3].size()==1)
        {
            if (instructionList[3].at(0)=='A' || instructionList[3].at(0)=='X' || instructionList[3].at(0)=='L' || instructionList[3].at(0)=='F' || instructionList[3].at(0)=='S'|| instructionList[3].at(0)=='T'|| instructionList[3].at(0)=='B' )
            {
                return 6;
            }
        }
        if (instructionList[3].size()==2)
        {
            if ((instructionList[3].at(0)=='P' &&instructionList[3].at(1)=='C' ) || (instructionList[3].at(0)=='S' &&instructionList[3].at(1)=='W' ))
            {
                return 6 ;
            }
        }
        instruction->operand = instructionList[3];

        if (locationCounter==-1) locationCounter=4 ;
        else locationCounter =locationCounter+4 ;
        return 0;
            }
            ///////////////////////////////////////////////

            instructionList[1] = instructionList[1].substr(1,instructionList[1].size());
            if (opTable->getValue(instructionList[1])==-2)return 7;
            if (opTable->getFormat(instructionList[1])==2){return 29;}
            instruction->mnemonic = "+"+instructionList[1] ;
        if (instructionList[1] == "RSUB")
        {
            if (locationCounter==-1) locationCounter=4 ;
            else locationCounter =locationCounter+4 ;
            return 0 ;
        }
        if (instructionList[2].empty())
        {
            return 5;
        }
        if (instructionList[2].at(0)=='+'){return 24;}
        if (instructionList[2].size()==1 && (instructionList[2].at(0)=='@' || instructionList[2].at(0)=='#')){
            if (instructionList[3].empty()){return 25;}
            else if (instructionList[3].at(0)=='@' ||instructionList[3].at(0)=='@' ) return 24 ;
            else if (opTable->getValue(instructionList[3])!=-2|| directiveTable->getValue(instructionList[3])!=-2){return 26;}
            else {
                string g = instructionList[3];
                if (g=="A" ||g=="B" ||g=="X" ||g=="PC" ||g=="SW" ||g=="S" ||g=="L" ||g=="T" ||g=="F")return 6 ;
                else if (((int)g.at(0) <= (int)'9') &&((int)g.at(0) >=  (int)'0' )){
                    if (!isHex(g))return 4;
                    }
                instruction->mnemonic = "+"+instructionList[1] ;
                instruction->operand = instructionList[2]+instructionList[3];
                if (locationCounter==-1) locationCounter=4 ;
                else locationCounter = locationCounter+4 ;
                return 0 ;
                }
            }
            if ((instructionList[2].at(0)=='@')|| (instructionList[2].at(0)=='#')){
                string g ;
                g = instructionList[2].substr(1,instructionList[2].size()) ;
                if (opTable->getValue(g)!=-2|| directiveTable->getValue(g)!=-2) return 26 ;
                else if (g.at(0)=='@' || g.at(0)=='#') return 24;
                if (g=="A" ||g=="B" ||g=="X" ||g=="PC" ||g=="SW" ||g=="S" ||g=="L" ||g=="T" ||g=="F") return 6;
                else if (((int)g.at(0) <= (int)'9') &&((int)g.at(0) >=  (int)'0' )){
                    if (!isHex(g))return 4;
                    }
                instruction->mnemonic = "+"+instructionList[1];
                instruction->operand = instructionList[2] ;
                return 0 ;
                }
        if (!instructionList[3].empty())
        {
            if ((instructionList[2].at(instructionList[2].size()-1)== ',') && (instructionList[3].at(0)=='X'))
            {
                //opppo
                if (instructionList[3].size() !=1)
                {
                    instruction->operand=instructionList[2];

                    if (locationCounter==-1) locationCounter=4 ;
                    else locationCounter =locationCounter+4 ;
                    return 0 ;
                }
                else
                {
                    instruction->operand=instructionList[2]+"X" ;

                    if (locationCounter==-1) locationCounter=4 ;
                    else locationCounter =locationCounter+4 ;
                    return 0 ;
                }
            }


            if ((instructionList[3].at(0)== ',') && (instructionList[3].size()==2))
            {
                if (instructionList[3].at(1)=='X')
                {
                    instruction->operand=instructionList[2]+",X";         //Modifed By Same7

                    if (locationCounter==-1) locationCounter=4 ;
                    else locationCounter =locationCounter+4 ;
                    return 0;
                }
            }
        }
        if (!instructionList[4].empty() && !instructionList[3].empty())
        {
            if ((instructionList[3].at(0)== ',') && (instructionList[3].size()==1)&& instructionList[4].size()==1 && instructionList[4].at(0)=='X')
            {
                instruction->operand=instructionList[2]+",X";   //Modified By Same7

                if (locationCounter==-1) locationCounter=4 ;
                else locationCounter =locationCounter+4 ;
                return 0;
            }
        }
        if (opTable->getValue(instructionList[2]) != -2)
        {
            return 1;
        }
        if (directiveTable->getValue(instructionList[2]) != -2)
        {
            return 2;
        }
        if (instructionList[2].at(0) == '.')
        {
            return 3;
        }
        if (((int)instructionList[2].at(0) <= (int)'9') &&((int)instructionList[2].at(0) >=  (int)'0' ) )
        {
            return 4;
        }
        //register error ya ma3alm
        if (instructionList[2].size()==1)
        {
            if (instructionList[2].at(0)=='A' || instructionList[2].at(0)=='X' || instructionList[2].at(0)=='L' || instructionList[2].at(0)=='F' || instructionList[2].at(0)=='S'|| instructionList[2].at(0)=='T'|| instructionList[2].at(0)=='B' )
            {
                return 6;
            }
        }
        if (instructionList[2].size()==2)
        {
            if ((instructionList[2].at(0)=='P' &&instructionList[2].at(1)=='C' ) || (instructionList[2].at(0)=='S' &&instructionList[2].at(1)=='W' ))
            {
                return 6 ;
            }
        }
        instruction->operand = instructionList[2];

        if (locationCounter==-1) locationCounter=4 ;
        else locationCounter =locationCounter+4 ;
        return 0;
        }

        bool w=0 ;
        instruction->label = instructionList[0];
        if (instructionList[1].empty())
        {
            return 17;
        }
        if (((int)instructionList[0].at(0) <= (int)'9') &&((int)instructionList[0].at(0) >=  (int)'0' ) )
        {
            return 4;
        }
                if (locationCounter==-1 && !instructionList[1].empty() && instructionList[2].empty() && instructionList[1]=="START" )
        {
            locationCounter=strtol(instructionList[2].c_str(),NULL,16);
            w=1 ;

        }
        if (locationCounter==-1 && !instructionList[1].empty() && !instructionList[2].empty() && instructionList[1]=="START" && isHex(instructionList[2]))
        {
            locationCounter=strtol(instructionList[2].c_str(),NULL,16);
            w=1 ;

        }
        if (locationCounter == -1)
        {
            locationCounter=0 ;
        }
        symbolTable->hash(instructionList[0],locationCounter);


        instruction->label=instructionList[0];
        if ((directiveTable->getValue(instructionList[1])==-2)&&(opTable->getValue(instructionList[1])==-2))
        {
            return 11;
        }
        else if (opTable->getValue(instructionList[1])!=-2)
        {
            instruction->mnemonic = instructionList[1] ;
            if (instructionList[1] == "RSUB")
            {
                locationCounter =locationCounter+3 ;
                return 0 ;
            }

                    if (opTable->getFormat(instructionList[1])==2){
                        instruction->label = instructionList[0];
                        if (instructionList[1]=="CLEAR" || instructionList[1]=="TIXR"){
                            if (isReg(instructionList[2].at(0))){
                instruction->mnemonic = instructionList[1] ;
                instruction->operand = instructionList[2] ;
                if (locationCounter==-1) locationCounter=2 ;
                else locationCounter = locationCounter + 2 ;
                return 0 ;
                                }
                                else return 31 ;
                            }

            if (instructionList[2].size()==1 && instructionList[3].size()==1 && instructionList[4].size()==1){
                if (instructionList[3]=="," && isReg(instructionList[2].at(0))&&isReg(instructionList[4].at(0))){
                instruction->mnemonic = instructionList[1] ;
                instruction->operand = instructionList[2]+","+instructionList[4] ;
                if (locationCounter==-1) locationCounter=2 ;
                else locationCounter = locationCounter + 2 ;
                return 0 ;
                }
                else return 30 ;
                }

                else if (instructionList[2].size()==2 && instructionList[3].size()==1){
                    if (isReg(instructionList[2].at(0))&&instructionList[2].at(1)==',' &&isReg(instructionList[3].at(0))){
                       instruction->mnemonic = instructionList[1] ;
                instruction->operand = instructionList[2]+instructionList[3];
                if (locationCounter==-1) locationCounter=2 ;
                else locationCounter = locationCounter + 2 ;
                return 0 ;
                        }
                        else return 30 ;
                    }
                else if (instructionList[2].size()==1 && instructionList[3].size()==2){
                    if (isReg(instructionList[2].at(0))&&instructionList[3].at(0)==',' &&isReg(instructionList[3].at(1))){
                       instruction->mnemonic = instructionList[1] ;
                instruction->operand = instructionList[2]+instructionList[3];
                if (locationCounter==-1) locationCounter=2 ;
                else locationCounter = locationCounter + 2 ;
                return 0 ;
                        }
                        else return 30 ;
                    }
                    else if (instructionList[2].size()==3){
                        if (isReg(instructionList[2].at(0))&&instructionList[2].at(1)==','&&isReg(instructionList[2].at(2))){
                    instruction->mnemonic = instructionList[1] ;
                instruction->operand = instructionList[2];
                if (locationCounter==-1) locationCounter=2 ;
                else locationCounter = locationCounter + 2 ;
                            return 0 ;
                            }
                            else return 30 ;
                        }
                    return 30 ;
            }

        if (instructionList[2].at(0)=='+'){return 24;}
        if (instructionList[2].size()==1 && (instructionList[2].at(0)=='@' || instructionList[2].at(0)=='#')){
            if (instructionList[3].empty()){return 25;}
            else if (instructionList[3].at(0)=='@' ||instructionList[3].at(0)=='@' ) return 24 ;
            else if (opTable->getValue(instructionList[3])!=-2|| directiveTable->getValue(instructionList[3])!=-2){return 26;}
            else {
                string g = instructionList[3];
                if (g=="A" ||g=="B" ||g=="X" ||g=="PC" ||g=="SW" ||g=="S" ||g=="L" ||g=="T" ||g=="F")return 6 ;
                else if (((int)g.at(0) <= (int)'9') &&((int)g.at(0) >=  (int)'0' )){
                    if (!isHex(g))return 4;
                    }
                instruction->mnemonic = instructionList[1] ;
                instruction->operand = instructionList[2]+instructionList[3];
                if (locationCounter==-1) locationCounter=3 ;
                else locationCounter = locationCounter+3 ;
                return 0 ;
                }
            }
            if ((instructionList[2].at(0)=='@')|| (instructionList[2].at(0)=='#')){
                string g ;
                g = instructionList[2].substr(1,instructionList[2].size()) ;
                if (opTable->getValue(g)!=-2|| directiveTable->getValue(g)!=-2) return 26 ;
                else if (g.at(0)=='@' || g.at(0)=='#') return 24;
                if (g=="A" ||g=="B" ||g=="X" ||g=="PC" ||g=="SW" ||g=="S" ||g=="L" ||g=="T" ||g=="F") return 6;
                else if (((int)g.at(0) <= (int)'9') &&((int)g.at(0) >=  (int)'0' )){
                    if (!isHex(g))return 4;
                    }

            if (locationCounter==-1) locationCounter=3 ;
            else locationCounter =locationCounter+3 ;
                instruction->mnemonic = instructionList[1];
                instruction->operand = instructionList[2] ;
                return 0 ;
                }

                    if (instructionList[2].empty())
            {
                return 5;
            }
            if (!instructionList[3].empty())
            {
                if ((instructionList[2].at(instructionList[2].size()-1)== ',') && (instructionList[3].at(0)=='X'))
                {
                    //opppo
                    if (instructionList[3].size() !=1)
                    {
                        instruction->operand=instructionList[2];

                        locationCounter =locationCounter+3 ;
                        return 0 ;
                    }
                    else
                    {
                        instruction->operand=instructionList[2]+"X" ;

                        locationCounter =locationCounter+3 ;
                        return 0 ;
                    }
                }
                if ((instructionList[3].at(0)== ',') && instructionList[3].size()==2)  //Check this one again :)_same7
                    //popopo
                {
                    if (instructionList[3].at(1)=='X')
                    {
                        instruction->operand= instructionList[2]+",X";

                        locationCounter =locationCounter+3 ;
                        return 0;
                    }
                }
            }
            if (!instructionList[4].empty() && !instructionList[3].empty())
            {
                if ((instructionList[3].at(0)== ',') && (instructionList[3].size()==1)&& instructionList[4].size()==1 && instructionList[4].at(0)=='X')
                {
                    instruction->operand=instructionList[2]+",X";     //it was a[2] so i modified it _ Sameh
                    locationCounter =locationCounter+3 ;
                    return 0;
                }
            }
            if (opTable->getValue(instructionList[2]) != -2)
            {
                return 1;
            }
            if (directiveTable->getValue(instructionList[2]) != -2)
            {
                return 2;
            }
            if (instructionList[2].at(0) == '.')
            {
                return 3;
            }
            if (((int)instructionList[2].at(0) <= (int)'9') &&((int)instructionList[2].at(0) >=  (int)'0' ) )
            {
                return 4;
            }
            //register error ya ma3alm
            if (instructionList[2].size()==1)
            {
                if (instructionList[2].at(0)=='A' || instructionList[2].at(0)=='X' || instructionList[2].at(0)=='L'|| instructionList[1].at(0)=='F' || instructionList[1].at(0)=='S'|| instructionList[1].at(0)=='T'|| instructionList[1].at(0)=='B' )
                {
                    return 6;
                }
            }
            if (instructionList[2].size()==2)
            {
                if ((instructionList[2].at(0)=='P' &&instructionList[2].at(1)=='C' ) || (instructionList[2].at(0)=='S' &&instructionList[2].at(1)=='W' ))
                {
                    return 6 ;
                }
            }
            instruction->operand = instructionList[2];
            locationCounter =locationCounter+3 ;
            return 0;
        }
        //Elly b3d el label directive ::::::hhaaaahhaa 3mr sa3id
        else if (directiveTable->getValue(instructionList[1])!=-2)
        {
            instruction->mnemonic=instructionList[1];
            if (instructionList[1]!="START" && instructionList[1]!="END")
            {
                 if (instructionList[1]=="BASE"){
            instruction->operand=instructionList[2];
            return 0;
            }
                    if (instructionList[1]=="NOBASE"){
            instruction->operand=instructionList[2];
            return 0;
            }
                if (instructionList[2].empty())
                {
                    return 12;
                }
                if (instructionList[1]=="RESW")
                {
                    if (!isInt(instructionList[2]))
                    {
                        return 7 ;
                    }
                    else
                    {
                        symbolTable->hash(instructionList[0],locationCounter);

                        locationCounter = locationCounter+(3*atoi(instructionList[2].c_str()));
                        instruction->operand = instructionList[2];
                        return 0;
                    }
                }
                if (instructionList[1]=="RESB")
                {
                    if (!isInt(instructionList[2]))
                    {
                        return 7 ;
                    }
                    else
                    {
                        symbolTable->hash(instructionList[0],locationCounter);

                        locationCounter = locationCounter+(atoi(instructionList[2].c_str()));
                        instruction->operand = instructionList[2];
                        return 0;
                    }
                }
                if (instructionList[1]=="WORD")
                {
                    if (!isInt(instructionList[2]))
                    {
                        return 7 ;
                    }
                    else
                    {
                        symbolTable->hash(instructionList[0],locationCounter);

                        locationCounter = locationCounter+3;
                        instruction->operand = instructionList[2];
                        return 0;
                    }
                }
                ////////////////////////////////////////////////////////////////////////////////// BYTE
                if (instructionList[1]=="BYTE")
                {
                    if (instructionList[2].at(0)!='C' && instructionList[2].at(0)!='X')
                    {
                        return 7;
                    }
                    if (instructionList[2].size()==1)
                    {
                        if (instructionList[3].at(0)!=(char)39)
                        {
                            return 7;
                        }
                    }
                    if (instructionList[2].size()>1 && instructionList[2].at(1)!=(char)39)
                    {
                        return 7;
                    }
                    instructionList[6]=instructionList[6].substr(1,instructionList[6].size());
                    if (findIn(instructionList[6], (char)39)==-1)
                    {
                        return 7;
                    }
                    int u = findIn(instructionList[6], (char)39);
                    //instructionList[6]=instructionList[6].substr(1,u-1);
                    instructionList[6]=instructionList[6].substr(0,u);
                    if (instructionList[2].at(0)=='C')
                    {
                        symbolTable->hash(instructionList[0],locationCounter);

                        //locationCounter = locationCounter + (u-1);
                        locationCounter = locationCounter + (u);
                        instruction->operand="C'"+instructionList[6] + "'" ;
                        return 0 ;
                    }
                    else
                    {
                        if (findIn(instructionList[6],' ')!=-1)
                        {
                            return 7;
                        }
                        symbolTable->hash(instructionList[0],locationCounter);

                        //if ((u-1)%2 == 1){return 7 ;}
                        if ((u)%2 == 1)
                        {
                            return 7 ;
                        }
                        if (!(isHex(instructionList[6])))
                        {
                            return 7;
                        }
                        //locationCounter = locationCounter+((u-1)/2);
                        locationCounter = locationCounter+((u)/2);
                        instruction->operand="X'"+instructionList[6] + "'" ;
                        return 0;
                    }
                }
                //////////////////////////////////////////////////////////////////////////////////
            }
            if (instructionList[1]=="START")
            {
                if (locationCounter!=-1 && w==0)
                {
                    return 13 ;
                }
                if (instructionList[2].empty())
                {
                    locationCounter=0;
                    symbolTable->hash(instructionList[0],locationCounter);

                }
                else
                {
                    if (!isHex(instructionList[2]))
                    {
                        return 14 ;
                    }
                    else
                    {
                        locationCounter = strtol(instructionList[2].c_str(),NULL,16);
                        instruction->operand = instructionList[2];
                        symbolTable->hash(instructionList[0],locationCounter);

                    }
                }
                return 0;
            }

            if (instructionList[1] == "END")
            {
                return 18;
            }
            //// 3mr sa3eeed eltany =D
        }
    }

    // THE FIRST string is DIRECTIve " START Or End "

    else if (directiveTable->getValue(instructionList[0])!=-2)
    {
        //if (!instructionList[1].empty() && (instructionList[1].at(0)=='+' ||instructionList[1].at(0)=='#'||instructionList[1].at(0)=='@' )) return 24;
        instruction->mnemonic=instructionList[0];
        if (instructionList[0]!="START" && instructionList[0]!="END")
        {
            if (locationCounter == -1) {locationCounter = 0;}
             if (instructionList[0]=="BASE"){
            instruction->operand=instructionList[1];
            return 0;
            }
                    if (instructionList[0]=="NOBASE"){
            instruction->operand=instructionList[1];
            return 0;
            }
            if (instructionList[1].empty())
            {
                return 12;
            }
            if (instructionList[0]=="RESW")
            {
                if (!isInt(instructionList[1]))
                {
                    return 7 ;
                }
                else
                {
                    locationCounter = locationCounter+(3*atoi(instructionList[1].c_str()));
                    instruction->operand = instructionList[1];
                    return 21;
                }
            }
            if (instructionList[0]=="RESB")
            {
                if (!isInt(instructionList[1]))
                {
                    return 7 ;
                }
                else
                {
                    locationCounter = locationCounter+(atoi(instructionList[1].c_str()));
                    instruction->operand = instructionList[1];
                    return 21;
                }
            }
            if (instructionList[0]=="WORD")
            {
                if (!isInt(instructionList[1]))
                {
                    return 7 ;
                }
                else
                {
                    locationCounter = locationCounter+3;
                    instruction->operand = instructionList[1];
                    return 21;
                }
            }
            ////////////////////////////////////////////////////////////////////////////////// BYTE
            if (instructionList[0]=="BYTE")
            {
                if (instructionList[1].at(0)!='C' && instructionList[1].at(0)!='X')
                {
                    return 7;
                }
                if (instructionList[1].size()==1)
                {
                    if (instructionList[2].at(0)!=(char)39)
                    {
                        return 7;
                    }
                }
                if (instructionList[1].size()>1 && instructionList[1].at(1)!=(char)39)
                {
                    return 7;
                }
                instructionList[6]=instructionList[6].substr(1,instructionList[6].size());
                if (findIn(instructionList[6], (char)39)==-1)
                {
                    return 7;
                }
                int u = findIn(instructionList[6], (char)39);
                //instructionList[6]=instructionList[6].substr(1,u-1);
                instructionList[6]=instructionList[6].substr(0,u);
                if (instructionList[1].at(0)=='C')
                {
                    //locationCounter = locationCounter + (u-1);
                    locationCounter = locationCounter + (u);
                    instruction->operand="C'"+instructionList[6] + "'" ;
                    return 21 ;
                }
                else
                {
                    if (findIn(instructionList[6],' ')!=-1)
                    {
                        return 7;
                    }

                    //if ((u-1)%2 == 1){return 7 ;}
                    if ((u)%2 == 1)
                    {
                        return 7 ;
                    }
                    if (!(isHex(instructionList[6])))
                    {
                        return 7;
                    }
                    //locationCounter = locationCounter+((u-1)/2);
                    locationCounter = locationCounter+((u)/2);
                    instruction->operand="X'"+instructionList[6] + "'" ;
                    return 21;
                }
            }
            //////////////////////////////////////////////////////////////////////////////////
        }
        if (instructionList[0]=="START")
        {
            if (locationCounter!=-1)
            {
                return 13 ;
            }
            if (instructionList[1].empty())
            {
                locationCounter=0;
            }
            else
            {

                if (!isHex(instructionList[1]))
                {
                    return 14 ;
                }
                else
                {
                    locationCounter = strtol(instructionList[1].c_str(),NULL,16);
                    instruction->operand = instructionList[1];
                }
            }
            return 0;
        }

        if (instructionList[0] == "END")
        {
                instruction->operand=instructionList[1];
                return 15 ;

        }

    }

}
