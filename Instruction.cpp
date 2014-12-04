
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include "Instruction.h"

void Instruction::read () {}

void Instruction::write(string output , int locationCounter)
{
    if (mnemonic == "END" && operand.empty()) errorFlag=23;
    ofstream b (output.c_str() , ios::app);
    if (input.size() == 0) {return ;}
    if (errorFlag != 0 && errorFlag != 9 && errorFlag != 15 && errorFlag!=19 && errorFlag!=20 && errorFlag!=21 && errorFlag!=23 )
    {

        b<<"."<<errorFlag<<" "<<'\t'<<input<<endl;
    }

    else if (errorFlag == 9) {return ;}

    else if (errorFlag==19)
    {
        b<<"."<<errorFlag<<'\t';
    }
    else if (errorFlag == 20){}

    else
    {

        if (locationCounter == -1)
        {
            if (mnemonic == "START")
            {
                if (operand.empty()) errorFlag=22 ;
                locationCounter= strtol(operand.c_str(),NULL ,16);
            }
            else
            {
                errorFlag = 20 ;
                locationCounter = 0;
            }
        }
        b<<setw(2)<<setfill('0')<<hex<<locationCounter<<'\t';
        b<<label<<'\t';
        b<<mnemonic<<'\t';
        b<<operand<<'\t' ;
        if (errorFlag == 20 || errorFlag == 21 || errorFlag==22|| errorFlag==23){
            b <<dec<< errorFlag << "W" ;
        }
        b<<endl ;

    }
    b.close();
}

Instruction::Instruction()
{
    input.clear() ;
    label.clear() ;
    mnemonic.clear() ;
    operand.clear() ;
    errorFlag=0 ;
}
