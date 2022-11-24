cmake_minimum_required(VERSION 3.0.0)
project(EiffelNet VERSION 0.0.1)

include(CTest)
enable_testing()


### LIBRARY ###
# Add includes for ./includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
# Build every c file under ./src
file(GLOB eiffelnet_src ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
# Build the project
add_compile_options(-Wall -Wextra -pedantic -Werror)
add_library(libeiffelnet ${eiffelnet_src})


### TESTS ###
# Build every c file under ./test
file(GLOB eiffelnet_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.c)
# Add includes for ./includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
# Build the test
add_executable(eiffelnet_test ${eiffelnet_test})
# Link the test with the project
target_link_libraries(eiffelnet_test libeiffelnet)
# Add the test to the test suite
add_test(NAME eiffelnet_test COMMAND $<TARGET_FILE:eiffelnet_test>)

### EXECUTABLE ###
# Build main.c and link it with the project
add_executable(eiffelnet ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
target_link_libraries(eiffelnet libeiffelnet)

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


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
