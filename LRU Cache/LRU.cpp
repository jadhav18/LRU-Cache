#include<iostream>
#include<list>
#include<unordered_map>
using namespace std;

//Node to store the data (linked list)
class Node
{
public:
    string key;
    int value;
    Node(string key, int value)
    {
        this->key = key;
        this->value = value;
    }

};


//LRU Cache Data Structure
class LRUCache
{
 public:
    int maxSize ;
    list<Node> l;
    unordered_map<string,list<Node>::iterator > map;

    LRUCache(int maxSize)
    {
        if(maxSize>1) this->maxSize = maxSize ;
        else this->maxSize = 1 ;
    }

    void insertKeyValue( string key , int value)
    {
        if(map.count(key)!=0)
        {
            //replace the old value and update
            auto it = map[key] ;
            it->value = value ;
        }
        else 
        {
            // check if cache is full or not
            // remove the least recently used item from cache

            if( l.size()==maxSize )
            {
                Node last = l.back();
                map.erase(last.key) ; // remove from hashmap
                l.pop_back() ; // remove from linked list
            }

            Node n(key,value) ;
            l.push_front(n) ;
            map[key] = l.begin() ;

        }
    }

    int* getValue( string key )
    {
        if( map.count(key) != 0)
        {
            auto it = map[key];
            int value = it->value ;
            l.push_front(*it);
            l.erase(it) ;
            map[key] = l.begin();
            return &l.begin()->value ;
        }
        return NULL ;
    }

    string mostRecentKey()
    {
        return l.front().key ;
    }

};



int main()
{
    LRUCache LRU(4) ;
    LRU.insertKeyValue("Blue", 10);
    LRU.insertKeyValue("Black", 20);
    LRU.insertKeyValue("Red", 30);
    LRU.insertKeyValue("Yellow", 40);

    cout<< LRU.mostRecentKey() <<endl;

    LRU.insertKeyValue("White",50) ;
    cout<<LRU.mostRecentKey()<<endl;
    cout<< LRU.getValue("Black")<<endl;

    if(LRU.getValue("Black")==NULL)
    {
        cout<< "Black doesn't exist!" << endl;
    }
    if(LRU.getValue("Blue")==NULL)
    {
        cout<< "Blue doesn't exist!" << endl;
    }
    if(LRU.getValue("White")==NULL)
    {
        cout<< "White doesn't exist!" << endl;
    }
    if(LRU.getValue("Red")==NULL)
    {
        cout<< "Red doesn't exist!" << endl;
    }
    if(LRU.getValue("Yellow")==NULL)
    {
        cout<< "Yellow doesn't exist!" << endl;
    }
    LRU.insertKeyValue("Black",100);
    int *orders = LRU.getValue("Black") ;
    if(orders!=NULL)
    {
        cout<< "Order of Blue : "<< *orders << endl;
    }


}