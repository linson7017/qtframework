project(qfmain)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include(files.cmake)
add_library(qfmain SHARED ${QFMAIN_SRCS})
add_definitions(-DMBILOG_STATIC_DEFINE)
target_link_libraries(qfmain mbilog)