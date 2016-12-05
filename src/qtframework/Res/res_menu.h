/*!
 * \file res_menu.h
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
 * \class res_menu
 *
 * \brief res_menu类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class res_menu
{
public:
	//构造函数
	//参数：无
	//返回值：无
	res_menu(void);
	//析构函数
	//参数：无
	//返回值：无
	~res_menu(void);
	//获得右键菜单资源
	//参数：id ID
	//返回值：根节点指针
	ui_node* getMenuRes(const char* id);
private:
	typedef map<string,ui_node*> ResMapType;
	ResMapType _res_map;
};

