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

//���캯��
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

//��������
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
//���UI��Դ���ĸ��ڵ㣬��ʱ��û��װ�䣬�ڵ���ObjectΪ�գ��޷����ص�UI��
//������id ID
//����ֵ���ڵ�ָ��
ui_node* R::getUIResource(const char* id)
{
	return _ui_res->getUIRootNode(id);
}

ui_node* R::getToolpanelResource(const char* id)
{
	return _toolpanel_res->getUIRootNode(id);
}


//����Ҽ��˵���Դ
//������id ID
//����ֵ�����ڵ�ָ��
ui_node* R::getMenuResource(const char* id)
{
	return _menu_res->getUIRootNode(id);
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
const xml_node* R::getCommandResource(const char* id)
{
	return _command_res->getCommandRes(id);
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