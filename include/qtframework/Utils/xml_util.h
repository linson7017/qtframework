/*!
 * \file xml_util.h
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
	//获得XPath对象指针
	//参数：
	//		doc:文档指针
	//		xpath:文档路径
	//返回值：XPath对象指针
	friend inline xmlXPathObjectPtr getXmlNodeSet(xmlDocPtr doc,const xmlChar* xpath);
	//转换为xml节点树
	//参数：
	//		root:ui_node节点树指针
	//		xmlRoot:xmlNode节点树指针
	//返回值：无
	static void convertToXMLTree(ui_node* root,xmlNodePtr xmlRoot);
	//关联ui_node和xmlNode指针
	//参数：
	//		node:ui_node节点树指针
	//		xmlNode:xmlNode节点树指针
	//返回值：关联成功返回true,否则返回false
	static bool relate(ui_node* node,xmlNodePtr xmlNode);
	//将xmlNode节点树存入xml文件
	//参数：
	//		xmlRoot:xmlNode节点树指针
	//		filename:xml文件路径
	//返回值：关联成功返回true,否则返回false
	static bool writeToFile(xmlNodePtr xmlRoot,const char* filename);
	//将ui_node节点树存入xml文件
	//参数：
	//		xmlRoot:ui_node节点树指针
	//		filename:xml文件路径
	//返回值：关联成功返回true,否则返回false
	static bool writeToFile(ui_node* root,const char* filename);
protected:
	//解析节点树
	//参数：
	//		node:ui_node节点树指针
	//		xmlNode:xmlNode节点树指针
	//返回值：无
	static void parseTree(ui_node* node,xmlNodePtr xmlNode);
};

xmlXPathObjectPtr getXmlNodeSet(xmlDocPtr doc,const xmlChar* xpath)
{
	xmlXPathContextPtr context;
	xmlXPathObjectPtr result;
	context = xmlXPathNewContext(doc);
	if (context==NULL)
	{
		return NULL;
	}
	result = xmlXPathEvalExpression(xpath,context);
	xmlXPathFreeContext(context);
	if (result==NULL)
	{
		return NULL;
	}
	if (xmlXPathNodeSetIsEmpty(result->nodesetval))
	{
		xmlXPathFreeObject(result);
		return NULL;
	}
	return result;
}