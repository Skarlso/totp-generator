cmake_minimum_required (VERSION 2.8.8)

project (totp-generator)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "-D_GLIBCXX_USE_CXX11_ABI=0")
set (CPACK_GENERATOR "TGZ")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")
#FindOpenSSL
find_package(openssl REQUIRED)
find_package(CryptoPP REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
message(STATUS "OPENSSL INCLUDE DIR:" ${OPENSSL_INCLUDE_DIR})
message(STATUS "OPENSSL VERSION:" ${OPENSSL_VERSION})
message(STATUS "OPENSSL ROOT DIR:" ${OPENSSL_ROOT_DIR})

# libraries to use
add_subdirectory("cpp-commander/Commander")
include_directories("cpp-commander")
link_libraries(commander)

add_executable(totp totp/totp.cpp totp/generator.cpp)
target_link_libraries(totp cryptopp ${OPENSSL_LIBRARIES})
