project(qtxml)

set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include(files.cmake)
set(CMAKE_AUTOMOC ON )

add_definitions(-DQTXML_LIB)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

add_library(qtxml SHARED ${QTXML_SRCS})
target_link_libraries(qtxml)
qt5_use_modules(qtxml Core Gui Widgets Quick OpenGL NetWork)