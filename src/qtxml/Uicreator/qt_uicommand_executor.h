/*!
 * \file qt_uicommand_executor.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once

class ui_node;
class xml_node;

/*!
 * \class qt_uicommand_executor
 *
 * \brief qt_uicommand_executor类
 *			处理UI类消息
 *
 * \author 宋凌
 * \date 五月 2016
 */
class qt_uicommand_executor
{
public:
	//构造函数
	//参数：无
	//返回值：无
	qt_uicommand_executor(void);
	//析构函数
	//参数：无
	//返回值：无
	~qt_uicommand_executor(void);
	//执行xml_node类型命令
	//参数：
	//		node: xml_node对象指针
	//返回值：是否执行成功
	static bool executeCommand(xml_node* node);
protected:
	//执行命令
	//参数：
	//		uicommand: uicommand类型节点指针
	//		sender: 消息发送者
	//返回值：是否执行成功
	static bool execute(xml_node* uicommand,ui_node* sender);
};

