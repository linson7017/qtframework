/*!
 * \file qt_standard.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once

//#define USE_QCUSTOM_PLOT

#include <QIcon>
#include <QHeaderView>
#include <QLineEdit>
#include <QFrame>
#include <QDockWidget>
#ifdef USE_QCUSTOM_PLOT
#include <QCustomPlot.h>
#endif 
#include <map>
#include "Utils/variant.h"
/*!
 * \class qt_standard
 *
 * \brief qt_standard类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class qt_standard
{
public:
	//构造函数
	//参数：无
	//返回值：无
	qt_standard(void);
	//析构函数
	//参数：无
	//返回值：无
	~qt_standard(void);
	//获得标准Icon实例
	//参数：
	//		name:输入
	//返回值：QIcon实例
	static QIcon getStandardIcon(const char* name);
	//获得标准WindowFlags实例
	//参数：
	//		name:输入
	//返回值：WindowFlags实例
	static Qt::WindowFlags getWindowType(const char* name);
	//获得标准ResizeMode实例
	//参数：
	//		name:输入
	//返回值：ResizeMode实例
	static QHeaderView::ResizeMode getHeaderResizeMode(const char* name);
	//获得按键对应的值
	//参数：
	//		key:按键
	//返回值：值
	static const char* getKeySymbol(Qt::Key key);
	//获得辅助键按键对应的值
	//参数：
	//		m:辅助键
	//返回值：值
	static const char* getModifiersSymbol(Qt::KeyboardModifiers m);
	//获得标准Alignment实例
	//参数：
	//		name:输入
	//返回值：Alignment实例
	static Qt::Alignment getAlignment(const char* name);
	//获得标准ToolButtonStyle实例
	//参数：
	//		name:输入
	//返回值：ToolButtonStyle实例
	static Qt::ToolButtonStyle getToolButtonStyle(const char* name);
	//获得标准CheckState实例
	//参数：
	//		name:输入
	//返回值：CheckState实例
	static Qt::CheckState getCheckState(const char* name);
	//获得标准QFont实例
	//参数：
	//		name:输入
	//返回值：QFont实例
	static QFont getStandardFont(const char* name);
	//获得标准EchoMode实例
	//参数：
	//		name:输入
	//返回值：EchoMode实例
	static QLineEdit::EchoMode getEchoMode(const char* name);
	//获得标准TabPosition实例
	//参数：
	//		name:输入
	//返回值：TabPosition实例
	static QTabWidget::TabPosition getTabPosition(const char* name);
	//获得标准Shape实例
	//参数：
	//		name:输入
	//返回值：Shape实例
	static QFrame::Shape getFrameShape(const char* name);
	//获得标准Shadow实例
	//参数：
	//		name:输入
	//返回值：Shadow实例
	static QFrame::Shadow getFrameShadow(const char* name);

    static Qt::ToolBarArea getToolBarArea(const char* name);

    static Qt::DockWidgetArea getDockWidgetArea(const char* name);

    static QDockWidget::DockWidgetFeature getDockWidgetFeature(const char* name);

    static QDockWidget::DockWidgetFeatures getDockWidgetFeatures(const char* name);

    static Qt::Orientation getOrientation(const char* name);

    static QTabWidget::TabShape getTabShape(const char* name);

    static QTabWidget::TabPosition GetTabPosition(const char* name);
#ifdef USE_QCUSTOM_PLOT
	//获得标准Interactions实例
	//参数：
	//		name:输入
	//返回值：Interactions实例
	static QCP::Interactions getQCPInteractions(const char* name);
	//获得标准Interaction实例
	//参数：
	//		name:输入
	//返回值：Interaction实例
	static QCP::Interaction getQCPInteraction(const char* name);
#endif 

#ifndef RECOGNIZE_QPORPERTY_DISABLED
	//获得属性值
	//参数：
	//		name:输入
	//		v: 
	//返回值：Shadow实例
	static bool getProperty(const char* name,QVariant& v);

    static bool exchangProperty(QVariant& property,variant& varient);
#endif


private:
	//重新映射键盘的键值
	//参数：无
	//返回值：无
	static void reMapKeyBoard();

	static std::map<Qt::Key,std::string> _keyMap;
	static std::map<Qt::KeyboardModifiers,std::string> _modifiersMap;
	static bool _bKeyBoardMaped;
};



