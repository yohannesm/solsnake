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
	 * O(1) in space
	 * O(n) in time                          
	 * @param lhs: a read-only reference to a Deque
	 * @param rhs: a read-only reference to a Deque
	 * @return bool true, if they are equal
	 * Deques are of the same type and equal size
	 * output is true if the elements inside the arrays are all the same. false, otherwise.
	 */
	friend bool operator == (const Deque& lhs, const Deque& rhs) {
		return std::equal(lhs.begin(), lhs.end(), rhs.begin());}

	// ----------
	// operator <
	// ----------

	/**
	 * O(1) in space
	 * O(n) in time                
	 * @param lhs: a read-only reference to a Deque
	 * @param rhs: a read-only reference to a Deque
	 * @return bool true, if elements inside the Deque on the lhs are all < the Deque on the rhs
	 * the Deques are of the same type
	 */
	friend bool operator < (const Deque& lhs, const Deque& rhs) {
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

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
		(b!=e &&  b_a < e_a && b < e_a && e < e_a); }

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
		 * O(1) in space
		 * O(n) in time                          
		 * @param lhs: a read-only reference to an Iterator
		 * @param rhs: a read-only reference to an Iterator
		 * @return bool true, if they are equal
		 */
		friend bool operator == (const iterator& lhs, const iterator& rhs) {
			return lhs.deque_ptr == rhs.deque_ptr && lhs.p == rhs.p;}

		/**
		 * O(1) in space
		 * O(n) in time                          
		 * @param lhs: a read-only reference to an Iterator
		 * @param rhs: a read-only reference to an Iterator
		 * @return bool true, if they are not equal
		 */			
		friend bool operator != (const iterator& lhs, const iterator& rhs) {
			//return lhs.deque_ptr != rhs.deque_ptr && lhs.p != rhs.p;}				 
			return !(lhs==rhs);}

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
		 * @param d_arg: specifies the deque
		 * @param d_ptr: pointer to the deque
		 * 
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
		 * O(1) in space
		 * O(n) in time                          
		 * @return dereferenced value
		 */			
		reference operator * () const {
			return *p;}

		// -----------
		// operator ->
		// -----------

		/**
		 * @return a pointer to deque
		 */
		pointer operator -> () const {
			return &**this;}

		// -----------
		// operator ++
		// -----------

		/**
		 * pre-increment
		 * @return incremented iterator
		 */
		iterator& operator ++ () {
			//if(p != deque_ptr->e){
			if((p + 1)== deque_ptr->e_a ){
				//wrap around 
				p = deque_ptr->b_a;
			}
			else{
				++p;
			}
			//}
			assert(valid());
			return *this;}

		/**
		 * post-increment 
		 * @return incremented iterator
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
		 * pre-decrement
		 * @return decremented iterator
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
		 * post-decrement
		 * @return decremented iterator
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
		 * @param d: differnce_type, value by which the iterator is to be incremented
		 * @return incremented iterator
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
		 * @param d: differnce_type, value by which the iterator is to be incremented
		 * @return incremented iterator
		 * calls +=
		 */
		iterator operator + (difference_type d) const {
			return iterator(*this) += d;}

		// -----------
		// operator -=
		// -----------

		/**
		 * @param d: differnce_type, value by which the iterator is to be decremented
		 * @return decremented iterator
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
		 * @param d: differnce_type, value by which the iterator is to be decremented
		 * @return decremented iterator
		 * calls -=
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
		 * O(1) in space
		 * O(n) in time                          
		 * @param lhs: a read-only reference to an Iterator
		 * @param rhs: a read-only reference to an Iterator
		 * @return bool true, if they are equal
		 */
		friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
			return lhs.deque_ptr == rhs.deque_ptr && lhs.p == rhs.p;}

		/**
		 * O(1) in space
		 * O(n) in time                          
		 * @param lhs: a read-only reference to an Iterator
		 * @param rhs: a read-only reference to an Iterator
		 * @return bool true, if they are not equal
		 */		
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
		 * @param d_arg: specifies the deque
		 * @param d_ptr: pointer to the deque
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
		 * O(1) in space
		 * O(n) in time                          
		 * @return dereferenced value
		 */			
		reference operator * () const {
			return *p;}

		// -----------
		// operator ->
		// -----------

		/**
		 * @return a pointer to deque
		 */
		pointer operator -> () const {
			return &**this;}

		// -----------
		// operator ++
		// -----------

		/**
		 * pre-increment
		 * @return incremented iterator
		 */
		const_iterator& operator ++ () {
			//if(p!= deque_ptr-> e){
			if( (p+1) == deque_ptr->e_a ){
				//wrap around 
				p = deque_ptr->b_a;
			}
			else  ++p;
			//}
			assert(valid());
			return *this;}

		/**
		 * post-increment
		 * @return incremented iterator
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
		 * pre-decrement
		 * @return decremented iterator
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
		 * post-decrement
		 * @return decremented iterator
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
		 * @param d: differnce_type, value by which the iterator is to be incremented
		 * @return incremented iterator
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
		 * @param d: differnce_type, value by which the iterator is to be incremented
		 * @return incremented iterator
		 * calls +=
		 */
		const_iterator operator + (difference_type d) const {
			return const_iterator(*this) += d;}

		// -----------
		// operator -=
		// -----------

		/**
		 * @param d: differnce_type, value by which the iterator is to be decremented
		 * @return decremented iterator
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
		 * @param d: differnce_type, value by which the iterator is to be decremented
		 * @return decremented iterator
		 * calls -=
		 */
		const_iterator operator - (difference_type d) const {
			return const_iterator(*this) -= d;}};

