# add_custom_target(build-tests COMMAND ${CMAKE_CTEST_COMMAND} --show-only)
# add_custom_target(check-tests COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
file(GLOB_RECURSE WSTL_TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*test.cpp")

foreach (wstl_test_source ${WSTL_TEST_SOURCES})
    # Create a human readable name.
    get_filename_component(wstl_test_filename ${wstl_test_source} NAME)
    string(REPLACE ".cpp" "" wstl_test_name ${wstl_test_filename})
    string(REPLACE "w_" "" wstl_test_name ${wstl_test_name})

    # Add the test target separately and as part of "make check-tests".
    add_executable(${wstl_test_name}  ${wstl_test_source})
    message(STATUS "add_executable: ${wstl_test_name}")
    # add_executable(${wstl_test_name} EXCLUDE_FROM_ALL ${wstl_test_source})

    # add_dependencies(build-tests ${wstl_test_name})
    # add_dependencies(check-tests ${wstl_test_name})

    # gtest_discover_tests(${wstl_test_name}
    #         EXTRA_ARGS
    #         --gtest_color=yes
    #         --gtest_output=xml:${CMAKE_BINARY_DIR}/test/${wstl_test_name}.xml
    #         --gtest_catch_exceptions=0
    #         PROPERTIES
    #         TIMEOUT 30
    #         )

    target_link_libraries(${wstl_test_name} wstl)

    # Set test target properties and dependencies.
    # set_target_properties(${wstl_test_name}
    #         PROPERTIES
    #         RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
    #         COMMAND ${wstl_test_name}
    #         )
endforeach (wstl_test_source ${WSTL_TEST_SOURCES})