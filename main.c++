// ---------------------------
// projects/c++/deque/main.c++
// Copyright (C) 2009
// Glenn P. Downing
// ---------------------------

// To run the program:
//     clear && g++ -ansi -pedantic -lcppunit -ldl -Wall -DTEST main.c++ -o main.app && main.app
//     valgrind main.app

// To configure Doxygen:
//     doxygen -g
// That creates the file Doxyfile.
// Make the following edits:
//     EXTRACT_ALL            = YES
//     EXTRACT_PRIVATE        = YES
//     EXTRACT_STATIC         = YES
//     GENERATE_LATEX         = NO

// To document the program:
//     doxygen Doxyfile

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // cout, endl

#include "cppunit/TestSuite.h"      // TestSuite
#include "cppunit/TextTestRunner.h" // TestRunner

#include "TestDeque.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ----------
    // unit tests
    // ----------

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDeque<My::Deque<int> >::suite());
	//tr.addTest(TestDeque<std::deque<int> >::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}

