#pragma once
#include <QtCore/QThread>

class AsynchronousAction : public QThread
{
	Q_OBJECT
public:
	AsynchronousAction();
	AsynchronousAction(void* pParam);
	~AsynchronousAction();
	virtual void run();
	void setParameter(void* pParam){_pParam = pParam;}
private:
	void* _pParam;
};

