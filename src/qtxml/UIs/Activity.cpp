#include <UIs/Activity.h>
#include "UIs/SplashWindow.h"

#include "Uicreator/xml_ui_paser.h"
#include "Uicreator/qt_ui_assembler.h"
#include <Res/R.h>

#include "Common/app_env.h"
#include "Common/qt_context.h"
#include "Utils/variant.h"
#include "Utils/Log.h"
#include "Utils/util.h"
#include "Utils/xml_util.h"
#include "Utils/qt_standard.h"


#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

#include <qfmain/iqf_main.h>
//���캯��
//��������
//����ֵ����
Activity::Activity(void):QWidget(NULL),_id(""),_showMode(NORMAL),_initPosX(0),
	_initPosY(0),_bPrepared(false),_content(NULL),_bParsed(false),_layout_filename(""),
	_initWidth(500),_initHeight(500),_splashWindow(NULL),_bShowSplashWindow(false)
{
}
//���캯��
//������
//		parent:������ָ��
//����ֵ����
Activity::Activity(Activity* parent):QWidget(parent),_showMode(NORMAL),
	_bPrepared(false),_content(NULL),_bParsed(false),_layout_filename(""),_initWidth(500),
	_initHeight(500),_splashWindow(NULL),_bShowSplashWindow(false)
{
}
//���캯��
//������
//		id:����id
//����ֵ����
Activity::Activity(const char* id):_id(id),QWidget(NULL),_showMode(NORMAL),
	_bPrepared(false),_content(NULL),_bParsed(false),_layout_filename(""),_initWidth(500),
	_initHeight(500),_splashWindow(NULL),_bShowSplashWindow(false)
{
}
//���캯��
//������
//		pSplashWindow:SplashWindow
//����ֵ����
Activity::Activity(SplashWindow* pSplashWindow):_splashWindow(pSplashWindow),_id(""),QWidget(NULL),_showMode(NORMAL),
	_bPrepared(false),_content(NULL),_bParsed(false),_layout_filename(""),_initWidth(500),_initHeight(500),_bShowSplashWindow(true)
{

}
//���캯��
//������
//		id:����id
//		parent:������ָ��
//����ֵ����
Activity::Activity(const char* id, Activity* parent):_id(id),QWidget(parent),
	_showMode(NORMAL),_bPrepared(false),_content(NULL),_bParsed(false),_layout_filename("")
	,_initWidth(500),_initHeight(500),_splashWindow(NULL),_bShowSplashWindow(false)
{
}
////��������
//��������
//����ֵ����
Activity::~Activity(void)
{
	if (_assembler!=NULL)
	{
		delete _assembler;
		_assembler = NULL;
	}
}
//��ʾ����
//��������
//����ֵ����ʾ�ɹ�����true
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
		//���������Ҫ��һЩ��ʾ���ã�����Ի�������Ļ�ϵ�λ�ã�Widget����ʵ�ߴ���show()�Ժ�ſ��Եõ�
		//�����������ƶ��Ի���λ�û������˸����ʱȥ�� 2015-08-31
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
//��ʾ����
//������
//		mode����ʾģʽ
//����ֵ���ɹ�����true,���򷵻�false
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
//�����ʾ����
//��������
//����ֵ����
void Activity::activeMaximized()
{
	showMaximized();
	_showMode = MAXIMIZED;
}
//��С����ʾ����
//��������
//����ֵ����
void Activity::activeMinimized()
{
	showMinimized();
	_showMode = MINIMIZED;
}
//��ʾ����
//��������
//����ֵ����
void Activity::activeNormal()
{
	showNormal();
	_showMode = NORMAL;
}
//ȫ����ʾ����
//��������
//����ֵ����
void Activity::activeFullScreen()
{
	showFullScreen();
	_showMode = FULL_SCREEN;
}
//������ʾģʽ
//������
//		title�����ڱ���
//����ֵ����
void Activity::setTitle(const char* title)
{
	this->setWindowTitle(title);
}
//��װ��������
//��������
//����ֵ����
void Activity::installContent()
{
    ///��Ӱ��qApp->setPalette()�Ľ��20180207
	////���ñ�����ɫ
	//const variant* v = R::Instance()->getConfigResource("BackgroundColor");
	//if (v)
	//{
	//	QPalette palette;
	//	setAutoFillBackground(true);
	//	palette.setColor(backgroundRole(),QColor(QString(v->getString())));
	//	setPalette(palette);
	//}
	//else
	//{
	//	QPalette palette;
	//	setAutoFillBackground(true);
	//	palette.setColor(backgroundRole(),QColor(240,240,240));
	//	setPalette(palette);
	//}
	if (_content->getType()==ui_node::LAYOUT)
	{
		setLayout((QLayout*)_content->getObject());
	}
	else if (_content->getType()==ui_node::WIDGET)
	{
		QHBoxLayout* layout = new QHBoxLayout;
		layout->setContentsMargins(0,0,0,0);  //����Widget�߽���ֿհ�
		layout->addWidget((QWidget*)_content->getObject());
		setLayout(layout);
	}
}
//���ô������ݶ�Ӧ��xml�ĵ�
//������
//		layout_filename:�����ļ�·��
//����ֵ���Ƿ����óɹ�
bool Activity::setContentView(const char* layout_filename)
{
    setWindowFlags(windowFlags()|Qt::Dialog);
	if (!actionBeforeCreated())
	{
		//ִ�д���ǰ��Ϊʧ��
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: Fail to execute the action before activity related to file %s created!\n",layout_filename);
		printf(szMsg);
		return false;
	}
	//��ȡxml�ļ��ĵ�ַ
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
    _assembler = new qt_ui_assembler;
	//����ui_node��
	if (!xml_ui_paser::parserXML(filename.c_str(),_assembler->getUINodeTreeRoot()))
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: Parse layout file %s failed! Please check if it has existed\n",filename.c_str());
		printf(szMsg);
		return  false;
	}
	_layout_filename = filename;
	_bParsed=true;
	
	//���UI�Ƿ�׼�����
	//����֮���԰����пؼ���ʵ������������֮ǰ���У���Ϊ�˴�����Щ�ڴ�����������Ҫ��������Ϣ��UI�ڵ�
	//������������С��ť��ͼƬ����֪�������ڳ�ʼ�������������ģʽ��ʾ
	if (!_bPrepared)
	{
		//���û��׼����װ�䣬װ��ʧ�ܷ���false
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
//׼��UI
//��������
//����ֵ���ɹ�����true,���򷵻�false
bool Activity::prepareUI()
{
	if (!_bParsed)
	{
		return false;
	}
	//װ��UI
	_assembler->assemble();
	_content = _assembler->getUINodeTreeRoot();
	if (!_content->getObject())
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: Assemble activity %s failed, its related layout file is %s\n",_id.c_str(),_layout_filename.c_str());
		printf(szMsg);
		return false;
	}
	//���ݸ��ڵ�����ͽ�װ��õĽ��氲װ��Widget��
	installContent();
	//����ui_node�ڵ������е�Container�ڵ㣬ʹ�䷢��Ч�ã���������û��Ч��
	activateAllContainers();
	//װ���������û��Զ����¼�
	if (!actionAfterCreated())
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: Fail to execute the action after activity related to file %s created!\n",_layout_filename);
		printf(szMsg);
		return false;
	}
	//�����layout�е�xml����Ҫ��ʾ�����������еĲ��֣�ȡ��������ֵ����Բ�����
	parseShowModeBeforeActived(_assembler->getUINodeTreeRoot()); 

	//�ɹ����Լ���ӵ�R�е�ActivityMap��
	installEventFilter((QObject*)_assembler->getEventHandler());
	xml_node* xmlRoot = new xml_node;
	if (xml_util::getXMLFileRoot(_layout_filename.c_str(),xmlRoot)) //���xml�ļ��ж�����id��Ϣ
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
	//��Activity��ӵ���Դ��
	R::Instance()->addActivity(_id.c_str(),this); 
	R::Instance()->addObjectGlobalMap(_id.c_str(),this);

	_bPrepared = true;
}
//�������е�����
//������
//����ֵ����
void Activity::activateAllContainers()
{
	//_assembler->activateAllContainers();
}
//��������
//������
//		id������ID
//����ֵ����
void Activity::activateContainer(const char* id)
{
	//_assembler->activateContainer(id);
}
//��ÿؼ�����
//������
//		id��ID
//����ֵ���ؼ�����ָ��
void* Activity::getViewByID(const char* id)
{
	return _assembler->getObjectByID(id);
}


