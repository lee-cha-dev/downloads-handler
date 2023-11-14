cmake_minimum_required(VERSION 3.26)
project(downloads-handler C)

add_library(downloads-handler-lib downloads_handler.c)

set(CMAKE_C_STANDARD 23)