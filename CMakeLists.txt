cmake_minimum_required(VERSION 3.10)
project(BulletHell)

set(CMAKE_CXX_STANDARD 17)

# Укажите путь к Raylib (измените, если распаковали в другое место)
set(RAYLIB_PATH "D:/raylib/raylib/raylib2")

include_directories(${RAYLIB_PATH}/include)
link_directories(${RAYLIB_PATH}/lib)

add_executable(BulletHell src/main.cpp)
target_link_libraries(BulletHell PRIVATE raylib)

# Для MinGW часто требуются дополнительные библиотеки:
target_link_libraries(BulletHell PRIVATE opengl32 gdi32 winmm)

# Скопируйте assets и dll (если используете динамическую библиотеку)
file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)
# Если используете raylib.dll, скопируйте его в папку сборки:
file(COPY ${RAYLIB_PATH}/bin/raylib.dll DESTINATION ${CMAKE_BINARY_DIR})