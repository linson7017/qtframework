#include <UIs/CustomActivity.h>
#include "UIs/TitleBar.h"
#include <QtGui>
#include <QtWidgets>
#include "Uicreator/ui_node.h"
#include "Res/R.h"
#include "Utils/util.h"
#include "Utils/variant.h"
#include "Common/qt_context.h"
#include "UIs/SplashWindow.h"
////构造函数
//参数：无
//返回值：无
CustomActivity::CustomActivity(void):_titleBar(NULL),_mouseArea(Other),_dragging(false),
	_curMouseX(0),_curMouseY(0),_preX(0),_preY(0),_preShowMode(Activity::NORMAL)
{
}
////构造函数
//参数：无
//返回值：无
CustomActivity::CustomActivity(SplashWindow* pSplashWindow):Activity(pSplashWindow),_titleBar(NULL),_mouseArea(Other),_dragging(false),
	_curMouseX(0),_curMouseY(0),_preX(0),_preY(0),_preShowMode(Activity::NORMAL)
{
}
//绘制事件
//参数：
//		event:事件
//返回值：无
void CustomActivity::paintEvent(QPaintEvent *)
{ 
	//窗口边框为圆角
	/*QPainter p(this);
	p.drawRoundedRect(0,0,width()-1,height()-1,5,5);*/
}

//析构函数
//参数：无
//返回值：无
CustomActivity::~CustomActivity(void)
{
}
//窗口创建之前的行为
//参数：无
//返回值：成功返回true,否则返回false
bool CustomActivity::actionBeforeCreated()
{
	//在创建之前设置window样式,第一个代表去掉默对话框框架，第二个参数代表可以允许任务栏按钮右键菜单，第三个参数代表允许最小化与还原
	setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint|Qt::WindowMinimizeButtonHint);
	setMouseTracking(true);  //鼠标不被按下时也可以接收鼠标移动事件
	
	//设置一个计时器来更新鼠标在不同区域的状态
	_timer = new QTimer;
	connect(_timer,SIGNAL(timeout()),this,SLOT(regionMouse()));
	

	QPalette palette;
	setAutoFillBackground(true);
	palette.setColor(QPalette::Background,QColor(51,107,252));
	setPalette(palette);
	return true;
}
//窗口创建之后的行为
//参数：无
//返回值：成功返回true,否则返回false
bool CustomActivity::actionAfterActived()
{
	//40ms更新一次

	return true;
}
//选中事件
//参数：
//		event:事件
//返回值：无
void CustomActivity::focusInEvent(QFocusEvent *event)
{
    Activity::focusInEvent(event);
}
//脱离焦点事件
//参数：
//		event:事件
//返回值：无
void CustomActivity::focusOutEvent(QFocusEvent * event)
{
   // _timer->stop();
    Activity::focusOutEvent(event);
}
//进入窗口事件
//参数：
//		event:事件
//返回值：无
void CustomActivity::enterEvent(QEvent *event)
{
	_timer->start(100);
    Activity::enterEvent(event);
}

