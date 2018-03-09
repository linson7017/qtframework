#include "ui_node.h"
//构造函数
//参数：无
//返回值：无
ui_node::ui_node():_uiParent(NULL),_type(UNKNOWN) , _uiName("ui")
{

}
//复制构造函数
//参数：无
//返回值：无
ui_node::ui_node(const ui_node& node) :xml_node(node)
{
    this->_type = node._type;
    this->_uiName = node._uiName;
    this->_objects = node._objects;
}
//析构函数
//参数：无
//返回值：无
ui_node::~ui_node()
{
	
}
//释放节点及子节点
//参数：无
//返回值：无
void ui_node::release()
{
	for (list<ui_node*>::iterator itor = _uiChildren.begin();itor!=_uiChildren.end();itor++ )
	{
		ui_node* child = *itor;
		if (child !=NULL)
		{
			child->release();
            child = NULL;
		}
	}
	delete this;
}
//合并两个属性表
//参数：
//		ta: 目标属性表
//		fa: 源属性表
//返回值：无
void ui_node::mergeAttributes(AttributeMapType& ta,AttributeMapType& fa)
{
	typedef AttributeMapType::iterator ItorType;

	for (ItorType faItor = fa.begin();faItor!=fa.end();++faItor)
	{
		ta[faItor->first]=faItor->second;
	}
}
//复制节点
//参数：
//		node: 要复制的节点指针
//返回值：无
void ui_node::clone(ui_node* node)
{
	this->_uiChildren = node->_uiChildren;
	this->_uiParent = node->_uiParent;
	this->_type = node->_type;
	this->_objects = node->_objects;
	this->_name = node->_name;
	this->_id = node->_id;
	//this->_attributes = node->_attributes;
	mergeAttributes(this->_attributes,node->_attributes); //合并两个属性集，重复的属性后面的会覆盖前面的
}
//添加子节点
//参数：
//		node: 子节点指针
//返回值：无
void ui_node::addChild(ui_node* node)
{
	_uiChildren.push_back(node);
	node->setParent(this);
}
//获得子节点
//参数：
//		index: 子节点索引
//返回值：子节点指针
ui_node* ui_node::getChild(int index)
{
	list<ui_node*>::iterator itor = _uiChildren.begin();
	//shisx 删除comboboxitem会死循环
	while(index > 0 )
	//while(index !=0 )
	{
		itor++;
		index--;
	}
	if (*itor!=NULL)
	{
		return *itor;
	}else
	{
		return NULL;
	}
}
//设置父节点
//参数：
//		node: 父节点指针
//返回值：无
void ui_node::setParent(ui_node* node)
{
	_uiParent = node;
}
//获得父节点
//参数：无
//返回值：父节点指针
ui_node* ui_node::getParent()
{
	return _uiParent;
}

//获得节点关联对象指针
//参数：无
//返回值：关联对象指针
void* ui_node::getObject(const char* name)
{
    std::string temp = name;
    if (temp.empty())
    {
        temp = _uiName;
    }
    ObjectMapType::iterator it = _objects.find(temp);
    if (it!=_objects.end())
    {
        return it->second;
    }
    else
    {
        return NULL;
    }

}
//设置节点关联对象指针
//参数：
//		object：关联对象指针
//返回值：无
void ui_node::setObject(void* object, const char* name)
{
    std::string temp = name;
    if (temp.empty())
    {
        temp = _uiName;
    }
    _objects[temp] = object;
}


