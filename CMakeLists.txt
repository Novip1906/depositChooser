cmake_minimum_required(VERSION 3.10)
project(DepositChooser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

find_package(cpr REQUIRED)

set(SOURCES
    main.cpp
    App.cpp
    App.h
    models/Deposit.cpp
    models/Deposit.h
    models/User.cpp
    models/User.h
    DepositAssistant.cpp
    DepositAssistant.h
    Menu.cpp
    Menu.h
    server.cpp
    server.h
    UserDepositManager.cpp
    UserDepositManager.h
)

add_executable(app ${SOURCES})

target_link_libraries(app PRIVATE cpr::cpr)

target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})