void CustomActivity::installContent()
{
	//总布局
	QVBoxLayout* frameLayout = new QVBoxLayout;
	int borderWidth = 4; //设置Activity外围边框的宽度
	if (R::Instance()->getConfigResource("CustomActivityBorderWidth"))
	{
		borderWidth = R::Instance()->getConfigResource("CustomActivityBorderWidth")->value<int>();
	}
	frameLayout->setContentsMargins(borderWidth,borderWidth,borderWidth,borderWidth); //这里的margin一定要比下面窗口的四个控制大小的区域大一些，否则鼠标变换过程中会出问题
    frameLayout->setSpacing(4);
	setLayout(frameLayout);
	//窗口标题栏
	for (int i=0;i<_content->getChildNum();i++)
	{
		ui_node* node = _content->getChild(i);
		if (strcmp(node->getName(),"TitleBar")==0)
		{
			_titleBar = (TitleBar*)node->getObject();
			_titleBar->setParentActivity(this);
          		//设置标题栏项目是否可见
			if (node->hasAttribute("minimizeButtonHint"))
			{
				_titleBar->setMinimizeButtonVisible(STR_TO_BOOL(node->getAttribute("minimizeButtonHint")));
			}
			if (node->hasAttribute("maximizeButtonHint"))
			{
				_titleBar->setMaximizeButtonVisible(STR_TO_BOOL(node->getAttribute("maximizeButtonHint")));
			}
			if (node->hasAttribute("closeButtonHint"))
			{
				_titleBar->setCloseButtonVisible(STR_TO_BOOL(node->getAttribute("closeButtonHint")));
			}
			if (node->hasAttribute("titleTextHint"))
			{
                _titleBar->setTitleText(" ");
			}
			if (node->hasAttribute("iconHint"))
			{
				_titleBar->setIconVisible(STR_TO_BOOL(node->getAttribute("iconHint")));
			}
			if (node->hasAttribute("minmaxButtonHint"))
			{
				_titleBar->setMinimizeButtonVisible(STR_TO_BOOL(node->getAttribute("minmaxButtonHint")));
				_titleBar->setMaximizeButtonVisible(STR_TO_BOOL(node->getAttribute("minmaxButtonHint")));
			}
			//复原按钮图片
			if (node->hasAttribute("restoreButtonImage"))
			{
				_titleBar->setRestoreButtonImage(node->getAttribute("restoreButtonImage"));
			}
			else
			{
				_titleBar->setRestoreButtonImage("@icon/restore_win.png");
			}
			//最小化按钮图片
			if (node->hasAttribute("minimizeButtonImage"))
			{
				_titleBar->setMinimizeButtonImage(node->getAttribute("minimizeButtonImage"));
			}
			else
			{
				_titleBar->setMinimizeButtonImage("@icon/min_win.png");
			}
			//最大化按钮图片
			if (node->hasAttribute("maximizeButtonImage"))
			{
				_titleBar->setMaximizeButtonImage(node->getAttribute("maximizeButtonImage"));
			}
			else
			{
				_titleBar->setMaximizeButtonImage("@icon/max_win.png");
			}
			//退出按钮图片
			if (node->hasAttribute("closeButtonImage"))
			{
				_titleBar->setCloseButtonImage(node->getAttribute("closeButtonImage"));
			}
			else
			{
				_titleBar->setCloseButtonImage("@icon/quit.png");
			}
			//标题文字
			if (node->hasAttribute("titleText"))
			{
				_titleBar->setTitleText(node->getAttribute("titleText"));
			}
			else
			{
                _titleBar->setTitleText(" ");
			}
			if (node->hasAttribute("size"))
			{
				_titleBar->setTitleSize(STR_TO_INT(node->getAttribute("size")));
			}
			else
			{
				_titleBar->setTitleSize(25);
			}
			if (node->hasAttribute("iconImage"))
			{
				_titleBar->setIconImage(node->getAttribute("iconImage"));
			}
			else
			{
				_titleBar->setIconImage("@icon/default_icon.png");
			}
			_titleBar->setTitleNode(node);
			break;
		}
	}
	//如果没有定义标题栏生成默认的标题栏
	if (!_titleBar)
	{
		_titleBar = new TitleBar;
		_titleBar->setParentActivity(this);
		_titleBar->setMinimizeButtonImage("@icon/min_win.png");
		_titleBar->setMaximizeButtonImage("@icon/max_win.png");
		_titleBar->setRestoreButtonImage("@icon/restore_win.png");
		_titleBar->setCloseButtonImage("@icon/quit.png");
		_titleBar->setIconImage("@icon/default_icon.png");
		_titleBar->setTitleText("");
	}
	//与标题栏关联事件
	relateTitleBar();
	//将标题栏添加进布局
	frameLayout->addWidget(_titleBar);

	//将内容添加进去，为了防止内容都为背景色，加一个Widget
	if (_content->getType()==ui_node::LAYOUT)
	{
		QLayout* contentLayout = (QLayout*)_content->getObject();
        contentLayout->setMargin(4);
		QWidget* widget = new QWidget;
		widget->setLayout(contentLayout);
		widget->setAutoFillBackground(true);
		//设置背景颜色
		const variant* v = R::Instance()->getConfigResource("BackgroundColor");
		if (v)
		{
			QPalette palette;
			palette.setColor(QPalette::Background,QColor(QString(v->getString())));
			widget->setPalette(palette);
		}else
		{
			QPalette palette;
			palette.setColor(QPalette::Background,QColor(240,240,240));
			widget->setPalette(palette);
		}
		widget->setParent(this);
		frameLayout->addWidget(widget);
	}
	else if (_content->getType()==ui_node::WIDGET)
	{
		frameLayout->addWidget((QWidget*)_content->getObject());
	}
}

