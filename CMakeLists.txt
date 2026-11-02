cmake_minimum_required(VERSION 3.16)
project(ProtonDriveQt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_standard_project_setup()

add_executable(ProtonDriveQt
    src/main.cpp
    src/mainwindow.h
    src/mainwindow.cpp
)

target_link_libraries(ProtonDriveQt PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)