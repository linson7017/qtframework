/*!
 * \file R.h
 *
 * \author 宋凌
 * \date 五月 2016
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

class ui_node;
class xml_node;
class Activity;
class variant;

class xml_ui_base;

class R_Private;
/*!
 * \class R
 *
 * \brief 资源类
 *
 * \author 宋凌
 * \date 五月 2016
 */

class QTXML_EXPORT R
{
public:
	 //程序结束析构单例实例
	class Garbo 
	{
	public:
		//构造函数
		Garbo(){}
		//析构函数
		~Garbo()
		{
			if (_res)
			{
				delete _res; //删除R实例
			}
		}
	};
	//析构函数
	~R();
	//获得R实例
	//参数：无
	//返回值：实例指针
    static R* Instance();

	//获得Style资源
	//参数：id ID
	//返回值：资源
	static const char* getStyleResource(const char* id);

	//获得String资源
	//参数：id ID
	//返回值：资源
	static const char* getStringResource(const char* id);
	static std::vector<std::string> getStringListResource(const char* id);

	//获得Application的样式
	//参数：无
	//返回值：资源
	static const char* getMainStyle();

	//获得UICommand资源
	//参数：id ID
	//返回值：资源
	static const xml_node* getCommandResource(const char* id);

	//获得快捷键资源
	//参数：name ID
	//返回值：资源
	static xml_node* getShortcutResource(const char* name);
	//获得配置文件中的属性资源
	//参数：name ID
	//返回值：资源
	static const variant* getConfigResource(const char* name);

	//向全局的Map中添加id-Object
	//参数：id ID，object 对象指针
	//返回值：添加是否成功
	static bool addObjectGlobalMap(const char* id,void* object);

	//从全局Map中获取id-Object
	//参数：id ID
	//返回值：实例指针
	static void* getObjectFromGlobalMap(const char* id);

	//向全局的Map中添加id-Activity
	//参数：id ID，activity 对象指针
	//返回值：添加是否成功
	static bool addActivity(const char* id,Activity* activity);

	//从全局Map中获取id-Activity
	//参数：id ID
	//返回值：实例指针
	static Activity* getActivity(const char* id);

	//获得UI资源树的根节点，此时还没有装配，节点中Object为空，无法加载到UI上
	//参数：id ID
	//返回值：节点指针
	static ui_node* getUIResource(const char* id);
	//获得右键菜单资源
	//参数：id ID
	//返回值：根节点指针
	static ui_node* getMenuResource(const char* id);

	//获得toolpanel资源树的根节点，此时还没有装配，节点中Object为空，无法加载到UI上
	//参数：id ID
	//返回值：节点指针
	static ui_node* getToolpanelResource(const char* id);
	
	//对Config资源进行操作
	//改变Config资源,不存在会添加
	//参数：id ID， variant 值
	//返回值：根节点指针
	static bool setConfigResource(const char* id,variant* v);
	//添加Config资源,存在会覆盖
	//参数：id ID， variant 值
	//返回值：根节点指针

	static void addConfigResource(const char* id,variant* v);
	//覆盖Config资源
	//参数：无
	//返回值：无
	static void overWriteConfigFile();

	//注册用户自定义的Widget//20150925
	//参数：name ID， object 控件指针
	//返回值：无
	static void registerCustomWidget(const char* name,void* object);

	//获得用户自定义的Widget
	//参数：name ID
	//返回值：控件指针
	static void* getCustomWidget(const char* name);

    static const char* getImageResourceUrl(const char* name);


    static void addUINodeName(const char* name);
    static bool hasUINodeName(const char* name);

    static void addIdentifiedNode(const char* id, xml_node* node);
    static xml_node* getIdentifiedNode(const char* id);

    void Constructed();
private:
	//构造函数
	R();
    static Garbo _garbo;
    static R* _res;
    static R_Private* _rp;
};

#endif
