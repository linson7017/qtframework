/*!
 * \file xml_node.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once
#include <string>
#include <map>
#include <list>
#include <libxml/tree.h>
#include <Utils/variant.h>
using namespace std;
/*!
 * \class xml_node
 *
 * \brief xml_node类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class xml_node
{
public:
	//定义属性表类型
	typedef std::map<string,string> AttributeMapType;
    typedef std::map<string, variant> ParameterMapType;
	//构造函数
	//参数：无
	//返回值：无
	xml_node(void);
	//析构函数
	//参数：无
	//返回值：无
	~xml_node(void);
	//释放节点及子节点
	//参数：无
	//返回值：无
	virtual void release();//20150925
	//添加子节点
	//参数：
	//		node: 子节点指针
	//返回值：无
	virtual void addChild(xml_node* node);
	//获得子节点
	//参数：
	//		index: 子节点索引
	//返回值：子节点指针
	virtual xml_node* getChild(int index);
	//获得子节点数量
	//参数：无
	//返回值：子节点数量
	virtual int getChildNum(){return _childs.size();}
	//设置父节点
	//参数：
	//		node: 父节点指针
	//返回值：无
	virtual void setParent(xml_node* node);
	//获得父节点
	//参数：无
	//返回值：父节点指针
	virtual xml_node* getParent();

	//设置节点名称
	//参数：
	//		name: 节点名称
	//返回值：无
	virtual void setName(const char* name){_name = name;}
	//获得节点名称
	//参数：无
	//返回值：节点名称
	virtual const char* getName(){return _name.c_str();}
	//设置节点内容
	//参数：
	//		content: 节点内容
	//返回值：无
	virtual void setContent(const char* content){_content = content;}
	//获得节点内容
	//参数：无
	//返回值：节点内容
	virtual const char* getContent(){return _content.c_str();}

	//获得属性
	//参数：
	//		key: 键值
	//返回值：属性字符串
	virtual const char* getAttribute(const char* key);
	//是否具有属性
	//参数：
	//		key: 键值
	//返回值：存在key属性返回true，否则返回false
	virtual bool hasAttribute(const char* key);
	//添加属性
	//参数：
	//		key: 键值
	//		value: 值
	//返回值：无
	virtual void addAttribute(const char* key,const char* value);
	//获得属性表
	//参数：无
	//返回值：属性表
	virtual AttributeMapType& getAttributeMap(){return _attributes;}
	//将节点与xmlNode节点关联，获得属性
	//参数：
	//		xmlNode: xmlNode节点指针
	//返回值：无
	virtual void relateXMLNode(xmlNode* xmlnode);
	//获得xmlNode节点
	//参数：无
	//返回值：xmlNode节点指针
	xmlNode* getXMLNode(){return _xmlNode;}

    virtual void addParameter(const char* key, const variant& parameter);
    virtual ParameterMapType& getParameters() { return _parameters; }
protected:
	string _name;
	string _id;
	string _content;
	list<xml_node*> _childs; 
	xml_node* _parent;
	AttributeMapType _attributes;
    ParameterMapType _parameters;
	xmlNode* _xmlNode;
};

