//----------------------------------------------------------------------
// Name: 
// File: hw4_test.cpp
// Date: Fall 2020
// Desc: Unit tests for ArrayList and LinkedList key-value collection
//       implementations
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "array_list.h"
#include "array_list_collection.h"
#include "linked_list_collection.h"
#include <time.h>

using namespace std;


// Helper function to print out a key-value collection
template<typename K,typename V>
void print(const Collection<K,V>& kv_list)
{
  cout << "{";
  ArrayList<K> the_keys;
  kv_list.keys(the_keys);
  for (size_t i = 0; i < the_keys.size(); ++i) {
    K key;
    V val;
    the_keys.get(i, key);
    kv_list.find(key, val);
    cout << key << ": " << val;
    if (i < the_keys.size() - 1)
      cout << ", ";
  }
  cout << "}";
}

// Helper function to check membership in a list
template<typename T>
bool member(const T& member_val, const List<T>& list)
{
  for (int i = 0; i < list.size(); ++i) {
    T list_val;
    list.get(i, list_val);
    if (list_val == member_val)
      return true;
  }
  return false;
}


// Test 1 (a): Check add and size
TEST(BasicArrayCollectionTest, CorrectSize) {
  ArrayListCollection<string,int> c;
  ASSERT_EQ(0, c.size());
  c.add("b", 10);
  ASSERT_EQ(1, c.size());
  c.add("a", 20);
  ASSERT_EQ(2, c.size());
  c.add("c", 20);
  ASSERT_EQ(3, c.size());
}

// Test 1 (b): Check add and size
TEST(BasicLinkedCollectionTest, CorrectSize) {
  LinkedListCollection<string,int> c;
  ASSERT_EQ(0, c.size());
  c.add("b", 10);
  ASSERT_EQ(1, c.size());
  c.add("a", 20);
  ASSERT_EQ(2, c.size());
  c.add("c", 20);
  ASSERT_EQ(3, c.size());
}

// Test 2(a): Test add and find
TEST(BasicArrayCollectionTest, SimpleFind) {
  ArrayListCollection<string,int> c;
  int v;
  ASSERT_EQ(false, c.find("b", v));
  c.add("b", 10);
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(10, v);
  ASSERT_EQ(false, c.find("a", v));
  c.add("a", 20);
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(20, v);
  ASSERT_EQ(false, c.find("c", v));
  c.add("c", 30);
  ASSERT_EQ(true, c.find("c", v));
  ASSERT_EQ(30, v);
}

// Test 2(b): Test add and find
TEST(BasicLinkedCollectionTest, SimpleFind) {
  LinkedListCollection<string,int> c;
  int v;
  ASSERT_EQ(false, c.find("b", v));
  c.add("b", 10);
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(10, v);
  ASSERT_EQ(false, c.find("a", v));
  c.add("a", 20);
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(20, v);
  ASSERT_EQ(false, c.find("c", v));
  c.add("c", 30);
  ASSERT_EQ(true, c.find("c", v));
  ASSERT_EQ(30, v);
}

// Test 3(a): Test add, size, and remove
TEST(BasicArrayCollectionTest, SimpleRemove) {
  ArrayListCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("c", 30);
  ASSERT_EQ(3, c.size());
  int v;
  // all three pairs in collection
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));  
  // remove one
  c.remove("a");
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(false, c.find("a", v));
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));  
  // remove another
  c.remove("b");
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(false, c.find("a", v));
  ASSERT_EQ(false, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));  
  // remove last one
  c.remove("c");
  ASSERT_EQ(0, c.size());
  ASSERT_EQ(false, c.find("a", v));
  ASSERT_EQ(false, c.find("b", v));
  ASSERT_EQ(false, c.find("c", v));  
}

// Test 3(b): Test add, size, and remove
TEST(BasicLinkedCollectionTest, SimpleRemove) {
  LinkedListCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("c", 30);
  ASSERT_EQ(3, c.size());
  int v;
  // all three pairs in collection
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));  
  // remove one
  c.remove("a");
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(false, c.find("a", v));
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));  
  // remove another
  c.remove("b");
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(false, c.find("a", v));
  ASSERT_EQ(false, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));  
  // remove last one
  c.remove("c");
  ASSERT_EQ(0, c.size());
  ASSERT_EQ(false, c.find("a", v));
  ASSERT_EQ(false, c.find("b", v));
  ASSERT_EQ(false, c.find("c", v));  
}

