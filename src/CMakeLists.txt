set(QTFRAMEWORK_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/qtframework)
set(QFMAIN_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/qfmain)
#set(QFCOMMON_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/qfcommon)
set(QTXML_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/qtxml)
set(MBILOG_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/mbilog)

#add_subdirectory(qtframework)
add_subdirectory(qfmain)
#add_subdirectory(qfcommon)
add_subdirectory(qtxml)
add_subdirectory(jsoncpp)
add_subdirectory(mbilog)

