cmake_minimum_required(VERSION 3.14)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(P004 VERSION ${PROJECT_VERSION})
#option(BUILD_TESTS "Whether to build Boost test" ON)
configure_file(version.h.in version.h)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(version.h.in version.h)
include_directories(${CMAKE_BINARY_DIR})
option(BUILD_TESTS "Build unittests" ON)

add_executable(hello_cli main.cpp)
add_library(lib_ver lib.cpp)
add_library(lib_hello hello.cpp)

target_include_directories(lib_ver
    PRIVATE "${CMAKE_BINARY_DIR}"
)
target_include_directories(lib_hello
    PRIVATE "${CMAKE_BINARY_DIR}"
)
target_link_libraries(hello_cli PRIVATE
    lib_hello
)
target_link_libraries(hello_cli PRIVATE
lib_ver
)

#if(BUILD_TESTS)
#set(BOOST_INCLUDEDIR "C:/VP_WORKS/PROJECTS_CPP/libs/boost_1_87_0/boost")
#set(BOOST_LIBRARYDIR "/custom/path/to/boost/lib")
#find_package(Boost REQUIRED)
if(Boost_FOUND)
  message(STATUS "Boost версии ${Boost_VERSION} найден")
  message(STATUS "Пути к заголовкам: ${Boost_INCLUDE_DIRS}")
  message(STATUS "Библиотеки: ${Boost_LIBRARIES}")
endif()
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
add_executable(test_version test_version.cpp)
add_executable(test_hello test_hello.cpp)

set_target_properties(test_version PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)
set_target_properties(test_hello PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)
target_include_directories(test_version PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(test_version PRIVATE lib_ver ${Boost_LIBRARIES})
target_include_directories(test_hello PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(test_hello PRIVATE lib_hello ${Boost_LIBRARIES})

#endif()

install(TARGETS hello_cli RUNTIME DESTINATION bin)

# set(CPACK_GENERATOR WIN32)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)


enable_testing()
add_test(test_hello test_hello)
add_test(test_version test_version)