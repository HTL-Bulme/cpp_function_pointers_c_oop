#include "int_array.hpp"

#include <cstddef>
#include <numeric>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

using ia::IntArray, ia::construct, ia::zeros, ia::ones, ia::range;

// TODO: adjust tests to ensure const correctness

struct IntArrayFixture {
public:
  IntArrayFixture() {
    ia_empty = construct(10);

    ia_12345 = construct(10);
    ia_12345->__elements = 5;
    ia_12345->__array[0] = 1;
    ia_12345->__array[1] = 2;
    ia_12345->__array[2] = 3;
    ia_12345->__array[3] = 4;
    ia_12345->__array[4] = 5;

    ia_567 = construct(10);
    ia_567->__elements = 3;
    ia_567->__array[0] = 5;
    ia_567->__array[1] = 6;
    ia_567->__array[2] = 7;
  }

  ~IntArrayFixture() {
    delete[] ia_empty->__array;
    delete ia_empty;
    delete[] ia_12345->__array;
    delete ia_12345;
    delete[] ia_567->__array;
    delete ia_567;
  }

  IntArray* ia_empty = nullptr;
  IntArray* ia_12345 = nullptr;
  IntArray* ia_567 = nullptr;
};


TEST_CASE("int_array", "[construct_default]") {
  IntArray* ia = construct();
  CHECK(ia->__elements == 0);
  CHECK(ia->__reserved == 100);
  delete[] ia->__array;
  delete ia;
}


TEST_CASE("int_array", "[construct]") {
  IntArray* ia = construct(27);
  CHECK(ia->__elements == 0);
  CHECK(ia->__reserved == 27);
  delete[] ia->__array;
  delete ia;
}


TEST_CASE("int_array", "[zeros]") {
  IntArray* ia1 = zeros(0);
  IntArray* ia2 = zeros(20);
  IntArray* ia3 = zeros(2000);

  CHECK(ia1->__elements == 0);
  CHECK(ia2->__elements == 20);
  CHECK(ia3->__elements == 2000);

  CHECK(ia2->__reserved >= 20);
  CHECK(ia3->__reserved >= 2000);

  std::vector<int> expected2(20, 0);
  std::vector<int32_t> actual2(ia2->__array, ia2->__array + 20);
  std::vector<int> expected3(2000, 0);
  std::vector<int32_t> actual3(ia3->__array, ia3->__array + 2000);

  CHECK_THAT(actual2, Catch::Matchers::Equals(expected2));
  CHECK_THAT(actual3, Catch::Matchers::Equals(expected3));

  delete[] ia1->__array;
  delete ia1;
  delete[] ia2->__array;
  delete ia2;
  delete[] ia3->__array;
  delete ia3;
}


TEST_CASE("int_array", "[ones]") {
  IntArray* ia1 = ones(0);
  IntArray* ia2 = ones(20);
  IntArray* ia3 = ones(2000);

  CHECK(ia1->__elements == 0);
  CHECK(ia2->__elements == 20);
  CHECK(ia3->__elements == 2000);

  CHECK(ia2->__reserved >= 20);
  CHECK(ia3->__reserved >= 2000);

  std::vector<int> expected2(20, 1);
  std::vector<int32_t> actual2(ia2->__array, ia2->__array + 20);
  std::vector<int> expected3(2000, 1);
  std::vector<int32_t> actual3(ia3->__array, ia3->__array + 2000);

  CHECK_THAT(actual2, Catch::Matchers::Equals(expected2));
  CHECK_THAT(actual3, Catch::Matchers::Equals(expected3));

  delete[] ia1->__array;
  delete ia1;
  delete[] ia2->__array;
  delete ia2;
  delete[] ia3->__array;
  delete ia3;
}


TEST_CASE("int_array", "[range]") {
  IntArray* ia1 = range(0, 0);
  IntArray* ia2 = range(0, 20);
  IntArray* ia3 = range(0, 2000);
  IntArray* ia4 = range(15, 30);

  CHECK(ia1->__elements == 0);
  CHECK(ia2->__elements == 20);
  CHECK(ia3->__elements == 2000);
  CHECK(ia4->__elements == 15);

  CHECK(ia2->__reserved >= 20);
  CHECK(ia3->__reserved >= 2000);
  CHECK(ia4->__reserved >= 15);

  std::vector<int> expected2(20);
  std::iota(expected2.begin(), expected2.end(), 0);
  std::vector<int32_t> actual2(ia2->__array, ia2->__array + 20);
  std::vector<int> expected3(2000);
  std::iota(expected3.begin(), expected3.end(), 0);
  std::vector<int32_t> actual3(ia3->__array, ia3->__array + 2000);
  std::vector<int> expected4(15);
  std::iota(expected4.begin(), expected4.end(), 15);
  std::vector<int32_t> actual4(ia4->__array, ia4->__array + 15);

  CHECK_THAT(actual2, Catch::Matchers::Equals(expected2));
  CHECK_THAT(actual3, Catch::Matchers::Equals(expected3));
  CHECK_THAT(actual4, Catch::Matchers::Equals(expected4));

  delete[] ia1->__array;
  delete ia1;
  delete[] ia2->__array;
  delete ia2;
  delete[] ia3->__array;
  delete ia3;
  delete[] ia4->__array;
  delete ia4;
}


