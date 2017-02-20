cmake_minimum_required (VERSION 2.8.8)

project (totp-generator)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")
#FindOpenSSL
find_package(openssl REQUIRED)
find_package(CryptoPP REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
message(STATUS "OPENSSL INCLUDE DIR:" ${OPENSSL_INCLUDE_DIR})
message(STATUS "OPENSSL VERSION:" ${OPENSSL_VERSION})
message(STATUS "OPENSSL ROOT DIR:" ${OPENSSL_ROOT_DIR})
add_executable(totp src/totp.cpp src/generator.cpp)
target_link_libraries(totp cryptopp ${OPENSSL_LIBRARIES})
