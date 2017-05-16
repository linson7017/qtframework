#include "res_config.h"
#include <QtCore/QDir>
#include <QtCore/QStringList>
#include "Uicreator/xml_node.h"
#include "Utils/variant.h"
#include "Utils/util.h"
#include "Utils/variant.h"
#include "Common/app_env.h"
#include "Uicreator/xml_ui_paser.h"
#include "Utils/xml_util.h"
//构造函数
res_config::res_config(void)
{
	string configResDir = app_env::getDir(app_env::CONFIG_RESOURCE);
	std::vector<std::string> files;
	getAllFilesInCurrentDir(configResDir,files,"*.xml");
	std::vector<std::string>::const_iterator it;

	for (it = files.begin(); it != files.end(); ++it )
	{
		string filepath = configResDir;
		filepath.append(*it);
		parseConfigXML(filepath.c_str());
	}
}

//析构函数
res_config::~res_config(void)
{
}
//覆盖Config资源
//参数：无
//返回值：无
void res_config::writeConfigFile()
{
	string filename = app_env::getDir(app_env::CONFIG_RESOURCE);
	filename.append("config.xml");
	xmlDocPtr doc;
	doc = xmlReadFile(filename.c_str(),"utf-8",XML_PARSE_READER);
	if (doc == NULL)
	{
		xmlFreeDoc(doc);
		return;
	}
	xmlNodePtr rootNode = xmlDocGetRootElement(doc);
	if (strcmp((const char*)rootNode->name,"Properties")==0)
	{
		xmlNodePtr str = rootNode->children;
		while(str!=NULL)
		{
			if (strcmp((const char*)str->name,"Property")==0)
			{
				string nameStr = (const char*)xmlGetProp(str,(const xmlChar*)"name");
				if (_change_map.count(nameStr))
				{
					xmlNodeSetContent(str,(const xmlChar*)_change_map[nameStr]->getContent());
					_change_map.erase(nameStr);
				}
			}
			str = str->next;
		}
	}
	ConfigPropertyMapType::const_iterator itor = _change_map.begin();
	while(itor!= _change_map.end())
	{
		xmlNodePtr node = xmlNewNode(NULL,(const xmlChar*)"Property");
		xmlSetProp(node,(const xmlChar*)"name",(const xmlChar*)itor->first.c_str());
		switch(itor->second->getType())
		{
		case variant::Int:
			xmlSetProp(node,(const xmlChar*)"valueType",(const xmlChar*)"int");
			break;
		case variant::Double:
			xmlSetProp(node,(const xmlChar*)"valueType",(const xmlChar*)"double");
			break;
		case variant::Bool:
			xmlSetProp(node,(const xmlChar*)"valueType",(const xmlChar*)"bool");
			break;
		case variant::String:
			xmlSetProp(node,(const xmlChar*)"valueType",(const xmlChar*)"string");
			break;
		default:
			xmlSetProp(node,(const xmlChar*)"valueType",(const xmlChar*)"string");
			break;
		}
		xmlNodeSetContent(node,(const xmlChar*)itor->second->getContent());
		xmlAddChild(rootNode,node);
		++itor;
	}
	xmlSaveFormatFileEnc(filename.c_str(),doc,"UTF-8",1);
	_change_map.clear();
}
//获得配置文件中的属性资源
//参数：id ID
//返回值：资源
variant* res_config::getConfigRes(const char* id)
{
	ConfigPropertyMapType::iterator it = _res_map.find(id);
	if (it != _res_map.end())
	{
		return it->second;
	}else
	{
		char szMsg[1024];
		//sprintf(szMsg, "QtFrameWork ERROR: The config resource whose ID is %s does not exist!\n",id);
		//printf(szMsg);
		return NULL;
	}
}
//设置配置文件中的属性资源
//参数：id ID, v 值
//返回值：是否设置成功
bool res_config::setConfigRes(const char* id,variant* v)
{
	ConfigPropertyMapType::iterator it = _res_map.find(id);
	if (it != _res_map.end())
	{
		it->second = v;
		_change_map[id] = v;
		return true;
	}else
	{
		return false;
	}
}
//添加配置文件中的属性资源
//参数：id ID, v 值
//返回值：是否添加成功
void res_config::addConfigRes(const char* id,variant* v)
{
	_res_map[id] = v; //会覆盖已有属性
	_change_map[id] = v;
}
//解析配置文件xml
//参数：filename 文件路径
//返回值：无
const char* res_config::parseConfigXML(const char* filename)
{
	xmlDocPtr doc;
	doc = xmlReadFile(filename,"utf-8",XML_PARSE_READER);
	if (doc == NULL)
	{
		xmlFreeDoc(doc);
		return "";
	}
	xmlNodePtr curXMLNode = xmlDocGetRootElement(doc);
	if (strcmp((const char*)curXMLNode->name,"Properties")==0)
	{
		xmlNodePtr str = curXMLNode->children;
		while(str!=NULL)
		{
			if (strcmp((const char*)str->name,"Property")==0)
			{
				xml_node strNode;
				strNode.relateXMLNode(str);
				if (strNode.hasAttribute("name")&&strNode.hasAttribute("valueType"))
				{
					if (strcmp(strNode.getAttribute("valueType"),"int")==0||
						strcmp(strNode.getAttribute("valueType"),"INT")==0||
						strcmp(strNode.getAttribute("valueType"),"Int")==0)
					{
						variant* v =  new variant(STR_TO_INT(strNode.getContent()));
						v->setContent(strNode.getContent());
						_res_map[strNode.getAttribute("name")] = v;
					}
					else if (strcmp(strNode.getAttribute("valueType"),"double")==0||
						strcmp(strNode.getAttribute("valueType"),"DOUBLE")==0||
						strcmp(strNode.getAttribute("valueType"),"Double")==0)
					{
						variant* v =  new variant(STR_TO_DOUBLE(strNode.getContent()));
						v->setContent(strNode.getContent());
						_res_map[strNode.getAttribute("name")] = v;
					}
					else if (strcmp(strNode.getAttribute("valueType"),"bool")==0||
						strcmp(strNode.getAttribute("valueType"),"BOOL")==0||
						strcmp(strNode.getAttribute("valueType"),"Bool")==0)
					{
						variant* v =  new variant(STR_TO_BOOL(strNode.getContent()));
						v->setContent(strNode.getContent());
						_res_map[strNode.getAttribute("name")] = v;
					}
					else if (strcmp(strNode.getAttribute("valueType"),"string")==0||
						strcmp(strNode.getAttribute("valueType"),"STRING")==0||
						strcmp(strNode.getAttribute("valueType"),"String")==0)
					{
						variant* v =  new variant(strNode.getContent());
						v->setContent(strNode.getContent());
						_res_map[strNode.getAttribute("name")] = v;
					}
				}
			}
			str = str->next;
		}
	}
	else
	{
		return "";
	}
}
