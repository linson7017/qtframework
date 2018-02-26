project(jsoncpp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include(files.cmake)
add_library(jsoncpp SHARED ${JSONCPP_SRCS})