/*!
 * \file res_ui.h
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

class ui_node;
/*!
 * \class res_ui
 *
 * \brief res_ui类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class res_ui
{
public:
	//构造函数
	//参数：无
	//返回值：无
	res_ui();
	//析构函数
	//参数：无
	//返回值：无
	~res_ui();
	//获得UI资源树的根节点，此时还没有装配，节点中Object为空，无法加载到UI上
	//参数：id ID
	//返回值：节点指针
	ui_node* getUIRes(const char* id);
private:
	typedef map<string,ui_node*> ResMapType;
	ResMapType _res_map;
};

