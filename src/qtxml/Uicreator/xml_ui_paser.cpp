#include "xml_ui_paser.h"
#include "Uicreator/ui_node.h"
#include "Res/R.h"
#include <iostream>
#include <string.h>
#include "Utils/util.h"
//构造函数
//参数：无
//返回值：无

std::string xml_ui_paser::_currentFileName = "";
xml_ui_paser::xml_ui_paser()
{	
}
//析构函数
//参数：无
//返回值：无
xml_ui_paser::~xml_ui_paser()
{
}

//解析xml文件
//参数：无
//返回值：是否解析成功
bool xml_ui_paser::parserXML(const char* filename, ui_node* root)
{
    if (!root)
    {
        return false;
    }
    tinyxml2::XMLDocument doc;
	logFileOrPathExist(filename);
    tinyxml2::XMLError error=doc.LoadFile(filename);
	if (error != tinyxml2::XML_SUCCESS)
	{
        std::cout << "Load xml file " << filename << " failed! " << "Error code: " << doc.ErrorStr() << std::endl;
		return false;
	}
    _currentFileName = filename;
    tinyxml2::XMLNode* curXMLNode = doc.RootElement();
	if (!curXMLNode)
	{
		return false;
	}
    root->relateXMLNode(curXMLNode);
	getXMLList(curXMLNode, root);
    
    _currentFileName = "";
	return true;
}
//获得节点树
//参数：
//		node: xmlNodePtr节点
//		uinode: ui_node节点
//返回值：无
void xml_ui_paser::getXMLList(tinyxml2::XMLNode* node,ui_node* uinode)
{
	if (!node->NoChildren())
	{
		tinyxml2::XMLNode* child = node->FirstChild();
		for (;child;child = child->NextSiblingElement())
		{
			ui_node* un = new ui_node;
			un->relateXMLNode(child);
            un->setFilename(_currentFileName.c_str());
            if (child->ToElement())
            {
                //如果是Holder则去资源里面获得对应的节点树并拷贝给它，这样防止assembler里面处理Holder出现递归混乱的问题
                if (strcmp(un->getName(), "Holder") == 0 && un->hasAttribute("id"))
                {
                    std::string res = un->getAttribute("id");
                    int i = res.find_first_of("@ui/");
                    res = res.substr(i + 4);
                    ui_node* node = R::Instance()->getUIResource(res.c_str());
                    if (node)
                    {
                        un->clone(node);
                    }
                }
            }
			uinode->addChild(un);
			getXMLList(child,un);
		}
	}
}

