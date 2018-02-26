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
    _res_map.clear();
    _filesInfo.clear();
    parseResourceXML(app_env::getDir(app_env::CONFIG_RESOURCE));
}

//析构函数
res_config::~res_config(void)
{
}

void res_config::releaseResource()
{
    xml_res_base::releaseResource();
    _res_map.clear();
}

//覆盖Config资源
//参数：无
//返回值：无
void res_config::writeConfigFile()
{
	string filename = app_env::getDir(app_env::CONFIG_RESOURCE);
	filename.append("config.xml");
    tinyxml2::XMLDocument  doc;
    tinyxml2::XMLError error = doc.LoadFile(filename.c_str());
    if (error != tinyxml2::XML_SUCCESS)
    {
        printf("Load xml file %s failed! Error code: %s \n", filename.c_str(), doc.ErrorStr());
        return;
    }
    tinyxml2::XMLElement* rootNode = doc.RootElement();
	if (strcmp((const char*)rootNode->Name(),"Properties")==0)
	{
        tinyxml2::XMLElement* str = rootNode->FirstChildElement();
		while(str!=NULL)
		{
			if (strcmp((const char*)str->Name(),"Property")==0)
			{
				string nameStr = str->Attribute("name");
				if (_change_map.count(nameStr))
				{
                    str->SetAttribute("name", _change_map[nameStr].getContent());
					_change_map.erase(nameStr);
				}
			}
			str = str->NextSiblingElement();
		}
	}
	ConfigPropertyMapType::const_iterator itor = _change_map.begin();
	while(itor!= _change_map.end())
	{
        tinyxml2::XMLElement* node = doc.NewElement("Property");
        node->SetAttribute("name", itor->first.c_str());
		switch(itor->second.getType())
		{
		case variant::Int:
            node->SetAttribute("valueType", "int");
			break;
		case variant::Double:
            node->SetAttribute("valueType", "double");
			break;
		case variant::Bool:
            node->SetAttribute("valueType", "bool");
			break;
		case variant::String:
            node->SetAttribute("valueType", "string");
			break;
		default:
			break;
		}
        node->SetText(itor->second.getContent());
        rootNode->InsertEndChild(node);
		++itor;
	}
    doc.SaveFile(filename.c_str());
	_change_map.clear();
}
//获得配置文件中的属性资源
//参数：id ID
//返回值：资源
variant* res_config::getConfigRes(const char* id)
{
    CHECK_FILES_CHANGED(CONFIG_RESOURCE)
	ConfigPropertyMapType::iterator it = _res_map.find(id);
	if (it != _res_map.end())
	{
		return &it->second;
	}else
	{
		char szMsg[1024];
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
		it->second = *v;
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
	_res_map[id] = *v; //会覆盖已有属性
	_change_map[id] = *v;
}
//解析配置文件xml
//参数：filename 文件路径
//返回值：无
void res_config::parseXML(const char* filename)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile(filename);
    if (error != tinyxml2::XML_SUCCESS)
    {
        printf("Load xml file %s failed! Error code: %s \n", filename, doc.ErrorStr());
        return;
    }
    tinyxml2::XMLElement* curXMLNode = doc.RootElement();

	if (strcmp(curXMLNode->Name(),"Properties")==0)
	{
        tinyxml2::XMLElement* str = curXMLNode->FirstChildElement();
		while(str!=NULL)
		{
			if (strcmp((const char*)str->Name(),"Property")==0)
			{
				xml_node strNode;
				strNode.relateXMLNode(str);
				if (strNode.hasAttribute("name")&&strNode.hasAttribute("valueType"))
				{
					if (strcmp(strNode.getAttribute("valueType"),"int")==0||
						strcmp(strNode.getAttribute("valueType"),"INT")==0||
						strcmp(strNode.getAttribute("valueType"),"Int")==0)
					{
                        variant v(STR_TO_INT(strNode.getContent()));
						v.setContent(strNode.getContent());
						_res_map[strNode.getAttribute("name")] = v;
					}
					else if (strcmp(strNode.getAttribute("valueType"),"double")==0||
						strcmp(strNode.getAttribute("valueType"),"DOUBLE")==0||
						strcmp(strNode.getAttribute("valueType"),"Double")==0)
					{
                        variant v(STR_TO_DOUBLE(strNode.getContent()));
                        v.setContent(strNode.getContent());
						_res_map[strNode.getAttribute("name")] = v;
					}
					else if (strcmp(strNode.getAttribute("valueType"),"bool")==0||
						strcmp(strNode.getAttribute("valueType"),"BOOL")==0||
						strcmp(strNode.getAttribute("valueType"),"Bool")==0)
					{
                        variant v(STR_TO_BOOL(strNode.getContent()));
                        v.setContent(strNode.getContent());
						_res_map[strNode.getAttribute("name")] = v;
					}
					else if (strcmp(strNode.getAttribute("valueType"),"string")==0||
						strcmp(strNode.getAttribute("valueType"),"STRING")==0||
						strcmp(strNode.getAttribute("valueType"),"String")==0)
					{
                        
                        variant v(strNode.getContent());
                        v.setContent(strNode.getContent());
						_res_map[strNode.getAttribute("name")] = v;
					}
				}
			}
			str = str->NextSiblingElement();
		}
	}
	else
	{
		return;
	}
}
