#include <UIs/Listener.h>
#include "Uicreator/ui_node.h"
#include "Utils/util.h"
//构造函数
//参数：无
//返回值：无
Listener::Listener(void):_sender(NULL)
{
}

//析构函数
//参数：无
//返回值：无
Listener::~Listener(void)
{
	//delete _sender;
}
//触发
//参数：无
//返回值：无
void Listener::trigger()
{
	QObject* senderobj = this->sender();
	_sender = (ui_node*)getUINodeFromObject(senderobj);
}