/*!
 * \file xml_ui_paser.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once
#include <string>
#include <Utils/tinyxml2.h>
//#include "ui_node.h"

class ui_node;
/*!
 * \class xml_ui_paser
 *
 * \brief xml_ui_paser类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class xml_ui_paser
{
public:
	//构造函数
	//参数：无
	//返回值：无
	xml_ui_paser();
	//析构函数
	//参数：无
	//返回值：无
	~xml_ui_paser();
	//解析xml文件
	//参数：无
	//返回值：是否解析成功
	static bool parserXML(const char* filename,ui_node* root);
protected:
	//获得节点树
	//参数：
	//		node: xmlNodePtr节点
	//		uinode: ui_node节点
	//返回值：无
	static void getXMLList(tinyxml2::XMLNode* node,ui_node* uinode);

private:
    static std::string _currentFileName;
};

