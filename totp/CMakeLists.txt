#FindOpenSSL
find_package(openssl REQUIRED)
find_package(CryptoPP REQUIRED)
find_package(Boost COMPONENTS filesystem)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OPENSSL_INCLUDE_DIR})

message(STATUS "OPENSSL INCLUDE DIR:" ${OPENSSL_INCLUDE_DIR})
message(STATUS "OPENSSL VERSION:" ${OPENSSL_VERSION})
message(STATUS "OPENSSL ROOT DIR:" ${OPENSSL_ROOT_DIR})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/commands COMMANDS_SOURCES)

link_libraries(commander)
add_library(totp_object OBJECT ${COMMANDS_SOURCES})

add_executable(totp totp.cpp accounting.cpp encrypt.cpp generator.cpp ${COMMANDS_SOURCES})
target_link_libraries(totp cryptopp ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES})

install(TARGETS totp RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/bin")
