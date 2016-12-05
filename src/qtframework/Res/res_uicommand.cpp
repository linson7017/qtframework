#include "res_uicommand.h"
#include "Uicreator/xml_node.h"
#include "Common/app_env.h"
#include "Utils/Log.h"
#include "Utils/util.h"

//构造函数
//参数：无
//返回值：无
res_uicommand::res_uicommand(void)
{
	string uicommandResDir = app_env::getDir(app_env::UICOMMAND_RESOURCE);
	std::vector<std::string> files;
	std::vector<std::string>::const_iterator it;
	getAllFilesInCurrentDir(uicommandResDir,files,"*.xml");
	for (it = files.begin(); it != files.end(); ++it )
	{
		string filepath = uicommandResDir;
		filepath.append(*it);
		parseUICommandXML(filepath.c_str());
	}
}

//析构函数
//参数：无
//返回值：无
res_uicommand::~res_uicommand(void)
{
}
//获得UICommand资源
//参数：id ID
//返回值：资源
xml_node* res_uicommand::getUICommandRes(const char* id)
{
	map<string,xml_node*>::iterator it = _res_map.find(id);
	if (it != _res_map.end())
	{
		return it->second;
	}else
	{
		return NULL;
	}
}
//解析配置文件xml
//参数：filename 文件路径
//返回值：无
void res_uicommand::parseUICommandXML(const char* filename)
{
	xmlDocPtr doc;
	doc = xmlReadFile(filename,"utf-8",XML_PARSE_READER);
	if (doc == NULL)
	{
		xmlFreeDoc(doc);
		return;
	}
	xmlNodePtr curXMLNode = xmlDocGetRootElement(doc);
	if (strcmp((const char*)curXMLNode->name,"UICommand")==0)
	{
		xmlNodePtr str = curXMLNode->children;
		while(str!=NULL)
		{
			if (strcmp((const char*)str->name,"Command")==0)
			{
				xml_node* strNode = new xml_node;
				strNode->relateXMLNode(str);
				if (strNode->hasAttribute("id"))
				{
					_res_map[strNode->getAttribute("id")] = strNode;					
				}
			}
			else if(strcmp((const char*)str->name,"Commands")==0)
			{
				xml_node* commandsNode = new xml_node;
				commandsNode->relateXMLNode(str);
				xmlNodePtr strchild = str->children;
				while(strchild!=NULL)
				{
					if (strcmp((const char*)strchild->name,"Command")==0)
					{
						xml_node* commandNode = new xml_node;
						commandNode->relateXMLNode(strchild);
						commandsNode->addChild(commandNode);
					}
					strchild = strchild->next;
				}
				if (commandsNode->hasAttribute("id"))
				{
					_res_map[commandsNode->getAttribute("id")] = commandsNode;					
				}
				
			}
			str = str->next;
		}
	}
	else
	{
		return;
	}
}
