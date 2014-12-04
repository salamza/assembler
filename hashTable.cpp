#include "hashTable.h"

hashTable::hashTable(int tableSize)
{
    this->tableSize=nextPrime(tableSize);
    table = new node [this->tableSize];
    size=0 ;
    for (int i=0 ; i<this->tableSize ; i++)
    {
        table[i].collision = NULL ;
        table[i].token.clear() ;
        table[i].value = -2;
    }
}

bool hashTable::hash(string token , int value )
{
    if (hashTable::getValue(token)==-2)
    {
        int n = (tableSize*3.0/4.0) ;
        if (size<=n)
        {
            int i = hashTable::generateKey(token) ;
            if (table[i].value==-2)
            {
                table[i].collision = NULL ;
                table[i].token = token ;
                table[i].value = value  ;
            }
            else if(table[i].value!=-2)
            {
                hashCollision(token,value);
            }
        }
        else
        {
            rehash(token ,  value );
        }
        size++ ;
        return true ;
    }
    else
        return false ;
}

int hashTable::getValue (string token)
{
    int i = generateKey(token) ;
    if (table[i].value==-2) return -2;
    else
    {
        if (table[i].collision == NULL )
        {
            if (table[i].token==token)return table[i].value ;
            else return -2 ;
        }
        else
        {
            return hashTable::getValueCollision (token) ;
        }
    }
}

int hashTable::getValueCollision (string token)
{
    int i= hashTable::generateKey(token);
    if(table[i].token==token) return table[i].value ;
    node* temp ;
    temp = new node ;
    temp = table[i].collision ;
    if (temp->token == token) return temp->value ;
    else
    {
        while (temp->collision!=NULL)
        {
            if (temp->token == token) return temp->value ;
            else temp = temp->collision ;
        }
    }
        if (temp->collision == NULL && temp->token==token){
     return temp->value ;
}
    if (temp->collision == NULL) return -2 ;
}

void hashTable::hashCollision (string token , int value)
{
    int i = generateKey(token) ;
    node* temp,*temp1 ;
    temp = new node ;
    temp->collision = NULL ;
    temp->value = value ;
    temp->token = token ;
    temp1 = table[i].collision;
    if (temp1 == NULL)
    {
        table[i].collision=new node ;
        table[i].collision=temp ;
    }
    else
    {
        while (temp1->collision !=NULL)
        {
            temp1= temp1->collision ;
        }
        temp1->collision = new node ;
        temp1->collision = temp;
    }
}

void hashTable::rehash (string token , int value)
{
    size=0 ;
    node* temp ;
    node* temp1;
    int j = tableSize;
    tableSize = nextPrime(tableSize*2) ;
    temp = new node[tableSize] ;
    temp1 = table ;
    table = temp ;
    temp = temp1 ;
    int n=tableSize;
    for (int i=0 ; i<tableSize ; i++)
    {
        table[i].value = -2 ;
        table[i].token.clear();
        table[i].collision = NULL ;
    }
    for (int i=0 ; i<j ; i++ )
    {
        if (temp[i].value!=-2)
        {
            if (temp[i].collision == NULL)
            {
                hashTable::hash(temp[i].token,temp[i].value);
            }
            else if (temp[i].collision!= NULL)
            {
                node *temp2;
                temp2 = new node ;
                hashTable::hash(temp[i].token,temp[i].value);
                temp2 = temp[i].collision ;
                while (temp2 != NULL)
                {
                    hashTable::hash(temp2->token,temp2->value);
                    temp2 = temp2->collision ;
                }
            }
        }
    }
    hashTable::hash(token , value);
    delete [] temp ;
}

int hashTable::generateKey(string token)
{
    int y=0 ;
    int n=token.size();
    for (int i=0 ; i<n ; i++)
    {
        y+=token[i];
    }
    return y%tableSize ;
}

int hashTable::nextPrime(int n)
{

    for (int i=0 ; i<n ; i++)
    {
        int j=n-1 ;
        while (j>1)
        {
            if (n%j==0) j=0 ;
            else j-- ;
        }
        if (j==1)return n ;
        else n++ ;
    }
}

hashTable::~hashTable()
{
    delete [] table ;
}

void hashTable::rehashf (string token , int value,int format){
        size=0 ;
    node* temp ;
    node* temp1;
    int j = tableSize;
    tableSize = nextPrime(tableSize*2) ;
    temp = new node[tableSize] ;
    temp1 = table ;
    table = temp ;
    temp = temp1 ;
    int n=tableSize;
    for (int i=0 ; i<tableSize ; i++)
    {
        table[i].value = -2 ;
        table[i].token.clear();
        table[i].collision = NULL ;
        table[i].format = 0 ;
    }
    for (int i=0 ; i<j ; i++ )
    {
        if (temp[i].value!=-2)
        {
            if (temp[i].collision == NULL)
            {
                hashTable::hashf(temp[i].token,temp[i].value , temp[i].format);
            }
            else if (temp[i].collision!= NULL)
            {
                node *temp2;
                temp2 = new node ;
                hashTable::hashf(temp[i].token,temp[i].value,temp[i].format);
                temp2 = temp[i].collision ;
                while (temp2 != NULL)
                {
                    hashTable::hashf(temp2->token,temp2->value , temp2->format);
                    temp2 = temp2->collision ;
                }
            }
        }
    }
    hashTable::hashf(token , value , format);
    delete [] temp ;
        }

    void hashTable::hashCollisionf (string token , int value,int format){
    int i = generateKey(token) ;
    node* temp,*temp1 ;
    temp = new node ;
    temp->collision = NULL ;
    temp->value = value ;
    temp->token = token ;
    temp->format=format;
    temp1 = table[i].collision;
    if (temp1 == NULL)
    {
        table[i].collision=new node ;
        table[i].collision=temp ;
    }
    else
    {
        while (temp1->collision !=NULL)
        {
            temp1= temp1->collision ;
        }
        temp1->collision = new node ;
        temp1->collision = temp;
    }
}

    bool hashTable::hashf (string token , int value,int format){
    if (hashTable::getValue(token)==-2)
    {
        int n = (tableSize*3.0/4.0) ;
        if (size<=n)
        {
            int i = hashTable::generateKey(token) ;
            if (table[i].value==-2)
            {
                table[i].collision = NULL ;
                table[i].token = token ;
                table[i].value = value  ;
                table[i].format = format ;
            }
            else if(table[i].value!=-2)
            {
                hashCollisionf(token,value,format);
            }
        }
        else
        {
            rehashf(token ,  value , format );
        }
        size++ ;
        return true ;
    }
    else
        return false ;
}

int hashTable::getFormat(string token){
    int i = generateKey(token) ;
    if (table[i].value==-2) return -2;
    else
    {
        if (table[i].collision == NULL )
        {
            if (table[i].token==token)return table[i].format ;
            else return -2 ;
        }
        else
        {
            return hashTable::getFormatCollision (token) ;
        }
    }
    }

    int hashTable::getFormatCollision(string token){
         int i= hashTable::generateKey(token);
    if(table[i].token==token) return table[i].format ;
    node* temp ;
    temp = new node ;
    temp = table[i].collision ;
    if (temp->token == token) return temp->format ;
    else
    {
        while (temp->collision!=NULL)
        {
            if (temp->token == token) return temp->format ;
            else temp = temp->collision ;
        }
    }
        if (temp->collision == NULL && temp->token==token){
     return temp->format ;
}
    if (temp->collision == NULL) return -2 ;
        }

