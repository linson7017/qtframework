#include "xml_ui_paser.h"
#include "Uicreator/ui_node.h"
#include "Res/R.h"
#include <iostream>
#include <string.h>
#include "Utils/util.h"
//构造函数
//参数：无
//返回值：无
xml_ui_paser::xml_ui_paser()
{	
}
//构造函数
//参数：
//		filename: 解析的文件路径
//返回值：无
xml_ui_paser::xml_ui_paser(const char* filename)
	:_filename(std::string(filename)),_root(NULL)

{
}
//析构函数
//参数：无
//返回值：无
xml_ui_paser::~xml_ui_paser()
{
    _root->release();//析构掉根节点 20150925
}

//解析xml文件
//参数：无
//返回值：是否解析成功
bool xml_ui_paser::parserXML()
{

	xmlKeepBlanksDefault(0);
	xmlDocPtr doc;
	logFileOrPathExist(_filename.c_str(),Log::LOG_ERROR);
	doc = xmlReadFile(_filename.c_str(),"utf-8",XML_PARSE_READER);
	if (doc == NULL)
	{
		xmlFreeDoc(doc);
		return false;
	}
	xmlNodePtr curXMLNode = xmlDocGetRootElement(doc);
	if (!curXMLNode)
	{
		return false;
	}
	if (!_root)
	{
		_root = new ui_node;
	}
	_curnode = _root;
	//relateXMLNodeAndUINode(curXMLNode,_curnode);
	_curnode->relateXMLNode(curXMLNode);
	getXMLList(curXMLNode,_curnode);
	xmlFreeDoc(doc);
	return true;
}
//关联xmlNodePtr节点和 ui_node节点
//参数：
//		node: xmlNodePtr节点
//		uinode: ui_node节点
//返回值：无
void xml_ui_paser::relateXMLNodeAndUINode(xmlNodePtr xmlnode,ui_node* uinode)
{
	xmlAttr* attr = xmlnode->properties;
	uinode->setName((const char*)xmlnode->name);
	
	while(attr!=NULL)
	{
		uinode->addAttribute((const char*)attr->name,(const char*)attr->children->content);
		attr = attr->next;
	}
}
//获得节点树
//参数：
//		node: xmlNodePtr节点
//		uinode: ui_node节点
//返回值：无
void xml_ui_paser::getXMLList(xmlNodePtr node,ui_node* uinode)
{
	if (node->children != NULL)
	{
		xmlNodePtr child = node->children;
		for (;child;child = child->next)
		{
			
			if (child->type == XML_ELEMENT_NODE)
			{
				ui_node* un = new ui_node;
				//relateXMLNodeAndUINode(child,un);  //保留
				un->relateXMLNode(child);
				//如果是Holder则去资源里面获得对应的节点树并拷贝给它，这样防止assembler里面处理Holder出现递归混乱的问题
				if (strcmp(un->getName(),"Holder")==0&&un->hasAttribute("id")) 
				{
					std::string res = un->getAttribute("id");
					int i = res.find_first_of("@ui/");
					res = res.substr(i+4);
					ui_node* node = R::Instance()->getUIResource(res.c_str());
					if (node)
					{
						un->clone(node);
					}	
				}
				uinode->addChild(un);
				std::string content = (char*)xmlNodeGetContent(child);
				getXMLList(child,un);
			}
		}
	}
}
//获得节点树根节点
//参数：无
//返回值：节点树根节点指针
ui_node* xml_ui_paser::getRoot()
{
	return _root;
}

