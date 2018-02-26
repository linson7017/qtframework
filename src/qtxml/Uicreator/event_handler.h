/*!
 * \file event_handler.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once
#include <QtCore/QObject>
class QTableWidgetItem;
class QTreeWidgetItem;
class ui_node;
class xml_node;

/*!
 * \class event_handler
 *
 * \brief
	主要事件处理器主要用来处理两种类型的消息
	1.绑定控件通过Signal发送的消息，是通过connect()函数链接到handle()的槽函数，
		暂时只能处理没有参数的消息函数
	2.绑定控件接收到的事件，通过installEventFilter()来链接
 *
 * \author 宋凌
 * \date 五月 2016
 */

class event_handler: public QObject
{
	Q_OBJECT
public:
	//构造函数
	//参数：
	//	parent: 父指针
	//返回值：无
	event_handler(QObject* parent=0);
	//析构函数
	//参数：无
	//返回值：无
	~event_handler(void);
	protected slots:
		//消息处理
		//参数：
		//		int: 传入类型
		//返回值：无
		void handle(int);
		//消息处理
		//参数：
		//		int: 传入类型
		//		int: 传入类型
		//返回值：无
		void handle(int,int);
		//消息处理
		//参数：无
		//返回值：无
		void handle();
		//消息处理
		//参数：
		//	QTreeWidgetItem*:传入类型
		//	int: 传入类型
		//返回值：无
		void handle(QTreeWidgetItem*,int);
protected:
	//事件过滤器
	//参数：
	//		obj: 关联对象
	//		event: 事件指针
	//返回值：是否处理完成
	bool eventFilter(QObject *obj, QEvent *event);
	//解析和执行ui_node类型命令
	//参数：
	//		node: ui_node对象指针
	//返回值：无
	void parseAndExecuteCommandForUINode(ui_node* node);
	//解析和执行xml_node类型命令
	//参数：
	//		node: xml_node对象指针
	//返回值：无
	void parseAndExecuteCommandForXmlNode(xml_node* node);
private:
	std::string _shortcutString;  //快捷键字符，这里主要是要识别辅助键
	int _globalPosX;
	int _globalPosY;
};

static event_handler gs_event_handler; //申请一个全局静态变量

