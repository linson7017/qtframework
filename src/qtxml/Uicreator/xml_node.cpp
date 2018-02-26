#include "xml_node.h"
#include "Utils/tinyxml2.h"
//构造函数
//参数：无
//返回值：无
xml_node::xml_node(void):_parent(NULL) ,TypeOfXMLNode(UNKNOWN), _lineNum(0) , _filename("")
{
	
}

//复制构造函数
//参数：无
//返回值：无
xml_node::xml_node(const xml_node& node)
{
    this->_name = node._name;
    this->_id = node._id;
    this->_content = node._content;
    //this->_childs = node._childs;
    //this->_parent = node._parent;
    this->_attributes = node._attributes;
    this->_parameters = node._parameters;
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
void xml_node::relateXMLNode(tinyxml2::XMLNode* xmlnode)
{
    _lineNum = xmlnode->GetLineNum();
    if (xmlnode->ToComment())
    {
        TypeOfXMLNode = COMMENT;
        setName((const char*)xmlnode->Value());
        setContent(xmlnode->Value());
    }
    if (xmlnode->ToElement())
    {
        TypeOfXMLNode = ELEMENT;
        setName((const char*)xmlnode->ToElement()->Name());
        if (xmlnode->ToElement()->GetText())
        {
            setContent(xmlnode->ToElement()->GetText());
        }
        const tinyxml2::XMLAttribute* attr = xmlnode->ToElement()->FirstAttribute();
        while (attr != NULL)
        {
            std::string attributeName = (const char*)attr->Name();
            if (strcmp(attributeName.substr(0, 9).c_str(), "parameter") == 0)
            {
                std::string valueStr = (const char*)attr->Value();
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
                    setParameter((const char*)attr->Name(), value);
                }

            }
            addAttribute((const char*)attr->Name(), (const char*)attr->Value());

            attr = attr->Next();
        }
        _id = hasAttribute("id") ? getAttribute("id") : "NULL";
    }    
    
}

void xml_node::setParameter(const char* key, const variant& parameter)
{
    _parameters[key] = parameter;
}

variant& xml_node::getParameter(const char* key)
{
    ParameterMapType::iterator it = _parameters.find(key);
    if (it!= _parameters.end())
    {
        return _parameters[key];
    }
    else
    {
        return variant();
    }
}