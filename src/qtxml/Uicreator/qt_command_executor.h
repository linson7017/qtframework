/*!
 * \file qt_command_executor.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once

#include <QtCore/QObject>
class ui_node;
class xml_node;

/*!
 * \class qt_command_executor
 *
 * \brief qt_command_executor类
	处理主控消息
 *
 * \author 宋凌
 * \date 五月 2016
 */
namespace QF
{
    class IQF_Properties;
    class IQF_Main_Ext;
}

class qt_command_executor : public QObject
{
	Q_OBJECT
public:
	//构造函数
	//参数：无
	//返回值：无
	qt_command_executor(void);
	//析构函数
	//参数：无
	//返回值：无
	~qt_command_executor(void);
	//执行ui_node类型命令
	//参数：
	//		node: ui_node对象指针
	//返回值：是否执行成功
	//static bool executeCommand(ui_node* node);
	//执行xml_node类型命令
	//参数：
	//		node: xml_node对象指针
	//返回值：是否执行成功
	static bool executeCommand(xml_node* node);

private:
    static void parseCommandProperty(xml_node* commandNode, QF::IQF_Properties* properties);
};

