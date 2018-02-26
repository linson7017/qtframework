/*!
 * \file res_uicommand.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once
#include "Res/xml_res_base.h"
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
class res_command :public xml_res_base
{
public:
	//构造函数
	//参数：无
	//返回值：无
    res_command(void);
	//析构函数
	//参数：无
	//返回值：无
	~res_command(void);
	//获得UICommand资源
	//参数：id ID
	//返回值：资源
    xml_node* getCommandRes(const char* id);
    virtual void releaseResource();
    
private:
	//解析配置文件xml
	//参数：filename 文件路径
	//返回值：无
	void parseXML(const char* filename);
    typedef   map< string, xml_node* > XMLNodeMapType;
    XMLNodeMapType _res_map;
    
};
