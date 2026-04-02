cmake_minimum_required(VERSION 3.16)

project(TUI C)

# Стандарт (по желанию)
set(CMAKE_C_STANDARD 11)

# Флаги компиляции
add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wno-alloc-size
    -Wpedantic
)

# Подключаем include
include_directories(include)

# Собираем все .c файлы
file(GLOB_RECURSE SRC_FILES
    src/*.c
)

# Создаём статическую библиотеку
add_library(logs STATIC ${SRC_FILES})
target_link_libraries(logs PUBLIC m)
# ===== ТЕСТЫ =====

# renderer test
add_executable(test_renderer tests/renderer.c)
target_link_libraries(test_renderer logs)

# color test
add_executable(test_color tests/color.c)
target_link_libraries(test_color logs)
