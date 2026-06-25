cmake_minimum_required(VERSION 3.10)
project(BulletHell)

set(CMAKE_CXX_STANDARD 17)

set(RAYLIB_PATH "D:/raylib/raylib/raylib2")

include_directories(${RAYLIB_PATH}/include)
link_directories(${RAYLIB_PATH}/lib)

add_executable(BulletHell src/main.cpp)
target_link_libraries(BulletHell PRIVATE raylib)

target_link_libraries(BulletHell PRIVATE opengl32 gdi32 winmm)


file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)

file(COPY ${RAYLIB_PATH}/bin/raylib.dll DESTINATION ${CMAKE_BINARY_DIR})