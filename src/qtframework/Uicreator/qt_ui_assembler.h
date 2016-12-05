/*!
 * \file qt_ui_assembler.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once
#include "ui_node.h"

class xml_ui_paser;
class event_handler;
class sl_MutexButtonBox;
class AView;
/*!
 * \class qt_ui_assembler
 *
 * \brief qt_ui_assembler类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class qt_ui_assembler
{
public:
	//构造函数
	//参数：
	//		root: 节点树的根节点
	//返回值：无
	qt_ui_assembler(ui_node* root);
	//构造函数
	//参数：
	//		parser: 解析器指针
	//返回值：无
	qt_ui_assembler(xml_ui_paser* parser);
	//析构函数
	//参数：无
	//返回值：无
	~qt_ui_assembler(void);
	//组装
	//参数：无
	//返回值：无
	void assemble();
	//获得根节点关联对象
	//参数：无
	//返回值：根节点关联对象
	void* getRootObject();
	//获得根节点对象
	//参数：无
	//返回值：根节点对象
	ui_node* getUINodeTreeRoot(){return _root;}
	//获得根节点类型
	//参数：无
	//返回值：节点类型
	ui_node::NodeType getRootType();
	//获得对象指针
	//参数：
	//		id: 对象id
	//返回值：对象指针
	void* getObjectByID(const char* id);
	//获得事件处理器
	//参数：无
	//返回值：事件处理器指针
	void* getEventHandler();
protected:
	//解析节点树
	//参数：
	//	node: 根节点指针
	//返回值：无
	void parseUITree(ui_node* node);
	//创建每个节点的实例
	//参数：
	//	node: 根节点指针
	//返回值：无
	bool createUI(ui_node* node);										//创建每个节点的实例
	//解析Widget类型节点的共有属性
	//参数：
	//	node: 根节点指针
	//返回值：无
	void ParseWidgetCommonAttribute(ui_node* node);						//解析Widget类型节点的共有属性
	//解析Layout类型节点的共有属性
	//参数：
	//	node: 根节点指针
	//返回值：无
	void ParseLayoutCommonAttribute(ui_node* node);						//解析Layout类型节点的共有属性
	//解析节点的QProperty
	//参数：
	//	node: 根节点指针
	//返回值：无
	void ParseObjectProperty(ui_node* node);							//解析节点的QProperty


	//装配子节点和父节点
	//参数：
	//		father: 父节点指针
	//		child: 子节点
	//返回值：无
	void assembleNodes(ui_node* father,ui_node* child);					
	//装配Layout和Widget或者Layout和Layout
	//参数：
	//		father: 父节点指针
	//		child: 子节点
	//返回值：无
	void assembleLayoutAndWidgetOrLayout(ui_node* father,ui_node* child);	//装配Layout和Widget或者Layout和Layout
	//装配Widget和Layout
	//参数：
	//		father: 父节点指针
	//		child: 子节点
	//返回值：无
	void assembleWidgetAndLayout(ui_node* father,ui_node* child);			//装配Widget和Layout
	//装配Container和Widget
	//参数：
	//		father: 父节点指针
	//		child: 子节点
	//返回值：无
	void assembleContainerAndWidget(ui_node* father,ui_node* child);		//装配Container和Widget
	//装配Widget和Widget
	//参数：
	//		father: 父节点指针
	//		child: 子节点
	//返回值：无
	void assembleWidgetAndWidget(ui_node* father,ui_node* child);			//装配Widget和Widget
	//装配Widget和Items
	//参数：
	//		father: 父节点指针
	//		child: 子节点
	//返回值：无
	void assembleWidgetAndItems(ui_node* father,ui_node* child);			//装配Widget和Items
	//装配Widget和Item
	//参数：
	//		father: 父节点指针
	//		child: 子节点
	//返回值：无
	void assembleWidgetAndItem(ui_node* father,ui_node* child);			//装配Widget和Item

	//将ui_node节点和object关联
	//参数：
	//		object:object对象指针
	//		node: 节点指针
	//返回值：是否关联成功
	bool bindObjectWithNode(void* object,ui_node* node);					//将ui_node节点和object关联
	//ID注册
	//参数：
	//		node: 节点指针
	//返回值：无
	void registerID(ui_node* node);
	//创建树形ui节点树
	//参数：
	//		node: 节点指针
	//返回值：无
	void createTreeUI(ui_node* node);

private:
	ui_node* _root;
	xml_ui_paser* _parser;
	event_handler* _event_handler;
	typedef std::map<std::string, void*> IDObjectMapType;
	IDObjectMapType _IDMap;
};



