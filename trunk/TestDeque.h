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
#include <string>

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
	  std::deque<int> a(1,2);
	  My::Deque<std::deque<int> > y(10,a);
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
    






    void test_deque_default_constructor1 () {
		using namespace My;
		Deque<int> a;
	}
	void test_deque_default_constructor2 () {
		using namespace My;
		Deque<char> a;
	}
	void test_deque_constructor1 () {
		using namespace My;
		Deque<int> a(9);
		Deque<int> b(10);
		Deque<int> c(9, 9);
		Deque<int> d(10, 10);
	}
	void test_deque_constructor2 () {
		using namespace My;
		Deque<char> a(9);
		Deque<char> b(10);
		Deque<char> c(9, 'a');
		Deque<char> d(10, 'w');
	}
	void test_deque_copy_constructor1 () {
		using namespace My;
		Deque<int> a(9);
		Deque<int> b(a);
		Deque<int> c(9, 9);
		Deque<int> d(c);
		Deque<int> e(10);
		Deque<int> f(e);
		Deque<int> g(10, 10);
		Deque<int> h(g);
	}
	void test_deque_copy_constructor2 () {
		using namespace My;
		Deque<char> a(9);
		Deque<char> b(a);
		Deque<char> c(9, 'a');
		Deque<char> d(c);
		Deque<char> e(10);
		Deque<char> f(e);
		Deque<char> g(10, 'w');
		Deque<char> h(g);
	}
	
	// ----------
	// assignment
	// ----------
	
	void test_deque_assignment1 () {
		using namespace My;
		Deque<int> a(3, 123);
		Deque<int> b = a;
		CPPUNIT_ASSERT(a == b);
	}
	void test_deque_assignment2 () {
		using namespace My;
	}
	
	// ---------
	// subscript
	// ---------
	
	void test_deque_subscript1 () {
		using namespace My;
		Deque<int> a(9);
		CPPUNIT_ASSERT(a[0] == 0);
		CPPUNIT_ASSERT(a[8] == 0);
		Deque<int> b(10);
		CPPUNIT_ASSERT(b[0] == 0);
		CPPUNIT_ASSERT(b[9] == 0);
		Deque<int> c(9, 9);
		CPPUNIT_ASSERT(c[0] == 9);
		CPPUNIT_ASSERT(c[8] == 9);
		Deque<int> d(10, 10);
		CPPUNIT_ASSERT(d[0] == 10);
		CPPUNIT_ASSERT(d[9] == 10);
	}
	void test_deque_subscript2 () {
		using namespace My;
		Deque<char> a(9);
		Deque<char> b(10);
		Deque<char> c(9, 'a');
		CPPUNIT_ASSERT(c[0] == 'a');
		CPPUNIT_ASSERT(c[8] == 'a');
		Deque<char> d(10, 'w');
		CPPUNIT_ASSERT(d[0] == 'w');
		CPPUNIT_ASSERT(d[9] == 'w');
	}
	
	// ----
	// back
	// ----
	
	void test_deque_back1 () {
		using namespace My;
		Deque<int> a(9);
		CPPUNIT_ASSERT(a.back() == 0);
		Deque<int> b(a);
		CPPUNIT_ASSERT(b.back() == 0);
		Deque<int> c(9, 123);
		CPPUNIT_ASSERT(c.back() == 123);
		Deque<int> d(c);
		CPPUNIT_ASSERT(d.back() == 123);
		Deque<int> e(10, 456);
		CPPUNIT_ASSERT(e.back() == 456);
		Deque<int> f(e);
		CPPUNIT_ASSERT(f.back() == 456);
	}
	
	void test_deque_back2 () {
		using namespace My;
		Deque<char> a(9);
		Deque<char> b(a);
		Deque<char> c(9, 'a');
		CPPUNIT_ASSERT(c.back() == 'a');
		Deque<char> d(c);
		CPPUNIT_ASSERT(d.back() == 'a');
		Deque<char> e(10, 'x');
		CPPUNIT_ASSERT(e.back() == 'x');
		Deque<char> f(e);
		CPPUNIT_ASSERT(f.back() == 'x');
	}
	
	// --------
	// iterator
	// --------
	void test_deque_iterator1 () {
		using namespace My;
		Deque<int> a(9,123);
		CPPUNIT_ASSERT(*(a.begin()) == 123);
		CPPUNIT_ASSERT(*(a.end()-1) == 123);
	}
	void test_deque_iterator2 () {
		using namespace My;
		Deque<int> a(9,123);
		CPPUNIT_ASSERT(*(a.begin()) == 123);
	}
	
	// ----
	// size
	// ----
	
	void test_deque_size1 () {
		using namespace My;
		Deque<int> a;
		CPPUNIT_ASSERT(a.size() == 0);
		Deque<int> b(a);
		CPPUNIT_ASSERT(b.size() == 0);
		Deque<int> c(9);
		CPPUNIT_ASSERT(c.size() == 9);
		Deque<int> d(c);
		CPPUNIT_ASSERT(d.size() == 9);
		Deque<int> e(10, 10);
		CPPUNIT_ASSERT(e.size() == 10);
		Deque<int> f(e);
		CPPUNIT_ASSERT(f.size() == 10);
	}
	void test_deque_size2 () {
		using namespace My;
		Deque<char> a;
		CPPUNIT_ASSERT(a.size() == 0);
		Deque<char> b(a);
		CPPUNIT_ASSERT(b.size() == 0);
		Deque<char> c(9);
		CPPUNIT_ASSERT(c.size() == 9);
		Deque<char> d(c);
		CPPUNIT_ASSERT(d.size() == 9);
		Deque<char> e(10, 'a');
		CPPUNIT_ASSERT(e.size() == 10);
		Deque<char> f(e);
		CPPUNIT_ASSERT(f.size() == 10);
	}
	
	// -----
	// empty
	// -----
	
	void test_deque_empty1 () {
		using namespace My;
		Deque<int> a;
		CPPUNIT_ASSERT(a.empty());
		Deque<int> b(a);
		CPPUNIT_ASSERT(b.empty());
		Deque<int> c(9);
		CPPUNIT_ASSERT(!c.empty());
		Deque<int> d(c);
		CPPUNIT_ASSERT(!d.empty());
		Deque<int> e(10, 10);
		CPPUNIT_ASSERT(!e.empty());
		Deque<int> f(e);
		CPPUNIT_ASSERT(!f.empty());
	}
	
	void test_deque_empty2 () {
		using namespace My;
		Deque<char> a;
		CPPUNIT_ASSERT(a.empty());
		Deque<char> b(a);
		CPPUNIT_ASSERT(b.empty());
		Deque<char> c(9);
		CPPUNIT_ASSERT(!c.empty());
		Deque<char> d(c);
		CPPUNIT_ASSERT(!d.empty());
		Deque<char> e(10, 'a');
		CPPUNIT_ASSERT(!e.empty());
		Deque<char> f(e);
		CPPUNIT_ASSERT(!f.empty());
	}
	
	// ----
	// swap
	// ----
	
	void test_deque_swap1 () {
		using namespace My;
		Deque<int> a(3, 123);
		Deque<int> b(5, 456);
		a.swap(b);
		CPPUNIT_ASSERT(*(a.begin()) == 456);
		CPPUNIT_ASSERT(*(b.begin()) == 123);
	}
	
	// ------
	// equals
	// ------
	
	void test_deque_equal1 () {
		using namespace My;
		const Deque<int> a(3, 123);
		const Deque<int> b(3, 123);
		const Deque<int> c(3, 456);
		
		CPPUNIT_ASSERT(a == b);
		CPPUNIT_ASSERT(!(a == c));
		CPPUNIT_ASSERT(!(b == c));
	}

	// ------
	// resize
	// ------

	void test_deque_resize1 () {
		using namespace My;
		Deque<int> a(10,222);
		a.resize(5);
		CPPUNIT_ASSERT(a.size() == 5);
		Deque<int> b(10,222);
		b.resize(20);
		CPPUNIT_ASSERT(b.size() == 20);
	}

	void test_deque_resize2 () {
		using namespace My;
		Deque<char> a(10,'a');
		a.resize(5);
		CPPUNIT_ASSERT(a.size() == 5);
		Deque<char> b(10,'a');
		b.resize(20);
		CPPUNIT_ASSERT(b.size() == 20);
	}

	// ------
	// insert
	// ------
	void test_deque_insert1 () {
		using namespace My;
		Deque<int> a(3,123);
		a.insert(a.begin()+1, 456);
		a.insert(a.begin(), 789);
		a.insert(a.end() - 1, 555);
		CPPUNIT_ASSERT(a.size() == 6);
	}

	void test_deque_insert2 () {
		using namespace My;
		Deque<int> a(10,1);
		Deque<int>::iterator it = a.begin();
		it += 1;
		a.insert(it, 34);
	        CPPUNIT_ASSERT(a.size() == 11);
	}

	// -----
	// erase
	// -----

	void test_deque_erase1 () {
		using namespace My;
		Deque<int> a(3,123);
		a.erase(a.begin()+1);
		CPPUNIT_ASSERT(a.size() == 2);
		Deque<int> b(4,456);
		b.erase(b.begin());
		CPPUNIT_ASSERT(b.size() == 3);
	}

	void test_deque_erase2 () {
		using namespace My;
		Deque<char> a(3,'a');
		a.erase(a.begin()+1);
		CPPUNIT_ASSERT(a.size() == 2);
		Deque<char> b(4,'x');
		b.erase(b.begin());
		CPPUNIT_ASSERT(b.size() == 3);
	}

	// --------
	// pop_back
	// --------

	void test_deque_pop_back1 () {
		using namespace My;
		Deque<int> a(3,123);
		a.pop_back();
		CPPUNIT_ASSERT(a.size() == 2);
	}
	void test_deque_pop_back2 () {
		using namespace My;
		Deque<char> a(3,'a');
		a.pop_back();
		CPPUNIT_ASSERT(a.size() == 2);
	}

	// ---------
	// pop_front
	// ---------

	void test_deque_pop_front1 () {
		using namespace My;
		Deque<int> a(3,123);
		a.pop_front();
		CPPUNIT_ASSERT(a.size() == 2);
	}

	void test_deque_pop_front2 () {
		using namespace My;
		Deque<char> a(3,'a');
		a.pop_front();
		CPPUNIT_ASSERT(a.size() == 2);
	}

	// ----------
	// push_front
	// ----------
	
	void test_deque_push_front1 () {
		using namespace My;
		Deque<int> a(3,123);
		a.push_front(456);
		CPPUNIT_ASSERT(a.size() == 4);
		CPPUNIT_ASSERT(a.at(0) == 456);
	}
	
	void test_deque_push_front2 () {
		using namespace My;
		Deque<char> a(3,'a');
		a.push_front('b');
		CPPUNIT_ASSERT(a.size() == 4);
		CPPUNIT_ASSERT(a.at(0) == 'b');
	}
	
	// ----------
	// push_back
	// ----------
	
	void test_deque_push_back1 () {
		using namespace My;
		Deque<int> a(3,123);
		a.push_back(456);
		CPPUNIT_ASSERT(a.size() == 4);
		CPPUNIT_ASSERT(a.at(3) == 456);
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


    CPPUNIT_TEST(test_deque_default_constructor1);
	CPPUNIT_TEST(test_deque_default_constructor2);
	CPPUNIT_TEST(test_deque_constructor1);
	CPPUNIT_TEST(test_deque_constructor2);
	CPPUNIT_TEST(test_deque_copy_constructor1);
	CPPUNIT_TEST(test_deque_copy_constructor2);
	CPPUNIT_TEST(test_deque_assignment1);
	CPPUNIT_TEST(test_deque_assignment2);
	CPPUNIT_TEST(test_deque_subscript1);
	CPPUNIT_TEST(test_deque_subscript2);
	CPPUNIT_TEST(test_deque_back1);
	CPPUNIT_TEST(test_deque_back2);
	CPPUNIT_TEST(test_deque_empty1);
        CPPUNIT_TEST(test_deque_empty2);
	CPPUNIT_TEST(test_deque_size1);
	CPPUNIT_TEST(test_deque_size2);
	CPPUNIT_TEST(test_deque_iterator1);
	CPPUNIT_TEST(test_deque_iterator2);
	CPPUNIT_TEST(test_deque_swap1);
	CPPUNIT_TEST(test_deque_equal1);
	CPPUNIT_TEST(test_deque_resize1);
	CPPUNIT_TEST(test_deque_resize2);
	CPPUNIT_TEST(test_deque_insert1);
	CPPUNIT_TEST(test_deque_insert2);
	CPPUNIT_TEST(test_deque_erase1);
	CPPUNIT_TEST(test_deque_erase2);
       	CPPUNIT_TEST(test_deque_pop_back1);
	CPPUNIT_TEST(test_deque_pop_back2);
	CPPUNIT_TEST(test_deque_pop_front1);
	CPPUNIT_TEST(test_deque_pop_front2);
	CPPUNIT_TEST(test_deque_push_front1);
	CPPUNIT_TEST(test_deque_push_front2);
	CPPUNIT_TEST(test_deque_push_back1);


    CPPUNIT_TEST_SUITE_END();};

#endif // TestDeque_h
 
