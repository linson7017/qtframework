/*!
 * \file res_string.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once
#include "Res/xml_res_base.h"
#include <vector>
using namespace std;
/*!
 * \class res_string
 *
 * \brief res_string类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class res_string  :public xml_res_base
{
public:
	//构造函数
	//参数：无
	//返回值：无
	res_string(void);
	//析构函数
	//参数：无
	//返回值：无
	~res_string(void);
	//获得String资源
	//参数：id ID
	//返回值：资源
	const char* getStringRes(const char* id);
	vector<string> getStringListRes(const char* id);
private:
    virtual void releaseResource();
	//解析配置文件xml
	//参数：filename 文件路径
	//返回值：无
	void parseXML(const char* filename);
	typedef map<string,string> StringMapType;
	typedef map< string,vector<string> > StringListMapType;
	StringMapType _res_map;
	StringListMapType _resList_map;
};

