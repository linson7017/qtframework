/*!
 * \file ui_node.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once

//#include <string>
#include <list>
#include "Uicreator/xml_node.h"
//#include <map>


using namespace std;
/*!
 * \class ui_node
 *
 * \brief ui_node类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class ui_node : public xml_node
{
public:
	//节点类型
	enum NodeType
	{
		WIDGET, //控件类型
		LAYOUT, //布局类型
		ITEM,   //项目类型
		ITEMS,  //项目集合类型
		CONTAINER, //容器类型
		CUSTOMER,  //用户自定义类型
        UNKNOWN
	};
	//构造函数
	//参数：无
	//返回值：无
	ui_node();
    //复制构造函数
    //参数：无
    //返回值：无
    ui_node(const ui_node& node);
	//析构函数
	//参数：无
	//返回值：无
	~ui_node();
	//释放节点及子节点
	//参数：无
	//返回值：无
	virtual void release(); //20150925
	//添加子节点
	//参数：
	//		node: 子节点指针
	//返回值：无
	virtual void addChild(ui_node* node);
	//获得子节点
	//参数：
	//		index: 子节点索引
	//返回值：子节点指针
	virtual ui_node* getChild(int index);
	//设置父节点
	//参数：
	//		node: 父节点指针
	//返回值：无
	virtual void setParent(ui_node* node);
	//获得父节点
	//参数：无
	//返回值：父节点指针
	virtual ui_node* getParent();
	//获得子节点数量
	//参数：无
	//返回值：子节点数量
	virtual int getChildNum(){return _uiChildren.size();}
	//设置节点类型
	//参数：
	//		type: 节点类型
	//返回值：无
	virtual void setType(NodeType type){_type = type;}
	//获得节点类型
	//参数：无
	//返回值：节点类型
	virtual NodeType getType(){return _type;}
	//获得节点关联对象指针
	//参数：无
	//返回值：关联对象指针
    virtual void* getObject(const char* name="");
	//设置节点关联对象指针
	//参数：
	//		object：关联对象指针
	//返回值：无
    virtual void setObject(void* object,const char* name="");
	//复制节点
	//参数：
	//		node: 要复制的节点指针
	//返回值：无
	virtual void clone(ui_node* node);
protected:
	//合并两个属性表
	//参数：
	//		ta: 目标属性表
	//		fa: 源属性表
	//返回值：无
	void mergeAttributes(AttributeMapType& ta,AttributeMapType& fa);

private:
	list<ui_node*> _uiChildren; 
	ui_node* _uiParent;
	NodeType _type;
    typedef std::map<std::string, void*> ObjectMapType;
    ObjectMapType _objects;
    std::string _uiName;
};

