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
     void test_pop_back1(){
     	using namespace My;
     	Deque<int> a(5, 1);
     	a.pop_back();
	Deque<int>::iterator it = a.begin();
	while( it != a.end() ){
	++it;
	}
    }

	void test_pop_front1(){
     	using namespace My;
     	Deque<int> a(5, 1);
	Deque<int>::iterator it = a.begin();
		a[0]=10;
	while( it != a.end() ){
	++it;
	}
	a.pop_front();
	it = a.begin();
	while( it != a.end() ){
	++it;
	}
    }
	
     void test_push_back1(){
     	using namespace My;
     	Deque<int> a(5, 1);
     	a.push_back(17);
     	a.push_back(17);
	Deque<int>::iterator it = a.begin();
	while( it != a.end() ){
	++it;
	}
     }
	 
     void test_push_front1(){
     	using namespace My;
     	Deque<int> a(5,1);
     	a.push_front(17);
     	a.push_front(16);
     	a.push_front(15);
     	a.push_front(14);
     	a.push_front(13);
     	a.push_front(12);
	Deque<int>::iterator it = a.begin();
	while( it != a.end() ){
	++it;
	}
     }
     void test_insert1(){
     	using namespace My;
     	Deque<int> a(10,2);
	Deque<int>::iterator it = a.begin();
	it += 3;
	a.insert(it, 9);
	it = a.end() - 1;
	a.insert(it, 100);
	it = a.begin();
	while( it != a.end() ){
	++it;
	}
     }
     void test_erase1(){
     	using namespace My;
     	Deque<int> a(7,3);
	Deque<int>::iterator it = a.begin();
	a[3] = 100;
	std::cout << std::endl;
	it += 3;
	a.erase(it);
	it = a.begin();
	while( it != a.end() ){
	++it;
	}
    }
    //std::cout << *it << std::endl;
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
    CPPUNIT_TEST(test_pop_back1);
    CPPUNIT_TEST(test_pop_front1);
    CPPUNIT_TEST(test_push_back1);
    CPPUNIT_TEST(test_push_front1);
    CPPUNIT_TEST(test_insert1);
    CPPUNIT_TEST(test_erase1);
    
    CPPUNIT_TEST_SUITE_END();};

#endif // TestDeque_h
 
