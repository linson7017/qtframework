/*!
 * \file res_config.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once
#include <map>
#include <string>
using namespace std;
class variant;
//class ui_node;
/*!
 * \class res_config
 *
 * \brief res_config类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class res_config
{
public:
	//构造函数
	//参数：无
	//返回值：无
	res_config(void);
	//析构函数
	//参数：无
	//返回值：无
	~res_config(void);
	//获得配置文件中的属性资源
	//参数：
	//		id:ID
	//返回值：资源
	variant* getConfigRes(const char* id);
	//设置配置文件中的属性资源
	//参数：
	//		id：ID
	//		v:值
	//返回值：是否设置成功
	bool setConfigRes(const char* id,variant* v);
	//添加配置文件中的属性资源
	//参数：
	//		id：ID
	//		v:值
	//返回值：是否添加成功
	void addConfigRes(const char* id,variant* v);
	//覆盖Config资源
	//参数：无
	//返回值：无
	void writeConfigFile();
private:
	//解析配置文件xml
	//参数：
	//	filename:文件路径
	//返回值：无
	const char* parseConfigXML(const char* filename);
	typedef map<string,variant*> ConfigPropertyMapType;
	ConfigPropertyMapType _res_map;
	ConfigPropertyMapType _change_map;
	//ui_node* _res_root;
};

