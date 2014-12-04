#include "obcode.h"
#include <iomanip>
#include <sstream>
#include <iostream>
using namespace std;
obcode::obcode(){
    x=0 ;
    opcode=0 ;
    address=0;
    }


void obcode::setOpcode(int opcode){
    this->opcode = opcode ;
    }
void obcode::setX (bool x){
    this->x = x;
    }
void obcode::setAddress (int address){
    this->address=address;
    }

    void obcode::setFlag(char flag){
        this->flag = flag ;
        }

    void obcode::setIn(){
        in.clear();
        stringstream a(stringstream::in | stringstream::out) ;
        string temp ;
        a<<setw(2)<<setfill('0')<<hex<<opcode;
        a>>temp;
        in = temp ;
        if(x==1){address = address+32768;}
        a.clear();
        a<<setw(4)<<setfill('0')<<hex<<address;
        a>>temp;
        in = in+temp;
        }

    string obcode::getIn(){
        return in ;
        }

    void obcode::setIn(string in){
        this->in = in ;
        }

void obcode::clearIn() {
    in.clear();
    }

obcode::~obcode(){}
