#include <UIs/Activity.h>
#include "Uicreator/xml_ui_paser.h"
#include "Uicreator/qt_ui_assembler.h"
#include <Res/R.h>
#include "Utils/util.h"
#include "Utils/qt_standard.h"
#include "Common/app_env.h"
#include "Common/qt_context.h"
#include "Utils/variant.h"
#include "Utils/Log.h"
#include "UIs/SplashWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

#include <qfmain/iqf_main.h>
//构造函数
//参数：无
//返回值：无
Activity::Activity(void):QWidget(NULL),_id(""),_showMode(NORMAL),_initPosX(0),
	_initPosY(0),_bPrepared(false),_content(NULL),_bParsed(false),_layout_filename(""),
	_initWidth(500),_initHeight(500),_splashWindow(NULL),_bShowSplashWindow(false)
{
}
//构造函数
//参数：
//		parent:父窗口指针
//返回值：无
Activity::Activity(Activity* parent):QWidget(parent),_showMode(NORMAL),
	_bPrepared(false),_content(NULL),_bParsed(false),_layout_filename(""),_initWidth(500),
	_initHeight(500),_splashWindow(NULL),_bShowSplashWindow(false)
{
}
//构造函数
//参数：
//		id:窗口id
//返回值：无
Activity::Activity(const char* id):_id(id),QWidget(NULL),_showMode(NORMAL),
	_bPrepared(false),_content(NULL),_bParsed(false),_layout_filename(""),_initWidth(500),
	_initHeight(500),_splashWindow(NULL),_bShowSplashWindow(false)
{
}
//构造函数
//参数：
//		pSplashWindow:SplashWindow
//返回值：无
Activity::Activity(SplashWindow* pSplashWindow):_splashWindow(pSplashWindow),_id(""),QWidget(NULL),_showMode(NORMAL),
	_bPrepared(false),_content(NULL),_bParsed(false),_layout_filename(""),_initWidth(500),_initHeight(500),_bShowSplashWindow(true)
{

}
//构造函数
//参数：
//		id:窗口id
//		parent:父窗口指针
//返回值：无
Activity::Activity(const char* id, Activity* parent):_id(id),QWidget(parent),
	_showMode(NORMAL),_bPrepared(false),_content(NULL),_bParsed(false),_layout_filename("")
	,_initWidth(500),_initHeight(500),_splashWindow(NULL),_bShowSplashWindow(false)
{
}
////析构函数
//参数：无
//返回值：无
Activity::~Activity(void)
{
	if (_parser!=NULL)
	{
		delete _parser;
		_parser = NULL;
	}
	if (_assembler!=NULL)
	{
		delete _assembler;
		_assembler = NULL;
	}
}
//显示窗口
//参数：无
//返回值：显示成功返回true
bool Activity::active()
{
	if (!actionBeforeActived())
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: Fail to execute the action before activity %s actived!\n",_id.c_str());
		printf(szMsg);
		return false;
	}
	if (active(_showMode))
	{
		//处理激活后需要的一些显示设置，比如对话框在屏幕上的位置，Widget的真实尺寸在show()以后才可以得到
		//由于启动后移动对话框位置会出现闪烁，暂时去掉 2015-08-31
		//parseShowModeAfterActived(_assembler->getUINodeTreeRoot()); 
		if (!actionAfterActived()) 
		{
			char szMsg[1024];
			sprintf(szMsg, "QtFrameWork ERROR: Fail to execute the action after activity %s actived!\n",_id.c_str());
			printf(szMsg);
			return false;
		}
		/*if (_splashWindow&&_bShowSplashWindow)
		{
			_splashWindow->finish(this);
		}*/
		return true;
	}
	else
		return false;
}
//显示窗口
//参数：
//		mode：显示模式
//返回值：成功返回true,否则返回false
bool Activity::active(ShowMode mode)
{
	_showMode = mode;
	if (!_bPrepared)
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: Fail to activate activity %s because parsing xml in layout falied!\n",_id.c_str());
		printf(szMsg);
		return false;
	}
	switch (mode)
	{
	case NORMAL:
		activeNormal();
		break;
	case MAXIMIZED:
		activeMaximized();
		break;
	case MINIMIZED:
		activeMinimized();
		break;
	case FULL_SCREEN:
		activeFullScreen();
		break;
	default:
		return false;
	}
	return true;
}
//最大化显示窗口
//参数：无
//返回值：无
void Activity::activeMaximized()
{
	showMaximized();
	_showMode = MAXIMIZED;
}
//最小化显示窗口
//参数：无
//返回值：无
void Activity::activeMinimized()
{
	showMinimized();
	_showMode = MINIMIZED;
}
//显示窗口
//参数：无
//返回值：无
void Activity::activeNormal()
{
	showNormal();
	_showMode = NORMAL;
}
//全屏显示窗口
//参数：无
//返回值：无
void Activity::activeFullScreen()
{
	showFullScreen();
	_showMode = FULL_SCREEN;
}
//设置显示模式
//参数：
//		title：窗口标题
//返回值：无
void Activity::setTitle(const char* title)
{
	this->setWindowTitle(title);
}
//安装窗口内容
//参数：无
//返回值：无
void Activity::installContent()
{
	//设置背景颜色
	const variant* v = R::Instance()->getConfigResource("BackgroundColor");
	if (v)
	{
		QPalette palette;
		setAutoFillBackground(true);
		palette.setColor(backgroundRole(),QColor(QString(v->getString())));
		setPalette(palette);
	}
	else
	{
		QPalette palette;
		setAutoFillBackground(true);
		palette.setColor(backgroundRole(),QColor(240,240,240));
		setPalette(palette);
	}
	if (_content->getType()==ui_node::LAYOUT)
	{
		setLayout((QLayout*)_content->getObject());
	}
	else if (_content->getType()==ui_node::WIDGET)
	{
		QHBoxLayout* layout = new QHBoxLayout;
		layout->setContentsMargins(0,0,0,0);  //避免Widget边界出现空白
		layout->addWidget((QWidget*)_content->getObject());
		setLayout(layout);
	}
}
//设置窗口内容对应的xml文档
//参数：
//		layout_filename:布局文件路径
//返回值：是否设置成功
bool Activity::setContentView(const char* layout_filename)
{
	
	if (!actionBeforeCreated())
	{
		//执行创建前行为失败
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: Fail to execute the action before activity related to file %s created!\n",layout_filename);
		printf(szMsg);
		return false;
	}
	//获取xml文件的地址
	std::string filename;
	if (fileOrPahtExist(layout_filename))
	{
		filename = layout_filename;
	}
	else
	{
		filename =app_env::getDir(app_env::LAYOUT);
		filename.append(layout_filename);
	}
	_parser = new xml_ui_paser(filename.c_str());
	//解析ui_node树
	if (!_parser->parserXML()) 
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: Parse layout file %s failed! Please check if it has existed\n",filename.c_str());
		printf(szMsg);
		return  false;
	}
	//装配ui_node树
	if (!_parser->getRoot())
	{
		//先判断解析出来的根节点是否有内容
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: Parse layout file %s nothing in it! Please check if the contents are correctly organized.\n",filename.c_str());
		printf(szMsg);
		return false;
	}
	_layout_filename = filename;
	_bParsed=true;
	
	//检查UI是否准备完成
	//这里之所以把所有控件的实例化放在启动之前进行，是为了处理那些在创建过程中需要父窗口信息的UI节点
	//，比如最大和最小按钮的图片必须知道父窗口初始化是最大还是正常模式显示
	if (!_bPrepared)
	{
		//如果没有准备则装配，装备失败返回false
		if (!prepareUI())
		{
			char szMsg[1024];
			sprintf(szMsg, "QtFrameWork ERROR: Fail to activate activity %s because it does not created!\n",_id.c_str());
			printf(szMsg);
			return false;
		}
	}
	
	return true;
}
//准备UI
//参数：无
//返回值：成功返回true,否则返回false
bool Activity::prepareUI()
{
	if (!_bParsed)
	{
		return false;
	}
	//装配UI
	_assembler = new qt_ui_assembler(_parser);
	_assembler->assemble();
	_content = _assembler->getUINodeTreeRoot();
	if (!_content->getObject())
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: Assemble activity %s failed, its related layout file is %s\n",_id.c_str(),_layout_filename.c_str());
		printf(szMsg);
		return false;
	}
	//根据根节点的类型将装配好的界面安装到Widget中
	installContent();
	//激活ui_node节点中所有的Container节点，使其发挥效用，不激活则没有效果
	activateAllContainers();
	//装配结束后的用户自定的事件
	if (!actionAfterCreated())
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: Fail to execute the action after activity related to file %s created!\n",_layout_filename);
		printf(szMsg);
		return false;
	}
	//如果是layout中的xml，即要显示到独立窗口中的布局，取得其根布局的属性并解析
	parseShowModeBeforeActived(_assembler->getUINodeTreeRoot()); 

	//成功后将自己添加到R中的ActivityMap中
	installEventFilter((QObject*)_assembler->getEventHandler());
	xml_node* xmlRoot = new xml_node;
	if (getXMLFileRoot(_layout_filename.c_str(),xmlRoot)) //如果xml文件中定义了id信息
	{
		if (xmlRoot->hasAttribute("activityRoot")&&xmlRoot->hasAttribute("id"))
		{
			if (STR_TO_BOOL(xmlRoot->getAttribute("activityRoot")))
			{
				setID(xmlRoot->getAttribute("id"));
			}
		}
		else
		{
			string id = _layout_filename;
			removeExtension(id);
			setID(id.c_str());
		}
	}
	xmlRoot->release();//20150925
	//将Activity添加到资源中
	R::Instance()->addActivity(_id.c_str(),this); 
	R::Instance()->addObjectGlobalMap(_id.c_str(),this);

	_bPrepared = true;
}
//激活所有的容器
//参数：
//返回值：无
void Activity::activateAllContainers()
{
	//_assembler->activateAllContainers();
}
//激活容器
//参数：
//		id：容器ID
//返回值：无
void Activity::activateContainer(const char* id)
{
	//_assembler->activateContainer(id);
}
//获得控件对象
//参数：
//		id：ID
//返回值：控件对象指针
void* Activity::getViewByID(const char* id)
{
	return _assembler->getObjectByID(id);
}


