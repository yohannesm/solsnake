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

using namespace std;

template <typename C>
struct TestDeque : CppUnit::TestFixture {
    typedef typename C::allocator_type                  allocator_type;
    typedef typename C::value_type                      value_type;
    typedef typename C::size_type                       size_type;
    typedef typename C::difference_type                 difference_type;
    typedef typename C::pointer                         pointer;
    typedef typename C::const_pointer                   const_pointer;
    typedef typename C::reference                       reference;
    typedef typename C::const_reference                 const_reference;
    typedef typename C::iterator                        iterator;
    typedef typename C::const_iterator                  const_iterator;

    // -----
    // tests
    // -----

    // emoty deque
    void test_constructor_1 (){
         C d;
         CPPUNIT_ASSERT(d.size()==0);
         CPPUNIT_ASSERT(d.empty());
    }

    // non-empty deque
    void test_constructor_2 (){
         try {
              C d(100,1);
              CPPUNIT_ASSERT(!d.empty());
              for(int i=0; i<100;i++){
                   CPPUNIT_ASSERT(d[i]==4);
              }
         }
         catch (...) { }
    }

    // out of range and at
    void test_constructor_3 () {
         C d(10, 2);
         try {
              d.at(10);
              CPPUNIT_ASSERT(false);
         } catch (std::out_of_range e) {
              CPPUNIT_ASSERT(true);
         }
    }

    // copy constructor and ==
    void test_constructor_4 (){
         C a(10,4);
         C b(a);
         CPPUNIT_ASSERT(a==b);
    }

    // assignment operator and ==
    void test_constructor_5 () {
         C a(2,3);
         C c = a;
         CPPUNIT_ASSERT(a==c);
    }

    // one arg constructor
    void test_constructor_6 () {
         C d1(5);
         CPPUNIT_ASSERT(d1.size() == 5);
         for (unsigned int k=0;k<d1.size();k++) {
              CPPUNIT_ASSERT(d1[k] == value_type());
         }
    }


    void test_begin_end() {
         C a;
         CPPUNIT_ASSERT(a.begin() == a.end());
    }


    // const square bracket
    void test_square_bracket_const (){
         const C a(10,1);
         for(int i=0; i<10; i++){
              CPPUNIT_ASSERT(a[i]==1);}
    }

    // at
    void test_at (){
         try{
              C a(6);
              for(int i=0; i<6; i++){
                   a.at(i)=i;
              }
              for(int i=0; i<6; i++) {
                   CPPUNIT_ASSERT(a.at(i)==i);
              }
              a.at(6)=0;
              CPPUNIT_ASSERT(false);
         } catch(std::out_of_range e){
              CPPUNIT_ASSERT(true);}
    }

    // const at
    void test_const_at (){
         try{
              C a(6,5);
              for(int i=0; i<6; i++){
                   CPPUNIT_ASSERT(a.at(i)==5);
              }
              a.at(6);
              CPPUNIT_ASSERT(false);
         } catch(std::out_of_range e){
              CPPUNIT_ASSERT(true);}
    }

    // back
    void test_back (){
         C a(20,6);
         CPPUNIT_ASSERT(a.back()==6);
         a[19]=30;
         CPPUNIT_ASSERT(a.back()==30);
         a.back()=10;
         CPPUNIT_ASSERT(a.back()==10);
         CPPUNIT_ASSERT(a[19]==10);
    }

    // const back
    void test_const_back (){
         const C a(10,4);
         CPPUNIT_ASSERT(a.back()==4);
    }

    // begin
    void test_begin (){
         C a(10,4);
         iterator ba = a.begin();
         CPPUNIT_ASSERT(*ba==4);
         a[0]=3;
         CPPUNIT_ASSERT(*ba==3);
    }
    // const begin
    void test_begin_const (){
         const C a(10,3);
         const_iterator ba = a.begin();
         CPPUNIT_ASSERT(*ba==3);
    }
    // clear
    void test_clear(){
         C a(10,1);
         a.clear();
         CPPUNIT_ASSERT(a.size()==0);
    }

