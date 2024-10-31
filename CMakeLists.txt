cmake_minimum_required(VERSION 3.10)
project(webServer)

set(CMAKE_CXX_STANDARD 14)

# Укажите путь к исходным файлам
add_executable(webServer src/main.cpp)

# Связываем библиотеку X11
find_package(X11 REQUIRED)
target_link_libraries(webServer X11)