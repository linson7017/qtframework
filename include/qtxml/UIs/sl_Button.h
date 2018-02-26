/*!
 * \file sl_Button.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#ifndef SL_BUTTON_H
#define SL_BUTTON_H

#pragma once
#include <QPushButton>
#include "Common/qtframework_com.h"
class ClickListenser;
/*!
 * \class sl_Button
 *
 * \brief sl_Button类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class QTFRAMEWORK_EXPORT sl_Button :
	/*public ui_node,*/ public QPushButton
{
	Q_OBJECT
public:
	//构造函数
	//参数：无
	//返回值：无
	sl_Button();
	////析构函数
	//参数：无
	//返回值：无
	~sl_Button();
	//添加监听器
	//参数：
	//		listenser:监听器
	//返回值：无
	void addClickListener(ClickListenser* listenser);
	//移除监听器
	//参数：
	//		listenser:监听器
	//返回值：无
	void removeClickListenser(ClickListenser* listenser);
	//设置按钮样式
	//参数：
	//		style:样式
	//返回值：无
	void setStyle(const char* style);
	//设置按钮样式
	//参数：
	//		style:样式
	//返回值：无
	void setStyle(std::string style);
	//设置按钮icon
	//参数：
	//		icon:icon路径
	//返回值：无
	void setIcon(const char* icon);
	//设置按钮背景图片
	//参数：
	//		resImg:图片路径
	//返回值：无
	void setBackgroundImage(const char* resImg);
	//设置按钮是否可以响应命令
	//参数：
	//		b:是否可以响应命令
	//返回值：无
	void setAvailable(bool b)
	{
		_bAvailable=b;
		if (!_bAvailable)
		{
			emit availabled();
		}
	}
	//获得按钮是否可以响应命令
	//参数：无
	//返回值：可以响应返回true,否则返回false
	bool availlabe(){return _bAvailable;}
	//获得按钮是否需要确认对话框
	//参数：无
	//返回值：需要返回true,否则返回false
	bool needToConfirm(){return _bNeedToConfirm;}
	//设置按钮是否需要确认对话框
	//参数：
	//		b:是否需要确认对话框
	//返回值：无
	void setNeedToConfirm(bool b)
	{
		_bNeedToConfirm = b;
	}
	//获得按钮是否已经被确认
	//参数：无
	//返回值：已确认返回true,否则返回false
	bool confirmed(){return _bConfirmed;}
	//设置按钮是否已经被确认
	//参数：
	//		b:是否已经被确认
	//返回值：无
	void setConfirmed(bool b)
	{
		_bConfirmed = b;
	}
	//shisx可以方便的设置同组的互斥按钮样式
	//设置按钮为互斥按钮
	//参数：
	//返回值：无
	void SetMutexButton(){_bMutexButton = true;}
	//获得按钮是否为互斥按钮
	//参数：
	//返回值：是互斥按钮返回true,否则返回false
	bool IsMutexButton(){return _bMutexButton;}
	//设置按钮的互斥容器
	//参数：
	//		box:互斥容器指针
	//返回值：无
	void SetMutexBox(void* box){_pMutexBox = box;}
	//获得按钮的互斥容器
	//参数：
	//返回值：按钮的互斥容器指针
	void* GetMutexBox(){return _pMutexBox;}
signals:
	void availabled();
private:
	bool _bAvailable;
	bool _bNeedToConfirm;
	bool _bConfirmed;
	//shisx
	bool _bMutexButton;
	void* _pMutexBox;
};

#endif