public:
	// ------------
	// constructors
	// ------------

	/**
	 * Default Construct
	 * @param a: Allocator instance, defaulted as std::Allocator<T>
	 */
	explicit Deque (const allocator_type& a = allocator_type()) : a(a) {
		b = e = b_a = e_a = 0;
		d_size = 0;
		assert(valid());}

	/**
	 * @param s: size of the deque
	 * @param v: value with which the deque is to be initialised
	 * @param a: Allocator instance, defaulted as std::Allocator<T>
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
	 * Copy Constructor
	 * @param that: reference to the deque to be copied
	 * @param a: Allocator instance
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
	 * Destroys the objects
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
	 * Assignment
	 * @param rhs: reference to the deque to be assigned
	 * @return this deque
	 */
	Deque& operator = (const Deque& rhs) {
		if(this == &rhs) return *this;
		if(rhs.size() == size())
			std::copy(rhs.begin(), rhs.end(), this->begin());
		else if(rhs.size() < size()){
			std::copy(rhs.begin(), rhs.end(), begin());
			resize(rhs.size());
			d_size = rhs.size();
		}
		else if(rhs.size() <= capacity()){
			iterator it = this->end();
			const_iterator rhs_it = rhs.begin();
			rhs_it += size();
			std::copy(rhs.begin(), rhs_it, begin());
			it = uninitialized_copy(a, rhs_it, 
					rhs.end(), end());
			e = it.p;
			d_size = rhs.size();
		}
		else{
			Deque x(rhs, rhs.capacity());
			this->swap(x);
		}
		assert(valid());
		return *this;}

	// -----------
	// operator []
	// -----------

	/**
	 * O(1) in space
	 * O(1) in time                 
	 * @param index: index of the deque
	 * @return reference to the element that index points to
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
	 * O(1) in space
	 * O(1) in time                 
	 * @param index: index of the deque
	 * @return read only reference to the element that index points to
	 */
	const_reference operator [] (size_type index) const {
		return const_cast<Deque*>(this)->operator[](index);}

	// --
	// at
	// --

	/**
	 * O(1) in space
	 * O(1) in time                 
	 * @param index: index of the deque
	 * @return reference to the element that index points to
	 * Throw's out of range exception if the index is out of deque's range
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
	 * O(1) in space
	 * O(1) in time                 
	 * @param index: index of the deque
	 * @return reference to the element that index points to
	 * Throw's out of range exception if the index is out of deque's range
	 */
	const_reference at (size_type index) const {
		return const_cast<Deque*>(this)->at(index);}

	// ----
	// back
	// ----

	/**
	 * @return reference to the last element
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
	 * @return read only reference to the last element
	 */
	const_reference back () const {
		return const_cast<Deque*>(this)->back();}

	// -----
	// begin
	// -----

	/**
	 * @return reference to the begining of the Deque
	 */
	iterator begin () {
		// <your code>
		return iterator(this, b);}

	/**
	 * @return read only reference to the begining of the Deque
	 */
	const_iterator begin () const {
		// <your code>
		return const_iterator(this, b);}

	// -----
	// clear
	// -----

	/**
	 * Calls destroy, resizes the deque to 0
	 */
	void clear () {
		resize(0);
		assert(valid());}

	// -----
	// empty
	// -----

	/**
	 * @return true if the Deque is not empty, false otherwise
	 */
	bool empty () const {
		return !size();}

	// ---
	// end
	// ---

	/**
	 * @return reference to the end of the Deque
	 */
	iterator end () {
		return iterator(this,e);}

	/**
	 * @return read only reference to the begining of the Deque
	 */
	const_iterator end () const {
		return const_iterator(this, e);}

	// -----
	// erase
	// -----

	/**
	 * @param iterator: points to the element to be erased
	 * @return the position from where the element was erased
	 */
	iterator erase (iterator i) {
		if(i == begin()){
			pop_front();
			return begin();
		}
		else if(i == end() - 1){
			pop_back();
			return end() -1;
		}
		else{
		//erasing at the middle
		iterator it= i;
			while(it != (end() -1) ){
			*it = * (it + 1);
			++it;
			}
	        assert(it == end() -1);
		pop_back();
		}
		assert(valid());
		return i;}

	// -----
	// front
	// -----

	/**
	 * @return reference to the element at the front 
	 */
	reference front () {
		return *b;
		}

	/**
	 * @return constant reference to the element at the front 
	 */
	const_reference front () const {
		return const_cast<Deque*>(this)->front();}

	// ------
	// insert
	// ------

	/**
	 * @param it1: location where the new element is to be inserted
	 * @param v: the value with which the element is to be initialised
	 * @return iterator to location where the insertion was made
	 */
	iterator insert (iterator it1, const_reference v) {
		if(it1==begin()){
			push_front(v);
			return begin();}
		else if(it1== (end() - 1) ){
			push_back(v);
			return (end()-1);}
		else{ //inserting at the middle
		// need to count the offset of it to it1
		iterator it = begin();
		difference_type diff = 0;
			while(it != it1){
		        ++diff; ++it;
			}	
		push_front(0);
		it = begin();
		it1 = it + diff;
		  while(it != it1){
			*it = *(it + 1);
			++it;
		      }	
		*it = v;
		}
		assert(valid());
		return it1;}

	// ---
	// pop
	// ---

	/**
	 * removes the last element
	 */
	void pop_back () {
		assert(!empty());
		resize(d_size - 1);
		assert(valid());}

	/**
	 * removes the element in front
	 */
	void pop_front () {
	        iterator it = begin();
		if( (it+1) == end()){
			clear(); return;
		}
		a.destroy(&*it);
		++it;
		b = it.p;
		d_size -= 1;
		assert(valid());}

	// ----
	// push
	// ----

	/**
	 * @param v: reference to the value to be pushed to the back
	 */
	void push_back (const_reference v) {
		resize(size() + 1, v);
		assert(valid());}

	/**
	 * @param v: reference to the value to be pushed to the front
	 */
	void push_front (const_reference v) {
		iterator it = begin();
		size_type temp = d_size;
		if( (it - 1) == end() ){
		     resize(2 * size());
		     it = begin();
		}
		     --it;
		     *it = v;
		     b = it.p;
		     d_size = temp + 1;
		assert(valid());}

	// --------
	// capacity
	// --------

	/**
	 * Private function to keep track of the capacity
	 */	
