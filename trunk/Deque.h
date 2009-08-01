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
#include <iostream> 
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
            ++b;
			}}
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
            // you must use std::equal()
            return std::equal(lhs.begin(), lhs.end(), rhs.begin());}

        // ----------
        // operator <
        // ----------

        /**
         * <your documentation>
         */
        friend bool operator < (const Deque& lhs, const Deque& rhs) {
            // you must use std::lexicographical_compare()
            return std::lexicographical_compare
	           (lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

    private:
        // ----
        // data
        // ----
	friend class iterator;
	friend class const_iterator;
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
                    return lhs.deque_ptr == rhs.deque_ptr && lhs.p == rhs.p;}
				
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    //return lhs.deque_ptr != rhs.deque_ptr && lhs.p != rhs.p;}				 
		    return !(lhs==rhs);
		    }
			
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
                    if(p != deque_ptr->e){
			if((p + 1)== deque_ptr->e_a ){
			 //wrap around 
			 p = deque_ptr->b_a;
					}
			else{
			 ++p;
			}
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
			else  --p;
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
                    return lhs.deque_ptr == rhs.deque_ptr && lhs.p == rhs.p;}

                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs==rhs);}
					
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
                    return (p >= deque_ptr -> b_a  && p <= deque_ptr->e_a);}


            public:
                // -----------
                // constructor
                // -----------

                /**
                 * <your documentation>
                 */
		const_iterator (const Deque<value_type>* d_arg, const pointer d_ptr){
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
                    if(p!= deque_ptr-> e){
			if( (p+1) == deque_ptr->e_a ){
			 //wrap around 
			 p = deque_ptr->b_a;
					}
			else  ++p;
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
			else  --p;
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
	    uninitialized_fill(this->a, b_a, e_a, v);
	    b = b_a +  ( (e_a - b_a)  / 2);
	    e = b-1;
	    //this->a.destroy(&*e); 
        assert(valid());
		}

        /**
         * <your documentation>
         */
        Deque (const Deque& that) : a(that.a) {
            d_size = that.d_size;
	    b_a = this->a.allocate( d_size + 1);
	    e_a = b_a + d_size + 1;
	    b = b_a +  ( (e_a - b_a)  / 2);
	    e = b-1;
	    uninitialized_copy(a, that.begin(), that.end(), begin());
	    assert(valid());}

        // ----------
        // destructor
        // ----------

        /**
         * <your documentation>
         */
        ~Deque () {
	    //destroy(this->a, b_a, e_a );
	    destroy(this->a, this->begin(), this->end() );
	    a.deallocate(b_a, (e_a - b_a) );
            assert(valid());}

        // ----------
        // operator =
        // ----------

        /**
         * <your documentation>
         */
        Deque& operator = (const Deque& rhs) {
            if(this == &rhs) return *this;
	    if(rhs.size() == size())
	    	std::copy(rhs.begin(), rhs.end(), this->begin());
            else if(rhs.size() < size()){
	        std::copy(rhs.begin(), rhs.end(), begin());
		//resize(rhs.size());
		d_size = rhs.size();
	    }
	    else if(rhs.size() <= capacity()){
	        std::copy(rhs.begin(), rhs.end(), begin());
		end() = uninitialized_copy(a, rhs.begin() + size(), 
					rhs.end(), end());
	    }
	    else{
	       clear();
	       Deque x(rhs, rhs.capacity());
	       swap(x);
	    }
	    assert(valid());
            return *this;}

        // -----------
        // operator []
        // -----------

        /**
         * <your documentation>
         */
        reference operator [] (size_type index) {
	    pointer b_copy = b;
	    size_type b2e_a = e_a - b;
	    if(index < b2e_a){
	    	b_copy += index;
	    	reference result = *b_copy;
		return result;
	    	}
	    else{ //index >= b2e_a
	    index -= b2e_a;
	    b_copy = b_a;
	    b_copy += index;
	    reference result = *b_copy;
	    return result;
	     }
	    }

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
	    if(index < 0 || index >= d_size){
	    	throw std::out_of_range("My::Deque.at(i) invalid index");
	    }
	    pointer b_copy = b;
	    size_type b2e_a = e_a - b;
	    if(index < b2e_a){
	    	b_copy += index;
	    	reference result = *b_copy;
		return result;
	    	}
	    else{ //index >= b2e_a
	    index -= b2e_a;
	    b_copy = b_a;
	    b_copy += index;
	    reference result = *b_copy;
	    return result;
	     }
	    }
	    

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
	    pointer back = e;
            if( b_a == back){
	        back = e_a - 1;
	        reference result = *back;
		return result;
	    }
	    else{
	    --back;
	    reference result = *back;
	    return result;
	    }
	  }
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
            resize(0);
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
            return *b;}

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
        // capacity
        // ------
	private:
	size_type capacity() const {
	    return (e_a - b_a);
	}

	Deque (const Deque& that, size_type c) : a(that.a) {
	    b_a = this->a.allocate( c + 1);
	    e_a = b_a + c + 1;
	    b = b_a +  ( (e_a - b_a)  / 2);
	    //Deque::const_iterator cit = begin() + that.size();
	    //e = cit.p;
	    size_type diff = e_a - b;
	    if(diff > that.size()){
	    //e = uninitialized_copy(a, that.begin(), that.end(), begin());
	    }
	    else{
	    //e = uinitialized_copy(a, that.begin(), that.end(), begin());
	    }
	    d_size = that.size();    
	}
	public:
        // ------
        // resize
        // ------
         
        /* const_iterator it(this, b);
	std::cout << "STAR IT = " << *it << std::endl;
	pointer qwe = const_cast<pointer&>(it.p);
	std::cout << qwe;
	assert(it.deque_ptr == this);*/
        /**
         * <your documentation>
         */
        void resize (size_type s, const_reference v = value_type()) {
            if (s == d_size) return;
	    if (s < size() ){
	        d_size = s;
	        //e = destroy(a, this->begin + s, this->end());
		}
	    else if(s < capacity() ){
	    //we can fill the spot between b and e
	      d_size = s;
	      //if(b > e && ( (b-e) > (s-size()) )){
	      //e = uninitialized_fill(a, e, e + s, v);
	      }
	      //else if(e > b && ( (e-b) > (s-size()) )){
	      //e = uninitialized_fill(a, this->end(), this->end() + s, v);
	      }
	    }
	    else{
	    //create a new deque
	    //populate with the new values
	    //destroy the old deque
	    d_size = s;
	    s = std::max(2*size(), s);
            Deque temp(*this, s);
	    this->swap(temp);
	    //e = uninitialized_fill(a, e, begin() + s, v);
	    }
	    
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
	 * FIXME: need to put the case where the allocator is different
	 * that will need to have the assignment operator defined
         */
        void swap (Deque& that) {
            if(a == that.a){
	    std::swap(b_a, that.b_a);
	    std::swap(e_a, that.e_a);
	    std::swap(b, that.b);
	    std::swap(e, that.e);
	    size_type temp = d_size;
	    d_size = that.d_size;
	    that.d_size = temp;
	    }
	    else{
	    Deque temp(*this);
	    *this = that;
	    that = temp;
	    }
            assert(valid());}};

} // My

#endif // Deque_h
