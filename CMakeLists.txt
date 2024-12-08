cmake_minimum_required(VERSION 3.16)
project(Lab3 VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(SQLITE_SOURCES "C:/Users/Viktor/Labs/Libs/sqlite-amalgamation-3470100/sqlite3.c")
set(SQLITE_INCLUDE_DIR "C:/Users/Viktor/Labs/Libs/sqlite-amalgamation-3470100")

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

include_directories(${SQLITE_INCLUDE_DIR})

include_directories("C:/Program Files/OpenSSL-Win64/include")

add_executable(Lab3
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    database.h
    database.cpp
    crypto.h crypto.cpp
    password_manager.h
    password_manager.cpp
    ${SQLITE_SOURCES}
)

message(STATUS "SQLite source file: ${SQLITE_SOURCES}")
message(STATUS "SQLite include directory: ${SQLITE_INCLUDE_DIR}")


target_link_libraries(Lab3 PRIVATE
    Qt6::Widgets
    Qt6::Sql
    debug "C:/Program Files/OpenSSL-Win64/lib/VC/x64/MDd/libcrypto.lib"
    debug "C:/Program Files/OpenSSL-Win64/lib/VC/x64/MDd/libssl.lib"
    optimized "C:/Program Files/OpenSSL-Win64/lib/VC/x64/MD/libcrypto.lib"
    optimized "C:/Program Files/OpenSSL-Win64/lib/VC/x64/MD/libssl.lib"
)
