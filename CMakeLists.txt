cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VESRION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

configure_file(version.h.in version.h)

add_executable(ip_filter_cli ip_filter.cpp)
add_library(lib_version lib.cpp)
add_library(lib_ip_filter lib_ip_filter.cpp)

set_target_properties(ip_filter_cli lib_version lib_ip_filter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(lib_version
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_include_directories(lib_ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)
 
target_link_libraries(ip_filter_cli PRIVATE
    lib_version
    lib_ip_filter
) 

if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(test_ip_filter test_ip_filter.cpp)

    set_target_properties(test_ip_filter PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(test_ip_filter PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

    target_link_libraries(test_ip_filter
        ${Boost_LIBRARIES}
        lib_version
        lib_ip_filter
    )
endif()

if (MSVC)
    target_compile_options(ip_filter_cli PRIVATE
        /W4
    )
    target_compile_options(lib_version lib_ip_filter PRIVATE
        /W4
    )
    target_compile_options(lib_ip_filter PRIVATE
        /W4
    )
    if(WITH_BOOST_TEST)
        target_compile_options(test_ip_filter PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(ip_filter_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(lib_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(lib_ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_BOOST_TEST)
        target_compile_options(test_ip_filter PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ip_filter_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(test_ip_filter test_ip_filter)
endif()

set(IP_FILTER_TSV ${CMAKE_SOURCE_DIR}/ip_filter.tsv)
configure_file(${IP_FILTER_TSV} ${CMAKE_CURRENT_BINARY_DIR})