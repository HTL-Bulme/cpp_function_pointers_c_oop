# Using Function Pointers for C-style Object Orientation

Implement `main(.)` in a separate module called `main.cpp`. Include all header
files of this exercise and use all of the implemented functions.
Have `main(.)` print the data and don't forget to use your "destructor".

Create the source and header files as required by the description of the
exercise below. Then compile your solution:

```
mkdir -p build && cd build
cmake ..
make -j8
```


## Create Your Own `int` Array Data Type

Implement a data structure `IntArray` that helps you to work with arrays of
dynamic size. The core of the data type should be a struct storing a pointer
to an array on the free store and the required metadata. All of your functions
as well as `IntArray` itself must be placed inside of a namespace called `ia`
(data structures). This exercise is almost identical to the prior free store
exercise. However, this time use function pointers to provide all
functionality directly as part of the `IntArray` instances.

As usual, place the declarations in the header file and the implementations
in the `cpp` source file. Consult the [test cases](int_array_test.cpp) for
details.

Implement the following API to create and work with `IntArray`:

```cpp
//! Create new empty IntArray for 100 elements.
IntArray* construct();

//! Create new empty IntArray for `dimension` elements.
IntArray* construct(std::size_t dimension);

//! Create new array with `dimension` zeros.
IntArray* zeros(std::size_t dimension);

//! Create new array with `dimension` ones.
IntArray* ones(std::size_t dimension);

//! Create new array with stop-start elements: start ... stop-1.
IntArray* range(int start, int stop);

//! Free the array and the IntArray struct; return `nullptr`.
IntArray* destruct(IntArray* ia);

//! Remove and return last element of `ia`
int pop_back(IntArray* ia);

/*! Add `elem` to `ia`.
 *
 * If that would exceed the available reserved memory, double the size of
 * the array.
 */
void push_back(IntArray* ia, int elem);

/*! Insert `elem` before element at index.
 *
 * If that would exceed the available reserved memory, double the size of
 * the array.
 */
void insert(IntArray* ia, std::size_t index, int elem);

//! Return the number of occurrences of `elem` in `ia`.
std::size_t count(IntArray* ia, int elem);

/*!
 * Return element at index.
 * If the index is out of bounds, write "IndexError" and some useful context
 * to stderr and terminate the execution of the program.
 */
int index(IntArray* ia, std::size_t index);

//! Print a representation of the array to stdout.
void print(IntArray* ia);

//! Return the current number of elements.
std::size_t size(IntArray* ia);

//! Return the sum of all elements.
long int sum(IntArray* ia);

/*
 * Return new `IntArray*` where all elements are the pairwise sum of the
 * elements of the given two arrays. If one array is shorter,
 * solely use the elements of the longer array for the higher indices.
 */
IntArray* add(IntArray* first, IntArray* second);

/*
 * Return new `IntArray*` where all elements are the pairwise product of the
 * elements of the given two arrays. If one array is shorter,
 * solely use the elements of the longer array for the higher indices.
 */
IntArray* mul(IntArray* first, IntArray* second);
```

All of the above functions must ensure that the data stored in the struct is
consistent at all times. For example, adding an element must also increase the
value of `elements` and, if needed, the value of `reserved`. Use and
thoroughly test your implementation in a designated `main(.)` function
in `main.cpp`.

In this implementation, users shall not touch the internal data (number
of reserved elements, number of actual elements and the internal array.
To help enforce this, hint users that internal data is not to be touched by
preceeding it with two underscores. For example, `reserved` must be called
`__reserved` instead. Functions that are meant to be used by others
(the "public API") must not have preceding underscores

Name the source file: `int_array.cpp` and the corresponding header
file `int_array.hpp`.
