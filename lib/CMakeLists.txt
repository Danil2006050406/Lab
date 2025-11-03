cmake_minimum_required(VERSION 3.21)

option(BUILD_SHARED_LIBS "Build LibraryCore as shared library" OFF)

add_library(LibraryCore
  Book.cpp       Book.h
  User.cpp       User.h
  Loan.cpp       Loan.h
  Library.cpp    Library.h
  LibraryUtils.cpp LibraryUtils.h
)

target_compile_features(LibraryCore PUBLIC cxx_std_17)
target_include_directories(LibraryCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
