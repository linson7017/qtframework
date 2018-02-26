#include "TitleBar.h"
#include <QtGui>
#include <QtWidgets>
#include <UIs/sl_ImageWidget.h>
#include <Utils/util.h>
#include <UIs/Activity.h>
#include "Res/R.h"
#include "Utils/Log.h"
#include "Utils/variant.h"
//构造函数
//参数：
//		activity：窗口
//返回值：无
TitleBar::TitleBar(Activity* activity):_titleNode(NULL),_parentActivity(activity),_size(25)
{
	setContentsMargins(0,0,0,0);
	//设置title默认大小
	const variant* v = R::Instance()->getConfigResource("WindowTitleHeight");
	if (v)
	{
		_size = v->getInt();
	}
	setFixedHeight(_size);

	QHBoxLayout* titleLayout = new QHBoxLayout;
	titleLayout->setSpacing(0);
	titleLayout->setMargin(0);
	setLayout(titleLayout);

	_iconImage = new sl_ImageWidget;  //标题栏左上角图标
	_titleText = new QLabel;  //标题栏中间文字
	//设置标题字体
	int textSize=14;
	const variant* vSize = R::Instance()->getConfigResource("TitleTextSize");
	if (vSize)
	{
		textSize = vSize->getInt();
	}
	_titleText->setStyleSheet(QString("font-size:%1px; font-weight:bold; color:white").arg(textSize));

	_minimizeBtn = new QToolButton(this); //标题栏最小化按钮
	_maximizeBtn = new QToolButton(this); //标题栏最大化按钮
	_closeBtn = new QToolButton(this); //标题栏退出按钮

	_maxPix = new QPixmap; 
	_restorePix = new QPixmap;
	_minPix = new QPixmap;
	_closePix = new QPixmap;

	titleLayout->addWidget(_iconImage);
	titleLayout->addWidget(_titleText);
	titleLayout->addWidget(_minimizeBtn);
	titleLayout->addWidget(_maximizeBtn);
	titleLayout->addWidget(_closeBtn);
	titleLayout->setAlignment(_titleText,Qt::AlignCenter);


	connect(_minimizeBtn,SIGNAL(clicked()),this,SLOT(minimizeParentWidget()));
	connect(_maximizeBtn,SIGNAL(clicked()),this,SLOT(maximizeParentWidget()));
	connect(_closeBtn,SIGNAL(clicked()),this,SLOT(closeParentWidget()));
}

//析构函数
//参数：无
//返回值：无
TitleBar::~TitleBar(void)
{
}
//设置最小化按钮是否显示
//参数：
//		b：是否显示
//返回值：无
void TitleBar::setMinimizeButtonVisible(bool b)
{
	_minimizeBtn->setVisible(b);
}
//设置最大化按钮是否显示
//参数：
//		b：是否显示
//返回值：无
void TitleBar::setMaximizeButtonVisible(bool b)
{
	_maximizeBtn->setVisible(b);
}
//设置关闭按钮是否显示
//参数：
//		b：是否显示
//返回值：无
void TitleBar::setCloseButtonVisible(bool b)
{
	_closeBtn->setVisible(b);
}
//设置标题栏文字是否显示
//参数：
//		b：是否显示
//返回值：无
void TitleBar::setTitleTextVisible(bool b)
{
	_titleText->setVisible(b);
}
//设置标题栏icon是否显示
//参数：
//		b：是否显示
//返回值：无
void TitleBar::setIconVisible(bool b)
{
	_iconImage->setVisible(b);
}
//设置标题栏高度
//参数：
//		size：高度
//返回值：无
void TitleBar::setTitleSize(int size)
{
	_size = size;
	setFixedHeight(_size);
}
//鼠标移动事件
//参数：
//		event:事件
//返回值：无
void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
	if (_dragging)
	{
		int dx = event->globalX()-_preMouseX;
		int dy = event->globalY()-_preMouseY;
		_parentActivity->move(_pwPreX+dx,_pwPreY+dy);
	}
}
//鼠标按下事件
//参数：
//		event:事件
//返回值：无
void TitleBar::mousePressEvent(QMouseEvent *event)
{
	//只有当窗口显示状态为正常状态时才可以拖动
	if ((event->button() & Qt::LeftButton)&&(_parentActivity->showMode()==Activity::NORMAL))
	{
		_dragging = true;
		_preMouseX = event->globalX();
		_preMouseY = event->globalY();
		_pwPreX = _parentActivity->pos().x();
		_pwPreY = _parentActivity->pos().y();
	}
}
//鼠标松开事件
//参数：
//		event:事件
//返回值：无
void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
	if ((event->button() & Qt::LeftButton))
	{
		_dragging = false;
	}
}
//鼠标双击事件
//参数：
//		event:事件
//返回值：无
void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
	maximizeParentWidget();
}
//最小化窗口
//参数：无
//返回值：无
void TitleBar::minimizeParentWidget()
{
	//_parentActivity->showMinimized();
	//_parentActivity->setShowMode(Activity::MINIMIZED);
	emit minimizeButtonClicked();
}
//最大化窗口
//参数：无
//返回值：无
void TitleBar::maximizeParentWidget()
{
	if (_parentActivity->showMode()==Activity::MAXIMIZED)
	{
		//_parentActivity->showNormal();
		//_parentActivity->setShowMode(Activity::NORMAL);
		updateMaximizeButtonImage();
		_maximizeBtn->setIcon(*_maxPix);
	}
	else
	{
		//_parentActivity->showMaximized();
		//_parentActivity->setShowMode(Activity::MAXIMIZED);
		updateMaximizeButtonImage();
		_maximizeBtn->setIcon(*_restorePix);
		//_parentActivity->move(0,0);
	}
	emit maximizeButtonClicked();
}

