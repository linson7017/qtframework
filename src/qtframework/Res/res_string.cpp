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
	string stringDir = app_env::getDir(app_env::STRING_RESOURCE);
	std::vector<std::string> files;
	getAllFilesInCurrentDir(stringDir,files,"*.xml");
	std::vector<std::string>::const_iterator it;

	for (it = files.begin(); it != files.end(); ++it )
	{
		string filepath = stringDir;
		filepath.append(*it);
		parseStringXML(filepath.c_str());
	}
}

//析构函数
//参数：无
//返回值：无
res_string::~res_string(void)
{
}
//获得String资源
//参数：id ID
//返回值：资源
const char* res_string::getStringRes(const char* id)
{
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
const char* res_string::parseStringXML(const char* filename)
{
	xmlDocPtr doc;
	doc = xmlReadFile(filename,"utf-8",XML_PARSE_READER);
	if (doc == NULL)
	{
		xmlFreeDoc(doc);
		return "";
	}
	xmlNodePtr curXMLNode = xmlDocGetRootElement(doc);
	if (strcmp((const char*)curXMLNode->name,"strings")==0)
	{
		xmlNodePtr str = curXMLNode->children;
		while(str!=NULL)
		{
			if (strcmp((const char*)str->name,"string")==0)
			{
				xml_node strNode;
				strNode.relateXMLNode(str);
				if (strNode.hasAttribute("id"))
				{
					_res_map[strNode.getAttribute("id")] = strNode.getContent();
				}
			}
			else if (strcmp((const char*)str->name,"stringlist")==0)
			{
				xml_node strNodeList;
				strNodeList.relateXMLNode(str);
				xmlNodePtr strList = str->children;
				vector<string> vs;
				while (strList!=NULL)
				{
					if (strcmp((const char*)strList->name,"string")==0)
					{
						xml_node strNode;
						strNode.relateXMLNode(strList);
						if (strNode.hasAttribute("id"))
						{
							_res_map[strNode.getAttribute("id")] = strNode.getContent();
						}
						vs.push_back(strNode.getContent());
					}
					strList = strList->next;
				}
				if (strNodeList.hasAttribute("id")&&vs.size()>0)
				{
					_resList_map[strNodeList.getAttribute("id")] = vs;
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
