set(QTXML_INCLUDE_DIR
${CMAKE_CURRENT_SOURCE_DIR}/Common
${CMAKE_CURRENT_SOURCE_DIR}/Res
${CMAKE_CURRENT_SOURCE_DIR}/Uicreator
${CMAKE_CURRENT_SOURCE_DIR}/UIs
${CMAKE_CURRENT_SOURCE_DIR}/Utils
)

set(QTXML_EXPROT_INCLUDE_DIR
${QF_INCLUDE_DIR}/qtxml
)

set(Common_Srcs
Common/app_env.cpp
Common/qt_context.cpp
${QTXML_EXPROT_INCLUDE_DIR}/Common/app_env.h
${QTXML_EXPROT_INCLUDE_DIR}/Common/qt_context.h
${QTXML_EXPROT_INCLUDE_DIR}/Common/qtxml_com.h
)

set(Res_Srcs
Res/R.cpp
Res/res_config.cpp
Res/res_shortcut.cpp
Res/res_string.cpp
Res/res_style.cpp
Res/res_command.cpp
Res/xml_res_base.cpp
Res/xml_ui_base.h


Res/res_config.h
Res/res_shortcut.h
Res/res_string.h
Res/res_style.h
Res/res_command.h
Res/xml_res_base.h
Res/xml_ui_base.cpp

${QTXML_EXPROT_INCLUDE_DIR}/Res/R.h
)

set(Uicreator_Srcs
Uicreator/event_handler.cpp
Uicreator/qt_command_executor.cpp
Uicreator/qt_ui_assembler.cpp
Uicreator/qt_ui_creater.cpp
Uicreator/qt_uicommand_executor.cpp
Uicreator/ui_node.cpp
Uicreator/xml_node.cpp
Uicreator/xml_ui_paser.cpp
Uicreator/event_handler.h
Uicreator/qt_command_executor.h
Uicreator/qt_ui_assembler.h
Uicreator/qt_ui_creater.h
Uicreator/qt_uicommand_executor.h
Uicreator/ui_node.h
Uicreator/xml_node.h
Uicreator/xml_ui_paser.h
)

set(UIs_Srcs
UIs/Activity.cpp
UIs/AsynchronousAction.cpp
UIs/ClickListenser.cpp
UIs/CustomActivity.cpp
UIs/GraphicButton.cpp
UIs/GraphicButtonGroup.cpp
UIs/Listener.cpp
UIs/sl_AnimationWidget.cpp
UIs/sl_Button.cpp
UIs/sl_ImageWidget.cpp
UIs/sl_MapContainer.cpp
UIs/sl_MutexButtonBox.cpp
UIs/sl_ToolPanel.cpp
UIs/sl_VectorContainer.cpp
UIs/SplashWindow.cpp
UIs/TitleBar.cpp
UIs/TriStateBtnClickListener.cpp
${QTXML_EXPROT_INCLUDE_DIR}/UIs/Activity.h
UIs/AsynchronousAction.h
${QTXML_EXPROT_INCLUDE_DIR}/UIs/ClickListenser.h
${QTXML_EXPROT_INCLUDE_DIR}/UIs/CustomActivity.h
UIs/GraphicButton.h
UIs/GraphicButtonGroup.h
${QTXML_EXPROT_INCLUDE_DIR}/UIs/Listener.h
${QTXML_EXPROT_INCLUDE_DIR}/UIs/sl_AnimationWidget.h
${QTXML_EXPROT_INCLUDE_DIR}/UIs/sl_Button.h
${QTXML_EXPROT_INCLUDE_DIR}/UIs/sl_ImageWidget.h
${QTXML_EXPROT_INCLUDE_DIR}/UIs/sl_MapContainer.h
${QTXML_EXPROT_INCLUDE_DIR}/UIs/sl_MutexButtonBox.h
UIs/sl_ToolPanel.h
${QTXML_EXPROT_INCLUDE_DIR}/UIs/sl_VectorContainer.h
${QTXML_EXPROT_INCLUDE_DIR}/UIs/SplashWindow.h
UIs/TitleBar.h
UIs/TriStateBtnClickListener.h
${QTXML_EXPROT_INCLUDE_DIR}/UIs/QF_Plugin.h
)

set(Utils_Srcs
Utils/Log.cpp
Utils/PluginFactory.cpp
Utils/QObjectFactory.cpp
Utils/qt_standard.cpp
Utils/util.cpp
Utils/variant.cpp
Utils/xml_util.cpp
Utils/sys_util.cpp
Utils/tinyxml2.cpp


${QTXML_EXPROT_INCLUDE_DIR}/Utils/Log.h
${QTXML_EXPROT_INCLUDE_DIR}/Utils/PluginFactory.h
${QTXML_EXPROT_INCLUDE_DIR}/Utils/QObjectFactory.h
Utils/qt_standard.h
Utils/util.h
${QTXML_EXPROT_INCLUDE_DIR}/Utils/variant.h
${QTXML_EXPROT_INCLUDE_DIR}/Utils/xml_util.h
Utils/sys_util.h
Utils/tinyxml2.h
)

set(QTXML_SRCS 
${Common_Srcs}
${Res_Srcs}
${Uicreator_Srcs}
${UIs_Srcs}
${Utils_Srcs}
)

source_group("Common" FILES ${Common_Srcs})
source_group("Res" FILES ${Res_Srcs})
source_group("Uicreator" FILES ${Uicreator_Srcs})
source_group("UIs" FILES ${UIs_Srcs})
source_group("Utils" FILES ${Utils_Srcs})
include_directories(
${CMAKE_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/include/qtxml
${CMAKE_SOURCE_DIR}/include/qfmain
)
link_directories(${QF_EXTERN_DIR}/lib)


