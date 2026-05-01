cmake_minimum_required(VERSION 3.5)
project(ServiceFinder_Server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


set(SYSTEM_PATH "../client_app")

# 1. Find Qt6 (or Qt5 - check your version!)
find_package(Qt6 REQUIRED COMPONENTS Core Sql)
find_package(Boost REQUIRED COMPONENTS system json container)
find_package(SQLite3 REQUIRED)

include_directories(${SYSTEM_PATH} ${SQLITE3_INCLUDE_DIRS})


add_executable(ServiceFinder_Server
    main.cpp
    ${SYSTEM_PATH}/System.cpp
    ${SYSTEM_PATH}/Databasemanager.cpp
    ${SYSTEM_PATH}/User.cpp
    ${SYSTEM_PATH}/Provider.cpp
    ${SYSTEM_PATH}/Booking.cpp
    ${SYSTEM_PATH}/notifications.cpp
    Jsonhandler.cpp Jsonhandler.h
)


target_link_libraries(ServiceFinder_Server PRIVATE
    Boost::system
    Boost::json
    ${SQLITE3_LIBRARIES}
    Qt6::Core
    Qt6::Sql
)
