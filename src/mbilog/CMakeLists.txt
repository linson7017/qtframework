project(mbilog)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_definitions(-DMBILOG_STATIC_DEFINE)
include(files.cmake)
add_library(mbilog STATIC ${CPP_FILES} ${H_FILES}) 