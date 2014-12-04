#ifndef OBCODE_H_INCLUDED
#define OBCODE_H_INCLUDED

#include <string>

using namespace std;

class obcode {
    protected :
    int opcode ;
    bool x ;
    int address ;
    char flag;
    string in ;


    public :
    obcode();
    void setOpcode(int opcode);
    void setX (bool x);
    void setAddress (int address);
    bool getX() {return x;}
    int getAddress() {return address;}
    void setFlag(char flag);
    ~obcode();
 void setIn();
    void setIn (string in);
    string getIn();
    void clearIn();
    };

#endif // OBCODE_H_INCLUDED
