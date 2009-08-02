// ------------------------------
// projects/c++/deque/TestDeque.h
// Copyright (C) 2009
// Glenn P. Downing
// ------------------------------

#ifndef TestDeque_h
#define TestDeque_h

// --------
// includes
// --------

#include <algorithm> // equal
#include <stdexcept> // out_of_range

#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE

#include "Deque.h"

// ---------
// TestDeque
// ---------

struct TestDeque : CppUnit::TestFixture {
    // -----
    // tests
    // -----
    void test_def_constructor1(){
      My::Deque<int> x;
    }
    void test_val_constructor1(){
      My::Deque<int> x(1);
      }
    void test_val_constructor2(){
      My::Deque<int> x(10, 10);
    }
    void test_copy_constructor1(){
      My::Deque<int> x(5, 6);
      My::Deque<int> y(x); 
      CPPUNIT_ASSERT(y == x);
    }
    void test_assignment1(){
      My::Deque<int> x(5, 6);
      My::Deque<int> y(5); 
      y = x;
      }
    void test_assignment2(){
      My::Deque<int> x(10, 6);
      My::Deque<int> y(12, 7);
      My::Deque<int>::iterator ity = y.begin();
      y.resize(8);
      y = x;
      ity = y.begin();
      while(ity != y.end()){
	++ity;
      }
      CPPUNIT_ASSERT(y == x);
      }
    void test_assignment3(){
      My::Deque<int> x(20, 6);
      My::Deque<int> y(12, 7);
      My::Deque<int>::iterator ity = y.begin();
      y = x;
      ity = y.begin();
      while(ity != y.end()){
	++ity;
      }
      CPPUNIT_ASSERT(y == x);
      }
    void test_iterator1(){
      My::Deque<int> x(5, 3);
      My::Deque<int>::iterator it = x.begin();
      while(it != x.end() ){
      ++it;
        }
      }
    void test_c_iterator1(){
      const My::Deque<int> a(5, 3);
      const My::Deque<int> b(a);
      My::Deque<int>::const_iterator ita = a.begin();
      My::Deque<int>::const_iterator itb = b.begin();
      while(ita != a.end() ){
       ++ita; ++itb;
        }
     }
     void test_subscript1(){
     using namespace My;
     Deque<int> a(6, 9);
     CPPUNIT_ASSERT(a[1] == 9);
     a[1] = 3;
     CPPUNIT_ASSERT(a[1] == 3);
     a[5] = 5;
     CPPUNIT_ASSERT(a[5] == 5);
     }
     void test_back1(){
     using namespace My;
     Deque<int> a(6, 9);
     a[5] = 5;
     CPPUNIT_ASSERT(a.back() == 5);
     }
     void test_resize1(){
     using namespace My;
     Deque<int> a(15, 1);
     a.resize(7);
     a.resize(14);
     a.resize(100);
     CPPUNIT_ASSERT(a.size() == 100);
     }
     void test_clear1(){
     using namespace My;
     Deque<int> a(15, 1);
     a.clear();
     CPPUNIT_ASSERT(a.size() == 0);
     }
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDeque);

    CPPUNIT_TEST(test_def_constructor1);
    CPPUNIT_TEST(test_val_constructor1);
    CPPUNIT_TEST(test_val_constructor2);
    CPPUNIT_TEST(test_copy_constructor1);
    CPPUNIT_TEST(test_assignment1);
    CPPUNIT_TEST(test_assignment2);
    CPPUNIT_TEST(test_assignment3);
    CPPUNIT_TEST(test_iterator1);
    CPPUNIT_TEST(test_c_iterator1);
    CPPUNIT_TEST(test_subscript1);
    CPPUNIT_TEST(test_back1);
    CPPUNIT_TEST(test_resize1);
    CPPUNIT_TEST(test_clear1);
    
    CPPUNIT_TEST_SUITE_END();};

#endif // TestDeque_h
 