// Test 4(a): Test add, size, and find range
TEST(BasicArrayCollectionTest, SimpleRange) {
  ArrayListCollection<string,int> c;
  c.add("e", 50);
  c.add("c", 30);
  c.add("d", 40);
  c.add("f", 60);
  c.add("b", 20);
  // search for proper sublist of keys
  ArrayList<string> s1;
  c.find("c", "e", s1);
  ASSERT_EQ(3, s1.size());
  ASSERT_EQ(true, member(string("c"), s1));
  ASSERT_EQ(true, member(string("d"), s1));
  ASSERT_EQ(true, member(string("e"), s1));
  // search for overlapping prefix
  ArrayList<string> s2;
  c.find("a", "c", s2);
  ASSERT_EQ(2, s2.size());
  ASSERT_EQ(true, member(string("b"), s2));
  ASSERT_EQ(true, member(string("c"), s2));
  // search for overlapping suffix
  ArrayList<string> s3;
  c.find("e", "g", s3);
  ASSERT_EQ(2, s3.size());
  ASSERT_EQ(true, member(string("e"), s3));
  ASSERT_EQ(true, member(string("f"), s3));
  // search for empty sublist of keys
  ArrayList<string> s4;
  c.find("f", "b", s4);
  ASSERT_EQ(0, s4.size());
}

// Test 4(a): Test add, size, and find range
TEST(BasicLinkedCollectionTest, SimpleRange) {
  LinkedListCollection<string,int> c;
  c.add("e", 50);
  c.add("c", 30);
  c.add("d", 40);
  c.add("f", 60);
  c.add("b", 20);
  // search for proper sublist of keys
  ArrayList<string> s1;
  c.find("c", "e", s1);
  ASSERT_EQ(3, s1.size());
  ASSERT_EQ(true, member(string("c"), s1));
  ASSERT_EQ(true, member(string("d"), s1));
  ASSERT_EQ(true, member(string("e"), s1));
  // search for overlapping prefix
  ArrayList<string> s2;
  c.find("a", "c", s2);
  ASSERT_EQ(2, s2.size());
  ASSERT_EQ(true, member(string("b"), s2));
  ASSERT_EQ(true, member(string("c"), s2));
  // search for overlapping suffix
  ArrayList<string> s3;
  c.find("e", "g", s3);
  ASSERT_EQ(2, s3.size());
  ASSERT_EQ(true, member(string("e"), s3));
  ASSERT_EQ(true, member(string("f"), s3));
  // search for empty sublist of keys
  ArrayList<string> s4;
  c.find("f", "b", s4);
  ASSERT_EQ(0, s4.size());
}

// Test 5(a): Test add and sort
TEST(BasicArrayCollectionTest, SimpleSort) {
  ArrayListCollection<string,int> c;
  c.add("a", 10);
  c.add("e", 50);
  c.add("c", 30);
  c.add("b", 20);
  c.add("d", 40);
  ArrayList<string> sorted_keys;
  c.sort(sorted_keys);
  ASSERT_EQ(5, sorted_keys.size());
  // check if in sorted order
  for (size_t i = 1; i < sorted_keys.size(); ++i) {
    string k1;
    string k2;
    ASSERT_EQ(true, sorted_keys.get(i-1, k1));
    ASSERT_EQ(true, sorted_keys.get(i, k2));
    ASSERT_LT(k1, k2);
  }
}

// Test 5(b): Test add and sort
TEST(BasicLinkedCollectionTest, SimpleSort) {
  LinkedListCollection<string,int> c;
  c.add("a", 10);
  c.add("e", 50);
  c.add("c", 30);
  c.add("b", 20);
  c.add("d", 40);
  ArrayList<string> sorted_keys;
  c.sort(sorted_keys);
  ASSERT_EQ(5, sorted_keys.size());
  // check if in sorted order
  for (size_t i = 1; i < sorted_keys.size(); ++i) {
    string k1;
    string k2;
    ASSERT_EQ(true, sorted_keys.get(i-1, k1));
    ASSERT_EQ(true, sorted_keys.get(i, k2));
    ASSERT_LT(k1, k2);
  }
}

