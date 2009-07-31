// ----------------------
// projects/deque/Deque.h
// Copyright (C) 2009
// Glenn P. Downing
// ----------------------

#ifndef Deque_h
#define Deque_h

// --------
// includes
// --------

#include <algorithm> // equal, lexicographical_compare
#include <cassert>   // assert
#include <iterator>  // iterator, bidirectional_iterator_tag
#include <memory>    // allocator
#include <stdexcept> // out_of_range
#include <utility>   // !=, <=, >, >=

// -----
// using
// -----

using namespace std::rel_ops;

// ----------
// namespaces
// ----------

namespace My {

// -------
// destroy
// -------

template <typename A, typename BI>
BI destroy (A& a, BI b, BI e) {
    while (b != e) {
        --e;
        a.destroy(&*e);}
    return b;}

// ------------------
// uninitialized_copy
// ------------------

template <typename A, typename II, typename BI>
BI uninitialized_copy (A& a, II b, II e, BI x) {
    BI p = x;
    try {
        while (b != e) {
            a.construct(&*x, *b);
            ++b;
            ++x;}}
    catch (...) {
        destroy(a, p, x);
        throw;}
    return x;}

// ------------------
// uninitialized_fill
// ------------------

template <typename A, typename BI, typename U>
BI uninitialized_fill (A& a, BI b, BI e, const U& v) {
    BI p = b;
    try {
        while (b != e) {
            a.construct(&*b, v);
            ++b;}}
    catch (...) {
        destroy(a, p, b);
        throw;}
    return e;}

// -----
// Deque
// -----

template < typename T, typename A = std::allocator<T> >
class Deque {
    public:
        // --------
        // typedefs
        // --------

        typedef A                                        allocator_type;
        typedef typename allocator_type::value_type      value_type;

        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::difference_type difference_type;

        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;

        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;

        // -----------
        // operator ==
        // -----------

        /**
         * <your documentation>
         */
        friend bool operator == (const Deque& lhs, const Deque& rhs) {
            // <your code>
            // you must use std::equal()
            return std::equal(lhs.begin(), lhs.end(), rhs.begin());}

        // ----------
        // operator <
        // ----------

        /**
         * <your documentation>
         */
        friend bool operator < (const Deque& lhs, const Deque& rhs) {
            // <your code>
            // you must use std::lexicographical_compare()
            return std::lexicographical_compare
	           (lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

    private:
        // ----
        // data
        // ----

        allocator_type a;
	
	pointer b_a; // beginning of the real heap array
	pointer b; // beginning value of the deque
	pointer e; // one past the end of the ending element of deque
	pointer e_a; // one past the end of the real array (ca)
	
	size_type d_size;
    private:
        // -----
        // valid
        // -----

        bool valid () const {
            return (!b && !e && !b_a && !e_a) ||
		(b!=e && b_a < e_a && b < e_a && e < e_a); }
    public:
        // --------
        // iterator
        // --------

        class iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag iterator_category;
                typedef typename Deque::value_type      value_type;
                typedef typename Deque::difference_type difference_type;
                typedef typename Deque::pointer         pointer;
                typedef typename Deque::reference       reference;

                // -----------
                // operator ==
                // -----------

                /**
                 * <your documentation>
                 */
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    // <your code>
                    return lhs.p == rhs.p;}

            private:
                // ----
                // data
                // ----
			friend class Deque;
				Deque<value_type>* deque_ptr;
				pointer p;
            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    return ( p >= (deque_ptr-> b_a)  &&  p <= (deque_ptr->e_a) ) ;}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * <your documentation>
                 */
		iterator (Deque<value_type>* d_arg, pointer d_ptr){
			deque_ptr = d_arg;
			p = d_ptr;
			assert(valid());
			}

                // Default copy, destructor, and copy assignment.
                // iterator (const iterator&);
                // ~iterator ();
                // iterator& operator = (const iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * <your documentation>
                 */
                reference operator * () const {
                    return *p;}

                // -----------
                // operator ->
                // -----------

