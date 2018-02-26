
#generate config files
set(QF_SOURCE_DIRECTORY ${CMAKE_SOURCE_DIR}) 
set(TEMPLATE_DIR ${CMAKE_SOURCE_DIR}/CMake/templates)
configure_file(
  ${TEMPLATE_DIR}/QtFramework-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/QtFramework-config.cmake
  @ONLY
)
configure_file(
  ${TEMPLATE_DIR}/FindlibQtframework.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/FindlibQtframework.cmake
  @ONLY
)
configure_file(
  ${TEMPLATE_DIR}/QfMain-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/QfMain-config.cmake
  @ONLY
)
configure_file(
  ${TEMPLATE_DIR}/FindlibQfMain.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/FindlibQfMain.cmake
  @ONLY
)
configure_file(
  ${TEMPLATE_DIR}/QfCommon-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/QfCommon-config.cmake
  @ONLY
)
configure_file(
  ${TEMPLATE_DIR}/FindlibQfCommon.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/FindlibQfCommon.cmake
  @ONLY
)
configure_file(
  ${TEMPLATE_DIR}/QtXML-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/QtXML-config.cmake
  @ONLY
)
configure_file(
  ${TEMPLATE_DIR}/FindlibQtXML.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/FindlibQtXML.cmake
  @ONLY
)