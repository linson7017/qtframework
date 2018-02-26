#include <UIs/SplashWindow.h>
#include <QtWidgets>
#include "UIs/Activity.h"
#include "Utils/Log.h"
#include "Utils/util.h"

class sl_Timer : public QThread
{
public:
	sl_Timer(int time):_time(time){}
	void run()
	{
		sleep(_time);
	}
private:
	int _time;
};
//构造函数
//参数：无
//返回值：无
SplashWindow::SplashWindow(void):_bDelay(false),_activeSuccess(false),_relateActivity(NULL),_pMessage(NULL)
{
	//将初始化窗口布局加入到SplashWindow中
	_contentActivity = new Activity;
}
//设置启动窗口的布局内容
//参数：
//		layout_filename:布局文件路径
//返回值：无
void SplashWindow::setContentView(const char* layout_filename)
{
	_contentActivity->setContentView(layout_filename);

	QVBoxLayout* layout = new QVBoxLayout;
	layout->setMargin(0);
	layout->addWidget(_contentActivity);
	setFixedWidth(_contentActivity->getInitWidth()); //窗口大小与布局大小一致
	setFixedHeight(_contentActivity->getInitHeight()); //窗口大小与布局大小一致
	setLayout(layout);

	//在中间显示
	int sw = QApplication::desktop()->width();
	int sh = QApplication::desktop()->height();
	move((sw-width())/2,(sh-height())/2);

}

//析构函数
//参数：无
//返回值：无
SplashWindow::~SplashWindow(void)
{
	//20150925
/*	if (_contentActivity!=NULL)//销毁界面内容
	{
		delete _contentActivity;
		_contentActivity = NULL;
	}
	if (_relateActivity!=NULL) //销毁关联的Activity
	{
		delete _relateActivity;
		_relateActivity = NULL;
    }     */
	if (_delay!=NULL) //销毁关联的Activity
	{
		delete _delay;
		_delay = NULL;
	}

	
}
//设置延时启动时间
//参数：
//		duration:延时启动时间
//返回值：无
//void SplashWindow::setDelay(int duration)
//{
//	_delay = new sl_Timer(duration);
//	QObject::connect(_delay,SIGNAL(finished()),this,SLOT(activeRelatedActivity()));
//	_bDelay = true;
//}

//void SplashWindow::activeRelatedActivity()
//{
//	if (_relateActivity->active())
//	{
//		_activeSuccess = true;
//	}
//	else
//	{
//		char szMsg[1024];
//		sprintf(szMsg, "QtFrameWork ERROR: Start the activity %s failed!\n",_relateActivity->getID());
//		printf(szMsg);
//	}
//	finish(_relateActivity);
//}
//开始启动
//参数：无
//返回值：无
//bool SplashWindow::start()
//{
//	if (_bDelay)
//	{
//		_delay->start();
//	}else
//	{
//		activeRelatedActivity();
//	}
//	return _activeSuccess;
//}

//设置显示信息的文本控件ID
//参数：
//		szMessageID:文本控件ID
//返回值：是否设置成功
bool SplashWindow::setMessageLabelID(const char* szMessageID)
{
	_pMessage = (QLabel*)_contentActivity->getViewByID(szMessageID);
	if (_pMessage)
		return true;
	else
		return false;
}

//设置显示信息
//参数：
//		szMessage:显示信息
//返回值：无
void SplashWindow::showMessage(const char* szMessage)
{
	if (_pMessage)
	{
		_pMessage->setText(szMessage);
		emit messageChanged(szMessage);
		repaint();

		//qApp.processEvents();
	}
	//QSplashScreen::showMessage(szMessage,Qt::AlignLeft|Qt::AlignBottom);
}

void SplashWindow::setBackground(const char* szFileName)
{
	std::string url ;
	getResImageUrl(url,szFileName);
	QPalette palette;
	_contentActivity->setAutoFillBackground(true);
	//根据widget的大小调整背景图片的大小
	palette.setBrush(_contentActivity->backgroundRole(),QBrush(QPixmap(url.c_str())));
	_contentActivity->setPalette(palette);
	_contentActivity->update();
	repaint();
}