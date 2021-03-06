#include "res_shortcut.h"
#include <QtCore/QDir>
#include <QtCore/QStringList>
#include "Uicreator/xml_node.h"
#include "Common/app_env.h"
#include "Utils/util.h"

//构造函数
//参数：无
//返回值：无
res_shortcut::res_shortcut(void)
{
	_found_shortcut=NULL;
	string uicommandResDir = app_env::getDir(app_env::SHORTCUT_RESOURCE);
	std::vector<std::string> files;
	getAllFilesInCurrentDir(uicommandResDir,files,"*.xml");
	std::vector<std::string>::const_iterator it;

	for (it = files.begin(); it != files.end(); ++it )
	{
		string filepath = uicommandResDir;
		filepath.append(*it);
		parseShortcutXML(filepath.c_str());
	}
}
//析构函数
//参数：无
//返回值：无
res_shortcut::~res_shortcut(void)
{
}
//全排列数组
//参数：inVec 输入数组, outVec 输出数组, s 起始位置, e大小
//返回值：无
void res_shortcut::perm(vector<string>& inVec,vector<string>& outVec,int s,int e)
{
	int i;
	if (s>=e)
	{
		std::string combinedKeyString;
		for (i=0;i<=e;i++)
		{
			combinedKeyString.append(inVec[i]+"+");
		}
		combinedKeyString.append(inVec[e+1]);
		outVec.push_back(combinedKeyString);
	}
	else
	{
		for (i=s;i<=e;i++)
		{
			if (i!=s)
				swap(inVec[s],inVec[i]);
			perm(inVec,outVec,s+1,e);
			if (i!=s)
				swap(inVec[s],inVec[i]);
		}
	}
}
//交换字符串
//参数：s1 数组1, s2 数组2
//返回值：无
void res_shortcut::swap(string& s1,string& s2)
{
	string temp = s1;
	s1 = s2;
	s2 = temp;
}
//获得快捷键资源
//参数：name ID
//返回值：资源
xml_node* res_shortcut::findRes(const char* name)
{
	ShortcutMapType::iterator it = _res_map.find(name);
	if (it != _res_map.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}
//获得快捷键资源
//参数：name ID
//返回值：资源
xml_node* res_shortcut::getShortcutRes(const char* name)
{
	_found_shortcut = findRes(name);
	if (_found_shortcut)
	{
		return _found_shortcut;
	}
	std::string keyString = name;
	if (keyString.find("+")!=std::string::npos) //如果是组合键则求出全排列，并从xml中查找是否存在，存在则返回对应的节点
	{
		std::vector<std::string> keys;
		std::vector<string> outv;  //输出全排列组合
		splitString(keyString,keys,"+");
		int modifierNum = keys.size()-2; //除了最后一个前面的全排列
		perm(keys,outv,0,modifierNum);
		for (int i=0;i<outv.size();i++)
		{
			_found_shortcut = findRes(outv[i].c_str());
			if (_found_shortcut)
			{
				return _found_shortcut;
			}
		}
	}
	return NULL;
}
//解析配置文件xml
//参数：filename 文件路径
//返回值：无
void res_shortcut::parseShortcutXML(const char* filename)
{
	xmlDocPtr doc;
	doc = xmlReadFile(filename,"utf-8",XML_PARSE_READER);
	if (doc == NULL)
	{
		xmlFreeDoc(doc);
		return;
	}
	xmlNodePtr curXMLNode = xmlDocGetRootElement(doc);
	if (strcmp((const char*)curXMLNode->name,"Shortcuts")==0)
	{
		xmlNodePtr str = curXMLNode->children;
		while(str!=NULL)
		{
			if (strcmp((const char*)str->name,"Shortcut")==0)
			{
				xml_node* strNode = new xml_node;
				strNode->relateXMLNode(str);
				if (strNode->hasAttribute("name"))
				{
					_res_map[strNode->getAttribute("name")] = strNode;
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