//重定位鼠标
//参数：无
//返回值：无
void CustomActivity::regionMouse()
{
	QPoint p = cursor().pos();
    QRect rec = geometry();
	int x = p.x() - rec.x();
	int y = p.y() - rec.y();
	int w = rec.width();
	int h = rec.height();

	int resizeMargin = 4;
	//这里设为2，要比窗口的contents_margin小一点，否则鼠标进入窗口内部控件无法将响应鼠标移动消息，会导致鼠标变化出错
	if ((x>resizeMargin&&x<w-resizeMargin&&y>resizeMargin&&y<h-resizeMargin)||(x<0|x>w|y<0|y>h))
	{
		_mouseArea = Other;
		setCursor(Qt::ArrowCursor);
		return;
	}
	else if (x<=resizeMargin&&x>=0&&y<=resizeMargin&&y>=0)
	{
		_mouseArea = TopLeft;
		setCursor(Qt::SizeFDiagCursor);
		return;
	}
	else if (x>=w-resizeMargin&&x<=w&&y<=resizeMargin&&y>=0)
	{
		_mouseArea = TopRight;
		setCursor(Qt::SizeBDiagCursor);
		return;
	}
	else if (x<=resizeMargin&&x>=0&&y>=h-resizeMargin&&y<=h)
	{
		_mouseArea = BottomLeft;
		setCursor(Qt::SizeBDiagCursor);
		return;
	}
	else if (x>=w-resizeMargin&&x<=w&&y>=h-resizeMargin&&y<=h)
	{
		_mouseArea = BottomRight;
		setCursor(Qt::SizeFDiagCursor);
		return;
	}
	else if (x>resizeMargin&&x<w-resizeMargin&&y<=resizeMargin&&y>=0)
	{
		_mouseArea = Top;
		setCursor(Qt::SizeVerCursor);
		return;
	}
	else if (x>resizeMargin&&x<w-resizeMargin&&y>=h-resizeMargin&&y<=h)
	{
		_mouseArea = Bottom;
		setCursor(Qt::SizeVerCursor);
		return;
	}
	else if (x<=resizeMargin&&x>=0&&y>resizeMargin&&y<h-resizeMargin)
	{
		_mouseArea = Left;
		setCursor(Qt::SizeHorCursor);
		return;
	}
	else if (x>=w-resizeMargin&&x<=w&&y>resizeMargin&&y<h-resizeMargin)
	{
		_mouseArea = Right;
		setCursor(Qt::SizeHorCursor);
		return;
	}
	else
	{
		_mouseArea = Other;
		setCursor(Qt::ArrowCursor);
		return;
	}
	
}