                /**
                 * <your documentation>
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator ++ () {
                    if(p!=e){
			if((p+1)== deque_ptr->e_a ){
			 //wrap around 
			 p = deque_ptr->b_a;
					}
			 ++p;
			}
			assert(valid());
                    return *this;}

                /**
                 * <your documentation>
                 */
                iterator operator ++ (int) {
                    iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator -- () {
                    if(p == deque_ptr->b_a ){
			//wrap around 
			 p = (deque_ptr->e_a) - 1 ;
			}
			 --p;
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation>
                 */
                iterator operator -- (int) {
                    iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator += (difference_type d) {
                    difference_type a = d % (deque_ptr->d_size);
                    while(a){
		    ++(*this);
		    --a;
		      }
		    assert(valid());
                    return *this;}

                // ----------
                // operator +
                // ----------

                /**
                 * <your documentation>
                 */
                iterator operator + (difference_type d) const {
                    return iterator(*this) += d;}

                // -----------
                // operator -=
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator -= (difference_type d) {
                    difference_type a = d % (deque_ptr->d_size);
                    while(a){
		    --(*this);
		    --a;
		      }
                    assert(valid());
                    return *this;}

                // ----------
                // operator -
                // ----------

                /**
                 * <your documentation>
                 */
                iterator operator - (difference_type d) const {
                    return iterator(*this) -= d;}
		    };

    public:
        // --------------
        // const_iterator
        // --------------

        class const_iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag iterator_category;
                typedef typename Deque::value_type      value_type;
                typedef typename Deque::difference_type difference_type;
                typedef typename Deque::const_pointer   pointer;
                typedef typename Deque::const_reference reference;

                // -----------
                // operator ==
                // -----------

                /**
                 * <your documentation>
                 */
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    // <your code>
                    return false;}

            private:
                // ----
                // data
                // ----
		friend class Deque;
		const Deque<value_type>* deque_ptr;
		pointer p;
		
            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    return (deque_ptr -> b_a <= p && p >= deque_ptr->e_a);}


            public:
                // -----------
                // constructor
                // -----------

                /**
                 * <your documentation>
                 */
		const_iterator (Deque<value_type>* d_arg, pointer d_ptr){
			deque_ptr = d_arg;
			p = d_ptr;
			assert(valid());}

                // Default copy, destructor, and copy assignment.
                // const_iterator (const const_iterator&);
                // ~const_iterator ();
                // const_iterator& operator = (const const_iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * <your documentation>
                 */
                reference operator * () const {
                    return *p;}

                // -----------
                // operator ->
                // -----------

