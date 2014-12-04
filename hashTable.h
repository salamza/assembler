#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include <iostream>
#include <string>

using namespace std ;

struct node
{
    int value ;
    string token;
    node* collision ;
    int format ;
};

class hashTable
{
private :
    int tableSize ;
    node*table ;
    int size ;
    void rehash (string token , int value) ;
    void rehashf (string token , int value,int format) ;
    void hashCollision (string token , int value);
    void hashCollisionf (string token , int value,int format);
    int getValueCollision (string token);
    int getFormatCollision (string token);
    int generateKey (string token);
    int nextPrime(int n);

public :
    hashTable(int tableSize);
    ~hashTable();
    bool hash (string token , int value);
    bool hashf (string token , int value,int format);
    int getValue (string token);
    int getFormat(string token);

};

#endif // HASHTABLE_H_INCLUDED
