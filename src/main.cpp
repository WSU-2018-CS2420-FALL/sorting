#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "collection.h"
#include "linked_list.h"
using namespace std;
using namespace chrono;

enum class SortAlgorithm{
  BUBBLE, SELECTION, INSERTION, SHELLSORT,
  QUICKSORT, MERGESORT, HEAPSORT
};

template <typename T>
struct SortRunningTime {
  SortAlgorithm algorithm;
  duration<double, nano> sorted;
  duration<double, nano> random;
  duration<double, nano> reversed;

  void sort(Collection<T>& c, bool reversed = false){
    switch(algorithm){
      case SortAlgorithm::BUBBLE:
        c.sortByBubble(reversed);
        break;
      case SortAlgorithm::SELECTION:
        c.sortBySelection(reversed);
        break;
      case SortAlgorithm::INSERTION:
        c.sortByInsertion(reversed);
        break;
      case SortAlgorithm::SHELLSORT:
        c.sortByShellsort(reversed);
        break;
      case SortAlgorithm::QUICKSORT:
        c.sortByQuicksort(reversed);
        break;
      case SortAlgorithm::MERGESORT:
        c.sortByMergesort(reversed);
        break;
      case SortAlgorithm::HEAPSORT:
        c.sortByHeapsort(reversed);
        break;
    }
  }

  string label(){
    switch(algorithm){
      case SortAlgorithm::BUBBLE: return "Bubble";
      case SortAlgorithm::SELECTION: return "Selection";
      case SortAlgorithm::INSERTION: return "Insertion";
      case SortAlgorithm::SHELLSORT: return "Shellsort";
      case SortAlgorithm::QUICKSORT: return "Quicksort";
      case SortAlgorithm::MERGESORT: return "Mergesort";
      case SortAlgorithm::HEAPSORT: return "Heapsort";
    }
  }
};
int main(){
  srand(time(NULL));
  const int MAX_COLLECTION_SIZE = 100;
  Collection<int> original;
  for(int i = 0; i < MAX_COLLECTION_SIZE; i++){
    original.add(rand() % (3 * MAX_COLLECTION_SIZE) + 100);
  }

  // cout << original << endl;
  // original.sortByQuicksort();
  // cout << original << endl;
  // original.sortByQuicksort(true);
  // cout << original << endl;

  SortRunningTime<int> runningTimes[] = {
    {SortAlgorithm::BUBBLE},
    {SortAlgorithm::SELECTION},
    {SortAlgorithm::INSERTION},
    {SortAlgorithm::SHELLSORT},
    {SortAlgorithm::QUICKSORT},
    {SortAlgorithm::MERGESORT},
    {SortAlgorithm::HEAPSORT}
  };

  for(auto& rt : runningTimes){
    Collection<int> a(original);
    rt.sort(a);
    auto start = high_resolution_clock::now();
    rt.sort(a);
    auto end = high_resolution_clock::now();
    rt.sorted = end - start;

    Collection<int> b(original);
    start = high_resolution_clock::now();
    rt.sort(b);
    end = high_resolution_clock::now();
    rt.random = end - start;

    Collection<int> c(original);
    rt.sort(c, true);
    start = high_resolution_clock::now();
    rt.sort(c);
    end = high_resolution_clock::now();
    rt.reversed = end - start;
  }

  cout << setw(15) << "Algorithm" 
       << setw(15) << "Sorted" 
       << setw(15) << "Random"
       << setw(15) << "Revered" << endl;

  for(auto& rt : runningTimes){
      cout << fixed << setprecision(2) << setw(15) << rt.label()
       << setw(15) << rt.sorted.count() 
       << setw(15) << rt.random.count()
       << setw(15) << rt.reversed.count() << endl;
  }    
  
  return 0;
}