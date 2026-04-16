cmake_minimum_required(VERSION 3.10)

project(SRB)

find_package(SDL2 REQUIRED)
find_package(SDL2_MIXER REQUIRED)

set(INTERFACE sdl2)
set(INTERFACE_SRCS
    src/interface/${INTERFACE}/mixer_sound.c
    src/interface/${INTERFACE}/i_main.c
    src/interface/${INTERFACE}/i_system.c
    src/interface/${INTERFACE}/i_video.c
)

set(COMMON_SRCS
    src/d_main.c
    src/states.c
    src/m_menu.c
    src/g_game.c
    src/v_video.c
)

if (CMAKE_SYSTEM_NAME MATCHES Linux)
    add_definitions(-DLINUX)
elseif (CMAKE_SYSTEM_NAME MATCHES Windows)
    add_definitions(-DWINDOWS)
elseif (CMAKE_SYSTEM_NAME MATCHES Windows)
    add_definitions(-DMACOS)
endif()

add_executable(SRB ${INTERFACE_SRCS} ${COMMON_SRCS})
target_include_directories(SRB PRIVATE ${SDL2_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})
target_link_libraries(SRB PRIVATE SDL2 SDL2_mixer)