//窗口显示之前解析根节点的显示设置
//参数：
//		attr：节点指针
//返回值：无
void Activity::parseShowModeBeforeActived(ui_node* attr)
{
	//如果没有设置activityRoot属性为true，默认认为不解析根节点里面的属性
	if (!attr->hasAttribute("activityRoot"))
	{
		return;	
	}
	if (!STR_TO_BOOL(attr->getAttribute("activityRoot")))
		return;

	

	if (attr->hasAttribute("id"))
	{
		_id = attr->getAttribute("id");
	}

	//父窗口
	if (attr->hasAttribute("parent"))
	{
		string id = attr->getAttribute("parent");
		R* r = R::Instance();
		Activity* parent = R::Instance()->getActivity(id.c_str());
		setParent(parent);
	}
	// 样式
	if (attr->hasAttribute("style")&&attr->getType()!=ui_node::WIDGET)
	{
		string res = attr->getAttribute("style");
		const char* stylesheet = getResStyle(attr->getAttribute("style"));
		setStyleSheet(stylesheet);
	}

	//windowflag
	if (attr->hasAttribute("flags"))
	{
		QStringList flagList = STR_TO_STR_VECTOR(attr->getAttribute("flags"));
		Qt::WindowFlags flags = 0;
		for (int i=0;i<flagList.size();i++)
		{
			flags |= qt_standard::getWindowType(flagList.at(i).toLocal8Bit().data());
		}
		setWindowFlags(flags);
	}
	//显示大小
	if (attr->hasAttribute("showMode"))
	{
		string mode = attr->getAttribute("showMode");
		if (strcmp(mode.c_str(),"FullScreen")==0)
			_showMode = FULL_SCREEN;
		else if (strcmp(mode.c_str(),"Minimized")==0)
			_showMode = MINIMIZED;
		else if (strcmp(mode.c_str(),"Maximized")==0)
			_showMode = MAXIMIZED;
		else if (strcmp(mode.c_str(),"Normal")==0)
			_showMode = NORMAL;
	}else
	{
		_showMode = NORMAL;
	}
	//标题
	if (attr->hasAttribute("title"))
	{
		setTitle(attr->getAttribute("title"));
	}

	if (attr->hasAttribute("pos"))
	{
		string posStr = attr->getAttribute("pos");
		int i = posStr.find_first_of(",");
		int len = posStr.length();
		_initPosX = STR_TO_INT(posStr.substr(0,i).c_str());
		_initPosY = STR_TO_INT(posStr.substr(i+1,len).c_str());
		move(_initPosX,_initPosY);
	}
	if (attr->hasAttribute("size"))
	{
		string posStr = attr->getAttribute("size");
		int i = posStr.find_first_of(",");
		int len = posStr.length();
		_initWidth = STR_TO_INT(posStr.substr(0,i).c_str());
		_initHeight = STR_TO_INT(posStr.substr(i+1,len).c_str());
		const variant* v = R::Instance()->getConfigResource("WindowTitleHeight");
        int windowTitleHeight = 0;
		if (v)
		{
			windowTitleHeight = v->getInt();
		}
		setGeometry(_initPosX,_initPosY+windowTitleHeight,_initWidth,_initHeight);
	}
    if (attr->hasAttribute("height"))
    {
        setFixedHeight(STR_TO_INT(attr->getAttribute("height")));
    }
    if (attr->hasAttribute("weight"))
    {
        setFixedWidth(STR_TO_INT(attr->getAttribute("weight")));
    }

}

