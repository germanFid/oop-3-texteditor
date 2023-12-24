cmake_minimum_required(VERSION 3.15)
project(mystring 
    VERSION 0.1.0 
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === GOOGLE TEST INCLUDE ===

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# === GOOGLE TEST END ===

include(CTest)
enable_testing()

set(SOURCE_LIB src/mystring.cpp src/charlist.h src/Aho-Corasick/aho.h src/Aho-Corasick/aho.cpp)

add_library(mystring STATIC ${SOURCE_LIB})

# for LEGACY main.cpp testing
# add_executable(oop-1 main.cpp)
# target_link_libraries(oop-1 mystring)

add_executable(operators_test tests/mystring-operators.cc)
add_executable(insert_test tests/mystring-insert.cc)
add_executable(erase_test tests/mystring-erase.cc)
add_executable(append_test tests/mystring-append.cc)
add_executable(replace_test tests/mystring-replace.cc)
add_executable(substr_test tests/mystring-substr.cc)
add_executable(find_test tests/mystring-find.cc)
add_executable(capacity_test tests/mystring-capacity.cc)
add_executable(extras_test tests/mystring-extras.cc)


# === TEST TARGETS ===
target_link_libraries(
  operators_test
    GTest::gtest_main
    mystring
)

target_link_libraries(
  insert_test
  GTest::gtest_main
  mystring
)

target_link_libraries(
  erase_test
  GTest::gtest_main
  mystring
)

target_link_libraries(
  append_test
  GTest::gtest_main
  mystring
)

target_link_libraries(
  replace_test
  GTest::gtest_main
  mystring
)

target_link_libraries(
  substr_test
  GTest::gtest_main
  mystring
)

target_link_libraries(
  find_test
  GTest::gtest_main
  mystring
)

target_link_libraries(
  capacity_test
  GTest::gtest_main
  mystring
)

target_link_libraries(
  extras_test
  GTest::gtest_main
  mystring
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# === GTEST TO CTEST ===
add_test(operators_test operators_test)
add_test(insert_test insert_test)
add_test(erase_test erase_test)
add_test(append_test append_test)
add_test(replace_test replace_test)
add_test(substr_test substr_test)
add_test(find_test find_test)
add_test(capacity_test capacity_test)
add_test(extras_test extras_test)
