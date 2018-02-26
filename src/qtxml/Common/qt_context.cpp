#include <Common/qt_context.h>
#include "Utils/Log.h"
#include "Res/R.h"
#include "Common/app_env.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QTextCodec>
#include <QTranslator>
#include <QStyleFactory>
#include "Utils/util.h"

int qt_context::_screenNum = 1;
int qt_context::_primaryScreen =0;
std::vector<sl_Rect*> qt_context::_screenRects;
QTranslator* qt_context::_translator = NULL;
//构造函数
//参数：app QApplication指针
//返回值：无
qt_context::qt_context(QApplication* app)
{
	QDesktopWidget* desktopWidget = app->desktop();
	_screenNum = desktopWidget->screenCount();
	_primaryScreen = desktopWidget->primaryScreen();
	for (int i=0;i<_screenNum;i++)
	{
		QRect rect = desktopWidget->screenGeometry(i);
		sl_Rect* screenRect = new sl_Rect;
		screenRect->x0 = rect.x();
		screenRect->y0 = rect.y();
		screenRect->x1 = rect.x()+rect.width();
		screenRect->y1 = rect.y()+rect.height();
		screenRect->w = rect.width();
		screenRect->h = rect.height();
		_screenRects.push_back(screenRect);
	}
}
//获得屏幕宽度
//参数：i 屏幕索引
//返回值：屏幕宽度
int qt_context::getScreenWidth(int i)
{
	return getScreenRect(i)->w;
}
//获得屏幕高度
//参数：i 屏幕索引
//返回值：屏幕高度
int qt_context::getScreenHeight(int i)
{
	return getScreenRect(i)->h;
}
//设置application编码格式
//参数：coding 编码格式
//返回值：是否设置成功
bool qt_context::setApplicationCoding(const char* coding)
{
	QTextCodec* codec = QTextCodec::codecForName(coding);
	if (codec)
	{
		QTextCodec::setCodecForLocale(codec);
		//QTextCodec::setCodecForTr(codec);
		//QTextCodec::setCodecForCStrings(codec);
		return true;
	}
	else
		return false;
}
//设置application默认语言
//参数：languageStr 语言类型
//返回值：是否设置成功
bool qt_context::setDefaultLanguage(const char* languageStr)
{
	_translator = new QTranslator;
	std::string languageDir = app_env::getLanguageDir();
#if defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__
	char temp[1024];
    languageDir = Gb2312ToUTF8(languageDir);
#endif
	if (_translator->load(app_env::getLanguageFile(languageStr),languageDir.c_str()))
	{
		QApplication::installTranslator(_translator);		
		return true;
	}
	else
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: Load Language File %s failed! Please check if it has existed!\n",app_env::getLanguageFile(languageStr));
		printf(szMsg);
		return false;
	}
}
//设置application样式
//参数：style 样式
//返回值：无
void qt_context::setApplicationStyle(const char* style)
{
	std::string styleRes = R::Instance()->getStyleResource(style);
	if (!styleRes.empty())
	{
        QString qss = styleRes.c_str();
         if (qss.contains("QPalette{background:"))
         {
             int index = qss.indexOf("QPalette{background:");
             QString paletteColor = qss.mid(index+20, 7);
             qApp->setPalette(QPalette(QColor(paletteColor)));
         }  
        qApp->setStyleSheet(qss);
		//qApp->setStyleSheet(styleRes.c_str());
	}
	else
	{
		QApplication::setStyle(QStyleFactory::create(style));
	}
}
//添加动态库添加目录
//参数：path 路径
//返回值：无
void qt_context::addLibraryPath(const char* path)
{
	/***********************加载Qt插件库*******************************/
	QApplication::addLibraryPath(path);
}
//析构函数
qt_context::~qt_context(void)
{
}




