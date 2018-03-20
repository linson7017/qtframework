/*!
 * \file R.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#ifndef R_H
#define R_H

#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>
#include "Common/qtxml_com.h"
using namespace std;

class ui_node;
class res_style;
class res_string;
class res_command;
class xml_node;
class res_config;
class Activity;
class variant;
class res_shortcut;

class xml_ui_base;
/*!
 * \class R
 *
 * \brief ��Դ��
 *
 * \author ����
 * \date ���� 2016
 */

class QTXML_EXPORT R
{
public:
	 //���������������ʵ��
	class Garbo 
	{
	public:
		//���캯��
		Garbo(){}
		//��������
		~Garbo()
		{
			if (_res)
			{
				delete _res; //ɾ��Rʵ��
			}
		}
	};
	//��������
	~R();
	//���Rʵ��
	//��������
	//����ֵ��ʵ��ָ��
    static R* Instance();

	//���Style��Դ
	//������id ID
	//����ֵ����Դ
	static const char* getStyleResource(const char* id);
	//���String��Դ
	//������id ID
	//����ֵ����Դ
	static const char* getStringResource(const char* id);
	static std::vector<string> getStringListResource(const char* id);
	//���Application����ʽ
	//��������
	//����ֵ����Դ
	static const char* getMainStyle();
	//���UICommand��Դ
	//������id ID
	//����ֵ����Դ
	static const xml_node* getCommandResource(const char* id);
	//��ÿ�ݼ���Դ
	//������name ID
	//����ֵ����Դ
	static xml_node* getShortcutResource(const char* name);
	//��������ļ��е�������Դ
	//������name ID
	//����ֵ����Դ
	static const variant* getConfigResource(const char* name);
	//��ȫ�ֵ�Map������id-Object
	//������id ID��object ����ָ��
	//����ֵ�������Ƿ�ɹ�
	static bool addObjectGlobalMap(const char* id,void* object);
	//��ȫ��Map�л�ȡid-Object
	//������id ID
	//����ֵ��ʵ��ָ��
	static void* getObjectFromGlobalMap(const char* id);
	//��ȫ�ֵ�Map������id-Activity
	//������id ID��activity ����ָ��
	//����ֵ�������Ƿ�ɹ�
	static bool addActivity(const char* id,Activity* activity);
	//��ȫ��Map�л�ȡid-Activity
	//������id ID
	//����ֵ��ʵ��ָ��
	static Activity* getActivity(const char* id);
	//���UI��Դ���ĸ��ڵ㣬��ʱ��û��װ�䣬�ڵ���ObjectΪ�գ��޷����ص�UI��
	//������id ID
	//����ֵ���ڵ�ָ��
	static ui_node* getUIResource(const char* id);
	//����Ҽ��˵���Դ
	//������id ID
	//����ֵ�����ڵ�ָ��
	static ui_node* getMenuResource(const char* id);

	//���toolpanel��Դ���ĸ��ڵ㣬��ʱ��û��װ�䣬�ڵ���ObjectΪ�գ��޷����ص�UI��
	//������id ID
	//����ֵ���ڵ�ָ��
	static ui_node* getToolpanelResource(const char* id);
	
	//��Config��Դ���в���
	//�ı�Config��Դ,�����ڻ�����
	//������id ID�� variant ֵ
	//����ֵ�����ڵ�ָ��
	static bool setConfigResource(const char* id,variant* v);
	//����Config��Դ,���ڻḲ��
	//������id ID�� variant ֵ
	//����ֵ�����ڵ�ָ��
	static void addConfigResource(const char* id,variant* v);
	//����Config��Դ
	//��������
	//����ֵ����
	static void overWriteConfigFile();

	//ע���û��Զ����Widget//20150925
	//������name ID�� object �ؼ�ָ��
	//����ֵ����
	static void registerCustomWidget(const char* name,void* object);
	//����û��Զ����Widget
	//������name ID
	//����ֵ���ؼ�ָ��
	static void* getCustomWidget(const char* name);

    static std::string getImageResourceUrl(const char* name);


    static void addUINodeName(const char* name);
    static bool hasUINodeName(const char* name);

    static void addIdentifiedNode(const char* id, xml_node* node);
    static xml_node* getIdentifiedNode(const char* id);

    void Constructed();
private:
	//���캯��
	R();
	static res_style* _style_res;
	static res_string* _string_res;
	static res_command* _command_res;
	static res_config* _config_res;
	static res_shortcut* _shortcut_res;

    //UI
	static xml_ui_base* _toolpanel_res;
    static xml_ui_base* _ui_res;
    static xml_ui_base* _menu_res;

	typedef map< string,void* > IDObjectMapType;
	static IDObjectMapType _global_IDObjectMap; //ȫ�ֵĿؼ���
	static IDObjectMapType _customWidgetMap;  //�û�ע���Widget�� //20150925
	typedef map< string,Activity* > IDActivityMapType;
    static set<string> _UINodeNameSet;
	static IDActivityMapType _ActivityMap;;
	static R* _res;
	static Garbo _garbo;
    typedef map<string, xml_node*> IdentifiedNodeMapType;
    static IdentifiedNodeMapType _IdentifiedNodeMap;
};

#endif