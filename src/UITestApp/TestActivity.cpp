#include "TestActivity.h"
//#include <PopWidget.h>
#include <QtGui>
#include <QtGui>
#include <Res/R.h>
#include <QtCore/QTimer>
#include <QtNetwork/QUdpSocket>
#include <QtWidgets>
//#include <../ViceMonitor/IViceMonitor.h>
static const int TUTORIAL_INDEX = 1;

TestActivity::TestActivity(void)
{
	
	switch(TUTORIAL_INDEX)
	{
	case 0:									//相对布局和基本控件
		{
			//showSplashMessage("Loading contents!");
			setContentView("main.xml");
			//Sleep(1000);
			////showSplashMessage("Loading compontents!");
			//Sleep(1000);
			////showSplashMessage("Init environment!");
			//Sleep(1000);
			////showSplashMessage("Done!");
			//Sleep(1000);
		}
		break;
	case 1:									//绝对位置布局
		{
            setContentView("panel.xml");
            QAction* action = (QAction*)getViewByID("action1");
            bool success = QObject::connect(action, SLOT(trigger()), this, SIGNAL(showMessageBox()));
			/*QProgressBar* pb = (QProgressBar*)getViewByID("pbar");
			pb->setValue(1000);*/
            int x = 0;
		}
		break;
	case 2:									//qtframework中嵌入自定义控件或者QDesigner设计控件
		{
            //EmbeddedWidget* embeddedWidget = new EmbeddedWidget;
            //R::Instance()->registerCustomWidget("EmbeddedWidget",embeddedWidget);
            //setContentView("tutorial_3.xml");
		}
		break;
	case 3:									//通过ID获取控件并以Qt的方法添加响应
		{
            setContentView("monitor.xml");
			/*setContentView("monitor.xml");
			_pMonitor = InitViceMonitor(R::Instance());
			QTimer* timer = new QTimer(this);
			connect(timer, SIGNAL(timeout()),this, SLOT(refreshData()));
			timer->start(1000);*/
			/*_udpSocket = new QUdpSocket(this);
			_udpSocket->bind(45454, QUdpSocket::ShareAddress);
			connect(_udpSocket, SIGNAL(readyRead()),this, SLOT(refreshData()));*/
			/*QPushButton* btn = (QPushButton*)getViewByID("Button1");
			connect(btn,SIGNAL(clicked()),this,SLOT(showMessageBox()));*/
		}
		break;
	case 4:									//更改控件样式
		{
			setContentView("tutorial_4.xml");
		}
		break;
	case 5:									//通过uicommand控制界面静态的逻辑操作
		{
			//PopWidget* popWidget = new PopWidget;
			setContentView("tutorial_5.xml");
		}
		break;
	case 6:									//添加右键菜单
		{
			setContentView("tutorial_6.xml");
		}
		break;
	case 7:									//设置快捷键
		{
			//PopWidget* popWidget = new PopWidget;
			setContentView("tutorial_6.xml");
		}
		break;
	default:
		break;
	}
}


TestActivity::~TestActivity(void)
{
}

void TestActivity::showMessageBox()
{
	QMessageBox mb;
	mb.setInformativeText("Signal Rescived!");
	mb.exec();
}


int dataTemp=2;

void TestActivity::refreshData()
{
	if (TUTORIAL_INDEX == 3)
	{
		//IViceMonitor* iv = InitViceMonitor(R::Instance());
		//memset(&data,0,sizeof(DataType));
		//iv->RefreshBITSystem(&data);
		//while (_udpSocket->hasPendingDatagrams()) {
			//_udpSocket->readDatagram((char*)&_data.g_sysBiteStatus,sizeof(SYS_BITE_STATUS));
		/*if (dataTemp>3)
		{
		dataTemp=0;
		}*/
			//memset(&_data.bitStatusInfo,rand()%(dataTemp+1),sizeof(SYS_BITE_STATUS));
			//memset(&_data.bitALLSysInfo,rand()%(dataTemp+1),sizeof(ALL_SYS_BIT_INFO_NEW));
			//memset(&_data.bitStatusInfo,(dataTemp),sizeof(SYS_BITE_STATUS));
			//memset(&_data.bitALLSysInfo,(dataTemp),sizeof(ALL_SYS_BIT_INFO_NEW));
			//dataTemp++;
			//_pMonitor->RefreshBITSystem(&_data);
		//}
	}
}