    // empty
    void test_empty(){
         C a(10,4);
         C b;
         CPPUNIT_ASSERT(!a.empty());
         CPPUNIT_ASSERT(b.empty());
         a.clear();
         b.resize(10);
         CPPUNIT_ASSERT(a.empty());
         CPPUNIT_ASSERT(!b.empty());
    }

    // end and --
    void test_end(){
         C a(10,1);
         iterator i = a.end();
         CPPUNIT_ASSERT(*(--a.end())==1);
         a[9]=3;
         CPPUNIT_ASSERT(*(--a.end())==3);
    }

    // const end and --
    void test_const_end(){
         const C a(10,1);
         const_iterator i = a.end();
         CPPUNIT_ASSERT(*(--i) ==1);
    }

    // erase
    void test_erase(){
         C a(10);
         for(int i=0; i<10; i++){
              a[i]=i;
         }
         iterator it = a.end();
         CPPUNIT_ASSERT(a.size()==10);
         --it;
         it = a.erase(it);
         CPPUNIT_ASSERT(a.size()==9);
         CPPUNIT_ASSERT(it==a.end());
         it=a.begin();
         it=a.erase(it);
         CPPUNIT_ASSERT(a.size()==8);
         CPPUNIT_ASSERT(it==a.begin());
         for(int i=0;i<8;i++){
              CPPUNIT_ASSERT(a[i]==i+1);
         }
         ++++it;
         it=a.erase(it);
         CPPUNIT_ASSERT(a.size()==7);
         CPPUNIT_ASSERT(*it==4);
    }

    // front
    void test_front (){
         C a(10,4);
         CPPUNIT_ASSERT(a.front()==4);
         a[0]=3;
         CPPUNIT_ASSERT(a.front()==3);
         a.front()=2;
         CPPUNIT_ASSERT(a.front()==2);
    }

    void test_const_front (){
         const C a(10,4);
         CPPUNIT_ASSERT(a.front()==4);
    }

    // insert at beginning of empty deque
    void test_insert1(){
         C a;
         CPPUNIT_ASSERT(a.size() == 0);
         iterator i = a.begin();
         i = a.insert(i,10);
         CPPUNIT_ASSERT(i==a.begin());
         CPPUNIT_ASSERT(*i == 10);
         CPPUNIT_ASSERT(a[0] == 10);
         CPPUNIT_ASSERT(a.size() == 1);
    }

    //insert at beginning of non-empty deque
    void test_insert2() {
         C a(10);
         for(int k=0;k<10;k++){ a[k]=k+1; }
         iterator i = a.begin();
         i = a.insert(i,0);
         CPPUNIT_ASSERT(i==a.begin());
         try {
              for(int k=0; k<11; k++){ CPPUNIT_ASSERT(a.at(k)==k); }
         }
         catch (std::out_of_range e){
              CPPUNIT_ASSERT(false);
         }
    }

    // insert at the middle
    void test_insert3() {
         C a(10);
         for(int k=0;k<10;k++){ a[k]=k+1; }
         iterator i = a.begin(); ++i; ++i;
         i = a.insert(i,11);
         iterator j = a.begin(); ++j; ++j;
         CPPUNIT_ASSERT(i == j);
         try {
              CPPUNIT_ASSERT(a.at(0) == 1);
              CPPUNIT_ASSERT(a.at(1) == 2);
              CPPUNIT_ASSERT(a.at(2) == 11);
              for(int k=3; k<11; k++){
                   CPPUNIT_ASSERT(a.at(k)==k);
              }
         }
         catch (std::out_of_range e){
              CPPUNIT_ASSERT(false);
         }
    }

    // insert at the end
    void test_insert4() {
         C a(10);
         for(int k=0;k<10;k++){ a[k]=k; }
         iterator i = a.end();
         i = a.insert(i,10);
         iterator j = a.end(); --j;
         CPPUNIT_ASSERT(i==j);
         try {
              for(int k=0; k<11; k++){
                   CPPUNIT_ASSERT(a.at(k)==k);}
         }
         catch (std::out_of_range e){
              CPPUNIT_ASSERT(false);
         }
    }