private:
	size_type capacity() const {
		return (e_a - b_a);
	}

	/*
	 * Private constructor for resize
	 * acts the same like a copy constructor but with a specified size_type c
	 */

	Deque (const Deque& that, size_type c) : a(that.a) {
		b_a = this->a.allocate( c + 1);
		e_a = b_a + c + 1;
		b = b_a +  ( (e_a - b_a)  / 2);
		iterator it(this, b);
		const_iterator thatIt(&that, that.b);
		it = uninitialized_copy(a, that.begin(), that.end(), begin());
		e = it.p;
		d_size = that.size();    
		assert(valid());
	}
public:
	// ------
	// resize
	// ------

	/**
	 * @param s: user specified size of the deque
	 * @param v: value with which the deque is to be initialized
	 */
	void resize (size_type s, const_reference v = value_type()) {
		iterator it(this, b);
		if(s == 0){
			it = destroy(a, it, this->end());
			b = b_a +  ( (e_a - b_a)  / 2);
			e = b+1;
			d_size = s;
		}
		if (s == d_size) return;
		if (s < size() ){
			it += s;
			it = destroy(a, it, this->end());
			/*if(s == 0){
			b = e = b_a = e_a = 0;
			}
		else{
			e = it.p;
			}*/
			e = it.p;
			d_size = s;
		}
		else if(s < capacity() ){
			it.p = e;
			it = uninitialized_fill(a, it , it + s, v);
			e = it.p;
			d_size = s;
		}
		else{
			size_type st = s;
			s = std::max(2*size(), s);
			Deque temp(*this, s);
			this->swap(temp);
			it.p = e;
			//we need to fill the rest of the spot, that we 
			// haven't filled in and that spot is size of dif
			size_type dif = st - d_size;
			it = uninitialized_fill(a, it, it + dif, v);
			e = it.p;
			d_size = st;
		}
		assert(valid());
	}

	// ----
	// size
	// ----

	/**
	 * @return the size of the deque
	 */
	size_type size () const {
		// <your code>
		return d_size;}

	// ----
	// swap
	// ----

	/**
	 * @param that: Deque to be swapped with
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
		//assert(valid());
	     }
		
	};// end Deque class

} // My

#endif // Deque_h
