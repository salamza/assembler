#ifndef SICXEOBCODE_H_INCLUDED
#define SICXEOBCODE_H_INCLUDED

#include <string>
#include "obcode.h"

using namespace std;

class sicxeObcode : public obcode {
    private :
    bool n;
    bool i;
    bool b;
    bool p;
    bool e ;
    int BASE ;
    int loc ;

    public :
   bool setIn();
    sicxeObcode();
 void seti (bool i);
void setn (bool n);
void setb (bool b);
 void setp (bool p);
 void sete (bool e);
 void setIn (string in);
 void setBASE(int BASE);
    bool geti() {return i;}
    bool gete() {return e;}
     bool getn() {return n;}
bool getp() {return p;}
       bool getb() {return b;}
    ~sicxeObcode();
    void setLoc (int loc){ this->loc = loc;}
        void setOpcode(int opcode){this->opcode = opcode;}
    void setX (bool x){this->x = x;}
    void setAddress (int address){this->address = address;}
        bool getX() {return x;}
    int getAddress() {return address;}
    int getOpcode (){return opcode;}
    string getIn(){return in;}
    };

#endif // SICXEOBCODE_H_INCLUDED