// TODO: Add at least 10 non-trival tests below. Be sure for each test
// to provide comments describing the detailed purpose of each the
// test.


// Test 6(a): Test add, size, and double remove on non present keys
TEST(BasicArrayCollectionTest, DoubleRemove) {
  ArrayListCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("c", 30);
  ASSERT_EQ(3, c.size());
  int v;
  // all three pairs in collection and nothing else
  ASSERT_EQ(false, c.find("d", v));
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));  
  
  //remove a twice and check that nothing changes after trying to remove again
  c.remove("a");
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(false, c.find("a", v));
  c.remove("a");
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(false, c.find("a", v));
//remove b twice and check that nothing changes after trying to remove again
  c.remove("b");
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(false, c.find("b", v));
  c.remove("b");
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(false, c.find("b", v));
//remove c twice and check that nothing changes after trying to remove again
  c.remove("c");
  ASSERT_EQ(0, c.size());
  ASSERT_EQ(false, c.find("c", v));
  c.remove("c");
  ASSERT_EQ(0, c.size());
  ASSERT_EQ(false, c.find("c", v));

}

// Test 6(b): Test add, size, and double remove on non present keys
TEST(BasicLinkedCollectionTest, DoubleRemove) {
  LinkedListCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("c", 30);
  ASSERT_EQ(3, c.size());
  int v;
  // all three pairs in collection and nothing else
  ASSERT_EQ(false, c.find("d", v));
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));  
  
  //remove a twice and check that nothing changes after trying to remove again
  c.remove("a");
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(false, c.find("a", v));
  c.remove("a");
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(false, c.find("a", v));
//remove b twice and check that nothing changes after trying to remove again
  c.remove("b");
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(false, c.find("b", v));
  c.remove("b");
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(false, c.find("b", v));
//remove c twice and check that nothing changes after trying to remove again
  c.remove("c");
  ASSERT_EQ(0, c.size());
  ASSERT_EQ(false, c.find("c", v));
  c.remove("c");
  ASSERT_EQ(0, c.size());
  ASSERT_EQ(false, c.find("c", v));

}


// Test 7(a): Test sort on large set of random positive and negative keys
TEST(BasicArrayCollectionTest, RandNegativeSort) {
  ArrayListCollection<int,string> c;
  c.add(7,"a");
  c.add(3, "a");
  c.add(-6, "a");
  c.add(1,"a");
  c.add(-9,"a");
  c.add(2,"a");
  c.add(-1,"a");
  c.add(76, "a");
  c.add(-36, "a");
  c.add(10,"a");
  c.add(4,"a");
  c.add(11,"a");
  ASSERT_EQ(12, c.size());
  ArrayList<int> a;
  c.sort(a);
  for (int i = 0; i < 11; ++i) {
    int val1 = 0;
    int val2 = 0;
    a.get(i, val1);
    a.get(i+1, val2);
    ASSERT_LE(val1, val2);
  }

}

// Test 7(b): Test sort on large set of random positive and negative keys
TEST(BasicLinkedCollectionTest, RandNegativeSort) {
  LinkedListCollection<int,string> c;
  c.add(7,"a");
  c.add(3, "a");
  c.add(-6, "a");
  c.add(1,"a");
  c.add(-9,"a");
  c.add(2,"a");
  c.add(-1,"a");
  c.add(76, "a");
  c.add(-36, "a");
  c.add(10,"a");
  c.add(4,"a");
  c.add(11,"a");
  ASSERT_EQ(12, c.size());
  ArrayList<int> a;
  c.sort(a);
  for (int i = 0; i < 11; ++i) {
    int val1 = 0;
    int val2 = 0;
    a.get(i, val1);
    a.get(i+1, val2);
    ASSERT_LE(val1, val2);
  }

}


