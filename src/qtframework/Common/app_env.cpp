#include <Common/app_env.h>
#include "Utils/util.h"
#include "Utils/Log.h"

string app_env::_workDir="";
string app_env::_appDir="";
string app_env::_exeName="";
string app_env::_resDir="";
string app_env::_layoutDir="";
string app_env::_stringResDir="";
string app_env::_styleResDir="";
string app_env::_uiResDir="";
string app_env::_uicommandResDir="";
string app_env::_menuResDir="";
string app_env::_configResDir="";
string app_env::_imageResDir="";
string app_env::_iconResDir="";
string app_env::_languageDir="";
string app_env::_shortcutDir="";
string app_env::_logDir="";
string app_env::_toolpanelDir="";
string app_env::_qmlResDir="";

bool app_env::_bShowTooltip=true;

IQF_Main* app_env::_pMain=NULL;
//构造函数
//参数：wDir qtframework工作路径
//返回值：无
app_env::app_env(const char *wkDir)
{
	std::string path_buffer;
	std::string drive;
	std::string dir;
	std::string fname;
	std::string ext;
	splitpath(wkDir,drive,dir,fname,ext);
	//application路径
	_appDir = dir;
	//执行程序名称
	_exeName = fname;
	setup();
}
//析构函数
app_env::~app_env(void)
{
}
//指定qtframework所在路径，即res,log,plugins等资源目录所在的目录，如C:/qtframe_ui/app_name/
//参数：wDir 路径
//返回值：无
void app_env::setWorkDir(const char* wDir)
{
	if (fileOrPahtExist(wDir))
	{
		_workDir = wDir;
		setup();
	}
	else
	{
		printf("QtFrameWork ERROR: The designated qtframework work directory does not exist! Please check! \n");
	}
	
}
//初始化
//参数：无
//返回值：无
void app_env::setup()
{
	if (_workDir.empty())
	{
		_workDir.append(_appDir+"ui_qtframework/"+_exeName+"/");
	}
	else
	{
		if (_workDir.compare(_workDir.length()-1,1,"/")!=0||
			_workDir.compare(_workDir.length()-2,2,"\\")!=0)
		{
			_workDir.append("/");
		}
	}
	//资源目录
	_resDir.clear();
	_resDir.append(_workDir+"res/");
	//布局目录
	_layoutDir.clear();
	_layoutDir.append(_resDir+"layout/");
	//Log目录
	_logDir.clear();
	_logDir.append(_workDir+"log/");
	//string资源目录
	_stringResDir.clear();
	_stringResDir.append(_resDir+"strings/");
	//style资源目录
	_styleResDir.clear();
	_styleResDir.append(_resDir+"styles/");
	//ui资源目录
	_uiResDir.clear();
	_uiResDir.append(_resDir+"ui/");
	//uicommand资源目录
	_uicommandResDir.clear();
	_uicommandResDir.append(_resDir+"uicommands/");
	//config资源目录
	_configResDir.clear();
	_configResDir.append(_resDir+"config/");
	//menu资源目录
	_menuResDir.clear();
	_menuResDir.append(_resDir+"menu/");
	//image资源目录
	_imageResDir.clear();
	_imageResDir.append(_resDir+"images/");
	//icon资源目录
	_iconResDir.clear();
	_iconResDir.append(_resDir+"icons/");
	//language资源目录
	_languageDir.clear();
	_languageDir.append(_resDir+"language/");
	//快捷键资源目录
	_shortcutDir.clear();
	_shortcutDir.append(_resDir+"shortcut/");

	_toolpanelDir.clear();
	_toolpanelDir.append(_resDir+"panel/");
	_qmlResDir.clear();
	_qmlResDir.append(_resDir+"qml/");

	////日志输出	
	logFileOrPathExist(_workDir.c_str(),Log::LOG_WARN,true);
	//logFileOrPathExist(arg,Log::LOG_ERROR);
	logFileOrPathExist(_layoutDir.c_str(),Log::LOG_WARN,true);
	logFileOrPathExist(_logDir.c_str(),Log::LOG_WARN,true);
	if (!fileOrPahtExist(_resDir.c_str()))
	{
		logFileOrPathExist(_resDir.c_str(),Log::LOG_WARN, true);
	}
	else
	{
		logFileOrPathExist(_uiResDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_uicommandResDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_stringResDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_configResDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_styleResDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_imageResDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_iconResDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_languageDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_menuResDir.c_str(),Log::LOG_WARN, true);
		logFileOrPathExist(_shortcutDir.c_str(),Log::LOG_WARN, true);
	}
}
//获得路径
//参数：type 路径类型
//返回值：路径
const char* app_env::getDir(DirType type)
{
	switch(type)
	{
	case WORKSPACE:
		return _workDir.c_str();
		break;
	case RESOURCE:
		return _resDir.c_str();
		break;
	case LAYOUT:
		return _layoutDir.c_str();
		break;
	case STRING_RESOURCE:
		return _stringResDir.c_str();
		break;
	case STYLE_RESOURCE:
		return _styleResDir.c_str();
		break;
	case UI_RESOURCE:
		return _uiResDir.c_str();
		break;
	case UICOMMAND_RESOURCE:
		return _uicommandResDir.c_str();
		break;
	case MENU_RESOURCE:
		return _menuResDir.c_str();
		break;
	case CONFIG_RESOURCE:
		return _configResDir.c_str();
		break;
	case IMAGE_RESOURCE:
		return _imageResDir.c_str();
		break;
	case ICON_RESOURCE:
		return _iconResDir.c_str();
		break;
	case LANGUAGE_RESOURCE:
		return _languageDir.c_str();
		break;
	case SHORTCUT_RESOURCE:
		return _shortcutDir.c_str();
		break;
	case TOOLPANEL_RESOURCE:
		return _toolpanelDir.c_str();
	default:
		break;
	}
	return "";
}
//获得语言文件
//参数：language 语言类型
//返回值：文件
const char* app_env::getLanguageFile(Language language)
{
	switch(language)
	{
	case CHINESE:
		return "qt_zh_CN.qm";
		break;
	case CHINESE_TW:
		return "qt_zh_TW.qm";
		break;
	case ENGLISH:
		return "";
		break;
	default:
		break;
	}
	return "";
}

//获得语言文件
//参数：languageStr 语言类型
//返回值：文件
const char* app_env::getLanguageFile(const char* languageStr)
{
	std::string tempStr = languageStr;
	if (tempStr.compare("Chinese")==0||tempStr.compare("chinese"))
	{
		return "qt_zh_CN.qm";
	}
	else if (tempStr.compare("Chinese_TW")==0||tempStr.compare("chinese_tw"))
	{
		return "qt_zh_TW.qm";
	}
	else if (tempStr.compare("English")==0||tempStr.compare("english"))
	{
		return "";
	}
	else
		return "";
}
