/*!
 * \file sl_MutexButtonBox.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once
#include <vector>
#include <string>
#include "Common/qtframework_com.h"
//#include <QWidget>

using namespace std;
class sl_Button;
class ui_node;
class QWidget;
class TriStateBtnClickListener;
/*!
 * \class sl_MutexButtonBox
 *
 * \brief 互斥按钮容器
 *
 * \author 宋凌
 * \date 五月 2016
 */
class QTFRAMEWORK_EXPORT  sl_MutexButtonBox
{
public:
	//构造函数
	//参数：无
	//返回值：无
	sl_MutexButtonBox(void);
	//析构函数
	//参数：无
	//返回值：无
	~sl_MutexButtonBox(void);
	//获得子按钮
	//参数：
	//		index:子按钮索引
	//返回值：自按钮指针
	sl_Button* getChildButton(int index)
	{
		return _childs.at(index);
	}
	//按钮数量
	//参数：无
	//返回值：按钮数量
	int buttonNum(){return _childs.size();}
	//添加子按钮
	//参数：
	//		w:按钮指针
	//返回值：无
	void addChildButton(sl_Button* w);
	//初始化容器
	//参数：无
	//返回值：无
	void init();
	//设置监听器
	//参数：
	//		listener:监听器
	//返回值：无
	void setListener(TriStateBtnClickListener* listener){_listener = listener;}
	//获得子按钮列表
	//参数：无
	//返回值：子按钮列表
	sl_Button** getChildren(){return _childs.data();}
	//设置按钮激活的样式
	//参数：
	//		style:按钮激活的样式
	//返回值：无
	void setButtonActivatedStyle(const char* style);
	//设置按钮正常的样式
	//参数：
	//		style:按钮正常的样式
	//返回值：无
	void setButtonNormalStyle(const char* style);
	//设置按钮激活被选择的样式
	//参数：
	//		style:按钮被选择的样式
	//返回值：无
	void setButtonSelectedStyle(const char* style);
	void setCurrentButton();
	
	sl_Button* selectedButton();
private:
	typedef vector<sl_Button*> ButtonVectorType;
	ButtonVectorType _childs;
	TriStateBtnClickListener* _listener;
	std::string _btnActivatedStyle;
	std::string _btnNormalStyle;
	std::string _btnSelectedStyle;
};

