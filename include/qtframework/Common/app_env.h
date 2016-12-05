/*!
 * \file app_env.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#ifndef APP_ENV_H
#define APP_ENV_H

#pragma once
#include <string>
#include "Common/qtframework_com.h"
using namespace std;
//主控指针类型
typedef void IGIS_Main_Void;

/*!
 * \class app_env
 *
 * \brief app_env类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class QTFRAMEWORK_EXPORT app_env
{
public:
	//目录类型
	enum DirType
	{
		WORKSPACE,			//qtframework工作目录
		RESOURCE,			//资源目录
		LAYOUT,				//布局资源目录
		LOG,				//日志目录
		STRING_RESOURCE,	//字符资源目录
		STYLE_RESOURCE,		//样式资源目录
		UI_RESOURCE,		//ui资源目录
		UICOMMAND_RESOURCE,	//uicommand资源目录
		MENU_RESOURCE,		//菜单资源目录
		CONFIG_RESOURCE,	//配置资源目录
		IMAGE_RESOURCE,		//图片资源目录
		ICON_RESOURCE,		//icon资源目录
		SHORTCUT_RESOURCE,	//快捷键资源目录
		LANGUAGE_RESOURCE,	//语言资源目录
		TOOLPANEL_RESOURCE
	};
	//语言类型
	enum Language
	{
		CHINESE,		//简体中文
		CHINESE_TW,		//繁体中文
		ENGLISH			//英文
	};
	//构造函数
	//参数：
	//		wDir:qtframework工作路径
	//返回值：无
	app_env(const char *wkDir);
	//析构函数
	~app_env(void);
	//setter
	//指定qtframework所在路径，即res,log,plugins等资源目录所在的目录，如C:/qtframe_ui/app_name/
	//参数：
	//		wDir: 路径
	//返回值：无
	static void setWorkDir(const char* wDir);
	//getter
	//运行程序所在工作目录
	//参数：无
	//返回值：路径
	static const char* getAppDir(){return _appDir.c_str();}
	//qtframework的工作目录
	//参数：无
	//返回值：路径
	static const char* getWorkDir(){return _workDir.c_str();}
	//运行程序的名称
	//参数：无
	//返回值：路径
	static const char* getExeName(){return _exeName.c_str();}
	//资源目录 "res/"
	//参数：无
	//返回值：路径
	static const char* getResDir(){return _resDir.c_str();}
	//layout目录 "res/layout"
	//参数：无
	//返回值：路径
	static const char* getLayoutDir(){return _layoutDir.c_str();}
	//外化字符串目录 "res/strings"
	//参数：无
	//返回值：路径
	static const char* getStringResDir(){return _stringResDir.c_str();}
	//样式目录 "res/styles"
	//参数：无
	//返回值：路径
	static const char* getStyleResDir(){return _styleResDir.c_str();}
	//嵌入式UI资源所在目录 "res/ui"
	//参数：无
	//返回值：路径
	static const char* getUIResDir(){return _uiResDir.c_str();}
	//uicommand所在目录 "res/uicommands"
	//参数：无
	//返回值：路径
	static const char* getUICommandResDir(){return _uicommandResDir.c_str();}
	//Menu资源所在目录 "res/menu"
	//参数：无
	//返回值：路径
	static const char* getMenuResDir(){return _menuResDir.c_str();}
	//配置文件所在目录 "res/config"
	//参数：无
	//返回值：路径
	static const char* getConfigResDir(){return _configResDir.c_str();}
	//图片文件所在目录 "res/images"
	//参数：无
	//返回值：路径
	static const char* getImageResDir(){return _imageResDir.c_str();}
	//icon文件所在目录 "res/icons"
	//参数：无
	//返回值：路径
	static const char* getIconResDir(){return _iconResDir.c_str();}
	//翻译文件所在目录 "res/language"
	//参数：无
	//返回值：路径
	static const char* getLanguageDir(){return _languageDir.c_str();}
	//快捷键文件所在目录 "res/shortcut"
	//参数：无
	//返回值：路径
	static const char* getShortcutDir(){return _shortcutDir.c_str();}
	//log文件所在目录 "log/"
	//参数：无
	//返回值：路径
	static const char* getLogDir(){return _logDir.c_str();}
	//qml文件所在目录 "qml/"
	//参数：无
	//返回值：路径
	static const char* getQmlResDir(){return _qmlResDir.c_str();}

	//获得路径
	//参数：
	//		type:路径类型
	//返回值：路径
	static const char* getDir(DirType type);
	//获得语言文件
	//参数：
	//		language:语言类型
	//返回值：文件
	static const char* getLanguageFile(Language language);
	//获得语言文件
	//参数：
	//	languageStr:语言类型
	//返回值：文件
	static const char* getLanguageFile(const char* languageStr);
	//获取主控指针
	//参数：无
	//返回值：主控指针
	static IGIS_Main_Void* getMainPtr(){return _pMain;}
	//设置主控指针
	//参数：
	//      pMain:主控指针
	//返回值：无
	static void setMainPtr(IGIS_Main_Void* pMain){_pMain = pMain;}

	//设置是否显示toolTip
	//参数：
	//		b:是否显示toolTip
	//返回值：无
	static void setShowTooltipOn(bool b){_bShowTooltip = b;}
	//返回是否显示toolTip
	//参数：无
	//返回值：显示返回true，不显示返回false
	static bool showTooltipOn(){return _bShowTooltip;}

protected:
	//初始化
	//参数：无
	//返回值：无
	static void setup();
private:
	static string _appDir;
	static string _workDir;
	static string _exeName;

	static string _layoutDir;
	static string _resDir;
	static string _stringResDir;
	static string _styleResDir;
	static string _uiResDir;
	static string _uicommandResDir;
	static string _menuResDir;
	static string _configResDir;
	static string _imageResDir;
	static string _iconResDir;
	static string _shortcutDir;
	static string _languageDir;
	static string _logDir;
	static string _toolpanelDir;
	static string _qmlResDir;

	static bool _bShowTooltip;
	static IGIS_Main_Void* _pMain;
};

#endif

