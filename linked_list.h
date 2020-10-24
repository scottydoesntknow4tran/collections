//----------------------------------------------------------------------
// FILE: linked_list (HW 1)
// NAME:  Scott Tornquist
// DATE:  9/3/2020
// DESC: Implements a linked list version of the list class. Elements
//       are added by default to the end of the list via a tail pointer.
//----------------------------------------------------------------------


#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "list.h"

template<typename T>
class LinkedList : public List<T>
{
public:
  LinkedList();
  LinkedList(const LinkedList<T>& rhs); // copy constructor invoked when new list created with an old list
  ~LinkedList(); // call make empty, Rule of 3, used to deallocate when a list goes out of scope, must be implemented
  LinkedList& operator=(const LinkedList<T>& rhs); //assignment operator changing the meaning of = for when a list is assigned to a list
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
  //hw2
  void merge_sort();
  void quick_sort();
  //hw4
  void sort() ;

private:
// i needed the head and tail to be public so i could test for them to make sure they are bieng updated and tracke correctly
  struct Node {
    T value;
    Node* next;
  };
  Node* head;
  Node* tail;
  size_t length;

  // helper to delete linked list
  void make_empty();
  //HW3
  Node* merge_sort(Node* left, int len);
  Node* quick_sort(Node* start, int len);
};

template <typename T>
void LinkedList<T>:: sort(){
  merge_sort();
}

template <typename T>
void LinkedList<T>::merge_sort() {
    
    //update tail
    if(size()>1){
    head = merge_sort(head, size());
    tail = head;
      for(int i=0; i<size()-1; i++) {
          tail = tail->next;
      }
    }
};

template <typename T>
typename LinkedList<T>::Node*
LinkedList<T>::merge_sort(Node* left, int len) {
    if (len <= 1) {
        return left;
    }
    int mid = len / 2;
    Node* right = left;
    if (len == 2) {
        right = left->next;
        mid = 0;
    }
    else {
        for (int i = 0; i <= mid; i++) {
            right = right->next;
        }
    }
    left = merge_sort(left, mid + 1);
    right = merge_sort(right, len - mid - 1);
    //merge
    Node* last = nullptr;
    Node* first = nullptr;
    int right_count = 0;
    int left_count = 0;
    for (;;) {
        if (((left->value <= right->value) || (right_count >= len - mid - 1)) && (left_count <= mid)) {
            if (first == nullptr) {
                first = left;
                last = left;
            }
            else {
                last->next = left;
                last = left;
            }
            if (left->next != nullptr) {
                left = left->next;
            }
            left_count++;
        }
        else if (right_count < len - mid - 1) {
            if (first == nullptr) {
                first = right;
                last = right;
            }
            else {
                last->next = right;
                last = right;
            }
            if (right->next != nullptr) {
                right = right->next;
            }
            right_count++;
        }
        else {
            break;
        }
    }
    last->next = nullptr;
    return first;
};

template <typename T>
void LinkedList<T>::quick_sort() {
    if (size() > 1) {
      head = quick_sort(head, size());
      tail = head;
      for(int i=0; i<size()-1; i++) {
        tail = tail->next;
      }
    }
};

template <typename T>
typename LinkedList<T>::Node*
LinkedList<T>::quick_sort(Node* start, int len) {
    if (len > 1) {
        T pivot_val = start->value;
        Node* placement = start;
        Node* ptr = start->next;
        int left_count = 0;
        int right_count = 0;
        for (int i = 0; i < len - 1; i++) {
            if (ptr->value <= pivot_val) {
                ptr = ptr->next;
                placement = placement->next;
                left_count++;
            }
            else if ((ptr->next != nullptr) && (ptr->next->value < pivot_val)) {
                if (i == 0) {
                    i++;
                    right_count++;
                }
                Node* move = ptr->next;
                ptr->next = move->next;
                move->next = placement->next;
                placement->next = move;
                placement = placement->next;
                left_count++;
            }
            else {
                ptr = ptr->next;
                right_count++;
            }
        }
        Node* head = start->next;
        if (placement != start) {
            start->next = placement->next;
            placement->next = start;
        }
        Node* right = start->next;
        head = quick_sort(head, left_count);
        start->next = quick_sort(right, right_count);
        if (left_count > 0) {
            return head;
        }
        else {
            return placement;
        }
    }
    else {
        return start;
    }
};

template<typename T>
LinkedList<T>:: ~LinkedList(){
  make_empty();

}

template<typename T>
void LinkedList<T>::selection_sort(){
  if (size() <= 1) {//if the list is 0 or 1 we do not need to sort
    }
  else{
    Node* start = head; // start is where we begin looking for the smallest value for every iteration
    while(start->next != nullptr){
      Node* ptr = start;
      Node* smallest = start;
      while(ptr!=nullptr){
        if(smallest->value > ptr->value){
          smallest = ptr;
        }
        ptr = ptr->next;
      }
      //at this point we know the smallest value
      if(smallest == start){ 
        start = start->next;
      }// do nothing becuase it already in the right spot
      else{
        Node* itr = start;
        while(itr->next != smallest){
          itr = itr->next;
        }//at this point itr points to the node before the smallest value that we want to move

        if(smallest == tail){
          tail = itr;// moving tail if smallest is the tail
        }

        if(smallest->next == nullptr){ //sets the node before smallest to null if smallest points to null
          itr->next = nullptr;
        }
        else{
        itr->next = smallest->next; // otherwise sets it to the node smallest points to 
        }

        if(start == head){ // sets the head to smallest if start was the head becasue it will go in front
          head = smallest;
        }
        else{
          Node* dtr = head;
          while(dtr->next != start){
            dtr = dtr->next;
          }//at thiss point dtr points to the node before start
          dtr->next = smallest;
        }
        smallest->next = start; //smallest will allways point to start
      }
    } 
  }
};

