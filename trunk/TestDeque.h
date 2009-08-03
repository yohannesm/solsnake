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
#include <deque>

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
      CPPUNIT_ASSERT(x.size() == 0);
      CPPUNIT_ASSERT(x.empty());
    }
    void test_def_constructor2(){
      My::Deque<char> x;
      CPPUNIT_ASSERT(x.size() == 0);
      CPPUNIT_ASSERT(x.empty());
    }
    void test_def_constructor3(){
      My::Deque<double> x;
      CPPUNIT_ASSERT(x.size() == 0);
      CPPUNIT_ASSERT(x.empty());
    }

    void test_val_constructor1(){
      My::Deque<int> x(1);
      CPPUNIT_ASSERT(x.size() == 1);
      CPPUNIT_ASSERT(x.at(0) == 0);
      }

    void test_val_constructor2(){
      My::Deque<int> x(10, 10);
      CPPUNIT_ASSERT(x.size() == 10);
      CPPUNIT_ASSERT(x.at(0) == 10);
      CPPUNIT_ASSERT(x.at(9) == 10);
    }
    void test_val_constructor3(){
      My::Deque<int> x(300, 10);
      CPPUNIT_ASSERT(x.size() == 300);
    }

    void test_copy_constructor1(){
      My::Deque<int> x(5, 6);
      My::Deque<int> y(x); 
      CPPUNIT_ASSERT(y == x);
      y.pop_back();
      CPPUNIT_ASSERT(y.size() == 4);
      CPPUNIT_ASSERT(x.size() == 5);
      CPPUNIT_ASSERT(y != x);
    }
    void test_copy_constructor2(){
      My::Deque<int> x(10, 6);
      My::Deque<int> y(x); 
      CPPUNIT_ASSERT(y == x);
      y[4] = 2;
      CPPUNIT_ASSERT(y.size() == 10);
      CPPUNIT_ASSERT(x.size() == 10);
      CPPUNIT_ASSERT(y < x);
      x = y;
      CPPUNIT_ASSERT(x == y);
    }

    void test_assignment1(){
      My::Deque<int> x(5, 6);
      My::Deque<int> y(5); 
      y = x;
      CPPUNIT_ASSERT(x == y);
      }

    void test_assignment2(){
      My::Deque<int> x(10, 6);
      My::Deque<int> y(12, 7);
      My::Deque<int>::iterator ity = y.begin();
      y.resize(8);
      y = x;
      CPPUNIT_ASSERT(y == x);
      }

    void test_assignment3(){
      My::Deque<int> x(20, 6);
      My::Deque<int> y(12, 7);
      My::Deque<int>::iterator ity = y.begin();
      y = x;
      CPPUNIT_ASSERT(y == x);
      }

    void test_iterator1(){
      My::Deque<int> x(5, 3);
      std::deque<int> y(5, 3);
      My::Deque<int>::iterator it = x.begin();
      std::deque<int>::iterator it1 = y.begin();
      while(it != x.end() ){
      CPPUNIT_ASSERT( *it == *it1);
      ++it; ++it1;
        }
      }
    void test_iterator2(){
      My::Deque<int> x(15, 10);
      std::deque<int> y(15, 10);
      My::Deque<int>::iterator it = x.begin();
      std::deque<int>::iterator it1 = y.begin();
      while(it != x.end() ){
      CPPUNIT_ASSERT( *it == *it1);
      ++it; ++it1;
        }
      }

    void test_c_iterator1(){
      const My::Deque<int> a(5, 3);
      const My::Deque<int> b(a);
      My::Deque<int>::const_iterator ita = a.begin();
      My::Deque<int>::const_iterator itb = b.begin();
      while(ita != a.end() ){
      CPPUNIT_ASSERT( *ita == *itb);
       ++ita; ++itb;
        }
     }
    void test_c_iterator2(){
      const My::Deque<int> a(5, 3);
      const std::deque<int> b(5,3);
      My::Deque<int>::const_iterator ita = a.begin();
      std::deque<int>::const_iterator itb = b.begin();
      while(ita != a.end() ){
      CPPUNIT_ASSERT( *ita == *itb);
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
     
     void test_subscript2(){
     using namespace My;
     Deque<int> a(10, 1);
     CPPUNIT_ASSERT(a[0] == 1);
     a[0] = 3;
     CPPUNIT_ASSERT(a[0] == 3);
     a[5] = 5;
     CPPUNIT_ASSERT(a[5] == 5);
     }

     void test_at1(){
     using namespace My;
     Deque<int> a(6, 9);
     CPPUNIT_ASSERT(a.at(1) == 9);
     a[1] = 3;
     CPPUNIT_ASSERT(a.at(1) == 3);
     try{
         a.at(18);
         CPPUNIT_ASSERT(false);
     }
     catch(std::out_of_range e){
        CPPUNIT_ASSERT(true);
     }
     }

     void test_at2(){
     using namespace My;
     Deque<int> a(10, 1);
     CPPUNIT_ASSERT(a.at(1) == 1);
     CPPUNIT_ASSERT(a.at(3) == 1);
     try{
         a.at(-1);
         CPPUNIT_ASSERT(false);
     }
     catch(std::out_of_range e){
        CPPUNIT_ASSERT(true);
     }
     }

     void test_back1(){
     using namespace My;
     Deque<int> a(6, 9);
     a[5] = 5;
     CPPUNIT_ASSERT(a.back() == 5);
     }

     void test_back2(){
     using namespace My;
     Deque<int> a(12, 8);
     CPPUNIT_ASSERT(a.back() == 8);
     a[11] = 1;
     CPPUNIT_ASSERT(a.back() == 1);
     a.push_back(31);
     CPPUNIT_ASSERT(a.back() == 31);
     }

     void test_resize1(){
     using namespace My;
     Deque<int> a(15, 1);
     a.resize(7);
     CPPUNIT_ASSERT(a.size() == 7);
     a.resize(100);
     CPPUNIT_ASSERT(a.size() == 100);
     }

     void test_resize2(){
     using namespace My;
     Deque<int> a(15, 1);
     a.resize(14);
     CPPUNIT_ASSERT(a.size() == 14);
     a.resize(100);
     CPPUNIT_ASSERT(a.size() == 100);
     }

     void test_resize3(){
     using namespace My;
     Deque<int> a(15, 1);
     a.resize(0);
     CPPUNIT_ASSERT(a.size() == 0);
     a.resize(1);
     CPPUNIT_ASSERT(a.size() == 1);
     }

     void test_clear1(){
     using namespace My;
     Deque<int> a(15, 1);
     a.clear();
     CPPUNIT_ASSERT(a.size() == 0);
     }

     void test_clear2(){
     using namespace My;
     Deque<int> a;
     a.clear();
     CPPUNIT_ASSERT(a.size() == 0);
     }

     void test_pop_back1(){
     	using namespace My;
     	Deque<int> a(5, 1);
     	a.pop_back();
        CPPUNIT_ASSERT(a.size() == 4);
        try{
         a.at(4);
         CPPUNIT_ASSERT(false);
         }
     catch(std::out_of_range e){
        CPPUNIT_ASSERT(true);
    }
    }

	void test_pop_front1(){
     	using namespace My;
     	Deque<int> a(5, 1);
	a[0] = 123;
	a.pop_front();
        CPPUNIT_ASSERT(a.size() == 4);
        CPPUNIT_ASSERT(a[0] == 1);
    }
	
     void test_push_back1(){
     	using namespace My;
     	Deque<int> a(5, 1);
     	a.push_back(17);
     	a.push_back(17);
        CPPUNIT_ASSERT(a[5] == 17);
        CPPUNIT_ASSERT(a[6] == 17);
     }
		
     void test_push_back2(){
     	using namespace My;
     	Deque<int> a(5, 1);
     	a.push_back(17);
     	a.push_back(17);
        CPPUNIT_ASSERT(a.size() == 7);
     }
	
     void test_push_front1(){
     	using namespace My;
     	Deque<int> a(5,1);
     	a.push_front(17);
        CPPUNIT_ASSERT(a[0] == 17);
     	a.push_front(16);
        CPPUNIT_ASSERT(a[0] == 16);
     	a.push_front(15);
        CPPUNIT_ASSERT(a[0] == 15);
     }

     void test_push_front2(){
     	using namespace My;
     	Deque<int> a(5,1);
     	a.push_front(17);
     	a.push_front(16);
     	a.push_front(15);
        CPPUNIT_ASSERT(a.size() == 8);
     }

//insert in the middle
     void test_insert1(){
     	using namespace My;
     	Deque<int> a(10,2);
	Deque<int>::iterator it = a.begin();
	it += 3;
	a.insert(it, 9);
	CPPUNIT_ASSERT(a[3]==9);
	it = a.end() - 1;
	a.insert(it, 100);
	it = a.begin();
	while( it != a.end() ){
	++it;
	}
     }


//insert in the front and end
     void test_insert2(){
     	using namespace My;
     	Deque<int> a(5,2);
	Deque<int>::iterator it = a.begin();
	a.insert(it,1000);
	CPPUNIT_ASSERT(a[0]==1000);
     }
     void test_insert3(){
     	using namespace My;
     	Deque<int> a(5,2);
	Deque<int>::iterator it = a.end() - 1;
	a.insert(it,13);
	CPPUNIT_ASSERT(a[5]==13);
     }

//erase in the middle
     void test_erase1(){
     	using namespace My;
     	Deque<int> a(7,3);
	Deque<int>::iterator it = a.begin();
	a[3] = 100;
	it += 3;
	a.erase(it);
	CPPUNIT_ASSERT(*it==3);
	it = a.begin();
	while( it != a.end() ){
	++it;
	}
    }

//erase front and back
     void test_erase2(){
     	using namespace My;
     	Deque<int> a(7,3);
	Deque<int>::iterator it = a.begin();
	a[0] = 100;
	a[6] = 1000;
	a.erase(it);
	CPPUNIT_ASSERT(*(a.begin())!=100);
	it= (a.end()-1);
	a.erase(it);
	it = a.begin();
	while( it != a.end() ){
	++it;
	}
	CPPUNIT_ASSERT(*(a.end()-1)!=1000);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDeque);

    CPPUNIT_TEST(test_def_constructor1);
    CPPUNIT_TEST(test_def_constructor2);
    CPPUNIT_TEST(test_def_constructor3);
    CPPUNIT_TEST(test_val_constructor1);
    CPPUNIT_TEST(test_val_constructor2);
    CPPUNIT_TEST(test_val_constructor3);
    CPPUNIT_TEST(test_copy_constructor1);
    CPPUNIT_TEST(test_copy_constructor2);
    CPPUNIT_TEST(test_assignment1);
    CPPUNIT_TEST(test_assignment2);
    CPPUNIT_TEST(test_assignment3);
    CPPUNIT_TEST(test_iterator1);
    CPPUNIT_TEST(test_iterator2);
    CPPUNIT_TEST(test_c_iterator1);
    CPPUNIT_TEST(test_c_iterator2);
    CPPUNIT_TEST(test_subscript1);
    CPPUNIT_TEST(test_subscript2);
    CPPUNIT_TEST(test_at1);
    CPPUNIT_TEST(test_at2);
    CPPUNIT_TEST(test_back1);
    CPPUNIT_TEST(test_back2);
    CPPUNIT_TEST(test_resize1);
    CPPUNIT_TEST(test_resize2);
    CPPUNIT_TEST(test_resize3);
    CPPUNIT_TEST(test_clear1);
    CPPUNIT_TEST(test_clear2);
    CPPUNIT_TEST(test_pop_back1);
    CPPUNIT_TEST(test_pop_front1);
    CPPUNIT_TEST(test_push_back1);
    CPPUNIT_TEST(test_push_back2);
    CPPUNIT_TEST(test_push_front1);
    CPPUNIT_TEST(test_push_front2);
    CPPUNIT_TEST(test_insert1);
    CPPUNIT_TEST(test_insert2);
    CPPUNIT_TEST(test_insert3);
    CPPUNIT_TEST(test_erase1);
    CPPUNIT_TEST(test_erase2);
    CPPUNIT_TEST_SUITE_END();};

#endif // TestDeque_h
 