// There is no real way to check if `delete` was called, so the only check made
// is whether the pointers have been set to nullptr.
TEST_CASE("int_array", "[destruct]") {
  IntArray* ia = construct(5);
  IntArray* ia_ptr = ia;  // allow to reference member of destroyed object
  ia = ia->destruct(ia);
  CHECK(ia_ptr->__array == nullptr);
  CHECK(ia == nullptr);
}


TEST_CASE("int_array", "[push_back]") {
  IntArray* ia = construct(2);
  ia->__elements = 1;
  ia->__array[0] = 10;

  ia->push_back(ia, 15);
  CHECK(ia->__elements == 2);
  CHECK(ia->__reserved == 2);
  CHECK(ia->__array[0] == 10);
  CHECK(ia->__array[1] == 15);

  ia->push_back(ia, 17);
  CHECK(ia->__elements == 3);
  CHECK(ia->__reserved >= 3);
  CHECK(ia->__array[0] == 10);
  CHECK(ia->__array[1] == 15);
  CHECK(ia->__array[2] == 17);

  delete[] ia->__array;
  delete ia;
}


TEST_CASE("int_array", "[insert]") {
  IntArray* ia = construct(2);
  ia->__elements = 1;
  ia->__array[0] = 10;

  ia->insert(ia, 0, 15);
  CHECK(ia->__elements == 2);
  CHECK(ia->__reserved == 2);
  CHECK(ia->__array[0] == 15);
  CHECK(ia->__array[1] == 10);

  ia->insert(ia, 1, 17);
  CHECK(ia->__elements == 3);
  CHECK(ia->__reserved >= 3);
  CHECK(ia->__array[0] == 15);
  CHECK(ia->__array[1] == 17);
  CHECK(ia->__array[2] == 10);

  delete[] ia->__array;
  delete ia;
}


TEST_CASE_METHOD(IntArrayFixture, "int_array", "[pop_back]") {
  int val = ia_567->pop_back(ia_567);
  CHECK(ia_567->__elements == 2);
  CHECK(ia_567->__array[0] == 5);
  CHECK(ia_567->__array[1] == 6);
  CHECK(val == 7);

  val = ia_567->pop_back(ia_567);
  CHECK(ia_567->__elements == 1);
  CHECK(ia_567->__array[0] == 5);
  CHECK(val == 6);

  val = ia_567->pop_back(ia_567);
  CHECK(ia_567->__elements == 0);
  CHECK(val == 5);
}


TEST_CASE_METHOD(IntArrayFixture, "int_array", "[size]") {
  const IntArray* arr = ia_12345;  // test const correctness
  CHECK(arr->size(arr) == 5);
  CHECK(ia_567->size(ia_567) == 3);
}


TEST_CASE_METHOD(IntArrayFixture, "int_array", "[count]") {
  SECTION("unique elements") {
    CHECK(ia_12345->count(ia_12345, 1) == 1);
    CHECK(ia_12345->count(ia_12345, 2) == 1);
    CHECK(ia_12345->count(ia_12345, 3) == 1);
    CHECK(ia_12345->count(ia_12345, 4) == 1);
    CHECK(ia_12345->count(ia_12345, 5) == 1);
    CHECK(ia_12345->count(ia_12345, 6) == 0);
    CHECK(ia_12345->count(ia_12345, 0) == 0);
    CHECK(ia_12345->count(ia_12345, -1) == 0);
    CHECK(ia_12345->count(ia_12345, -2) == 0);
  }

  SECTION("non-unique elements") {
    ia_12345->__array[1] = 5;
    ia_12345->__array[3] = 5;
    CHECK(ia_12345->count(ia_12345, 1) == 1);
    CHECK(ia_12345->count(ia_12345, 2) == 0);
    CHECK(ia_12345->count(ia_12345, 3) == 1);
    CHECK(ia_12345->count(ia_12345, 4) == 0);
    CHECK(ia_12345->count(ia_12345, 5) == 3);
    CHECK(ia_12345->count(ia_12345, 6) == 0);
    CHECK(ia_12345->count(ia_12345, 0) == 0);
    CHECK(ia_12345->count(ia_12345, -1) == 0);
    CHECK(ia_12345->count(ia_12345, -2) == 0);
  }
}