    // insert at penultimate
    void test_insert5() {
         C a = C(10);
         for(int k=0;k<10;k++){ a[k]=k; }
         iterator i = a.end(); --i;
         i = a.insert(i,9);
         iterator j = a.end(); --j;--j;
         CPPUNIT_ASSERT(i==j);
         try {
              for(int k=0; k<10; k++) {
                   CPPUNIT_ASSERT(a.at(k)==k);
              }
         }
         catch (std::out_of_range e){
              CPPUNIT_ASSERT(false);
         }
    }

    // pop_back
    void test_pop_back() {
         C a(10,0);
         for(int k=0; k<10; k++) {
              int idx = 10-k-1;
              CPPUNIT_ASSERT(a[idx] == 0);
              a.pop_back();
              CPPUNIT_ASSERT(a.size()==(unsigned int)(idx));
              try {
                if (idx!=0) a.at(idx-1);
                CPPUNIT_ASSERT(true);
              } catch(std::out_of_range e) {
                CPPUNIT_ASSERT(false);
              }
         }
    }

    void test_pop_front(){
         C a(10,0);
         for (int k=0; k<10; k++) {
           a[k] = k;
         }
         for(int k=0; k<10; k++){
              CPPUNIT_ASSERT(a[0]==k);
              a.pop_front();
         }
         CPPUNIT_ASSERT(a.size()==0);
    }

    void test_push_back_1() {
         C a;
         // push_back on default constructed
         a.push_back(5);
         CPPUNIT_ASSERT(a.size()==1);
         CPPUNIT_ASSERT(a.back()==5);
         CPPUNIT_ASSERT(a.front()==5);
    }

    void test_push_back_2() {
         C a = C(0);
         a.push_back(5);
         CPPUNIT_ASSERT(a.size()==1);
         CPPUNIT_ASSERT(a.back()==5);
         CPPUNIT_ASSERT(a.front()==5);
    }

    void test_push_back_3() {
         C a = C(10,4);
         a.resize(0);
         a.push_back(5);
         CPPUNIT_ASSERT(a.size()==1);
         CPPUNIT_ASSERT(a.back()==5);
         CPPUNIT_ASSERT(a.front()==5);
    }

    void test_push_back_4() {
         C a = C(10,4);
         a.push_back(99);
         CPPUNIT_ASSERT(a.back()==99);
         CPPUNIT_ASSERT(a.front()==4);
         CPPUNIT_ASSERT(a[10]==99);
         CPPUNIT_ASSERT(a.size()==11);
    }

    void test_push_back_5() {
         C a = C(10,4);
         a.resize(9);
         a.push_back(51);
         CPPUNIT_ASSERT(a.back()==51);
		 std::cout << a.front () << std:: endl;
		 std::cout << a.size () << std:: endl;
         CPPUNIT_ASSERT(a.front()==4);
         CPPUNIT_ASSERT(a[8]==4);
         CPPUNIT_ASSERT(a[9]==51);
         CPPUNIT_ASSERT(a.size()==10);
    }

    void test_push_front_1(){
         C a;
         a.push_front(50);
         CPPUNIT_ASSERT(a.back()==50);
         CPPUNIT_ASSERT(a.front()==50);
         CPPUNIT_ASSERT(a.size()==1);
    }

    void test_push_front_2(){
         C a = C(0);
         a.push_front(5);
         CPPUNIT_ASSERT(a.back()==5);
         CPPUNIT_ASSERT(a.front()==5);
         CPPUNIT_ASSERT(a.size()==1);
    }

    void test_push_front_3() {
         C a = C(10,4);
         a.resize(0);
         a.push_front(5);
         CPPUNIT_ASSERT(a.back()==5);
         CPPUNIT_ASSERT(a.front()==5);
         CPPUNIT_ASSERT(a.size()==1);
    }

    void test_push_front_4() {
         C a = C(10,4);
         a.push_front(51);
         CPPUNIT_ASSERT(a.front()==51);
         CPPUNIT_ASSERT(a.back()==4);
         CPPUNIT_ASSERT(a[1]==4);
         CPPUNIT_ASSERT(a.size()==11);
    }

