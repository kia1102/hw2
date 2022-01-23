cmake_minimum_required(VERSION 3.10.0)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(homework2 VERSION  ${PROJECT_VESRION})

include(CTest)
enable_testing()

option(WITH_TEST "Whether to build GoogleTest" OFF)

configure_file(version.h.in version.h)

add_executable(homework2 ip_filter.cpp)
add_library(buildinfo buildinfo.cpp)

set_target_properties(homework2 buildinfo PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(buildinfo
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(homework2 PRIVATE
buildinfo
)

if(WITH_TEST)
    enable_testing()
    find_package(GTest  REQUIRED)
    add_executable(testFilters tests/testFilters.cpp)   
    target_link_libraries(testFilters GTest::gtest GTest::gtest_main)
    add_test(testFilters testFilters)
    install(TARGETS testFilters RUNTIME DESTINATION tests)
endif()


install(TARGETS homework2 RUNTIME DESTINATION bin)


set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT ivan.ku.work@gmail.com)
include(CPack)
 
