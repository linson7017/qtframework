#include "res_menu.h"
#include "Uicreator/xml_ui_paser.h"
#include "Uicreator/ui_node.h"
#include "Common/app_env.h"
#include "Utils/util.h"
//构造函数
//参数：无
//返回值：无
res_menu::res_menu(void)
{
	string menuResDir = app_env::getDir(app_env::MENU_RESOURCE);
	std::vector<std::string> files;
	getAllFilesInCurrentDir(menuResDir,files,"*.xml");
	std::vector<std::string>::const_iterator it;

	for (it = files.begin(); it != files.end(); ++it )
	{
		string filepath = menuResDir;
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
res_menu::~res_menu(void)
{
}
//获得右键菜单资源
//参数：id ID
//返回值：根节点指针
ui_node* res_menu::getMenuRes(const char* id)
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