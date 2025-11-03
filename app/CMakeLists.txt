cmake_minimum_required(VERSION 3.21)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(LibraryGui
  main.cpp
  mainwindow.h
  mainwindow.cpp
)

target_link_libraries(LibraryGui PRIVATE Qt6::Widgets LibraryCore)
target_include_directories(LibraryGui PRIVATE ${CMAKE_SOURCE_DIR}/lib)

# скопировать тест-данные рядом с exe
add_custom_command(TARGET LibraryGui POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/books.txt
    $<TARGET_FILE_DIR:LibraryGui>/books.txt
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/readers.txt
    $<TARGET_FILE_DIR:LibraryGui>/readers.txt
)
