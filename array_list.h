//----------------------------------------------------------------------
// FILE: array_list
// NAME: Scott Tornquist
// DATE: 9/4/2020
// DESC: Implements a resizable array version of the list
//       class. Elements are added by default to the last available
//       index in the array. 
//----------------------------------------------------------------------

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "list.h"

template<typename T>
class ArrayList : public List<T>
{
public:
  ArrayList();
  ArrayList(const ArrayList<T>& rhs);
  ~ArrayList();
  ArrayList& operator=(const ArrayList<T>& rhs);
  //hw1
  void add(const T& item);
  bool add(size_t index, const T& item);
  bool get(size_t index, T& return_item) const;
  bool set(size_t index, const T& new_item);
  bool remove(size_t index);
  size_t size() const;
  //hw2
  void selection_sort();
  void insertion_sort();
  void swap(size_t x, size_t y);
  //hw3
  void merge_sort();
  void quick_sort();
  //hw4
  void sort();

private:
// i needed this public so i could test items to make sure they are bieng updated and tracked correctly
  T* items; //pointer to an array
  size_t capacity;
  size_t length;
  // helper to resize items array
  void resize();
  //hw3 helper functions
  void merge_sort(size_t start, size_t end);
  void quick_sort(size_t start, size_t end);
};

template <typename T>
void ArrayList<T>:: sort() {
  quick_sort();
}

template <typename T>
void ArrayList<T>:: merge_sort(){
  if(size()>1){
  size_t start = 0;
  size_t end = size()-1;
  size_t mid = (start + end)/2;
  merge_sort(0, end);
  //merge_sort(mid+1, end);
  }
};

template <typename T>
void ArrayList<T>:: merge_sort(size_t start, size_t end){
  if(start < end){
    size_t mid = (start + end)/2;
    merge_sort(start, mid);
    merge_sort(mid+1, end);
    T*tmp = new T[(end-start)+1];
    int first1 = start;
    int first2 = mid+1;
    int i = 0;
    while((first1 <= mid) && (first2 <= end)){
      if(items[first1+1] < items[first2]){
       tmp[i] = items[first1];
       first1++;
       i++;
      }
      else{
        tmp[i++] = items[first2++];
      }
    }
    while(first1 <= mid){
      tmp[i++] = items[first1++];
    }
    while(first2 <= end){
      tmp[i++] = items[first2++];
    }
    for(int k = start; k<=end; k++ ){
      items[k] = tmp[k-start];
    }

  delete[] tmp;
  }

};

template <typename T>
void ArrayList<T>:: quick_sort(){
  if(size()>1){
  size_t end = size()-1;
  quick_sort(0,end);
  }
};

template <typename T>
void ArrayList<T>:: quick_sort(size_t start, size_t end){
  if(start < end){
    T pivot_val = items[start];
    size_t last_index = start;
    for(int i = start+1; i<=end; i++){
      if(items[i]< pivot_val){
        last_index++;
        swap(i, last_index);
      }
    }
    swap(start, last_index);
    quick_sort(start, last_index);
    quick_sort(last_index+1, end);

  }

};

template <typename T>
void ArrayList<T>:: swap(size_t x, size_t y){ // simple swap function
  T z = items[x];
  items[x] = items[y];
  items[y] = z;
};

template<typename T>
void ArrayList<T>::selection_sort(){
  if(size() <= 1){ // size mus be big enough to sort
  }
  else{ // i is the end the unsorted area
    for(int i = size()-1; i>=1; i--){ //starting from the last index seach for the largest value
      int indexOfLargest = i;
      for(int j = i; j >= 0; j--){
        if(items[j] > items[indexOfLargest])
        indexOfLargest = j;
      } // each time when the larget value is found, the index is found and swapped with the last one, unless it is the last in the unsorted area, i
      if(indexOfLargest != i){
      swap(indexOfLargest, i);
      }
    }
  }

};

template<typename T>
void ArrayList<T>::insertion_sort(){
  if(size() <= 1){
  }
  else{
    for(int i =1; i<size(); i++){ //i is the selection that is being sorted in the sorted region
      int j = 0;
      while(items[j] < items[i]){ // j is the position in the sorted region
        j++;
        if(j==i){
          break;
        }
      }
      if(j != i){
        T saver = items[i];
        for(int k=i; k>j ; k--){
        items[k] = items[k-1];//shifting all items over between the values
        }
        items[j] = saver; // placing value into sorted spot
        //remove(i); // this essentially what i am doing, but more efficiently
        //add(j, saver);
      }
    }
  }
};

template<typename T>
ArrayList<T>::~ArrayList(){
  length = 0;
  items = nullptr;
  delete [] items;
  

};

template<typename T>
ArrayList<T>::ArrayList() : capacity(10), length(0)
{
  items = new T[capacity];
}

template<typename T>
ArrayList<T>& ArrayList<T> :: operator=(const ArrayList<T>& rhs){
if(this != &rhs){ // list1= list1
  capacity = rhs.capacity;
  items = new T[capacity]; // creating new array
  length=0;
    for(int i=0; i<rhs.size(); i++){ // moving items
      items[i] = rhs.items[i];
      length++;
    }
    length = rhs.size(); // moving size
  }
  //return lhs(this)
  return *this;
}

template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& rhs) : capacity(10), length(0), items(nullptr)
{
  // defer to assignment operator
  *this = rhs;
}


// TODO: Finish the remaining functions below
template<typename T>
 void ArrayList<T>:: resize(){
    capacity = capacity*2; // double size
    T* ptr = new T [capacity];
    for(int i = 0; i< length; i++){ //move
      ptr[i] = items[i];
    }
    delete [] items; // delete old
    items = ptr;
    ptr = nullptr;
  };

template<typename T>
 void ArrayList<T>:: add(const T& item){
   if(length==capacity){ //resize if at capacity
     resize();
   }
     items[length] = item; // add to end
     length++;
 };

 template<typename T>
 bool ArrayList<T>:: add(size_t index, const T& item){
   int a = index-size()+1; // again i use this odd method becuase i found it worked where other methods did not
   if(a>1) { // check for valid index
     return false;
   } 
   if(length == capacity){ // check for resize
     resize();
   }
   if(a == 1) { //check if adding to end
     add(item);
     return true;
   }
   else{
     for(int i=length; i>index ; i--){
        items[i] = items[i-1];//shifting over
     }
     items[index] = item; //inserting item
     length++;
     return true;
   }
 };

template<typename T>
 bool ArrayList<T>:: get(size_t index, T& return_item) const{
   int a = index-size()+1; //check valid
   if(a > 0 ){
     return false;
   }
   else{
     return_item = items[index];
     return true;
   }
 };

template<typename T>
 bool ArrayList<T>:: set(size_t index, const T& new_item){
   int a = index-size()+1;
   if(a > 0 ){
     return false;
   }
   else{
     items[index] = new_item;
     return true;
   }
 }

  template<typename T>
 bool ArrayList<T>:: remove(size_t index){ // this function works and preforms correctly even though the linked list version does not
   int a = index-size()+1;
   if(a > 0){
     return false;
   }
   else{
     for(int i=index; i<length-1 ; i++){//shift everyting down by one and cover up index, deleting it
       if(i+1 > capacity){ // if reaching over the edge of array
         resize();
        }
        items[i] = items[i+1];
      }
     length--;
     return true;
   }
 }

 template<typename T>
 size_t ArrayList<T>:: size() const{
   return length;
 }
 

#endif