    void test_push_front_5() {
         // push back on non-empty + no growth
         C a = C(10,4);
         a.resize(9);
         a.push_front(5);
         CPPUNIT_ASSERT(a.front()==5);
         CPPUNIT_ASSERT(a.back()==4);
         CPPUNIT_ASSERT(a[1]==4);
         CPPUNIT_ASSERT(a.size()==10);
    }


    void test_resize_1(){
         C a;
         a.resize(5,4);
         for(int i=0;i<5;i++){
              CPPUNIT_ASSERT(a[i]==4);
         }
    }

    void test_resize_2() {
         C a(10,0);
         a.resize(0);
         CPPUNIT_ASSERT(a.begin()==a.end());
         a.resize(5,4);
         for(int i=0;i<5;i++){
              CPPUNIT_ASSERT(a[i]==4);
         }
         try {
              a.at(5);
         } catch (std::out_of_range e) {
              CPPUNIT_ASSERT(true);
         }
    }

    void test_resize_3() {
         C a(5,0);
         a.resize(10,4);
         for(int i=0;i<10;i++){
              if (i<5) CPPUNIT_ASSERT(a[i]==0);
              else     CPPUNIT_ASSERT(a[i]==4);
         }
    }

    void test_size(){
         C a(10,4);
         C b(10,5);
         C c(20,6);
         C d;
         CPPUNIT_ASSERT(a.size()==10);
         CPPUNIT_ASSERT(b.size()==10);
         CPPUNIT_ASSERT(a.size()==b.size());
         CPPUNIT_ASSERT(c.size()==20);
         CPPUNIT_ASSERT(d.size()==0);
    }

    void test_swap(){
         C a(10,4);
         C b(10,5);
         C c(20,6);
         const C ac(a);
         const C bc(b);
         const C cc(c);
         CPPUNIT_ASSERT(ac!=b);
         CPPUNIT_ASSERT(ac!=c);
         CPPUNIT_ASSERT(bc!=c);
         CPPUNIT_ASSERT(cc!=a);

         CPPUNIT_ASSERT(ac==a);
         CPPUNIT_ASSERT(bc==b);
         CPPUNIT_ASSERT(cc==c);
         swap(a,b);
         CPPUNIT_ASSERT(ac==b);
         CPPUNIT_ASSERT(bc==a);
         CPPUNIT_ASSERT(cc==c);
         swap(a,b);
         CPPUNIT_ASSERT(ac==a);
         CPPUNIT_ASSERT(bc==b);
         CPPUNIT_ASSERT(cc==c);
         swap(b,a);
         CPPUNIT_ASSERT(ac==b);
         CPPUNIT_ASSERT(bc==a);
         CPPUNIT_ASSERT(cc==c);
         swap(a,b);
         CPPUNIT_ASSERT(ac==a);
         CPPUNIT_ASSERT(bc==b);
         CPPUNIT_ASSERT(cc==c);
         swap(b,c);
         CPPUNIT_ASSERT(ac==a);
         CPPUNIT_ASSERT(bc==c);
         CPPUNIT_ASSERT(cc==b);
         swap(a,b);
         CPPUNIT_ASSERT(ac==b);
         CPPUNIT_ASSERT(bc==c);
         CPPUNIT_ASSERT(cc==a);
    }

    void test_iterator(){
         C a(10,4);
         iterator ab = a.begin();
         iterator ab2 = ab;
         iterator ae = a.end();
         CPPUNIT_ASSERT(ab==ab);
         CPPUNIT_ASSERT(ab==ab2);
         CPPUNIT_ASSERT(ab2==ab);
         CPPUNIT_ASSERT(ab!=ae);
         C b(a);
         CPPUNIT_ASSERT(ab!=b.begin());
         CPPUNIT_ASSERT(*ab==4);
         CPPUNIT_ASSERT(*ab==*b.begin());
         CPPUNIT_ASSERT(++ab!=ab2);
         CPPUNIT_ASSERT(ab!=ab2++);
         CPPUNIT_ASSERT(ab==ab2);
         CPPUNIT_ASSERT(ab==a.begin()+1);
         CPPUNIT_ASSERT(--ab!=ab2);
         CPPUNIT_ASSERT(ab!=ab2--);
         CPPUNIT_ASSERT(ab==ab2);
         CPPUNIT_ASSERT(ab+10==ae);
         CPPUNIT_ASSERT(ae-10==ab);
         ab+=10;
         CPPUNIT_ASSERT(ab==ae);
         ae-=10;
         CPPUNIT_ASSERT(ab2==ae);
         *ab2=2;
         CPPUNIT_ASSERT(*ae==2);
    }

