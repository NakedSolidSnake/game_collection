cmake_minimum_required(VERSION 3.7.0)

project(spaceship)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

# This one is important
SET(CMAKE_SYSTEM_NAME Linux)

# Specify the cross compiler
#SET(CMAKE_C_COMPILER   arm-linux-gnueabihf-gcc)
#SET(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

set (CMAKE_C_FLAGS "-D_GNU_SOURCE -Wall -std=c99")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_BUILD_TYPE Debug)

include(GNUInstallDirs)


function(add_test_unit BIN_NAME BIN SOURCE)
  add_executable(${BIN} ${SOURCE})
  set_target_properties(${BIN}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_lib
    )
    add_test(NAME ${BIN_NAME} COMMAND ${BIN})
endfunction()

enable_testing()

# ipc library
add_library(game "")
target_sources(game 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/src/game_loop.c
  )
target_include_directories(game 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/include
  )
#------------------------------------------------------------------------------------------------------
# Tests
#------------------------------------------------------------------------------------------------------
add_test_unit(interface test_interface tests/test_interface.c)
target_link_libraries(test_interface PUBLIC game)

add_test_unit(test_sdl test_sdl2 tests/test_sdl2.c)
target_link_libraries(test_sdl2 PUBLIC game SDL2)

#------------------------------------------------------------------------------------------------------
# Install
#------------------------------------------------------------------------------------------------------
# install(DIRECTORY include/collection   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# install(DIRECTORY include/file         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# install(DIRECTORY include/log          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# install(DIRECTORY include/queue        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# install(DIRECTORY include/semaphore    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# install(DIRECTORY include/server       DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# install(DIRECTORY include/sharedmemory DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# install(DIRECTORY include/signal       DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# install(DIRECTORY include/util         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# install(DIRECTORY include/database     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# install(DIRECTORY include/json     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# install(TARGETS  util ipc comm database collection json LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})