//������ʾ֮ǰ�������ڵ����ʾ����
//������
//		attr���ڵ�ָ��
//����ֵ����
void Activity::parseShowModeBeforeActived(ui_node* attr)
{
	//���û������activityRoot����Ϊtrue��Ĭ����Ϊ���������ڵ����������
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
    
	//������
	if (attr->hasAttribute("parent"))
	{
		string id = attr->getAttribute("parent");
		R* r = R::Instance();
		Activity* parent = R::Instance()->getActivity(id.c_str());
		setParent(parent);
	}
	// ��ʽ
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
	//��ʾ��С
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
	//����
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

    if (attr->hasAttribute("icon"))
    {
        setWindowIcon(QIcon(R::Instance()->getImageResourceUrl(attr->getAttribute("icon")).c_str()));
    }
}

//����Widget����Ļ���߸������µ���ʾλ��
//���ô���λ��
//������
//		align��λ��
//����ֵ����
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

//��ʾ��ʾ��Ϣ
//������
//		szMessage:��ʾ��Ϣ
//����ֵ����
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

void Activity::setup()
{
    _assembler->setupUITree(_assembler->getUINodeTreeRoot());
}

//����˸����ʱȥ��
//void Activity::parseShowModeAfterActived(ui_node* attr)
//{
//	//������ʾλ��
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
