cmake_minimum_required(VERSION 3.0.0)
project(EiffelNet VERSION 1.0.0)

include(CTest)
enable_testing()


### LIBRARY ###
# Add includes for ./includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
# Build every c file under ./src
file(GLOB eiffelnet_src ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
# Build the project
add_compile_options(-Wall -Wextra -pedantic -g)
add_library(efnet ${eiffelnet_src})
set_property(TARGET efnet PROPERTY C_STANDARD 99)


### TESTS ###
# Build every c file under ./test
file(GLOB eiffelnet_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.c)
# Add includes for ./includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
# Build the test
add_executable(eiffelnet_test ${eiffelnet_test})
# Link the test with the project
target_link_libraries(eiffelnet_test efnet)
# Add a "test" that builds the test executable
add_test(
    NAME build_tests
    COMMAND "${CMAKE_COMMAND}"
  --build "${CMAKE_BINARY_DIR}"
  --config "$<CONFIG>"
  --target eiffelnet_test
)
# Add a test that builds the real executable
add_test(
    NAME build_executable
    COMMAND "${CMAKE_COMMAND}"
  --build "${CMAKE_BINARY_DIR}"
  --config "$<CONFIG>"
  --target eiffelnet
)
# Add the test to the test suite
add_test(
    NAME c_file
    COMMAND $<TARGET_FILE:eiffelnet_test>
)
set_tests_properties(build_tests PROPERTIES FIXTURES_SETUP    test_fixture)
set_tests_properties(c_file PROPERTIES FIXTURES_REQUIRED test_fixture)

# check_functions.pY
add_test(
    NAME check_functions
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/tests/check_functions.py
)

# Check if the output of the C program is the same as the output of the python program
add_test(
    NAME check_output
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/tests/eiffelnet.py $<TARGET_FILE:eiffelnet>
)
set_tests_properties(build_executable PROPERTIES FIXTURES_SETUP test_fixture_executable)
set_tests_properties(check_output PROPERTIES FIXTURES_REQUIRED test_fixture_executable)


### EXECUTABLE ###
# Build main.c and link it with the project
add_executable(eiffelnet ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
target_link_libraries(eiffelnet efnet)

### MAKE RUN ###
# Add a make run command to run the executable
add_custom_target(run
    COMMAND eiffelnet
    DEPENDS eiffelnet
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

### MAKE VALGRIND ###
# Add a make valgrind command to run the executable with valgrind
add_custom_target(valgrind
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./eiffelnet
    DEPENDS eiffelnet
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)


### MAKE GENFILES ###
# Add a make genfiles command to generate random files using the python script
add_custom_target(genfiles
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/tests/generate_values.py ../data/
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
