set(QTFRAMEWORK_INCLUDE_DIR
${CMAKE_CURRENT_SOURCE_DIR}/Common
${CMAKE_CURRENT_SOURCE_DIR}/Res
${CMAKE_CURRENT_SOURCE_DIR}/Uicreator
${CMAKE_CURRENT_SOURCE_DIR}/UIs
${CMAKE_CURRENT_SOURCE_DIR}/Utils
)

set(QTFRAMEWORK_EXPROT_INCLUDE_DIR
${QF_INCLUDE_DIR}/qtframework
)

set(Common_Srcs
Common/app_env.cpp
Common/qt_context.cpp
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/Common/app_env.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/Common/qt_context.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/Common/qtframework_com.h
)

set(Res_Srcs
Res/R.cpp
Res/res_config.cpp
Res/res_menu.cpp
Res/res_shortcut.cpp
Res/res_string.cpp
Res/res_style.cpp
Res/res_toolpanel.cpp
Res/res_ui.cpp
Res/res_uicommand.cpp
Res/res_config.h
Res/res_menu.h
Res/res_shortcut.h
Res/res_string.h
Res/res_style.h
Res/res_toolpanel.h
Res/res_ui.h
Res/res_uicommand.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/Res/R.h
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
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/UIs/Activity.h
UIs/AsynchronousAction.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/UIs/ClickListenser.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/UIs/CustomActivity.h
UIs/GraphicButton.h
UIs/GraphicButtonGroup.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/UIs/Listener.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/UIs/sl_AnimationWidget.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/UIs/sl_Button.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/UIs/sl_ImageWidget.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/UIs/sl_MapContainer.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/UIs/sl_MutexButtonBox.h
UIs/sl_ToolPanel.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/UIs/sl_VectorContainer.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/UIs/SplashWindow.h
UIs/TitleBar.h
UIs/TriStateBtnClickListener.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/UIs/QF_Plugin.h
)

set(Utils_Srcs
Utils/Log.cpp
Utils/PluginFactory.cpp
Utils/QObjectFactory.cpp
Utils/qt_standard.cpp
Utils/util.cpp
Utils/variant.cpp
Utils/xml_util.cpp
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/Utils/Log.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/Utils/PluginFactory.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/Utils/QObjectFactory.h
Utils/qt_standard.h
Utils/util.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/Utils/variant.h
${QTFRAMEWORK_EXPROT_INCLUDE_DIR}/Utils/xml_util.h
)

set(QTFRAMEWORK_SRCS 
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
${CMAKE_SOURCE_DIR}/include/qtframework
${QF_EXTERN_DIR}/include/iconv
${QF_EXTERN_DIR}/include/libxml2
)
link_directories(${QF_EXTERN_DIR}/lib)


