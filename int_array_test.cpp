#include "int_array.hpp"

#include <cstddef>
#include <numeric>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include <iostream>

using namespace ia;


struct IntArrayFixture {
public:
  IntArrayFixture() {
    ia_empty = new IntArray;
    ia_empty->reserved = 10;
    ia_empty->elements = 0;
    ia_empty->array = new int[10];

    ia_12345 = new IntArray;
    ia_12345->array = new int[10];
    ia_12345->reserved = 10;
    ia_12345->elements = 5;
    ia_12345->array[0] = 1;
    ia_12345->array[1] = 2;
    ia_12345->array[2] = 3;
    ia_12345->array[3] = 4;
    ia_12345->array[4] = 5;

    ia_567 = new IntArray;
    ia_567->array = new int[10];
    ia_567->reserved = 10;
    ia_567->elements = 3;
    ia_567->array[0] = 5;
    ia_567->array[1] = 6;
    ia_567->array[2] = 7;
  }

  ~IntArrayFixture() {
    delete[] ia_empty->array;
    delete ia_empty;
    delete[] ia_12345->array;
    delete ia_12345;
    delete[] ia_567->array;
    delete ia_567;
  }

  IntArray* ia_empty = nullptr;
  IntArray* ia_12345;// = nullptr;
  IntArray* ia_567 = nullptr;
};


TEST_CASE("int_array", "[create]") {
  IntArray* ia = create();
  CHECK(ia->elements == 0);
  CHECK(ia->reserved == 100);
  delete[] ia->array;
  delete ia;
}


TEST_CASE("int_array", "[zeros]") {
  IntArray* ia1 = zeros(0);
  IntArray* ia2 = zeros(20);
  IntArray* ia3 = zeros(2000);

  CHECK(ia1->elements == 0);
  CHECK(ia2->elements == 20);
  CHECK(ia3->elements == 2000);

  CHECK(ia2->reserved >= 20);
  CHECK(ia3->reserved >= 2000);

  std::vector<int> expected2(20, 0);
  std::vector<int32_t> actual2(ia2->array, ia2->array + 20);
  std::vector<int> expected3(2000, 0);
  std::vector<int32_t> actual3(ia3->array, ia3->array + 2000);

  CHECK_THAT(actual2, Catch::Matchers::Equals(expected2));
  CHECK_THAT(actual3, Catch::Matchers::Equals(expected3));

  delete[] ia1->array;
  delete ia1;
  delete[] ia2->array;
  delete ia2;
  delete[] ia3->array;
  delete ia3;
}


TEST_CASE("int_array", "[ones]") {
  IntArray* ia1 = ones(0);
  IntArray* ia2 = ones(20);
  IntArray* ia3 = ones(2000);

  CHECK(ia1->elements == 0);
  CHECK(ia2->elements == 20);
  CHECK(ia3->elements == 2000);

  CHECK(ia2->reserved >= 20);
  CHECK(ia3->reserved >= 2000);

  std::vector<int> expected2(20, 1);
  std::vector<int32_t> actual2(ia2->array, ia2->array + 20);
  std::vector<int> expected3(2000, 1);
  std::vector<int32_t> actual3(ia3->array, ia3->array + 2000);

  CHECK_THAT(actual2, Catch::Matchers::Equals(expected2));
  CHECK_THAT(actual3, Catch::Matchers::Equals(expected3));

  delete[] ia1->array;
  delete ia1;
  delete[] ia2->array;
  delete ia2;
  delete[] ia3->array;
  delete ia3;
}