//设置Widget在屏幕或者父窗口下的显示位置
//设置窗口位置
//参数：
//		align：位置
//返回值：无
void Activity::setAlignment(Alignment align)
{
	int sw;
	int sh;
	int px=0;
	int py=0;
	int w = width();
	int h = height();
	if (parent())
	{
		QWidget* pw = (QWidget*)parent();
        QRect prect = pw->geometry();
		sw = pw->width();
		sh = pw->height();
        QPoint positon = pw->pos();
        QPoint pGloble = pw->mapToGlobal(positon);
        px = pGloble.x();
        py = pGloble.y();
	}
	else
	{
		sw = qt_context::getScreenWidth(0);
		sh = qt_context::getScreenHeight(0);
	}
    //const variant* v = R::Instance()->getConfigResource("WindowTitleHeight");
    int windowTitleHeight = 0;
//	if (v)
//	{
//		windowTitleHeight = v->getInt();
//	}
	switch (align)
	{
	case RIGHT:
		move(sw-w+px,(sh-h)/2+py);
		break;
	case LEFT:
		move(px,(sh-h)/2+py);
		break;
	case TOP:
		move(((sw-w)/2)+px,py);
		break;
	case TOP_LEFT:
		move(px,py);
		break;
	case TOP_RIGHT:
		move(sw-w+px,py);
		break;
	case BOTTOM_LEFT:
		move(px,sh-h+py+windowTitleHeight);
		break;
	case BOTTOM_RIGHT:
		move(sw-w+px,sh-h+py+windowTitleHeight);
		break;
	case CENTER:
		move(((sw-w)/2)+px,((sh-h)/2)+py);
		break;
	default:
		break;
	}
}

