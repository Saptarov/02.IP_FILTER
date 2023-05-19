cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
project(ip_filter VERSION ${PROJECT_VESRION} LANGUAGES CXX)


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/version.h)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/googletest-release-1.12.1)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
file(GLOB_RECURSE FILTER_SRC ${CMAKE_CURRENT_SOURCE_DIR}/lib/*)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Source" FILES ${SRC})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(
    ${PROJECT_NAME}_lib
    ${FILTER_SRC}
)

add_executable(
    ${PROJECT_NAME}
    ${MAIN_SRC}
)

target_link_libraries(
    ${PROJECT_NAME}
    ${PROJECT_NAME}_lib
    )



include(GoogleTest)
enable_testing()

add_executable(
    test_${PROJECT_NAME}
    ${SRC}
    tests/test_ip_addr.cpp
    )

target_link_libraries(
    test_${PROJECT_NAME}
    GTest::gtest_main
    ${PROJECT_NAME}_lib
    )

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
    target_compile_options(test_${PROJECT_NAME} PRIVATE
        /W4
    )
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_${PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

gtest_discover_tests(test_${PROJECT_NAME})