template<typename T>
void LinkedList<T>::insertion_sort() {
    if (size() <= 1) {
    }
    else {
        Node* start = head;// start is the  end of the sorted region in this function
        while (start->next != nullptr) {
            Node* ptr = start->next; // we always takt the node directly after start
            //at this point we know our value
            if (ptr->value > start->value) {
                start = start->next;
            }// do nothing becuase it already in the right spot
            else {
                if (ptr == tail) {// if we have arrived to the tail move it
                    tail = start;
                } 
                if(head->value > ptr->value){ 
                    start->next = ptr->next;
                    ptr->next = head;
                    head = ptr;
                }//put at front of list
                else {
                    Node* itr = head;
                    while (itr != start) {
                        if ((itr->next->value < ptr->value)) {// sorting through sort region for correct location
                            itr = itr->next;
                        } 
                        else {
                            break;
                            //itr is pointing to the place we need to insert ptr
                        }
                    }
                    start->next = ptr->next;// splicing node into correct position
                    ptr->next = itr->next;
                    itr->next = ptr; 
                }
            }
        }
    }

};

template<typename T>
void LinkedList<T>:: make_empty()
{
  if(length != 0){
  Node* current = head;
  head = nullptr;
  tail = nullptr;
  while(current != nullptr){
    Node* nxt = current->next;
    delete current;
    current = nxt;
  }
  length = 0;
  }
}

//constructor
template<typename T>
LinkedList<T>::LinkedList() {
  head = nullptr;
  tail = nullptr;
  length = 0;
//nothing to do
};

template<typename T>
LinkedList<T>& LinkedList<T> :: operator=(const LinkedList<T>& rhs){
if(this != &rhs){ // list1= list1
    // delete lhs, use make empty
    make_empty();
    //copy rhs into lhs(current object)
    Node *ptr1 = rhs.head;
    while (ptr1!= nullptr){
      add(ptr1->value);
      ptr1= ptr1->next;
    }

  }
  //return lhs(this)
  return *this;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs) : head(nullptr), tail(nullptr), length(0)
{
  // defer to assignment operator
  *this = rhs; // this is a pointer to the whole current object 
  //done
}

template<typename T>
void LinkedList<T>:: add(const T& item) 
{
  Node* ptr = new Node();
  ptr->value = item; 
  ptr->next = nullptr;
  if(tail == nullptr){
    head = ptr;
    tail = ptr;
  }
  else{
    tail->next = ptr;
    tail = ptr;
  }
  length++;
}

template<typename T>
bool LinkedList<T>:: add(size_t index, const T& item) 
{
  int a = index-size()+1; // i am using this method of detecting an invalid index because i had trouble using a regular inequlity
   if(a > 1 ){
     return false;
   }
  else {
    if(a == 1){ //if index== the last element
      add(item);
      return true;
    }
    else{
      Node* ptr = new Node();
      ptr->value = item; 
      ptr->next = nullptr;
      if(index==0){ // if at the front move the head
        ptr->next = head;
        head = ptr;
      }
      else{
        Node* itr = head;
        for(int i=0; i < index-1; i++){
        itr = itr->next;
      }
      ptr->next = itr->next;
      itr->next = ptr;
      itr = nullptr;
    }
    length++;
    ptr = nullptr;
    return true;
    }
  }
}

template<typename T>
bool LinkedList<T>:: get(size_t index, T& return_item) const //nothing crazy here
{
  int a = index-size()+1;
   if(a > 0 ){
     return false;
   }
   else{
    Node * itr = head;
    for(int i=0; i< index; i++){
      if(itr->next != nullptr){
        itr = itr->next;
      }
    }
    return_item = itr->value;
    itr = nullptr;
    return true;
  }
}

template<typename T>
bool LinkedList<T>:: set(size_t index, const T& new_item) //not much intresting here
{
  int a = index-size()+1;
   if(a > 0 ){
     return false;
   }
   else{
    Node* itr = head;
    for(int i=0; i< index; i++){
      itr = itr->next;
    }
    itr->value = new_item;
    itr = nullptr;
    return true;
  }

}

template<typename T>
bool LinkedList<T>:: remove(size_t index) // this was the only function i think may not be working correctly based on the performance tests, I would love it if you found the bug
{
int a = index-size()+1; 
   if(a > 0 ){ // check valid index
     return false;
   }
  else if(index == 0){ // check if removing front
    Node* itr = head;
    if(size()>1){ //if more than one node then move head
      head = itr->next;
    }
    else{ // if last node
      tail = nullptr;
      head = nullptr;
    }
    delete itr; // delete
    //itr = nullptr;// not sure if i need this
    length--;
    return true;
  }
  else{ // if not removing front node
    Node* itr = head;
    for(int i=0; i< index-1; i++){ // go to node directly before removal node
      itr = itr->next;// set itr to removal node -1
    }
    Node* ptr = itr->next;  // set ptr to removal node
    if(a == 0){ // if last node, move tail
      tail = itr; 
      itr->next = nullptr;
    }
    else{ //otherwise move next pointer to 2 nodes down
      itr->next = ptr->next;
    }
    length--;
    delete ptr; // remove ptr
    return true;
  }

return true;
}

template<typename T>
size_t LinkedList<T>:: size() const
{ 
  
  return length;
}
// TODO: Finish the remaining functions below




#endif
