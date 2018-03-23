project(mbilog)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include(files.cmake)
add_library(mbilog STATIC ${CPP_FILES}) 