// Test 8(a): Test keys and find function return on empty lists, and make sure they are equivalent on non-empty list
TEST(BasicArrayCollectionTest, KeysFunction) {
  ArrayListCollection<int,string> c;
  ASSERT_EQ(0, c.size());
  ArrayList<int> a;
  ArrayList<int> b;
  c.keys(a);
  ASSERT_EQ(0,a.size());
  c.find(-100,100,b);
  ASSERT_EQ(0,b.size());

  for (int i =0 ; i<=9; i++){
    c.add(i,"a");
  }

  ASSERT_EQ(10, c.size());
  c.keys(a);
  
  c.find(-100,100,b);
  for (int i = 0; i <= 9; ++i) {
    int val1 =0;
    int val2 =0;
    a.get(i, val1);
    b.get(i, val2);
    ASSERT_EQ(val1, val2);
  }

}

// Test 8(b): Test keys and find function return on empty lists, and make sure they are equivalent on non-empty list
TEST(BasicLinkedCollectionTest, KeysFunction) {
  LinkedListCollection<int,string> c;
  ASSERT_EQ(0, c.size());
  ArrayList<int> a;
  ArrayList<int> b;
  c.keys(a);
  ASSERT_EQ(0,a.size());
  c.find(-100,100,b);
  ASSERT_EQ(0,b.size());

  for (int i =0 ; i<=9; i++){
    c.add(i,"a");
  }

  ASSERT_EQ(10, c.size());
  c.keys(a);
  
  c.find(-100,100,b);
  for (int i = 0; i <= 9; ++i) {
    int val1 =0;
    int val2 =0;
    a.get(i, val1);
    b.get(i, val2);
    ASSERT_EQ(val1, val2);
  }
}

// Test 9(a): Rapid add and remove to 0, 1 and 2 length lists to check corner cases and using find functon on corners
TEST(BasicArrayCollectionTest, RapidAddRemove) {
  ArrayListCollection<int,string> c;
  ASSERT_EQ(0, c.size());
  ArrayList<int> a;
  //testing 0 length array
  for(int i=0; i++; i<10){
    c.add(7, "q");
    ASSERT_EQ(1, c.size());
    c.remove(7);
    ASSERT_EQ(0, c.size());
  }

  c.add(8, "q");
  ASSERT_EQ(1, c.size());
  //testing 1 length array
  for(int i=0; i++; i<10){
    c.add(7, "d");
    ASSERT_EQ(2, c.size());
    c.remove(7);
    ASSERT_EQ(1, c.size());
  }

  c.add(7, "d");
  ASSERT_EQ(2, c.size());
  //testing 1 length array
  for(int i=0; i++; i<10){
    c.remove(8);
    ASSERT_EQ(1, c.size());
    c.add(8, "q");
    ASSERT_EQ(2, c.size());
  }

  ASSERT_EQ(2, c.size());
  //testing 2 length array
  string temp1;
  string temp2;
  for(int i=0; i++; i<10){

    c.add(9, "e");

    ASSERT_EQ(3, c.size());
    c.find(9,temp1);
    ASSERT_EQ("e", temp1) ;
    c.find(7,temp2);
    ASSERT_EQ("q", temp2) ;

    c.remove(8);

    ASSERT_EQ(2, c.size());
    c.find(9,temp1);
    ASSERT_EQ("e", temp1) ;
    c.find(7,temp2);
    ASSERT_EQ("q", temp2) ;
  }
}

