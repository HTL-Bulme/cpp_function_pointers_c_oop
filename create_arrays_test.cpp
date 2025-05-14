#include "create_arrays.hpp"


#include <cstddef>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>


TEST_CASE("test zeros", "[zeros]") {

  SECTION("single element") {
    int* actual = zeros(1);
    CHECK(actual[0] == 0);
    delete[] actual;
  }

  SECTION("regular") {
    size_t dimension = 5;
    int* actual = zeros(dimension);
    std::vector<int> expected{0, 0, 0, 0, 0};
    std::vector<int32_t> actual_v(actual, actual + dimension);
    CHECK_THAT(actual_v,
      Catch::Matchers::Equals(expected));
    delete[] actual;
  }

  SECTION("large") {
    int* actual = zeros(50000);
    CHECK(actual[0] == 0);
    CHECK(actual[25000] == 0);
    CHECK(actual[49999] == 0);
    delete[] actual;
  }
}


TEST_CASE("test ones", "[ones]") {

  SECTION("single element") {
    int* actual = ones(1);
    CHECK(actual[0] == 1);
    delete[] actual;
  }

  SECTION("regular") {
    size_t dimension = 5;
    int* actual = ones(dimension);
    std::vector<int> expected{1, 1, 1, 1, 1};
    std::vector<int32_t> actual_v(actual, actual + dimension);
    CHECK_THAT(actual_v,
      Catch::Matchers::Equals(expected));
    delete[] actual;
  }

  SECTION("large") {
    int* actual = ones(50000);
    CHECK(actual[0] == 1);
    CHECK(actual[25000] == 1);
    CHECK(actual[49999] == 1);
    delete[] actual;
  }
}


TEST_CASE("test range", "[range]") {

  SECTION("single element") {
    int* actual = range(1);
    CHECK(actual[0] == 0);
    delete[] actual;
  }

  SECTION("regular") {
    size_t dimension = 5;
    int* actual = range(dimension);
    std::vector<int> expected{0, 1, 2, 3, 4};
    std::vector<int32_t> actual_v(actual, actual + dimension);
    CHECK_THAT(actual_v,
      Catch::Matchers::Equals(expected));
    delete[] actual;
  }

  SECTION("large") {
    int* actual = range(50000);
    CHECK(actual[0] == 0);
    CHECK(actual[25000] == 25000);
    CHECK(actual[49999] == 49999);
    delete[] actual;
  }
}
