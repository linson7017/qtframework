/*!
 * \file xml_ui_paser.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>
#include <libxml/xpath.h>
#include <string>
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
	//构造函数
	//参数：
	//		filename: 解析的文件路径
	//返回值：无
	xml_ui_paser(const char* filename);
	//析构函数
	//参数：无
	//返回值：无
	~xml_ui_paser();
	//解析xml文件
	//参数：无
	//返回值：是否解析成功
	bool parserXML();
	//获得节点树根节点
	//参数：无
	//返回值：节点树根节点指针
	ui_node* getRoot();
	//设置节点树根节点
	//参数：
	//		root:节点树根节点指针
	//返回值：无
	void setRoot(ui_node* root){_root = root; };
	//设置解析的xml文件
	//参数：
	//		filename:解析的xml文件路径
	//返回值：无
	void setFileName(const char* filename){_filename=filename;}
protected:
	//获得节点树
	//参数：
	//		node: xmlNodePtr节点
	//		uinode: ui_node节点
	//返回值：无
	void getXMLList(xmlNodePtr node,ui_node* uinode);
	//关联xmlNodePtr节点和 ui_node节点
	//参数：
	//		node: xmlNodePtr节点
	//		uinode: ui_node节点
	//返回值：无
	void relateXMLNodeAndUINode(xmlNodePtr xmlnode,ui_node* uinode);
private:
	std::string _filename;
	ui_node* _root;
	ui_node* _curnode;
};

