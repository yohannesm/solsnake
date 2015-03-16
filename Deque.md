# Class Deque #

## Introduction ##

The problem dealt with creating a class deque which would mimic the behavior of the deque from the standard library.

## Details ##

### Deque.h ###
The deque class was implemented by using a heap allocated array by using allocator. The allocator can be provided by the user as an argument to the deque. However, it is defaulted to the `std::Allocator<T>`.

#### Constructors ####

Default: The default constructor constructs a Deque with size zero and initializes the pointers to point at the same location. Uses the uninitialized fill method.

Copy: Copy's the objects from that deque to this deque. Uses the uninitialized copy method.

Assignment: Assigns that deque to this deque. Resizes if required.

Destructor: Calls the destroy method. Destructs the objects in the specified range.

#### Operators ####

`==` Compares 2 deques. Returns true if the Deque's are equal. False otherwise. Checks equality of deque's of same type and size. Calls the `std::equal` to make the comparison by passing the iterators.

`<=` Returns true if the Deque on the lhs is lexicographically less than the other one. Makes a call to `std::lexicographical_compare`.

#### Methods ####

The following methods were implemented for the Deque class:
  1. Destroy - For destroying the elements. Destructor calls this method
  1. Uninitialized fill
  1. Uninitialized copy
  1. at - returns the element that the iterator points to, throws an exception if the index is out of the range of Deque
  1. back - Returns the element at the back of the Deque
  1. begin - Returns iterator to the beginning of the Deque
  1. end - Returns iterator to the end of the Deque
  1. clear - Clears the Deque. Destroys all the element and re-sizes the deque to 0
  1. empty - Bool function, informs if the Deque is empty or not
  1. insert - It takes in an iterator as argument. Inserts the new element at the location that iterator points to. Returns the iterator where the element was inserted
  1. erase - Takes in an iterator. Erases the element the iterator points to
  1. push front - Insert at the beginning of the deque
  1. push back - Inserts new element at the back of the deque
  1. pop front - Removes the element at the front
  1. pop back - Reemoves the element at the back
  1. front - Returns the element in the front (Does not remove it)
  1. Capacity - Private method to keep track of Deque's capacity
  1. Size - Returns the size of the Deque
  1. Resize - Resizes the deque.
  1. Swap - Swaps between 2 Deque's

#### Nested Class Iterator and Const Iterator ####
These classes are friends of the deque class. These classes create iterators which can iterate the Deque.
== and != were defined for these iterator classes to check their equality.
++,-- were defined for pre/post increment/decrement of iterator. The functionality for wrap around was defined in these operators
+=, -=, +, - were defined for the iterators to increment/decrement by specified amount.

### TestDeque.h ###
Comprehensive test suite was built to test the correct functionality of the Deque class. The results were compared with the real standard deque to confirm the correctness.


---


## References ##
1) C++ Standard Template Library by Nicolai Jossutis.

2) Dr Downing's Class Examples: http://www.cs.utexas.edu/users/downing/cs378/Examples.html