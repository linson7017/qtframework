/*!
 * \file xml_util.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once
#include "Utils/tinyxml2.h"
#include <Uicreator/ui_node.h>
using namespace std;
/*!
 * \class class xml_util
 *
 * \brief class xml_util类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class xml_util
{
public:
	//构造函数
	//参数：无
	//返回值：无
	xml_util(void);
	//析构函数
	//参数：无
	//返回值：无
	~xml_util(void);
	//转换为xml节点树
	//参数：
	//		root:ui_node节点树指针
	//		xmlRoot:xmlNode节点树指针
	//返回值：无
	static void convertToXMLDoc(ui_node* root,tinyxml2::XMLDocument& xmlDoc);
	//关联ui_node和xmlNode指针
	//参数：
	//		node:ui_node节点树指针
	//		xmlNode:xmlNode节点树指针
	//返回值：关联成功返回true,否则返回false
	static bool relate(ui_node* node, tinyxml2::XMLNode* xmlNode);
	//将xmlNode节点树存入xml文件
	//参数：
	//		xmlRoot:xmlNode节点树指针
	//		filename:xml文件路径
	//返回值：关联成功返回true,否则返回false
	static bool writeToFile(tinyxml2::XMLDocument& xmlDoc,const char* filename);
	//将ui_node节点树存入xml文件
	//参数：
	//		xmlRoot:ui_node节点树指针
	//		filename:xml文件路径
	//返回值：关联成功返回true,否则返回false
	static bool writeToFile(ui_node* root,const char* filename);


    //获得xml文件根节点
    //参数：
    //	filename:xml文件路径
    //	root:xml根节点
    //返回值：获得成功返回true,否则返回false
    static bool getXMLFileRoot(const char* filename, xml_node* root);
protected:
	//解析节点树
	//参数：
	//		node:ui_node节点树指针
	//		xmlNode:xmlNode节点树指针
	//返回值：无
	static void parseTree(ui_node* node, tinyxml2::XMLNode* xmlNode, tinyxml2::XMLDocument& xmlDoc);
};
