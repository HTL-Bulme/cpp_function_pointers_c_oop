# Dynamic Memory Management (Free Store)

Exercise material for using the free store in the C++ programming language.
In this homework you are asked to restrict yourself to not using any
`include` except `<cstddef>` and `<iostream>`.

Before creating a build to run the tests, it is important that all of the
required files (`create_arrays.{cpp,hpp}`, `int_array.{cpp,hpp}`, `main.cpp`)
are created alongside the `*_test.cpp` files. Until all required functions are
declared in the header files, compilation will fail. Until all required
functions are defined (an empty function body or returning a dummy value is
sufficient), the linking won't succeed. In `main.cpp`, at least
a dummy `main(.)` function is required for compilation. Do not add a `main(.)`
function to your `create_arrays.cpp` or `int_array.cpp` files.
With all this in place, compile and run the tests as described below.
Implement `main(.)` in a separate module called `main.cpp`. Include all header
files of this exercise and use all of the implemented functions.
Have `main(.)` print the data and never forget to use `delete` / `delete[]`.
Explain in a comment, why `delete` and `delete[]` has to be used.

Create the source and header files as required by the description of the
exercise below. Then compile your solution:

```
mkdir -p build && cd build
cmake ..
make -j8
```


## Create Arrays on the Free Store

Implement the following functions:

```cpp
/*! Return array on the free store containing `dimension` zeros.
 *
 * The memory for the array is allocated on the heap and all values are
 * initialized to zero.
 *
 * eg. zeros(3) -> {0, 0, 0}
*/
int* zeros(std::size_t dimension);

//! Return array on the free store containing `dimension` ones.
int* ones(std::size_t dimension);

//! Return array on the free store containing `0, 1, 2, 3, ..., dimension-1`.
int* range(std::size_t dimension);
```

Name the source file: `create_arrays.cpp` and the corresponding header file
`create_arrays.hpp`.


## Create Your Own int Array Data Type

Implement a data structure IntArray that helps you to work with arrays of
dynamic size. The core of the data type should be a struct storing a pointer
to an array on the free store and the required metadata. All of your functions
as well as `IntArray` itself must be placed inside of a namespace called `ia`.

```cpp
struct IntArray {
  std::size_t reserved;  ///< available storage
  std::size_t elements;  ///< current number of elements
  int* array;
};
```

Implement the following API to create and work with `IntArray`:

```cpp
//! Create new empty IntArray for 100 elements.
IntArray* create();

//! Create new array with `dimension` zeros.
IntArray* zeros(std::size_t dimension);

//! Create new array with `dimension` ones.
IntArray* ones(std::size_t dimension);

//! Create new array with stop-start elements: start ... stop-1.
IntArray* range(int start, int stop);

//! Free the array and the IntArray struct; return `nullptr`.
IntArray* destroy(IntArray* ia);

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

Name the source file: `int_array.cpp` and the corresponding header
file `int_array.hpp`.
