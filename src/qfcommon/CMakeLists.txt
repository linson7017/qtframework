project(qfcommon)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include(files.cmake)
add_definitions(-DQFMAIN_LIB)
add_library(qfcommon SHARED ${QFCOMMON_SRCS})