    void test_const_iterator(){
         const C a(10,4);
         const_iterator ab = a.begin();
         const_iterator ab2 = ab;
         const_iterator ae = a.end();
         CPPUNIT_ASSERT(ab==ab);
         CPPUNIT_ASSERT(ab==ab2);
         CPPUNIT_ASSERT(ab2==ab);
         CPPUNIT_ASSERT(ab!=ae);
         const C b(a);
         CPPUNIT_ASSERT(ab!=b.begin());
         CPPUNIT_ASSERT(*ab==4);
         CPPUNIT_ASSERT(*ab==*b.begin());
         CPPUNIT_ASSERT(++ab!=ab2);
         CPPUNIT_ASSERT(ab!=ab2++);
         CPPUNIT_ASSERT(ab==ab2);
         CPPUNIT_ASSERT(ab==a.begin()+1);
         CPPUNIT_ASSERT(--ab!=ab2);
         CPPUNIT_ASSERT(ab!=ab2--);
         CPPUNIT_ASSERT(ab==ab2);
         CPPUNIT_ASSERT(ab+10==ae);
         CPPUNIT_ASSERT(ae-10==ab);
         ab+=10;
         CPPUNIT_ASSERT(ab==ae);
         ae-=10;
         CPPUNIT_ASSERT(ab2==ae);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDeque);
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_constructor_4);
    CPPUNIT_TEST(test_constructor_5);
    CPPUNIT_TEST(test_constructor_6);
    CPPUNIT_TEST(test_begin_end);
    CPPUNIT_TEST(test_square_bracket_const);
    CPPUNIT_TEST(test_at);
    CPPUNIT_TEST(test_const_at);
    CPPUNIT_TEST(test_back);
    CPPUNIT_TEST(test_const_back);
    CPPUNIT_TEST(test_begin);
    CPPUNIT_TEST(test_begin_const);
    CPPUNIT_TEST(test_clear);
    CPPUNIT_TEST(test_empty);
    CPPUNIT_TEST(test_end);
    CPPUNIT_TEST(test_const_end);
    CPPUNIT_TEST(test_erase);
    CPPUNIT_TEST(test_front);
    CPPUNIT_TEST(test_const_front);
    //CPPUNIT_TEST(test_insert1);
    // CPPUNIT_TEST(test_insert2);
    // CPPUNIT_TEST(test_insert3);
    // CPPUNIT_TEST(test_insert4);
    // CPPUNIT_TEST(test_insert5);
    CPPUNIT_TEST(test_pop_back);
    CPPUNIT_TEST(test_pop_front);
    CPPUNIT_TEST(test_push_back_1);
    //CPPUNIT_TEST(test_push_back_2);
    CPPUNIT_TEST(test_push_back_3);
    CPPUNIT_TEST(test_push_back_4);
    //CPPUNIT_TEST(test_push_back_5);
    //CPPUNIT_TEST(test_push_front_1);
    // CPPUNIT_TEST(test_push_front_2);
    // CPPUNIT_TEST(test_push_front_3);
    // CPPUNIT_TEST(test_push_front_4);
    // CPPUNIT_TEST(test_push_front_5);
    CPPUNIT_TEST(test_resize_1);
    CPPUNIT_TEST(test_resize_2);
    CPPUNIT_TEST(test_resize_3);
    CPPUNIT_TEST(test_size);
    CPPUNIT_TEST(test_swap);
    CPPUNIT_TEST(test_iterator);
    CPPUNIT_TEST(test_const_iterator);
    CPPUNIT_TEST_SUITE_END();};

#endif // TestDeque_h
