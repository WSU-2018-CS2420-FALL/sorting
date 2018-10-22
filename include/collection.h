#ifndef _COLLECTION_H_
#define _COLLECTION_H_

#include <iostream>
template<typename Item>
class Collection {
public:
    Collection(): sz(0), capacity(8), elements(new Item[capacity]){}
    Collection(int size): sz(size), capacity(size), elements(new Item[size]){}
    Collection(const Collection<Item>& c): sz(c.sz), capacity(c.capacity) {
        elements = new Item[capacity];
        for(int i = 0; i < c.sz; i++){
            elements[i] = c.elements[i];
        }
    }

    Collection<Item>& operator=(const Collection<Item>& c){
       Item* newElements = new Item[c.capacity];
       for(int i = 0; i < sz; i++){
             newElements[i] = c.elements[i];
       }
       
       delete[] elements;
       elements = newElements;
       sz = c.sz;
       capacity = c.capacity;

       return *this;
    }

    // Required to support range-based for loop
    Item* begin(){ return elements; }
    Item* end(){ return elements + sz; }

    void add(Item e){
        if(sz == capacity){
            Item* newElements = new Item[capacity * 2];
            for(int i = 0; i < sz; i++){
                newElements[i] = elements[i];
            }
            delete[] elements;
            elements = newElements;
            capacity *= 2;
        }
        elements[sz++] = e;
    }

    Item operator[](int i) const{
        return elements[i];
    }

    Item& operator[](int i) {
        return elements[i];
    }
    
    Collection<Item>& remove(){
        sz--;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Collection<Item>& c){
        for(int i = 0; i < c.sz; i++){
            out << c.elements[i] << " ";
        }

        return out;
    }

    void sortByBubble(bool reversed = false){

    }

    void sortBySelection(bool reversed = false){

    }

    void sortByInsertion(bool reversed = false){

    }

    void sortByShell(bool reversed = false){

    }
    ~Collection(){
        delete[] elements;
    }
protected:
    int  sz, capacity;
    Item *elements;
};
#endif