TEST_CASE_METHOD(IntArrayFixture, "int_array", "[index]") {
  CHECK(ia_567->index(ia_567, 0) == 5);
  CHECK(ia_567->index(ia_567, 1) == 6);
  CHECK(ia_567->index(ia_567, 2) == 7);
}


TEST_CASE_METHOD(IntArrayFixture, "int_array", "[sum]") {
  CHECK(ia_empty->sum(ia_empty) == 0);
  CHECK(ia_12345->sum(ia_12345) == 15);
  CHECK(ia_567->sum(ia_567) == 18);
}


TEST_CASE_METHOD(IntArrayFixture, "int_array", "[add]") {
  SECTION("same size") {
    IntArray* ia_actual = ia_567->add(ia_567, ia_567);
    std::vector<int> expected = {10, 12, 14};

    std::vector<int> actual(ia_actual->__array, ia_actual->__array + 3);
    CHECK(ia_actual->__elements == ia_567->__elements);
    CHECK_THAT(actual, Catch::Matchers::Equals(expected));

    delete[] ia_actual->__array;
    delete ia_actual;
  }

  SECTION("different size") {
    IntArray* first = ia_567->add(ia_567, ia_12345);
    IntArray* second = ia_12345->add(ia_12345, ia_567);
    std::vector<int> expected = {6, 8, 10, 4, 5};

    std::vector<int> first_actual(first->__array, first->__array + 5);
    std::vector<int> second_actual(second->__array, second->__array + 5);
    CHECK(first->__elements == ia_12345->__elements);
    CHECK(second->__elements == ia_12345->__elements);
    CHECK_THAT(first_actual, Catch::Matchers::Equals(expected));
    CHECK_THAT(second_actual, Catch::Matchers::Equals(expected));

    delete[] first->__array;
    delete first;
    delete[] second->__array;
    delete second;
  }

  SECTION("add empty") {
    std::vector<int> expected(ia_567->__array, ia_567->__array + 3);
    IntArray* ia_actual = ia_567->add(ia_567, ia_empty);
    std::vector<int> actual(ia_actual->__array, ia_actual->__array + 3);
    CHECK(ia_actual->__elements == ia_567->__elements);
    CHECK_THAT(actual, Catch::Matchers::Equals(expected));
    delete[] ia_actual->__array;
    delete ia_actual;
  }
}


TEST_CASE_METHOD(IntArrayFixture, "int_array", "[mul]") {
  SECTION("same size") {
    IntArray* ia_actual = ia_567->mul(ia_567, ia_567);
    CHECK(ia_actual->__elements == ia_567->__elements);
    std::vector<int> expected = {25, 36, 49};

    std::vector<int> actual(ia_actual->__array, ia_actual->__array + 3);
    CHECK_THAT(actual, Catch::Matchers::Equals(expected));

    delete[] ia_actual->__array;
    delete ia_actual;
  }

  SECTION("different size") {
    IntArray* first = ia_567->mul(ia_567, ia_12345);
    IntArray* second = ia_12345->mul(ia_12345, ia_567);
    CHECK(first->__elements == ia_12345->__elements);
    CHECK(second->__elements == ia_12345->__elements);
    std::vector<int> expected = {5, 12, 21, 4, 5};

    std::vector<int> first_actual(first->__array, first->__array + 5);
    std::vector<int> second_actual(second->__array, second->__array + 5);
    CHECK_THAT(first_actual, Catch::Matchers::Equals(expected));
    CHECK_THAT(second_actual, Catch::Matchers::Equals(expected));

    delete[] first->__array;
    delete first;
    delete[] second->__array;
    delete second;
  }

  SECTION("multiply with empty") {
    std::vector<int> expected(ia_567->__array, ia_567->__array + 3);
    IntArray* ia_actual = ia_567->mul(ia_567, ia_empty);
    CHECK(ia_actual->__elements == ia_567->__elements);
    std::vector<int> actual(ia_actual->__array, ia_actual->__array + 3);
    CHECK_THAT(actual, Catch::Matchers::Equals(expected));
    delete[] ia_actual->__array;
    delete ia_actual;
  }
}
