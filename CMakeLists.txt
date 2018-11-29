cmake_minimum_required(VERSION 3.12)
project(randomseedtest)

set(CMAKE_CXX_STANDARD 14)

add_executable(randomseedtest randomtest.cpp)

find_package(OpenSSL REQUIRED)
target_include_directories(randomseedtest PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(randomseedtest PRIVATE ${OPENSSL_CRYPTO_LIBRARY})
