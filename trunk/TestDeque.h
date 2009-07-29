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
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDeque);

    CPPUNIT_TEST(test_def_constructor1);
    CPPUNIT_TEST(test_val_constructor1);
    CPPUNIT_TEST(test_val_constructor2);

    CPPUNIT_TEST_SUITE_END();};

#endif // TestDeque_h
 
