#include "sicxeAssembler.h"
#include <string>
#include "hashTable.h"
#include "sicxeParser.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std ;

int reg(char c){
    if (c=='A')return 0 ;
    if (c=='B')return  3;
    if (c=='L')return 2 ;
    if (c=='X')return 1 ;
    if (c=='S')return 4 ;
    if (c=='T')return 5 ;
    if (c=='F')return 6 ;
    }

bool hexa(string a){
    for (int i=0 ; i<a.size();i++){

if ((a.at(i)<'0' || a.at(i)>'9' )&& a.at(i)!='A'&& a.at(i)!='B'&& a.at(i)!='C'&& a.at(i)!='D'&& a.at(i)!='E'&& a.at(i)!='F'&& a.at(i)!=(char)0){return 0;}
}
return 1 ;
    }

int sicxeAssembler::findIna(string b , char c){
for (int i=0 ; i<b.size();i++){
if (b.at(i)==c) return i ;
}
return -1 ;
}

void sicxeAssembler::tokens(string interInput){
    int size = interInput.size() ;
    int i=0;
    int n=0;
    bool f;
    int j=0 ;
    for (i ; i<=size ; i++ )
        {
            f=0 ;
            if (interInput[i] =='\t' || i==size )
            {
                for (n; n<=i ; n++ )
                {
                    if(interInput[n]=='\t') {}
                    else
                    {
                        instructionList[j].push_back(interInput[n]) ;

                        f = 1 ;
                    }
                }
                if (f==1)
                {
                    j++;
                }

                n=i ;
            }
            if (j==5)
            {
                n=i ;
                i=size+1 ;
            }
        }
    }

sicxeAssembler::sicxeAssembler(string fileName){

locationCounter = -1 ;
symbolTable = new hashTable(15) ;
opTable= new hashTable(30) ;
directiveTable = new hashTable(10) ;
this->fileName = fileName ;
intFile = " ";
pars = new sicxeParser();

directiveTable->hash("START" , 0);
directiveTable->hash("END" , 0);
directiveTable->hash("RESW" , 0);
directiveTable->hash("RESB" , 0);
directiveTable->hash("WORD" , 0);
directiveTable->hash("BYTE" , 0);
directiveTable->hash("BASE",0);
directiveTable->hash("NOBASE",0);

opTable->hashf("STL",20,3);
opTable->hashf("ADD",24,3);
opTable->hashf("COMP",40,3);
opTable->hashf("DIV",36,3);
opTable->hashf("J",60,3);
opTable->hashf("JEQ",48,3);
opTable->hashf("LDB",104,3);
opTable->hashf("JGT",52,3);
opTable->hashf("JLT",56,3);
opTable->hashf("JSUB",72,3);
opTable->hashf("LDA",0,3);
opTable->hashf("LDCH",80,3);
opTable->hashf("LDX",4,3);
opTable->hashf("STA",12,3);
opTable->hashf("STCH",84,3);
opTable->hashf("STX",16,3);
opTable->hashf("SUB",28,3);
opTable->hashf("MUL",32,3);
opTable->hashf("TD",224,3);
opTable->hashf("WD",220,3);
opTable->hashf("RSUB",76,3);
opTable->hashf("ADDR",144,2);
opTable->hashf("CLEAR",180,2);
opTable->hashf("COMPR",160,2);
opTable->hashf("DIVR",156,2);
opTable->hashf("MULR",152,2);
opTable->hashf("RMO",172,2);
opTable->hashf("SUBR",148,2);
opTable->hashf("TIXR",184,2);


a[1] = "Error: Mnemonic cannot be used as operand";
a[2] = "Error: Directive cannot be used as operand";
a[3] = "Error: Operand cannot start with a '.' ";
a[4] = "Error: Label cannot start with a number";
a[5] = "Error: This mnemonic must have an operand";
a[6] = "Error: Registers cannot be used as operands";
a[7] = "Error: Invalid operand on directive";
a[10] = "Error: Duplicate label. Choose another label!";
a[11] = "Error: Mnemonic was not found in instruction set";
a[12] = "Error: This directive must have an operand";
a[13] = "Error: 'START' statement must be at the beginning of the program";
a[14] = "Error: 'START' statement only uses hexadecimal operands in the range from 0 to 7FFF ";
a[17] = "Error: This instruction needs more than a label";
a[18] = "Error: 'END' directive cannot have a label";
a[19] = "Error: Expected 'END' at the end of the program";
a[20] = "Warning: Expected 'START' at the start of the file";
a[21] = "Warning: Expected label before directives";
a[22] = "Warning: Expected operand after 'START' statement";
a[23] = "Warning: Expected operand after 'END' statement";
a[24] = "Error: Invalid XE Operand " ;
a[25]="Error: Missing Operand" ;
a[26]="Error: Mnemonics and directives can't used as operands";
a[27]="Error: Line cannot start with '@' or '#' ";
a[28]="Error: Missing insntruction after '+'" ;
a[29]="Error: Operator '+' can't used with format 2 instruction" ;
a[30]="Error: Operands must be 2 valid registers" ;
a[31]="Error: Clear must followed by a valid register" ;

pars->lexicalAnalyzer(opTable , symbolTable , directiveTable, fileName, locationCounter);
objectCode.setBASE(0);
}