// Test 9(b): Rapid add and remove to 0, 1 and 2 length lists to check corner cases and using find functon on corners
TEST(BasicLinkedCollectionTest, RapidAddRemove) {
  LinkedListCollection<int,string> c;
  ASSERT_EQ(0, c.size());
  LinkedList<int> a;
  //testing 0 length array
  for(int i=0; i++; i<10){
    c.add(7, "q");
    ASSERT_EQ(1, c.size());
    c.remove(7);
    ASSERT_EQ(0, c.size());
  }

  c.add(8, "q");
  ASSERT_EQ(1, c.size());
  //testing 1 length array
  for(int i=0; i++; i<10){
    c.add(7, "d");
    ASSERT_EQ(2, c.size());
    c.remove(7);
    ASSERT_EQ(1, c.size());
  }

  c.add(7, "d");
  ASSERT_EQ(2, c.size());
  //testing 1 length array
  for(int i=0; i++; i<10){
    c.remove(8);
    ASSERT_EQ(1, c.size());
    c.add(8, "q");
    ASSERT_EQ(2, c.size());
  }

  ASSERT_EQ(2, c.size());
  //testing 2 length array
  string temp1;
  string temp2;
  for(int i=0; i++; i<10){

    c.add(9, "e");

    ASSERT_EQ(3, c.size());
    c.find(9,temp1);
    ASSERT_EQ("e", temp1) ;
    c.find(7,temp2);
    ASSERT_EQ("q", temp2) ;

    c.remove(8);

    ASSERT_EQ(2, c.size());
    c.find(9,temp1);
    ASSERT_EQ("e", temp1) ;
    c.find(7,temp2);
    ASSERT_EQ("q", temp2) ;
  }
}

// Test 10(a): Testing that all functions work correcly together in congruence
TEST(BasicArrayCollectionTest, AllFunctions) {
  ArrayListCollection<int,string> c;
  ASSERT_EQ(0, c.size());

  for (int i =0 ; i<=9; i++){
    c.add(i,"a");
  }
  ASSERT_EQ(10, c.size()); //testing add

  string t;
  for (int i =0 ; i<=9; i++){
    c.find(i,t);
    ASSERT_EQ("a",t); //testing find1
  }

  ASSERT_EQ(10,c.size());

  ArrayList<int> a;
  for (int i =0 ; i<=9; i++){
    c.find(i,9,a);
    ASSERT_EQ(10-i,a.size()); //testing find2
  }

  ASSERT_EQ(10,c.size());

  c.keys(a); // testing keys
  ArrayList<int> b;
  c.find(-100,100,b);
  for (int i = 0; i <= 9; ++i) {
    int val1 =0;
    int val2 =0;
    a.get(i, val1);
    b.get(i, val2);
    ASSERT_EQ(val1, val2);
  }

  ASSERT_EQ(10,c.size());

  c.sort(a); //testing sort
  int val1 = 0;
  int val2 = 0;
  for (int i = 0; i <= 8; ++i) {
    a.get(i, val1);
    a.get(i+1, val2);
    ASSERT_LE(val1, val2);
  }

  ASSERT_EQ(10,c.size());

  for (int i = 0; i <= 9; ++i) { //testing remove
    ASSERT_EQ(10-i,c.size());
    c.remove(i);
  }
  
  ASSERT_EQ(0,c.size());

}

// Test 10(b): Testing that all functions work correcly together in congruence
TEST(BasicLinkedCollectionTest, AllFunctions) {
  LinkedListCollection<int,string> c;
  ASSERT_EQ(0, c.size());

  for (int i =0 ; i<=9; i++){
    c.add(i,"a");
  }
  ASSERT_EQ(10, c.size()); //testing add

  string t;
  for (int i =0 ; i<=9; i++){
    c.find(i,t);
    ASSERT_EQ("a",t); //testing find1
  }

  ASSERT_EQ(10,c.size());

  ArrayList<int> a;
  for (int i =0 ; i<=9; i++){
    c.find(i,9,a);
    ASSERT_EQ(10-i,a.size()); //testing find2
  }

  ASSERT_EQ(10,c.size());

  c.keys(a); // testing keys
  ArrayList<int> b;
  c.find(-100,100,b);
  for (int i = 0; i <= 9; ++i) {
    int val1 =0;
    int val2 =0;
    a.get(i, val1);
    b.get(i, val2);
    ASSERT_EQ(val1, val2);
  }

  ASSERT_EQ(10,c.size());

  c.sort(a); //testing sort
  int val1 = 0;
  int val2 = 0;
  for (int i = 0; i <= 8; ++i) {
    a.get(i, val1);
    a.get(i+1, val2);
    ASSERT_LE(val1, val2);
  }

  ASSERT_EQ(10,c.size());

  for (int i = 0; i <= 9; ++i) { //testing remove
    ASSERT_EQ(10-i,c.size());
    c.remove(i);
  }
  
  ASSERT_EQ(0,c.size());

}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

