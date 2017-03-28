#pragma once
#include <UIs/CustomActivity.h>
//#include <../ViceMonitor/MonitorConfig.h>
class QUdpSocket;
class IViceMonitor;
class TestActivity:public CustomActivity,public QObject
{
	Q_OBJECT
public:
	TestActivity(void);
	~TestActivity(void);
    void closeEvent(QCloseEvent *ev){
        //QWidget::closeEvent(ev);
    }
	public slots:
		void showMessageBox();
		void refreshData();
private:
	QUdpSocket *_udpSocket;
	//ViceMonitorDataType _data;
	IViceMonitor* _pMonitor;
};


