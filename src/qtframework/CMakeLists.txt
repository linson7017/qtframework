project(qtframework)

set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include(files.cmake)
set(CMAKE_AUTOMOC ON)

add_definitions(-DQTFRAMEWORK_LIB)

add_library(qtframework SHARED ${QTFRAMEWORK_SRCS})
target_link_libraries(qtframework iconv libxml2)
qt5_use_modules(qtframework Core Gui Widgets Quick OpenGL NetWork)