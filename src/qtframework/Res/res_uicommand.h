/*!
 * \file res_uicommand.h
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

class xml_node;
/*!
 * \class res_uicommand
 *
 * \brief res_uicommand类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class res_uicommand
{
public:
	//构造函数
	//参数：无
	//返回值：无
	res_uicommand(void);
	//析构函数
	//参数：无
	//返回值：无
	~res_uicommand(void);
	//获得UICommand资源
	//参数：id ID
	//返回值：资源
	xml_node* getUICommandRes(const char* id);

private:
	//解析配置文件xml
	//参数：filename 文件路径
	//返回值：无
	void parseUICommandXML(const char* filename);
	map<string,xml_node*> _res_map;
};
