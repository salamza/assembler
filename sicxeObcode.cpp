#include "sicxeObcode.h"
#include <iomanip>
#include <sstream>
#include <iostream>

using namespace std;
sicxeObcode::sicxeObcode(){
    loc=0 ;
    x=0 ;
    opcode=0 ;
    address=0;
    i=0;
    n=0;
    b=0;
    p=0;
    e=0;
    }



    bool sicxeObcode::setIn(){
        if (opcode != 144 && opcode != 180 && opcode != 160 && opcode != 156 && opcode != 152 &&opcode != 172 &&opcode != 148 && opcode != 184 ){
        if (i){
            p=0;
            b=0;
            }
        else if (!e){
        if (address+loc<2047 || loc-address>-2048){
            p=1;
            loc = loc+3;
            if (address+loc<2047 ){
            address =address-loc;
            if(address<0){
                address = -1*address ;
                stringstream a(stringstream::in | stringstream::out) ;
                string temp ;
                temp.clear();
                int i = strtol("fff",NULL,16) - address +1 ;
                a<<hex<<i;
                a>>temp ;
                address = strtol(temp.c_str(),NULL,16);
                }
            }
            else {
                address=address+loc;
                stringstream a(stringstream::in | stringstream::out) ;
                string temp;
                a.clear();
                a<< hex <<  address ;
                a>>temp ;
                a.clear();
                address = strtol("fff",NULL,16) - strtol(temp.c_str(),NULL,16) + 1 ;
                }
        }
        else {
            if (BASE && (address+BASE<4095)){
                b=1 ;
                }
            else return 0;
            }
        }
        in.clear();
        string temp ;
        temp.clear();
        stringstream a(stringstream::in | stringstream::out) ;
        a.clear();
        if (n) opcode = opcode+2;
        else if (i) opcode = opcode+1;
        else if (!n && !i) opcode = opcode + 3 ;
        a<<setw(2)<<setfill('0')<<hex<<opcode;
        a>>temp;
        in = temp ;
        a.clear();
        temp.clear();
        a<<dec<<x << b<<p<<e;
        a>>temp ;
        a.clear();
        a<<hex << strtol(temp.c_str(),NULL,2);
        temp.clear();
        a>>temp;
        in = in+temp;
        a.clear();
        temp.clear();
        if (!e)a<<setw(3)<<setfill('0')<<hex<<address;
        else a<<setw(5)<<setfill('0')<<hex<<address;
        a>>temp;
        in = in+temp;
        return 1 ;
        }
        else {
            stringstream a(stringstream::in | stringstream::out) ;
            a.clear();
            a<<hex<<opcode ;
            string temp ;
            temp.clear();
            a>>temp;
            in=temp ;
            a.clear();
            a<<hex<<address ;
            temp.clear();
            a>>temp ;
            in = in+temp ;
            }
            return 1;
        }


     void sicxeObcode::seti (bool i){
         this->i = i ;
         }
void sicxeObcode::setn (bool n){
         this->n = n ;
         }
void sicxeObcode::setb (bool b){
         this->b = b ;
         }
 void sicxeObcode::setp (bool p){
         this->p = p ;
         }
 void sicxeObcode::sete (bool e){
         this->e = e ;
         }
 void sicxeObcode::setIn(string in){
        this->in = in ;
        }
        void sicxeObcode::setBASE(int BASE) {
            this->BASE = BASE ;
            }

sicxeObcode::~sicxeObcode(){}
