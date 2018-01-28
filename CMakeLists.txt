cmake_minimum_required (VERSION 2.8.8)

project (totp-generator)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "-D_GLIBCXX_USE_CXX11_ABI=0")
set (CPACK_GENERATOR "TGZ")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")

# Add Commander
add_subdirectory("cpp-commander/Commander")
include_directories("cpp-commander")
link_libraries(commander)

# Totp
add_subdirectory("totp")
# add_subdirectory("tests")
include_directories("totp")