                /**
                 * <your documentation>
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator ++ () {
                    if(p!=e){
			if((p+1)== deque_ptr->e_a ){
			 //wrap around 
			 p = deque_ptr->b_a;
					}
			 ++p;
			}
			assert(valid());
                    return *this;}

                /**
                 * <your documentation>
                 */
                const_iterator operator ++ (int) {
                    const_iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator -- () {
                    if(p == deque_ptr->b_a ){
			//wrap around 
			 p = (deque_ptr->e_a) - 1 ;
			}
			 --p;
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation>
                 */
                const_iterator operator -- (int) {
                    const_iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator += (difference_type d) {
                    difference_type a = d % (deque_ptr->d_size);
                    while(a){
		    ++(*this);
		    --a;
		      }
		    assert(valid());
                    return *this;}

                // ----------
                // operator +
                // ----------

                /**
                 * <your documentation>
                 */
                const_iterator operator + (difference_type d) const {
                    return const_iterator(*this) += d;}

                // -----------
                // operator -=
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator -= (difference_type d) {
                    difference_type a = d % (deque_ptr->d_size);
                    while(a){
		    --(*this);
		    --a;
		      }
                    assert(valid());
                    return *this;}

                // ----------
                // operator -
                // ----------

                /**
                 * <your documentation>
                 */
                const_iterator operator - (difference_type d) const {
                    return const_iterator(*this) -= d;}};

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        explicit Deque (const allocator_type& a = allocator_type()) : a(a) {
            b = e = b_a = e_a = 0;
	    d_size = 0;
	    assert(valid());}

        /**
         * <your documentation>
         */
        explicit Deque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()) : a(a) {
            d_size = s;
	    b_a = this->a.allocate( s+1 );
	    e_a = b_a + s + 1;
	    std::cout << (e_a - b_a) << std::endl;
	    std::cout << "exited";
	    uninitialized_fill(this->a, b_a, e_a, v);
	    std::cout << "exited";
	    b = b_a +  ( (e_a - b_a)  / 2);
	    e = b-1;
	    this->a.destroy(&*e);   
	    //Destroy the last element that e points to (empty space) coz we need 
	//the spot for the algorithm's to run on the iterator class
        assert(valid());}

        /**
         * <your documentation>
         */
        Deque (const Deque& that) {
            // <your code>
            assert(valid());}

        // ----------
        // destructor
        // ----------

        /**
         * <your documentation>
	 * FIXME: don't forget to implement iterator to do the right thing
         */
        ~Deque () {
            destroy(this->a, this->begin(), this->end() );
	    std::cout << "xxxited";
	    a.deallocate(b_a, (e_a - b_a) );
            assert(valid());}

        // ----------
        // operator =
        // ----------

        /**
         * <your documentation>
         */
        Deque& operator = (const Deque& rhs) {
            // <your code>
            assert(valid());
            return *this;}

        // -----------
        // operator []
        // -----------

        /**
         * <your documentation>
         */
        reference operator [] (size_type index) {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;}

        /**
         * <your documentation>
         */
        const_reference operator [] (size_type index) const {
            return const_cast<Deque*>(this)->operator[](index);}

        // --
        // at
        // --

        /**
         * <your documentation>
         */
        reference at (size_type index) {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;}

        /**
         * <your documentation>
         */
        const_reference at (size_type index) const {
            return const_cast<Deque*>(this)->at(index);}

        // ----
        // back
        // ----

        /**
         * <your documentation>
         */
        reference back () {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;}

        /**
         * <your documentation>
         */
        const_reference back () const {
            return const_cast<Deque*>(this)->back();}

        // -----
        // begin
        // -----

        /**
         * <your documentation>
         */
        iterator begin () {
            // <your code>
            return iterator(this, b);}

        /**
         * <your documentation>
         */
        const_iterator begin () const {
            // <your code>
            return const_iterator(this, b);}

        // -----
        // clear
        // -----

        /**
         * <your documentation>
         */
        void clear () {
            // <your code>
            assert(valid());}

        // -----
        // empty
        // -----

        /**
         * <your documentation>
         */
        bool empty () const {
            return !size();}

        // ---
        // end
        // ---

        /**
         * <your documentation>
         */
        iterator end () {
            // <your code>
            return iterator(this,e);}

        /**
         * <your documentation>
         */
        const_iterator end () const {
            // <your code>
            return const_iterator(this, e);}

        // -----
        // erase
        // -----

        /**
         * <your documentation>
         */
        iterator erase (iterator) {
            // <your code>
            assert(valid());
            return iterator();}

        // -----
        // front
        // -----

        /**
         * <your documentation>
         */
        reference front () {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;}

        /**
         * <your documentation>
         */
        const_reference front () const {
            return const_cast<Deque*>(this)->front();}

        // ------
        // insert
        // ------

        /**
         * <your documentation>
         */
        iterator insert (iterator, const_reference) {
            // <your code>
            assert(valid());
            return iterator();}

        // ---
        // pop
        // ---

        /**
         * <your documentation>
         */
        void pop_back () {
            // <your code>
            assert(valid());}

        /**
         * <your documentation>
         */
        void pop_front () {
            // <your code>
            assert(valid());}

        // ----
        // push
        // ----

        /**
         * <your documentation>
         */
        void push_back (const_reference) {
            // <your code>
            assert(valid());}

        /**
         * <your documentation>
         */
        void push_front (const_reference) {
            // <your code>
            assert(valid());}

        // ------
        // resize
        // ------

        /**
         * <your documentation>
         */
        void resize (size_type s, const_reference v = value_type()) {
            // <your code>
            assert(valid());}

        // ----
        // size
        // ----

        /**
         * <your documentation>
         */
        size_type size () const {
            // <your code>
            return d_size;}

        // ----
        // swap
        // ----

        /**
         * <your documentation>
         */
        void swap (Deque&) {
            // <your code>
            assert(valid());}};

} // My

#endif // Deque_h
