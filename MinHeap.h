#include <iostream>
#include <vector>
#include <utility>

template <typename T>
  class MinHeap {
     public:
       MinHeap (int d);
       /* Constructor that builds a d-ary Min Heap
          This should work for any d >= 2,
          but doesn't have to do anything for smaller d.*/

       ~MinHeap ();

       void add (T item, int priority);
         /* adds the item to the heap, with the given priority. */

       const T & peek () const;
         /* returns the element with smallest priority.  
			Break ties however you wish.  
			Throws an exception if the heap is empty. */

       void remove ();
         /* removes the element with smallest priority.
			Break ties however you wish.
            Throws an exception if the heap is empty. */

       bool isEmpty () const;
         /* returns true iff there are no elements on the heap. */

   private:
      std::vector<std::pair<T, int>> arr; //Stores item and priority
      int d;  
      void trickleDown(int curr);   
      int getParent(int i);
      int getChild(unsigned int i, int c);
  };

template<typename T>
MinHeap<T>::MinHeap(int d){
    if (d < 2) throw "Error: size must be >= 2";
    this->d = d;
}

template<typename T>
MinHeap<T>::~MinHeap()
{}

template<typename T>
void MinHeap<T>::add(T item, int priority){
    arr.push_back(std::pair<T, int>(item, priority));    
    int curr = arr.size() - 1;
    int parentLoc;

    /*getParent will throw an exception for
    the first item added, since it doesn't
    have a parent*/
    try{
        parentLoc = getParent(curr);
    }
    catch(char const* noParent){
        return;
    }

    //Bubble Up
    while (arr[curr].second < arr[parentLoc].second || (arr[curr].second == arr[parentLoc].second && arr[curr].first < arr[parentLoc].first)){
        //Swap with parent
        std::pair<T, int> temp = arr[curr];
        arr[curr] = arr[parentLoc];
        arr[parentLoc] = temp;
        curr = parentLoc;
        try{
            parentLoc = getParent(curr);
        }
        catch (char const* noParent){
            return;
        } 
    } 
}

template<typename T>
const T & MinHeap<T>::peek () const{
    if (isEmpty()) throw "Error: heap is empty";
    return arr[0].first;    //Returns item, not priority
}

template<typename T>
void MinHeap<T>::remove(){
    if (isEmpty()) throw "Error: heap is empty";
    //Swap first and last items, then delete the new last item
    arr[0] = arr[arr.size() - 1];
    std::vector<std::pair<T, int>> newArr;
    for (unsigned int i = 0; i < arr.size() - 1; i++){
        newArr.push_back(arr[i]);
    } 
    arr = newArr;
    trickleDown(0);
}

template<typename T>
void MinHeap<T>::trickleDown(int curr){
    int lowestChild = curr; 
    int lowestChildPriority = arr[curr].second;    
   
     //Select the child with lowest priority
    for (int i = 1; i <= d; i++){
        /*getChild will return curr if this child does not exist,
        and lowestChildPriority is initialized to curr's priority,
        so this condition will be false if the child does not exist*/
        if (arr[getChild(curr, i)].second < lowestChildPriority || (arr[getChild(curr, i)].second == lowestChildPriority && arr[getChild(curr, i)].first < arr[lowestChild].first)){ 
            lowestChildPriority = arr[getChild(curr, i)].second;
            lowestChild = getChild(curr, i);
        }  
    }

    /*lowestChild was initialized to curr, so if no children exist 
    or if the item is in the correct spot, this will be true*/
    if (lowestChild == curr) return;    

    std::pair<T, int> temp = arr[curr];
    arr[curr] = arr[lowestChild];
    arr[lowestChild] = temp;
    trickleDown(lowestChild);
}

template<typename T>
bool MinHeap<T>::isEmpty () const{
    return arr.empty();
}

template<typename T>
int MinHeap<T>::getParent(int i){
    if (i <= 0) throw "Error: parent does not exist";
    return (i - 1) / d;
}

template<typename T>
int MinHeap<T>::getChild(unsigned int i, int c){
    if (c > d || c < 1 || d * i + c >= arr.size()) return i;    //Returns current index if child doesn't exist. Function calling getChild is designed to handle this. 
    return d * i + c;   //c is the first, second, third child, etc. 
}