//离开窗口事件
//参数：
//		event:事件
//返回值：无
void CustomActivity::leaveEvent(QEvent *event)
{
	
	setCursor(Qt::ArrowCursor);
	_timer->stop();
	Activity::leaveEvent(event);
}
//设置显示模式
//参数：
//		mode:显示模式
//返回值：资源
void CustomActivity::setShowMode(ShowMode mode)
{

	Activity::setShowMode(mode);
	if (_bPrepared)
	{
		_titleBar->updateMaximizeButtonImage();
	}
}
//鼠标移动事件
//参数：
//		event:事件
//返回值：无
void CustomActivity::mouseMoveEvent(QMouseEvent *event)
{
	if (showMode()!=Activity::NORMAL)
	{
		setCursor(Qt::ArrowCursor);
		Activity::mouseMoveEvent(event);
		return;
	}
	_curMouseX = event->globalX();
	_curMouseY = event->globalY();
	int gx = event->globalX();
	int gy = event->globalY();
	if (_dragging)
	{
		QRect g = geometry();
		switch (_mouseArea)
		{
		case Left:
			g.setLeft(gx);
			break;
		case Right:
			g.setRight(gx);
			break;
		case Bottom:
			g.setBottom(gy);
			break;
		case Top:
			g.setTop(gy);
			break;
		case TopLeft:
			g.setTop(gy);
			g.setLeft(gx);
			break;
		case TopRight:
			g.setTop(gy);
			g.setRight(gx);
			break;
		case BottomLeft:
			g.setBottom(gy);
			g.setLeft(gx);
			break;
		case BottomRight:
			g.setBottom(gy);
			g.setRight(gx);
			break;
		case Other:
				break;
		}
		if (_mouseArea!=Other)
		{
			setGeometry(g);
		}
			
	}else
	{
		regionMouse();
	}
	Activity::mouseMoveEvent(event);
}
//鼠标按下事件
//参数：
//		event:事件
//返回值：无
void CustomActivity::mousePressEvent(QMouseEvent *event)
{
	if ((event->button() & Qt::LeftButton)&&!_dragging)
	{
		_dragging = true;
		regionMouse();
		_timer->stop();
	}
	Activity::mousePressEvent(event);
}
//鼠标松开事件
//参数：
//		event:事件
//返回值：无
void CustomActivity::mouseReleaseEvent(QMouseEvent *event)
{
	_dragging = false;
	if (_mouseArea!=Other)
	{
		this->releaseMouse();
		setCursor(Qt::ArrowCursor);
		//regionMouse();
	}
	Activity::mouseReleaseEvent(event);
}

void CustomActivity::relateTitleBar()
{
	connect(_titleBar,SIGNAL(minimizeButtonClicked()),this,SLOT(minimizeActivity()));
	connect(_titleBar,SIGNAL(maximizeButtonClicked()),this,SLOT(maximizeActivity()));
	connect(_titleBar,SIGNAL(closeButtonClicked()),this,SLOT(closeActivity()));
}
////重写放大缩小函数
//显示事件
//参数：无
//返回值：无
void CustomActivity::showEvent(QShowEvent *e)
{
	if (_preShowMode==Activity::MAXIMIZED)
	{
		setShowMode(Activity::MAXIMIZED);
	}
	else if (_preShowMode==Activity::NORMAL)
	{
		setShowMode(Activity::NORMAL);
	}
	Activity::showEvent(e);
}
//隐藏事件
//参数：无
//返回值：无
void CustomActivity::hideEvent(QHideEvent *e)
{
	_preShowMode = showMode();
	setShowMode(Activity::MINIMIZED);
	Activity::hideEvent(e);
}
//激活
//参数：无
//返回值：激活成功返回true,否则返回false
bool CustomActivity::active()
{
    if(showMode()==MINIMIZED)
    {
        setShowMode(_preShowMode);
    }
    return Activity::active();
}
//最小化窗口
//参数：无
//返回值：无
void CustomActivity::minimizeActivity(){minimizeActivityEvent();}
//最大化窗口
//参数：无
//返回值：无
void CustomActivity::maximizeActivity(){maximizeActivityEvent();}
//关闭窗口
//参数：无
//返回值：无
void CustomActivity::closeActivity(){closeActivityEvent();}
//最小化事件
//参数：无
//返回值：无
void CustomActivity::minimizeActivityEvent()
{
	this->activeMinimized();
	setShowMode(Activity::MINIMIZED);
}
//最大化事件
//参数：无
//返回值：无
void CustomActivity::maximizeActivityEvent()
{
	if (showMode()==Activity::MAXIMIZED)
	{
		activeNormal();
		setShowMode(Activity::NORMAL);
	}
	else
	{
		activeMaximized();
		setShowMode(Activity::MAXIMIZED);
	}
}
//关闭事件
//参数：无
//返回值：无
void CustomActivity::closeActivityEvent()
{
	close();
}