TEST_CASE("int_array", "[range]") {
  IntArray* ia1 = range(0, 0);
  IntArray* ia2 = range(0, 20);
  IntArray* ia3 = range(0, 2000);
  IntArray* ia4 = range(15, 30);

  CHECK(ia1->elements == 0);
  CHECK(ia2->elements == 20);
  CHECK(ia3->elements == 2000);
  CHECK(ia4->elements == 15);

  CHECK(ia2->reserved >= 20);
  CHECK(ia3->reserved >= 2000);
  CHECK(ia4->reserved >= 15);

  std::vector<int> expected2(20);
  std::iota(expected2.begin(), expected2.end(), 0);
  std::vector<int32_t> actual2(ia2->array, ia2->array + 20);
  std::vector<int> expected3(2000);
  std::iota(expected3.begin(), expected3.end(), 0);
  std::vector<int32_t> actual3(ia3->array, ia3->array + 2000);
  std::vector<int> expected4(15);
  std::iota(expected4.begin(), expected4.end(), 15);
  std::vector<int32_t> actual4(ia4->array, ia4->array + 15);

  CHECK_THAT(actual2, Catch::Matchers::Equals(expected2));
  CHECK_THAT(actual3, Catch::Matchers::Equals(expected3));
  CHECK_THAT(actual4, Catch::Matchers::Equals(expected4));

  delete[] ia1->array;
  delete ia1;
  delete[] ia2->array;
  delete ia2;
  delete[] ia3->array;
  delete ia3;
  delete[] ia4->array;
  delete ia4;
}


// There is no real way to check if `delete` was called, so the only check made
// is whether the pointers have been set to nullptr.
TEST_CASE("int_array", "[destroy]") {
  IntArray* ia = new IntArray;
  ia->array = new int[5];
  IntArray* ia_ptr = ia;  // allow to reference member of destroyed object
  ia = destroy(ia);
  CHECK(ia_ptr->array == nullptr);
  CHECK(ia == nullptr);
}


TEST_CASE("int_array", "[push_back]") {
  IntArray* ia = new IntArray;
  ia->reserved = 2;
  ia->elements = 1;
  ia->array = new int[ia->reserved];
  ia->array[0] = 10;

  push_back(ia, 15);
  CHECK(ia->elements == 2);
  CHECK(ia->reserved == 2);
  CHECK(ia->array[0] == 10);
  CHECK(ia->array[1] == 15);

  push_back(ia, 17);
  CHECK(ia->elements == 3);
  CHECK(ia->reserved >= 3);
  CHECK(ia->array[0] == 10);
  CHECK(ia->array[1] == 15);
  CHECK(ia->array[2] == 17);

  delete[] ia->array;
  delete ia;
}


TEST_CASE("int_array", "[insert]") {
  IntArray* ia = new IntArray;
  ia->reserved = 2;
  ia->elements = 1;
  ia->array = new int[ia->reserved];
  ia->array[0] = 10;

  insert(ia, 0, 15);
  CHECK(ia->elements == 2);
  CHECK(ia->reserved == 2);
  CHECK(ia->array[0] == 15);
  CHECK(ia->array[1] == 10);

  insert(ia, 1, 17);
  CHECK(ia->elements == 3);
  CHECK(ia->reserved >= 3);
  CHECK(ia->array[0] == 15);
  CHECK(ia->array[1] == 17);
  CHECK(ia->array[2] == 10);

  delete[] ia->array;
  delete ia;
}


TEST_CASE_METHOD(IntArrayFixture, "int_array", "[pop_back]") {
  int val = pop_back(ia_567);
  CHECK(ia_567->elements == 2);
  CHECK(ia_567->array[0] == 5);
  CHECK(ia_567->array[1] == 6);
  CHECK(val == 7);

  val = pop_back(ia_567);
  CHECK(ia_567->elements == 1);
  CHECK(ia_567->array[0] == 5);
  CHECK(val == 6);

  val = pop_back(ia_567);
  CHECK(ia_567->elements == 0);
  CHECK(val == 5);
}


TEST_CASE_METHOD(IntArrayFixture, "int_array", "[size]") {
  CHECK(size(ia_12345) == 5);
  CHECK(size(ia_567) == 3);
}


TEST_CASE_METHOD(IntArrayFixture, "int_array", "[count]") {
  SECTION("unique elements") {
    CHECK(count(ia_12345, 1) == 1);
    CHECK(count(ia_12345, 2) == 1);
    CHECK(count(ia_12345, 3) == 1);
    CHECK(count(ia_12345, 4) == 1);
    CHECK(count(ia_12345, 5) == 1);
    CHECK(count(ia_12345, 6) == 0);
    CHECK(count(ia_12345, 0) == 0);
    CHECK(count(ia_12345, -1) == 0);
    CHECK(count(ia_12345, -2) == 0);
  }

  SECTION("non-unique elements") {
    ia_12345->array[1] = 5;
    ia_12345->array[3] = 5;
    CHECK(count(ia_12345, 1) == 1);
    CHECK(count(ia_12345, 2) == 0);
    CHECK(count(ia_12345, 3) == 1);
    CHECK(count(ia_12345, 4) == 0);
    CHECK(count(ia_12345, 5) == 3);
    CHECK(count(ia_12345, 6) == 0);
    CHECK(count(ia_12345, 0) == 0);
    CHECK(count(ia_12345, -1) == 0);
    CHECK(count(ia_12345, -2) == 0);
  }
}


