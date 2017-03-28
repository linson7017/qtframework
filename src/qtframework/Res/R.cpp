#include <Res/R.h>
#include <Res/res_ui.h>
#include <Res/res_menu.h>
#include <Res/res_style.h>
#include <Res/res_string.h>
#include <Res/res_string.h>
#include <Res/res_config.h>
#include "Res/res_uicommand.h"
#include "Res/res_shortcut.h"
#include <stdlib.h>
#include <string.h>
#include <Res/res_toolpanel.h>
#include <Utils/util.h>

R* R::_res = NULL;
R::Garbo R::_garbo;
res_ui* R::_ui_res = NULL;
res_menu* R::_menu_res = NULL;
res_style* R::_style_res = NULL;
res_string* R::_string_res =NULL;
res_uicommand* R::_uicommand_res = NULL;
res_shortcut* R::_shortcut_res = NULL;
res_config* R::_config_res = NULL;
res_toolpanel* R::_toolpanel_res = NULL;
map< string,void* > R::_global_IDObjectMap;
map< string,void* > R::_customWidgetMap;
map< string,Activity* > R::_ActivityMap;
//构造函数
R::R()
{
	_string_res = new res_string;
	_config_res = new res_config;
	_ui_res = new res_ui;
	_menu_res = new res_menu;
	_style_res = new res_style;
	_uicommand_res = new res_uicommand;
	_shortcut_res = new res_shortcut;
	_toolpanel_res = new res_toolpanel;
	
}

//析构函数
R::~R()
{
	delete _config_res;
	delete _ui_res;
	delete _menu_res;
	delete _style_res;
	delete _string_res;
	delete _uicommand_res;
	delete _shortcut_res;
}
//获得UI资源树的根节点，此时还没有装配，节点中Object为空，无法加载到UI上
//参数：id ID
//返回值：节点指针
ui_node* R::getUIResource(const char* id)
{
	return _ui_res->getUIRes(id);
}

ui_node* R::getToolpanelResource(const char* id)
{
	return _toolpanel_res->getToolpanelRes(id);
}


//获得右键菜单资源
//参数：id ID
//返回值：根节点指针
ui_node* R::getMenuResource(const char* id)
{
	return _menu_res->getMenuRes(id);
}
//获得Style资源
//参数：id ID
//返回值：资源
const char* R::getStyleResource(const char* id)
{
	return _style_res->getStyleRes(id);
}
//获得String资源
//参数：id ID
//返回值：资源
const char* R::getStringResource(const char* id)
{
	return _string_res->getStringRes(id);
}

std::vector<string> R::getStringListResource(const char* id)
{
	return _string_res->getStringListRes(id);
}
//获得Application的样式
//参数：无
//返回值：资源
const char*  R::getMainStyle()  //获得程序全局的风格 windowsxp等
{
	return _style_res->getMainStyle();
}
//获得UICommand资源
//参数：id ID
//返回值：资源
const xml_node* R::getUICommandResource(const char* id)
{
	return _uicommand_res->getUICommandRes(id);
}
//获得配置文件中的属性资源
//参数：name ID
//返回值：资源
const variant* R::getConfigResource(const char* name)
{
	return _config_res->getConfigRes(name);
}
//获得快捷键资源
//参数：name ID
//返回值：资源
xml_node* R::getShortcutResource(const char* name)
{
	return _shortcut_res->getShortcutRes(name);
}
//向全局的Map中添加id-Object
//参数：id ID，object 对象指针
//返回值：添加是否成功
bool R::addObjectGlobalMap(const char* id,void* object)
{
	if (strcmp(id,"")==0)
	{
		return false;
	}
	_global_IDObjectMap[id] = object;
	return true;
}
//从全局Map中获取id-Object
//参数：id ID
//返回值：实例指针
void* R::getObjectFromGlobalMap(const char* id)
{
	IDObjectMapType::iterator it = _global_IDObjectMap.find(id);
	if (it != _global_IDObjectMap.end())
	{
		return it->second;
	}else
	{
		return NULL;
	}
}
//向全局的Map中添加id-Activity
//参数：id ID，activity 对象指针
//返回值：添加是否成功
bool R::addActivity(const char* id,Activity* activity)
{
	if (strcmp(id,"")==0)
	{
		return false;
	}
	_ActivityMap[id] = activity;
	return true;
}
//从全局Map中获取id-Activity
//参数：id ID
//返回值：实例指针
Activity* R::getActivity(const char* id)
{
	IDActivityMapType::iterator it = _ActivityMap.find(id);
	if (it != _ActivityMap.end())
	{
		return it->second;
	}else
	{
		return NULL;
	}
}
//改变Config资源,不存在会添加
//参数：id ID， variant 值
//返回值：根节点指针
bool R::setConfigResource(const char* id,variant* v)
{
	return _config_res->setConfigRes(id,v);
}
//添加Config资源,存在会覆盖
//参数：id ID， variant 值
//返回值：根节点指针
void R::addConfigResource(const char* id,variant* v)
{
	_config_res->addConfigRes(id,v);
}
//注册用户自定义的Widget//20150925
//参数：name ID， object 控件指针
//返回值：无
void R::overWriteConfigFile()
{
	_config_res->writeConfigFile();
}

//注册用户自定义的Widget//20150925
//参数：name ID， object 控件指针
//返回值：无
void R::registerCustomWidget(const char* name,void* object)
{
	_customWidgetMap[name] = object;
}
//获得用户自定义的Widget
//参数：name ID
//返回值：控件指针
void* R::getCustomWidget(const char* name)
{
	IDObjectMapType::iterator it = _customWidgetMap.find(name);
	if (it!=_customWidgetMap.end())
	{
		return it->second;
	}else
	{
		return NULL;
	}
}


const char* R::getImageResourceUrl(const char* name)
{
    std::string imageUrl;
    getResImageOrIconUrl(imageUrl, name);
    return imageUrl.c_str();
}