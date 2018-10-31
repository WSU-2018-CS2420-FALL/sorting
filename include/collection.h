#ifndef _COLLECTION_H_
#define _COLLECTION_H_

#include <iostream>
#include <cstdlib>
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
        for(int i = 0; i < sz - 1; i++){
            for(int j = 1; j < sz - i; j++){
                if(lessOrGreaterThan(j, j-1, reversed)){
                    swap(j, j-1);
                }
            }
        }
    }

    void sortBySelection(bool reversed = false){
        for(int i = 0; i < sz; i++){
            swap(i, findMinOrMax(i, sz, reversed));
        }
    }

    void sortByInsertion(bool reversed = false){
        for(int i = 1; i < sz; i++){
            for(int j = i; j >= 1 && lessOrGreaterThan(j, j-1, reversed); j--){
                swap(j, j-1);
            }
        }
    }

    void sortByShellsort(bool reversed = false){
        int h;
        for(h = 1; h < sz / 3; h = 3 * h + 1);

        while(h >= 1){
            for(int i = h; i < sz; i++){
                for(int j = i; j >= h && lessOrGreaterThan(j, j-h, reversed); j = j - h){
                    swap(j, j-h);
                }
            }

            h = h / 3;
        }
    }

    void sortByQuicksort(bool reversed = false){
        quicksort(0, sz-1, reversed);
    }

    void quicksort(int lo, int hi, bool reversed){
      if(lo < hi){
          int m = partition(lo, hi, reversed);
          quicksort(lo, m - 1, reversed);
          quicksort(m + 1, hi, reversed);
      }
    }

    int partition(int lo, int hi, bool reversed){
      int r = rand() % (hi - lo + 1) + lo;
      swap(r, hi);
      int i = lo - 1;
      for(int j = lo; j < hi; j++){
        if(lessOrGreaterThan(j, hi, reversed)){
          swap(++i, j);
        }
      }
      swap(i + 1, hi);
      return i + 1;
    }

    void sortByMergesort(bool reversed = false){
      Item* aux = new Item[sz];
      mergesort(aux, 0, sz-1, reversed);
      delete[] aux;
    }

    void mergesort(Item* aux, int lo, int hi, bool reversed){
      if (hi <= lo) return;

      int mid = lo + (hi - lo)/2;
      mergesort(aux, lo, mid, reversed); 
      mergesort(aux, mid+1, hi, reversed);
      merge(aux, lo, mid, hi, reversed);
    }

    void merge(Item* aux, int lo, int mid, int hi, bool reversed){
      int i = lo;
      int j = mid + 1;
      
      for(int k = lo; k <= hi; k++){
        if(i > mid) aux[k] = elements[j++];
        else if(j > hi) aux[k] = elements[i++];
        else if(lessOrGreaterThan(i, j, reversed)){
          aux[k] = elements[i++];
        }else{
          aux[k] = elements[j++];
        }
      }

      for(int i = lo; i <= hi; i++){
        elements[i] = aux[i];
      }
    }

    void sortByHeapsort(bool reversed = false){
      buildHeap(reversed);
      for(int i = sz  - 1; i > 0; i--){
        swap(0, i);
        heapify(0, i, reversed);
      }
    }

    void buildHeap(bool reversed){
      for(int i = sz / 2 - 1; i >= 0; i--){
        heapify(i, sz, reversed);
      }
    }

    void heapify(int p, int hsz, bool reversed){
      int left = 2 * p + 1;
      int right = left + 1;
      int largest = p;
      if(left < hsz && lessOrGreaterThan(p , left, reversed)) {
        largest = left;
      }

      if(right < hsz && lessOrGreaterThan(largest , right, reversed)) {
        largest = right;
      }

      if(largest != p){
        swap(p, largest);
        heapify(largest, hsz, reversed);
      }
    }

    ~Collection(){
      delete[] elements;
    }
protected:
    int  sz, capacity;
    Item *elements;

    void swap(int i, int j){
        Item temp = elements[i];
        elements[i] = elements[j];
        elements[j] = temp;
    }

    bool lessOrGreaterThan(int i, int j, bool reversed){
        return (!reversed && elements[i] < elements[j]) || 
               (reversed && elements[i] > elements[j]);
    }

    int findMinOrMax(int start, int sz, bool reversed){
        int minOrMax = start;

        for(int i = start; i < sz; i++){
            if(lessOrGreaterThan(i, minOrMax, reversed)){
                minOrMax = i;
            }
        } 

        return minOrMax;
    }
};
#endif