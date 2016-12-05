#include "res_ui.h"
#include "Uicreator/xml_ui_paser.h"
#include "Utils/util.h"
#include "Common/app_env.h"
#include "Uicreator/ui_node.h"
//构造函数
//参数：无
//返回值：无
res_ui::res_ui()
{
	string uiResDir = app_env::getDir(app_env::UI_RESOURCE);
	std::vector<std::string> files;
	getAllFilesInCurrentDir(uiResDir,files,"*.xml");
	std::vector<std::string>::const_iterator it;

	for (it = files.begin(); it != files.end(); ++it )
	{
		string filepath = uiResDir;
		filepath.append(*it);
		xml_ui_paser* parser = new xml_ui_paser(filepath.c_str());
		if (parser->parserXML())
		{
			if (parser->getRoot()->hasAttribute("id"))
			{
				string id = parser->getRoot()->getAttribute("id");
				if (!_res_map.count(id.c_str()))
				{
					_res_map[id] = parser->getRoot();
				}
			}	
		}
	}
}

//析构函数
//参数：无
//返回值：无
res_ui::~res_ui()
{
}
//获得UI资源树的根节点，此时还没有装配，节点中Object为空，无法加载到UI上
//参数：id ID
//返回值：节点指针
ui_node* res_ui::getUIRes(const char* id)
{
	ResMapType::iterator it = _res_map.find(id);
	if (it != _res_map.end())
	{
		return it->second;
	}else
	{
		return NULL;
	}
	
}