sicxeAssembler::~sicxeAssembler(){
delete pars ;
}

void sicxeAssembler::assemble(){
    temp.clear();
    bool flag=1 ;
    bool c=1;
    int locationCounter;
    locationCounter = this->locationCounter;
    ofstream listFile ("listfile.txt",ios::app);
    ofstream errorFile ("errorfile.txt" , ios::app);
    ofstream objectFile ("objectfile.txt",ios::app);
    ifstream intermediateFile ("outputfile.txt");
    string interInput;

    int lineNo = 0;
    while (!intermediateFile.eof()) {
        for (int i=0 ; i<5 ; i++){
            instructionList[i].clear();
            }
        getline (intermediateFile , interInput);
        lineNo++;
        //Law mosh error//
tokens (interInput);
objectCode.setLoc(strtol(instructionList[0].c_str(),NULL,16));
if (!interInput.empty()){
                    if (interInput.at(0)=='.'){
                    listFile<<dec<<lineNo<<'\t'<<interInput.substr(3,interInput.size()-1) <<endl ;
                string errorMsg=a[atoi(instructionList[0].substr(1,instructionList[0].size()-1).c_str())];

                errorFile<<"In line no: "<<lineNo<<" "<<errorMsg<<endl ;
                flag=0;
                    }
        else if (interInput.at(0) != '.') {
        //7ottaha fil instructionList//
        //tokens (interInput);
        //case that instructionList[1] is not a mnemonic nor a directive//
if ((opTable->getValue(instructionList[1]) !=-2) || (directiveTable->getValue(instructionList[1]) !=-2) || (instructionList[1].at(0)=='+')) {}

else {
//for (int i =0 ; i<5 ; i++) {cout<<i<<" "<<instructionList[i]<<endl;}

        //loop to shift//
        string temp = instructionList[1]; //put label in temp//
        for (int i=2 ; i<5 ; i++) {
            instructionList [i-1] = instructionList [i];
            }
  instructionList[4] = temp; //put label in last field//
}
//cout<<"---------------------"<<endl;

//for (int i =0 ; i<5 ; i++) {cout<<i<<" "<<instructionList[i]<<endl;}
         //3andena kaza case://
        //1 - Teb2a mnemonic//
        if (opTable->getValue(instructionList[1]) != -2 || (instructionList[1].at(0)=='+'))
        {
            objectCode.seti(0);
            objectCode.sete(0);
            objectCode.setp(0);
            objectCode.setb(0);
            objectCode.setn(0);
            objectCode.setX(0);

            if (instructionList[1].at(0)=='+'){
                instructionList[1]=instructionList[1].substr(1,instructionList[1].size()-1);
              objectCode.sete(1);
                }
                objectCode.setOpcode(opTable->getValue(instructionList[1]));
            //Check indexed or not//
        string xcheck ;
         if (!instructionList[2].empty()) xcheck = instructionList[2].substr(instructionList[2].size()-2,instructionList[2].size());
         if (instructionList[1]=="RSUB"){
             listFile<<dec<<lineNo<<'\t';
             if (objectCode.gete()) listFile<<"+";
                 listFile<<instructionList[0];
                 listFile<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t';
                 //nekteb el object code kaman fil listing file//
                 listFile<<setw(6)<<setfill('0')<<hex<<opTable->getValue("RSUB")<<endl ;
             }
             else if (opTable->getFormat(instructionList[1])==2){
                 string temp ;
                 string temp2 ;
                 temp = reg(instructionList[2].at(0)) ;
                 if (instructionList[1]!="CLEAR" || instructionList[1]!="TIXR"){
                 temp2 = reg(instructionList[2].at(2)) ;
                 temp=temp+temp2 ;
                 }
                 objectCode.setAddress(strtol(temp.c_str(),NULL,10));
                 listFile<<dec<<lineNo<<'\t';
                 listFile<<instructionList[0];
                 listFile<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t'<<instructionList[2]<<'\t';
                 //nekteb el object code kaman fil listing file//
                 c=objectCode.setIn();
                 listFile<<objectCode.getIn()<<endl;
                 }
         else{
             if (instructionList[2].at(0)=='@'){
                 objectCode.setn(1);
                 instructionList[2] = instructionList[2].substr(1,instructionList[2].size()-1);
                 if ((symbolTable->getValue(instructionList[2])==-2) && !hexa(instructionList[2])) {
                listFile<<dec<<lineNo<<'\t';
                listFile<<instructionList[0]<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t'<<"@"<<instructionList[2];
                listFile<<endl;
                flag = 0 ;
                errorFile<<"In line number "<<lineNo<<" :Label was not declared in this program"<<endl;
                 }
                 else {
                if (!(instructionList[3].size()>1)) {
                if (hexa(instructionList[2]))objectCode.setAddress(strtol(instructionList[2].c_str(),NULL,16));
                else objectCode.setAddress(symbolTable->getValue(instructionList[2]));
                 listFile<<dec<<lineNo<<'\t';
                 listFile<<instructionList[0];
                 listFile<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t'<<"@"<<instructionList[2]<<'\t';
                 //nekteb el object code kaman fil listing file//
                 c=objectCode.setIn();
                 listFile<<objectCode.getIn()<<endl;
                }
                else {
                if (hexa(instructionList[2]))objectCode.setAddress(strtol(instructionList[2].c_str(),NULL,16));
                else objectCode.setAddress(symbolTable->getValue(instructionList[2]));
                 listFile<<dec<<lineNo<<'\t';
                 listFile<<instructionList[0];
                 listFile<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t'<<"@"<<instructionList[2]<<'\t';
                 //nekteb el object code kaman fil listing file//
                 c=objectCode.setIn();
                 listFile<<objectCode.getIn()<<endl;

                 instructionList[3] = instructionList[3].substr(0,instructionList[3].size()-1);
                 errorFile<<"In line no : "<<lineNo<<" "<<a[atoi(instructionList[3].c_str())]<<endl;
               }
                    }
                     }
            else if (instructionList[2].at(0)=='#'){
                objectCode.seti(1);
                 instructionList[2] = instructionList[2].substr(1,instructionList[2].size()-1);
                 if ((symbolTable->getValue(instructionList[2])==-2) && !hexa(instructionList[2])) {
                listFile<<dec<<lineNo<<'\t';
                listFile<<instructionList[0]<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t'<<"#"<<instructionList[2];
                listFile<<endl;
                flag = 0 ;
                errorFile<<"In line number "<<lineNo<<" :Label was not declared in this program"<<endl;
                }
                else {
                if (!(instructionList[3].size()>1)) {
                if (hexa(instructionList[2]))objectCode.setAddress(strtol(instructionList[2].c_str(),NULL,16));
                else objectCode.setAddress(symbolTable->getValue(instructionList[2]));

                 listFile<<dec<<lineNo<<'\t';
                 listFile<<instructionList[0];
                 listFile<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t'<<"#"<<instructionList[2]<<'\t';
                 //nekteb el object code kaman fil listing file//
                 c=objectCode.setIn();
                 listFile<<objectCode.getIn()<<endl;
                }
                else {
                if (hexa(instructionList[2]))objectCode.setAddress(strtol(instructionList[2].c_str(),NULL,16));
                else objectCode.setAddress(symbolTable->getValue(instructionList[2]));
                 listFile<<dec<<lineNo<<'\t';
                 listFile<<instructionList[0];
                 listFile<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t'<<"#"<<instructionList[2]<<'\t';
                 //nekteb el object code kaman fil listing file//
                 c=objectCode.setIn();
                 listFile<<objectCode.getIn()<<endl;

                 instructionList[3] = instructionList[3].substr(0,instructionList[3].size()-1);
                 errorFile<<"In line no : "<<lineNo<<" "<<a[atoi(instructionList[3].c_str())]<<endl;
               }
                    }
            }
            else  if (xcheck == ",X") {
                objectCode.setX(1);
                if (symbolTable->getValue(instructionList[2].substr(0,instructionList[2].size()-2)) == -2) {
                listFile<<dec<<lineNo<<'\t';
                listFile<<instructionList[0]<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t'<<instructionList[2];
                listFile<<endl;
                flag = 0 ;
                errorFile<<"In line number "<<lineNo<<" :Label was not declared in this program"<<endl;
                }
                else if (!(instructionList[3].size()>1)) {
                if (objectCode.getX())objectCode.setAddress(symbolTable->getValue(instructionList[2].substr(0,instructionList[2].size()-2)));
                 else objectCode.setAddress(symbolTable->getValue(instructionList[2]));
                 listFile<<dec<<lineNo<<'\t';
                 listFile<<instructionList[0];
                 listFile<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t'<<instructionList[2]<<'\t';
                 //nekteb el object code kaman fil listing file//
                 c=objectCode.setIn();
                 listFile<<objectCode.getIn()<<endl;
                }
                else {
                if (objectCode.getX())objectCode.setAddress(symbolTable->getValue(instructionList[2].substr(0,instructionList[2].size()-2)));
                 else objectCode.setAddress(symbolTable->getValue(instructionList[2]));
                 listFile<<dec<<lineNo<<'\t';
                 listFile<<instructionList[0];
                 listFile<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t'<<instructionList[2]<<'\t';
                 //nekteb el object code kaman fil listing file//

                 c=objectCode.setIn();
                 listFile<<objectCode.getIn()<<endl;

                 instructionList[3] = instructionList[3].substr(0,instructionList[3].size()-1);
                 errorFile<<"In line no : "<<lineNo<<" "<<a[atoi(instructionList[3].c_str())]<<endl;


               }
                }
            else {
                objectCode.setX(0);

//cout<<instructionList[2]<<endl;
            //Invalid label//

            if (symbolTable->getValue(instructionList[2]) == -2) {
                listFile<<dec<<lineNo<<'\t';
                listFile<<instructionList[0]<<'\t'<<instructionList[4]<<'\t';
                if (objectCode.gete()==1)listFile<<"+" ;
                listFile<<instructionList[1]<<'\t'<<instructionList[2];
                listFile<<endl;
                flag=0 ;
                errorFile<<"In line number "<<lineNo<<" :Label was not declared in this program"<<endl;
                }
                else if (!(instructionList[3].size()>1)) {
                if (objectCode.getX())objectCode.setAddress(symbolTable->getValue(instructionList[2].substr(0,instructionList[2].size()-2)));
                 else objectCode.setAddress(symbolTable->getValue(instructionList[2]));
                 listFile<<dec<<lineNo<<'\t';
                 listFile<<instructionList[0];
                 listFile<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t';
                  if (objectCode.gete()==1)listFile<<"+" ;
                  listFile<<instructionList[2]<<'\t';
                 //nekteb el object code kaman fil listing file//
                 c=objectCode.setIn();
                 listFile<<objectCode.getIn()<<endl;
                }
                else {
                if (objectCode.getX())objectCode.setAddress(symbolTable->getValue(instructionList[2].substr(0,instructionList[2].size()-2)));
                 else objectCode.setAddress(symbolTable->getValue(instructionList[2]));
                 listFile<<dec<<lineNo<<'\t';
                 listFile<<instructionList[0];
                 listFile<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t';
                  if (objectCode.gete()==1)listFile<<"+" ;
                 listFile<<instructionList[2]<<'\t';
                 //nekteb el object code kaman fil listing file//
                 c=objectCode.setIn();
                 listFile<<objectCode.getIn()<<endl;

                 instructionList[3] = instructionList[3].substr(0,instructionList[3].size()-1);
                 errorFile<<"In line no : "<<lineNo<<" "<<a[atoi(instructionList[3].c_str())]<<endl;


               }
            }
           //Valid label...Mafeesh mashakel khalis//
               //3'ayyar di ba3dein! ew3a tensa!!!!//



            }
            if (!c){
                flag = 0;
                errorFile<<"In line no : "<<lineNo<<" Requested place is out of the memory range " << endl;
                }
        }
        //2- Ennaha teb2a directive//
   else if (directiveTable->getValue(instructionList[1]) != -2) {
        if (instructionList[1] == "RESW" || instructionList[1] == "RESB") {
            objectCode.clearIn();

            listFile<<dec<<lineNo<<'\t'<<instructionList[0]<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t'<<instructionList[2]<<endl;
           if (instructionList[3].size()>1){
                 instructionList[3] = instructionList[3].substr(0,instructionList[3].size()-1);
                 errorFile<<"In line no : "<<lineNo<<" "<<a[atoi(instructionList[3].c_str())]<<endl;

                }
            }
        else if (instructionList[1] == "BYTE" || instructionList[1] == "WORD") {
            listFile<<dec<<lineNo<<'\t'<<instructionList[0]<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t'<<instructionList[2]<<'\t';
           if (instructionList[3].size()>1){
                 instructionList[3] = instructionList[3].substr(0,instructionList[3].size()-1);
                 errorFile<<"In line no : "<<lineNo<<" "<<a[atoi(instructionList[3].c_str())]<<endl;
                }
                if (instructionList[1]=="WORD"){
                    listFile<<setw(6) << setfill('0')<<instructionList[2];
                    stringstream a(stringstream::in | stringstream::out);
                                a.clear();
                                string b ;
                                b.clear();
                                a<<setw(6) << setfill('0')<<instructionList[2];
                                    a>>b;
                                    a.clear();
                                    objectCode.setIn(b);
                    }
                    else {
                        if (instructionList[2].at(0)=='X'){
                            listFile<<instructionList[2].substr(2,instructionList[2].size()-3);
                            objectCode.setIn( instructionList[2].substr(2,instructionList[2].size()-3));
                            }
                            else {
                                stringstream a(stringstream::in | stringstream::out);
                                a.clear();
                                string b ;
                                b.clear();
                                string c ;
                                c.clear();
                                for (int i=2 ; i<instructionList[2].size()-1 ; i++){
                                    listFile<<hex<<(int)instructionList[2].at(i);
                                    a<<hex<<(int)instructionList[2].at(i);
                                    a>>b;
                                    c=c+b ;
                                    a.clear();
                                    }
                                    objectCode.setIn(c);
                                }
                        }
                        listFile<<endl ;
            }
        else if (instructionList[1] == "START" || instructionList[1] == "END") {
            bool f=1 ;
             listFile<<dec<<lineNo<<'\t'<<instructionList[0]<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t';
             if (instructionList[2].size()>2 && instructionList[2].at(2)=='W'){f=0;}
             else {listFile<<instructionList[2];}
             listFile<<endl ;
           if (instructionList[3].size()>1 || !f){
                 instructionList[3] = instructionList[3].substr(0,instructionList[3].size()-1);
                 errorFile<<"In line no : "<<lineNo<<" "<<a[atoi(instructionList[3].c_str())];
                 if (!f)errorFile<<a[atoi(instructionList[2].c_str())];
                 errorFile<<endl ;

                }
            }
            else if (instructionList[1]=="BASE") {
                if (symbolTable->getValue(instructionList[2])!=-2){
               objectCode.setBASE(symbolTable->getValue(instructionList[2]));
                  listFile<<dec<<lineNo<<'\t'<<instructionList[0]<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t'<<instructionList[2]<<endl;
            }
            else {

               flag =0 ;
                  listFile<<dec<<lineNo<<'\t'<<instructionList[0]<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t'<<instructionList[2]<<endl;
                                errorFile<<"In line number "<<lineNo<<" :Label was not declared in this program"<<endl;
                }
            }
            else if (instructionList[1]=="NOBASE")
            {objectCode.setBASE(0);
              listFile<<dec<<lineNo<<'\t'<<instructionList[0]<<'\t'<<instructionList[4]<<'\t'<<instructionList[1]<<'\t'<<instructionList[2]<<endl;
            }
        }
        }
        }
        if (flag){
            if (instructionList[1]=="BASE" || instructionList[1]=="NOBASE"){}
        else if (lineNo == 1){
            objectFile<<"H";
            firstLoc = strtol(instructionList[0].c_str(),NULL,16);
            if (instructionList[4].size()<6){
                while (instructionList[4].size()!=6){
                instructionList[4]=instructionList[4]+" ";
                }
                }
                else if (instructionList[4].size()>6)instructionList[4]=instructionList[4].substr(0,5);
            objectFile<<instructionList[4];
            objectFile<<setw(6)<<setfill('0')<<instructionList[0];
            int programLength = locationCounter-strtol(instructionList[0].c_str(),NULL,16);
            objectFile<<hex<<setw(6)<<setfill('0')<<programLength<<endl;
            ob="T";
            }

            if (((temp.size()+objectCode.getIn().size())>60)||((instructionList[1]=="RESW" || instructionList[1]=="RESB")&& ob!="T")||intermediateFile.eof()){
             if (intermediateFile.eof() && temp.size()==0){}
             else{   objectFile<<ob;
                objectFile<<setw(2)<<setfill('0')<<hex<<temp.size()/2;
                objectFile<<temp<<endl;
                ob.clear();
                temp.clear();
                ob = "T" ;
            }
                }
                if (ob=="T" && (instructionList[1]!="RESW" && instructionList[1]!="RESB" )){
                     string b = "000000" ;
                     int j=0 ;
                     if (instructionList[0].size()<6){
                         for (int i=6-instructionList[0].size(); j<instructionList[0].size();i++){
                             b[i]=instructionList[0].at(j);
                             j++;
                             }
                         }
                     ob = ob+b;
                }
                if (instructionList[1]!="END"){
            temp = temp+objectCode.getIn();
                }
            if (intermediateFile.eof()){
            objectFile<<"E"<<hex<<setw(6)<<setfill('0')<<firstLoc<<endl;
            }

        }

    }
        listFile.close();
        errorFile.close();
        intermediateFile.close();
        objectFile.close();

    }