TEST_CASE_METHOD(IntArrayFixture, "int_array", "[index]") {
  CHECK(index(ia_567, 0) == 5);
  CHECK(index(ia_567, 1) == 6);
  CHECK(index(ia_567, 2) == 7);
}


TEST_CASE_METHOD(IntArrayFixture, "int_array", "[sum]") {
  CHECK(sum(ia_empty) == 0);
  CHECK(sum(ia_12345) == 15);
  CHECK(sum(ia_567) == 18);
}


TEST_CASE_METHOD(IntArrayFixture, "int_array", "[add]") {
  SECTION("same size") {
    IntArray* ia_actual = add(ia_567, ia_567);
    std::vector<int> expected = {10, 12, 14};

    std::vector<int> actual(ia_actual->array, ia_actual->array + 3);
    CHECK(ia_actual->elements == ia_567->elements);
    CHECK_THAT(actual, Catch::Matchers::Equals(expected));

    delete[] ia_actual->array;
    delete ia_actual;
  }

  SECTION("different size") {
    IntArray* first = add(ia_567, ia_12345);
    IntArray* second = add(ia_12345, ia_567);
    std::vector<int> expected = {6, 8, 10, 4, 5};

    std::vector<int> first_actual(first->array, first->array + 5);
    std::vector<int> second_actual(second->array, second->array + 5);
    CHECK(first->elements == ia_12345->elements);
    CHECK(second->elements == ia_12345->elements);
    CHECK_THAT(first_actual, Catch::Matchers::Equals(expected));
    CHECK_THAT(second_actual, Catch::Matchers::Equals(expected));

    delete[] first->array;
    delete first;
    delete[] second->array;
    delete second;
  }

  SECTION("add empty") {
    std::vector<int> expected(ia_567->array, ia_567->array + 3);
    IntArray* ia_actual = add(ia_567, ia_empty);
    std::vector<int> actual(ia_actual->array, ia_actual->array + 3);
    CHECK(ia_actual->elements == ia_567->elements);
    CHECK_THAT(actual, Catch::Matchers::Equals(expected));
    delete[] ia_actual->array;
    delete ia_actual;
  }
}


TEST_CASE_METHOD(IntArrayFixture, "int_array", "[mul]") {
  SECTION("same size") {
    IntArray* ia_actual = mul(ia_567, ia_567);
    CHECK(ia_actual->elements == ia_567->elements);
    std::vector<int> expected = {25, 36, 49};

    std::vector<int> actual(ia_actual->array, ia_actual->array + 3);
    CHECK_THAT(actual, Catch::Matchers::Equals(expected));

    delete[] ia_actual->array;
    delete ia_actual;
  }

  SECTION("different size") {
    IntArray* first = mul(ia_567, ia_12345);
    IntArray* second = mul(ia_12345, ia_567);
    CHECK(first->elements == ia_12345->elements);
    CHECK(second->elements == ia_12345->elements);
    std::vector<int> expected = {5, 12, 21, 4, 5};

    std::vector<int> first_actual(first->array, first->array + 5);
    std::vector<int> second_actual(second->array, second->array + 5);
    CHECK_THAT(first_actual, Catch::Matchers::Equals(expected));
    CHECK_THAT(second_actual, Catch::Matchers::Equals(expected));

    delete[] first->array;
    delete first;
    delete[] second->array;
    delete second;
  }

  SECTION("multiply with empty") {
    std::vector<int> expected(ia_567->array, ia_567->array + 3);
    IntArray* ia_actual = mul(ia_567, ia_empty);
    CHECK(ia_actual->elements == ia_567->elements);
    std::vector<int> actual(ia_actual->array, ia_actual->array + 3);
    CHECK_THAT(actual, Catch::Matchers::Equals(expected));
    delete[] ia_actual->array;
    delete ia_actual;
  }
}