//显示提示信息
//参数：
//		szMessage:显示信息
//返回值：无
void Activity::showSplashMessage(const char* szMessage)
{
	if (_splashWindow)
	{
		_splashWindow->showMessage(szMessage);
	}
}

void Activity::closeEvent(QCloseEvent *ev)
{
    actionBeforeClosed();
    QWidget::closeEvent(ev);
}

//会闪烁，暂时去掉
//void Activity::parseShowModeAfterActived(ui_node* attr)
//{
//	//设置显示位置
//	if (attr->hasAttribute("align"))
//	{
//		string alignStr = attr->getAttribute("align");
//		if (strcmp(alignStr.c_str(),"left")==0)
//			setAlignment(LEFT);
//		else if (strcmp(alignStr.c_str(),"right")==0)
//			setAlignment(RIGHT);
//		else if (strcmp(alignStr.c_str(),"top")==0)
//			setAlignment(TOP);
//		else if (strcmp(alignStr.c_str(),"bottom")==0)
//			setAlignment(BOTTOM);
//		else if (strcmp(alignStr.c_str(),"topLeft")==0)
//			setAlignment(TOP_LEFT);
//		else if (strcmp(alignStr.c_str(),"topRight")==0)
//			setAlignment(TOP_RIGHT);
//		else if (strcmp(alignStr.c_str(),"bottomLeft")==0)
//			setAlignment(BOTTOM_LEFT);
//		else if (strcmp(alignStr.c_str(),"bottomRight")==0)
//			setAlignment(BOTTOM_RIGHT);
//		else if (strcmp(alignStr.c_str(),"center")==0)
//			setAlignment(CENTER);
//	}
//}
