#include "res_string.h"
#include <QtCore/QDir>
#include <QtCore/QStringList>
#include "Uicreator/xml_node.h"
#include "Common/app_env.h"
#include "Utils/util.h"
//构造函数
//参数：无
//返回值：无
res_string::res_string(void)
{
    _res_map.clear();
    _filesInfo.clear();
    parseResourceXML(app_env::getDir(app_env::STRING_RESOURCE));
}

//析构函数
//参数：无
//返回值：无
res_string::~res_string(void)
{
}

void res_string::releaseResource()
{
    xml_res_base::releaseResource();
    _res_map.clear();
    _resList_map.clear();
}
//获得String资源
//参数：id ID
//返回值：资源
const char* res_string::getStringRes(const char* id)
{
    CHECK_FILES_CHANGED(STRING_RESOURCE)
	StringMapType::iterator it = _res_map.find(id);
	if (it != _res_map.end())
	{
		return it->second.c_str();
	}else
	{
		char szMsg[1024];
	//	sprintf(szMsg, "QtFrameWork ERROR: The string resource whose ID is %s does not exist!\n",id);
	//	printf(szMsg);
		return "";
	}
}

vector<string> res_string::getStringListRes(const char* id)
{
	StringListMapType::iterator it = _resList_map.find(id);
	if (it != _resList_map.end())
	{
		return it->second;
	}else
	{
		char szMsg[1024];
	//	sprintf(szMsg, "QtFrameWork ERROR: The stringList resource whose ID is %s does not exist!\n",id);
	//	printf(szMsg);
		return vector<string>();
	}
}

//解析配置文件xml
//参数：filename 文件路径
//返回值：无
void res_string::parseXML(const char* filename)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile(filename);
    if (error != tinyxml2::XML_SUCCESS)
    {
        printf("Load xml file %s failed! Error code: %s \n", filename, doc.ErrorStr());
        return;
    }
    tinyxml2::XMLElement* curXMLNode = doc.RootElement();

	if (strcmp(curXMLNode->Name(),"strings")==0)
	{
        tinyxml2::XMLElement* str = curXMLNode->FirstChildElement();
		while(str!=NULL)
		{
			if (strcmp(str->Name(),"string")==0)
			{
				xml_node strNode;
				strNode.relateXMLNode(str);
				if (strNode.hasAttribute("id"))
				{
					_res_map[strNode.getAttribute("id")] = strNode.getContent();
				}
			}
			else if (strcmp(str->Name(),"stringlist")==0)
			{
				xml_node strNodeList;
				strNodeList.relateXMLNode(str);
                tinyxml2::XMLElement* strList = str->FirstChildElement();
				vector<string> vs;
				while (strList!=NULL)
				{
					if (strcmp(strList->Name(),"string")==0)
					{
						xml_node strNode;
						strNode.relateXMLNode(strList);
						if (strNode.hasAttribute("id"))
						{
							_res_map[strNode.getAttribute("id")] = strNode.getContent();
						}
						vs.push_back(strNode.getContent());
					}
					strList = strList->NextSiblingElement();
				}
				if (strNodeList.hasAttribute("id")&&vs.size()>0)
				{
					_resList_map[strNodeList.getAttribute("id")] = vs;
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
