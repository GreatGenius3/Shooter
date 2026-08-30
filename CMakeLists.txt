cmake_minimum_required(VERSION 4.3)
project(Shooter C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Option för att välja mellan shared och static länkning
option(BUILD_SHARED_LIBS "Build with shared libraries (DLLs)" ON)

string(TOLOWER "${CMAKE_BUILD_TYPE}" LOWER_BUILD_TYPE)

# Skriv ut build mode (Debug eller Release)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(BUILD_MODE_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(BUILD_MODE_RELEASE)
endif()

if(BUILD_SHARED_LIBS)
    set(LINK_TYPE "shared")
else()
    set(LINK_TYPE "static")
endif()

# 1. Skapa ett interface-bibliotek som samlar alla inst?llningar
# add_library(Shooter INTERFACE)

set(RAYLIB_INCLUDE_DIR "C:/raylibSDL3_dev/src")
set(SDL_INCLUDE_DIR "C:/sdl_dev/include")
set(FLECS_INCLUDE_DIR "C:/flecs_dev/include")
set(PHYSFS_INCLUDE_DIR "C:/physfs_dev/src")
set(LUAJIT_INCLUDE_DIR "C:/luajit_dev/src")

set(SDL_LIB_DIR     "C:/sdl_dev/lib/${LINK_TYPE}/${LOWER_BUILD_TYPE}")
set(RAYLIB_LIB_DIR     "C:/raylibSDL3_dev/lib/${LINK_TYPE}/${LOWER_BUILD_TYPE}")

set(SDL_BIN_DIR     "C:/sdl_dev/bin/${LOWER_BUILD_TYPE}")
set(RAYLIB_BIN_DIR     "C:/raylibSDL3_dev/bin/${LOWER_BUILD_TYPE}")

# Add the include path for raylib
include_directories(${RAYLIB_INCLUDE_DIR})

# Add the include path for SDL3 (för mixern)
include_directories(${SDL_INCLUDE_DIR})

# Add the include path for flecs
include_directories(${FLECS_INCLUDE_DIR})

# Add the include path for physFS
include_directories(${PHYSFS_INCLUDE_DIR})

# Add the include path for Luajit
include_directories(${LUAJIT_INCLUDE_DIR})

# Add the include path for ECS
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ecs)

link_directories("${SDL_LIB_DIR}")
link_directories("${RAYLIB_LIB_DIR}")

add_executable(Shooter main.c
        TheGame.c
        TheGame.h
        ecs/systems/Movement.c
        ecs/components/Sprite.h)

# Sätt kompilerings-definitions baserat på build mode (Debug eller Release)
# Länka till rätt .dll.a-fil baserat på build-typ (Fixar MinGW-felet)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (BUILD_SHARED_LIBS)
        target_compile_definitions(Shooter PRIVATE BUILD_MODE_DEBUG)
        target_link_libraries(Shooter "C:/raylibSDL3_dev/lib/shared/debug/libraylib.dll.a")
        target_link_libraries(Shooter "C:/sdl_dev/lib/shared/debug/libSDL3.dll.a")
        target_link_libraries(Shooter "C:/sdl_dev/lib/shared/debug/libSDL3_mixer.dll.a")
        target_link_libraries(Shooter "C:/flecs_dev/lib/shared/debug/libflecs.dll.a")
        target_link_libraries(Shooter "C:/physfs_dev/lib/shared/debug/libphysfs.dll.a")
        target_link_libraries(Shooter "C:/luajit_dev/lib/shared/debug/libluajit-5.1.dll.a")
    else()
        target_compile_definitions(Shooter PRIVATE BUILD_MODE_DEBUG)
        target_link_libraries(Shooter "C:/raylibSDL3_dev/lib/static/debug/libraylib.a")
        target_link_libraries(Shooter "C:/sdl_dev/lib/static/debug/libSDL3.a")
        target_link_libraries(Shooter "C:/flecs_dev/lib/static/debug/libflecs_static.a")
        target_link_libraries(Shooter "C:/physfs_dev/lib/static/debug/libphysfs.a")
        target_link_libraries(Shooter "C:/luajit_dev/lib/static/debug/libluajit.a")
        target_link_libraries(Shooter user32 gdi32 winmm imm32 ole32 oleaut32 dbghelp ws2_32 version uuid setupapi opengl32)
    endif()
else()
    if (BUILD_SHARED_LIBS)
        target_compile_definitions(Shooter PRIVATE BUILD_MODE_RELEASE)
        target_link_libraries(Shooter "C:/raylibSDL3_dev/lib/shared/release/libraylib.dll.a")
        target_link_libraries(Shooter "C:/sdl_dev/lib/shared/release/libSDL3.dll.a")
        target_link_libraries(Shooter "C:/sdl_dev/lib/shared/release/libSDL3_mixer.dll.a")
        target_link_libraries(Shooter "C:/flecs_dev/lib/shared/release/libflecs.dll.a")
        target_link_libraries(Shooter "C:/physfs_dev/lib/shared/release/libphysfs.dll.a")
        target_link_libraries(Shooter "C:/luajit_dev/lib/shared/release/libluajit-5.1.dll.a")
    else()
        target_compile_definitions(Shooter PRIVATE BUILD_MODE_RELEASE)
        target_link_libraries(Shooter "C:/raylibSDL3_dev/lib/static/release/libraylib.a")
        target_link_libraries(Shooter "C:/sdl_dev/lib/static/release/libSDL3.a")
        target_link_libraries(Shooter "C:/flecs_dev/lib/static/release/libflecs_static.a")
        target_link_libraries(Shooter "C:/physfs_dev/lib/static/release/libphysfs.a")
        target_link_libraries(Shooter "C:/luajit_dev/lib/static/release/libluajit.a")
        target_link_libraries(Shooter user32 gdi32 winmm imm32 ole32 oleaut32 dbghelp ws2_32 version uuid setupapi opengl32)
    endif()
endif()

# Automatisera kopieringen av rätt .dll till din build-mapp
if(BUILD_SHARED_LIBS)
    add_custom_command(TARGET Shooter POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<$<CONFIG:Debug>:"C:/raylibSDL3_dev/bin/debug/libraylib.dll">
            $<$<CONFIG:Debug>:"C:/sdl_dev/bin/debug/SDL3.dll">
            $<$<CONFIG:Debug>:"C:/sdl_dev/bin/debug/SDL3_mixer.dll">
            $<$<CONFIG:Debug>:"C:/flecs_dev/bin/debug/libflecs.dll">
            $<$<CONFIG:Debug>:"C:/physfs_dev/bin/debug/physfs.dll">
            $<$<CONFIG:Debug>:"C:/luajit_dev/bin/debug/lua51.dll">
            $<$<CONFIG:Release>:"C:/raylibSDL3_dev/bin/release/libraylib.dll">
            $<$<CONFIG:Release>:"C:/sdl_dev/bin/release/SDL3.dll">
            $<$<CONFIG:Release>:"C:/sdl_dev/bin/release/SDL3_mixer.dll">
            $<$<CONFIG:Release>:"C:/flecs_dev/bin/release/libflecs.dll">
            $<$<CONFIG:Release>:"C:/physfs_dev/bin/release/physfs.dll">
            $<$<CONFIG:Release>:"C:/luajit_dev/bin/release/lua51.dll">
            $<TARGET_FILE_DIR:Shooter>
    )
endif()