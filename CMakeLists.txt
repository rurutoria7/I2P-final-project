cmake_minimum_required(VERSION 3.24)
project(Allegro5Template)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig)

pkg_check_modules(ALLEGRO5 REQUIRED allegro-5 allegro_main-5 allegro_font-5 allegro_dialog-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5)

include_directories(Src)

file(COPY Assets/Music DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Allegro5Template
        Src/game.c
        Src/game.h
        Src/ghost.c
        Src/ghost.h
        Src/ghost_red_move_script.c
        Src/main.c
        Src/map.c
        Src/map.h
        Src/pacman_obj.c
        Src/pacman_obj.h
        Src/scene_game.c
        Src/scene_game.h
        Src/scene_menu.c
        Src/scene_menu.h
        Src/scene_menu_object.c
        Src/scene_menu_object.h
        Src/scene_settings.c
        Src/scene_settings.h
        Src/shared.c
        Src/shared.h
        Src/utility.c
        Src/utility.h)

target_include_directories(Allegro5Template PUBLIC ${ALLEGRO5_INCLUDE_DIRS})
target_compile_options(Allegro5Template PUBLIC ${ALLEGRO5_CFLAGS_OTHER})
target_link_libraries(Allegro5Template ${ALLEGRO5_LIBRARIES})
target_link_directories(Allegro5Template PUBLIC ${ALLEGRO5_LIBRARY_DIRS})
