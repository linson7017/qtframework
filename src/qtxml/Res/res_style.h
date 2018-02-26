#pragma once
#include "Res/xml_res_base.h"
using namespace std;

class res_style:public xml_res_base
{
public:
	//构造函数
	//参数：无
	//返回值：无
	res_style(void);
	//析构函数
	//参数：无
	//返回值：无
	~res_style(void);
	//获得Style资源
	//参数：id ID
	//返回值：资源
	const char* getStyleRes(const char* id);
	//获得Application的样式
	//参数：无
	//返回值：资源
	const char* getMainStyle();
private:
    virtual void releaseResource();
	//解析配置文件xml
	//参数：filename 文件路径
	//返回值：无
	void parseXML(const char* filename);
	//解析节点Name
	//参数：str 节点Name
	//返回值：输出字符
	const char* parseName(const char* str);
	//解析内容
	//参数：icontent 输入内容, ocontent 输出内容, name 节点Name
	//返回值：输出字符
	const char* parseContent(string& ocontent,const char* icontent,const char* name);

    void parseQSSResource();

	typedef map<string,string> StyleMapType;
	StyleMapType _res_map;
};

