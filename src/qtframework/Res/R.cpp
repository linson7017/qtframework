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
#include <iostream>
#include <Res/res_toolpanel.h>
#include <Utils/util.h>
#include <Common/app_env.h>
#include <qfmain/internal/iqf_main_ext.h>


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
set<string> R::_UINodeNameSet;

//���캯��
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

R* R::Instance()
{
    if (_res == 0)
    {
        _res = new R;
    }
    return _res;
}

//��������
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
//���UI��Դ���ĸ��ڵ㣬��ʱ��û��װ�䣬�ڵ���ObjectΪ�գ��޷����ص�UI��
//������id ID
//����ֵ���ڵ�ָ��
ui_node* R::getUIResource(const char* id)
{
	return _ui_res->getUIRes(id);
}

ui_node* R::getToolpanelResource(const char* id)
{
	return _toolpanel_res->getToolpanelRes(id);
}


//����Ҽ��˵���Դ
//������id ID
//����ֵ�����ڵ�ָ��
ui_node* R::getMenuResource(const char* id)
{
	return _menu_res->getMenuRes(id);
}
//���Style��Դ
//������id ID
//����ֵ����Դ
const char* R::getStyleResource(const char* id)
{
	return _style_res->getStyleRes(id);
}
//���String��Դ
//������id ID
//����ֵ����Դ
const char* R::getStringResource(const char* id)
{
	return _string_res->getStringRes(id);
}

std::vector<string> R::getStringListResource(const char* id)
{
	return _string_res->getStringListRes(id);
}
//���Application����ʽ
//��������
//����ֵ����Դ
const char*  R::getMainStyle()  //��ó���ȫ�ֵķ�� windowsxp��
{
	return _style_res->getMainStyle();
}
//���UICommand��Դ
//������id ID
//����ֵ����Դ
const xml_node* R::getUICommandResource(const char* id)
{
	return _uicommand_res->getUICommandRes(id);
}
//��������ļ��е�������Դ
//������name ID
//����ֵ����Դ
const variant* R::getConfigResource(const char* name)
{
	return _config_res->getConfigRes(name);
}
//��ÿ�ݼ���Դ
//������name ID
//����ֵ����Դ
xml_node* R::getShortcutResource(const char* name)
{
	return _shortcut_res->getShortcutRes(name);
}
//��ȫ�ֵ�Map�����id-Object
//������id ID��object ����ָ��
//����ֵ������Ƿ�ɹ�
bool R::addObjectGlobalMap(const char* id,void* object)
{
	if (strcmp(id,"")==0)
	{
		return false;
	}
	_global_IDObjectMap[id] = object;
	return true;
}
//��ȫ��Map�л�ȡid-Object
//������id ID
//����ֵ��ʵ��ָ��
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
//��ȫ�ֵ�Map�����id-Activity
//������id ID��activity ����ָ��
//����ֵ������Ƿ�ɹ�
bool R::addActivity(const char* id,Activity* activity)
{
	if (strcmp(id,"")==0)
	{
		return false;
	}
	_ActivityMap[id] = activity;
	return true;
}
//��ȫ��Map�л�ȡid-Activity
//������id ID
//����ֵ��ʵ��ָ��
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
//�ı�Config��Դ,�����ڻ����
//������id ID�� variant ֵ
//����ֵ�����ڵ�ָ��
bool R::setConfigResource(const char* id,variant* v)
{
	return _config_res->setConfigRes(id,v);
}
//���Config��Դ,���ڻḲ��
//������id ID�� variant ֵ
//����ֵ�����ڵ�ָ��
void R::addConfigResource(const char* id,variant* v)
{
	_config_res->addConfigRes(id,v);
}
//ע���û��Զ����Widget//20150925
//������name ID�� object �ؼ�ָ��
//����ֵ����
void R::overWriteConfigFile()
{
	_config_res->writeConfigFile();
}

//ע���û��Զ����Widget//20150925
//������name ID�� object �ؼ�ָ��
//����ֵ����
void R::registerCustomWidget(const char* name,void* object)
{
    if (object==NULL)
    {
        return;
        std::cerr << "Register Custom Widget " << name << " Failed! " << "Because The Widget Has Not Instanced!";
    }
	_customWidgetMap[name] = object;
}
//����û��Զ����Widget
//������name ID
//����ֵ���ؼ�ָ��
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