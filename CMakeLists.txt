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


# breakoutless library
add_library(breakoutless SHARED "")
target_link_libraries(breakoutless PUBLIC SDL2 SDL2_image SDL2_ttf SDL2_mixer)
target_sources(breakoutless 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/games/breakoutless/src/breakoutless_collision.c
  ${CMAKE_CURRENT_LIST_DIR}/games/breakoutless/src/breakoutless_destroy.c
  ${CMAKE_CURRENT_LIST_DIR}/games/breakoutless/src/breakoutless_draw.c 
  ${CMAKE_CURRENT_LIST_DIR}/games/breakoutless/src/breakoutless_init.c 
  ${CMAKE_CURRENT_LIST_DIR}/games/breakoutless/src/breakoutless_input.c 
  ${CMAKE_CURRENT_LIST_DIR}/games/breakoutless/src/breakoutless_update.c
  ${CMAKE_CURRENT_LIST_DIR}/games/breakoutless/src/breakoutless.c
  )
target_include_directories(breakoutless 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_CURRENT_LIST_DIR}/games/breakoutless/include
  )

# tictactoe library
add_library(tictactoe SHARED "")
target_link_libraries(tictactoe PUBLIC SDL2 SDL2_image SDL2_ttf SDL2_mixer)
target_sources(tictactoe 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/games/tictactoe/src/tictactoe_collision.c
  ${CMAKE_CURRENT_LIST_DIR}/games/tictactoe/src/tictactoe_destroy.c
  ${CMAKE_CURRENT_LIST_DIR}/games/tictactoe/src/tictactoe_draw.c 
  ${CMAKE_CURRENT_LIST_DIR}/games/tictactoe/src/tictactoe_init.c 
  ${CMAKE_CURRENT_LIST_DIR}/games/tictactoe/src/tictactoe_input.c 
  ${CMAKE_CURRENT_LIST_DIR}/games/tictactoe/src/tictactoe_update.c
  ${CMAKE_CURRENT_LIST_DIR}/games/tictactoe/src/tictactoe.c
  )
target_include_directories(tictactoe 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_CURRENT_LIST_DIR}/games/tictactoe/include
  )


# game menu
add_executable(game_menu "")
target_link_libraries(game_menu PUBLIC dl)
target_sources(game_menu 
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/src/main.c
  ${CMAKE_CURRENT_LIST_DIR}/src/game_loop.c 
  ${CMAKE_CURRENT_LIST_DIR}/src/game_selection.c
  )
target_include_directories(game_menu
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/include
  )

#------------------------------------------------------------------------------------------------------
# Tests
#------------------------------------------------------------------------------------------------------
# add_test_unit(interface test_interface tests/test_interface.c)
# target_link_libraries(test_interface PUBLIC game)

# add_test_unit(test_sdl test_sdl2 tests/test_sdl2.c)
# target_link_libraries(test_sdl2 PUBLIC game SDL2)

# add_test_unit(test_image test_sdl2_image tests/test_sdl2_image.c)
# target_link_libraries(test_sdl2_image PUBLIC game SDL2 SDL2_image)

# add_test_unit(test_animation test_sdl2_animation tests/test_sdl2_animation.c)
# target_link_libraries(test_sdl2_animation PUBLIC game SDL2 SDL2_image)

# add_test_unit(test_events test_sdl2_events tests/test_sdl2_events.c)
# target_link_libraries(test_sdl2_events PUBLIC game SDL2 SDL2_image)


#------------------------------------------------------------------------------------------------------
# Install
#------------------------------------------------------------------------------------------------------
# install(DIRECTORY include/collection   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# install(TARGETS  util ipc comm database collection json LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

file(COPY games/breakoutless/assets DESTINATION bin/breakoutless)
file(COPY games/spaceship/assets DESTINATION bin/spaceship)