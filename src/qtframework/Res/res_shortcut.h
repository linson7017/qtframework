/*!
 * \file res_shortcut.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once
#include <map>
#include <vector>
#include <string>
using namespace std;
class xml_node;
/*!
 * \class res_shortcut
 *
 * \brief res_shortcut类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class res_shortcut
{
public:
	//构造函数
	//参数：无
	//返回值：无
	res_shortcut(void);
	//构造函数
	//参数：无
	//返回值：无
	~res_shortcut(void);
	//获得快捷键资源
	//参数：name ID
	//返回值：资源
	xml_node* getShortcutRes(const char* name);

private:
	//解析配置文件xml
	//参数：filename 文件路径
	//返回值：无
	void parseShortcutXML(const char* filename);
	//全排列数组
	//参数：inVec 输入数组, outVec 输出数组, s 起始位置, e大小
	//返回值：无
	void perm(vector<string>& inVec,vector<string>& outVec,int s,int e);
	//交换字符串
	//参数：s1 数组1, s2 数组2
	//返回值：无
	void swap(string& s1,string& s2);
	//获得快捷键资源
	//参数：name ID
	//返回值：资源
	xml_node* findRes(const char* name);
	typedef map<string,xml_node*> ShortcutMapType;
	ShortcutMapType _res_map;
	
	xml_node* _found_shortcut;
};

