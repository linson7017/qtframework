#include "Res/R.h"
#include "Res/res_style.h"
#include "Res/res_string.h"
#include "Res/res_string.h"
#include "Res/res_config.h"
#include "Res/res_command.h"
#include "Res/res_shortcut.h"
#include "Res/xml_ui_base.h"

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <Utils/util.h>
#include <Common/app_env.h>
#include <qfmain/internal/iqf_main_ext.h>


R* R::_res = NULL;
R::Garbo R::_garbo;
res_style* R::_style_res = NULL;
res_string* R::_string_res =NULL;
res_command* R::_command_res = NULL;
res_shortcut* R::_shortcut_res = NULL;
res_config* R::_config_res = NULL;

xml_ui_base* R::_toolpanel_res = NULL;
xml_ui_base* R::_ui_res = NULL;
xml_ui_base* R::_menu_res = NULL;

R::IDObjectMapType R::_global_IDObjectMap;
R::IDObjectMapType R::_customWidgetMap;
R::IDActivityMapType R::_ActivityMap;
set<string> R::_UINodeNameSet;
R::IdentifiedNodeMapType R::_IdentifiedNodeMap;

//构造函数
R::R()
{
	_string_res = new res_string;
	_config_res = new res_config;
	_style_res = new res_style;
	_command_res = new res_command;
	_shortcut_res = new res_shortcut;

    _ui_res = new xml_ui_base(app_env::getUIResDir());
    _menu_res = new xml_ui_base(app_env::getMenuResDir());
	_toolpanel_res = new xml_ui_base(app_env::getDir(app_env::TOOLPANEL_RESOURCE));
   
}

R* R::Instance()
{
    if (_res == 0)
    {
        _res = new R;
    }
    return _res;
}

//析构函数
R::~R()
{
	delete _config_res;
	delete _ui_res;
	delete _menu_res;
	delete _style_res;
	delete _string_res;
	delete _command_res;
	delete _shortcut_res;
}
//获得UI资源树的根节点，此时还没有装配，节点中Object为空，无法加载到UI上
//参数：id ID
//返回值：节点指针
ui_node* R::getUIResource(const char* id)
{
	return _ui_res->getUIRootNode(id);
}

ui_node* R::getToolpanelResource(const char* id)
{
	return _toolpanel_res->getUIRootNode(id);
}


//获得右键菜单资源
//参数：id ID
//返回值：根节点指针
ui_node* R::getMenuResource(const char* id)
{
	return _menu_res->getUIRootNode(id);
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
const xml_node* R::getCommandResource(const char* id)
{
	return _command_res->getCommandRes(id);
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
    if (object==NULL)
    {
        return;
        std::cerr << "Register Custom Widget " << name << " Failed! " << "Because The Widget Has Not Instanced!";
    }
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


std::string R::getImageResourceUrl(const char* name)
{
    std::string imageUrl;
    getResImageOrIconUrl(imageUrl, name);
    return imageUrl;
}

void R::Constructed()
{
    QF::IQF_Main_Ext* pMainExt = (QF::IQF_Main_Ext*)app_env::getMainPtr();
    if (pMainExt)
    {
        pMainExt->ResourceConstructed();
    }
}

void R::addUINodeName(const char* name)
{
    _UINodeNameSet.insert(name);
}

bool R::hasUINodeName(const char* name)
{
    return _UINodeNameSet.count(name);
}

void R::addIdentifiedNode(const char* id, xml_node* node)
{
    IdentifiedNodeMapType::iterator it = _IdentifiedNodeMap.find(id);
    if (it != _IdentifiedNodeMap.end())
    {
        printf("qtxml error: ID %s has been named!");
        return;
    }
    _IdentifiedNodeMap[id] = node;
}

xml_node* R::getIdentifiedNode(const char* id)
{
    IdentifiedNodeMapType::iterator it = _IdentifiedNodeMap.find(id);
    if (it != _IdentifiedNodeMap.end())
    {
        return it->second;
    }
    else
    {
        return NULL;
    }
}