#include "xml_node.h"
//构造函数
//参数：无
//返回值：无
xml_node::xml_node(void):_parent(NULL)
{
	
}

//析构函数
//参数：无
//返回值：无
xml_node::~xml_node(void)
{
}
//释放节点及子节点
//参数：无
//返回值：无
void xml_node::release()
{//20150925
	for (list<xml_node*>::iterator itor = _childs.begin();itor!=_childs.end();itor++ )
	{
		xml_node* child = *itor;
		if (child !=NULL)
		{
			child->release();
		}
	}
	delete this;
}
//获得属性
//参数：
//		key: 键值
//返回值：属性字符串
const char* xml_node::getAttribute(const char* key)
{
	map<string,string>::iterator it = _attributes.find(key);
	if (it!=_attributes.end())
	{
		return it->second.c_str();
	}else
	{
		return "";
	}
}
//是否具有属性
//参数：
//		key: 键值
//返回值：存在key属性返回true，否则返回false
bool xml_node::hasAttribute(const char* key)
{
	if (_attributes.count(key))
	{
		return true;
	}else
	{
		return false;
	}
}
//添加子节点
//参数：
//		node: 子节点指针
//返回值：无
void xml_node::addChild(xml_node* node)
{
	_childs.push_back(node);
	node->setParent(this);
}
//获得子节点
//参数：
//		index: 子节点索引
//返回值：子节点指针
xml_node* xml_node::getChild(int index)
{
	list<xml_node*>::iterator itor = _childs.begin();
	while(index !=0 )
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
void xml_node::setParent(xml_node* node)
{
	_parent = node;
}
//获得父节点
//参数：无
//返回值：父节点指针
xml_node* xml_node::getParent()
{
	return _parent;
}
//添加属性
//参数：
//		key: 键值
//		value: 值
//返回值：无
void xml_node::addAttribute(const char* key,const char* value) 
{
	_attributes[key] = value;
}
//将节点与xmlNode节点关联，获得属性
//参数：
//		xmlNode: xmlNode节点指针
//返回值：无
void xml_node::relateXMLNode(xmlNode* xmlnode)
{
	_xmlNode = xmlnode;
	xmlAttr* attr = xmlnode->properties;
	setName((const char*)xmlnode->name);
	setContent((char*)xmlNodeGetContent(xmlnode));
	while(attr!=NULL)
	{
        std::string attributeName = (const char*)attr->name;
        if (strcmp(attributeName.substr(0,9).c_str(),"parameter")==0)
        {
            std::string valueStr = (const char*)attr->children->content;
            int i = valueStr.find(":");
            if (i != std::string::npos)
            {
                std::string type = valueStr.substr(0, i);
                std::string vs = valueStr.substr(i + 1, valueStr.length() - 1 - i);
                variant value;
                if (strcmp(type.c_str(), "bool") == 0 || strcmp(type.c_str(), "Bool") == 0 || strcmp(type.c_str(), "BOOL") == 0)
                {
                    if (strcmp(vs.c_str(), "true") == 0 || strcmp(vs.c_str(), "TRUE") == 0)
                        value.setBool(true);
                    else
                        value.setBool(false);
                }
                else if (strcmp(type.c_str(), "int") == 0 || strcmp(type.c_str(), "Int") == 0 || strcmp(type.c_str(), "INT") == 0)
                {
                    value.setInt(atoi(vs.c_str()));
                }
                else if (strcmp(type.c_str(), "double") == 0 || strcmp(type.c_str(), "double") == 0 || strcmp(type.c_str(), "double") == 0)
                {
                    value.setInt(atof(vs.c_str()));
                }
                else
                {
                    value.setString(vs.c_str());
                }
                addParameter((const char*)attr->name, value);
            }
            
        }
		addAttribute((const char*)attr->name,(const char*)attr->children->content);
        
		attr = attr->next;
	}
	_id = hasAttribute("id")?getAttribute("id"):"NULL";
}


void xml_node::addParameter(const char* key, const variant& parameter)
{
    _parameters[key] = parameter;
}