//关闭窗口
//参数：无
//返回值：无
void TitleBar::closeParentWidget()
{
	//_parentActivity->close();
	emit closeButtonClicked();
}
//获得图片路径
//参数：
//		pix:位图
//		url:图片路径
//返回值：无
void TitleBar::getPixelImage(QPixmap* pix,const char* url)
{
	std::string filename;
	std::string tempStr = url;
	if (tempStr.find("@image/")!=std::string::npos)
	{
		getResImageUrl(filename,url);
	}
	else if (tempStr.find("@icon/")!=std::string::npos)
	{
		getResIconUrl(filename,url);
	}

	if (!filename.empty())
	{
		if (!pix->load(filename.c_str()))
		{
			char szMsg[1024];
			sprintf(szMsg, "QtFrameWork ERROR: Load pixmap %s failed\n",filename.c_str());
			printf(szMsg);
		}
	}else
	{
		if (!pix->load(url))
		{
			char szMsg[1024];
			sprintf(szMsg, "QtFrameWork ERROR: Load pixmap %s failed\n",url);
			printf(szMsg);
		}
	}
}
//设置最小化按钮对应的图片路径
//参数：
//		url：图片路径
//返回值：无
void TitleBar::setMinimizeButtonImage(const char* url)
{
	getPixelImage(_minPix,url);
	_minimizeBtn->setIcon(*_minPix);
}
//设置最大化按钮对应的图片路径
//参数：
//		url：图片路径
//返回值：无
void TitleBar::setMaximizeButtonImage(const char* url)
{
	getPixelImage(_maxPix,url);
	updateMaximizeButtonImage();
}
//更新最大化按钮图片
//参数：无
//返回值：无
void TitleBar::updateMaximizeButtonImage()
{
	if (_parentActivity&&_parentActivity->showMode()==Activity::MAXIMIZED)
	{
		_maximizeBtn->setIcon(*_restorePix);
	}
	else
	{
		_maximizeBtn->setIcon(*_maxPix);
	}
}
//设置恢复按钮对应的图片路径
//参数：
//		url：图片路径
//返回值：无
void TitleBar::setRestoreButtonImage(const char* url)
{
	getPixelImage(_restorePix,url);
}
//设置关闭按钮对应的图片路径
//参数：
//		url：图片路径
//返回值：无
void TitleBar::setCloseButtonImage(const char* url)
{
	getPixelImage(_closePix,url);
	_closeBtn->setIcon(*_closePix);
}
//设置icon图片路径
//参数：
//		url：图片路径
//返回值：无
void TitleBar::setIconImage(const char* url)
{
	_iconImage->setImage(url);
}
//设置标题栏文字
//参数：
//		text：标题栏文字
//返回值：无
void TitleBar::setTitleText(const char* text)
{
	_titleText->setText(text);
}