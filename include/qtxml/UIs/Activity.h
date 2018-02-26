/*!
 * \file Activity.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#ifndef ACTIVITY_H
#define ACTIVITY_H

#pragma once
#include <QtGui>
#include <QWidget>
#include <string.h>
#include "Common/qtframework_com.h"
class ui_node;
class qt_ui_assembler;
class SplashWindow;
/*!
 * \class Activity
 *
 * \brief Activity类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class QTFRAMEWORK_EXPORT Activity : /*private*/public QWidget  //这里私有继承，封装Qt功能
{
	Q_OBJECT
public:
	//显示模式
	enum ShowMode
	{
		NORMAL,
		MAXIMIZED,
		MINIMIZED,
		FULL_SCREEN,
		EXTERNAL_DEFINED
	};
	//位置
	enum Alignment
	{
		LEFT,
		RIGHT,
		BOTTOM,
		TOP,
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
		CENTER
	};
	//构造函数
	//参数：无
	//返回值：无
	Activity(void);
	//构造函数
	//参数：
	//		parent:父窗口指针
	//返回值：无
	Activity(Activity* parent);
	//构造函数
	//参数：
	//		id:窗口id
	//返回值：无
	Activity(const char* id);
	//构造函数
	//参数：
	//		id:窗口id
	//		parent:父窗口指针
	//返回值：无
	Activity(const char* id, Activity* parent);
	//构造函数
	//参数：
	//		pSplashWindow:SplashWindow
	//返回值：无
	Activity(SplashWindow* pSplashWindow);
	////析构函数
	//参数：无
	//返回值：无
	virtual ~Activity(void);
	//设置窗口内容对应的xml文档
	//参数：
	//		layout_filename:布局文件路径
	//返回值：是否设置成功
	virtual bool setContentView(const char* layout_filename);	
	//在窗口创建之前的行为,重写用
	//参数：无
	//返回值：是否设置成功
	virtual bool actionBeforeCreated(){return true;}
	//在窗口创建之后的行为,重写用
	//参数：无
	//返回值：是否设置成功
	virtual bool actionAfterCreated(){return true;}
	//在窗口激活之前的行为,重写用
	//参数：无
	//返回值：是否设置成功
	virtual bool actionBeforeActived(){return true;}
	//在窗口激活之后的行为,重写用
	//参数：无
	//返回值：是否设置成功
	virtual bool actionAfterActived(){return true;}
	//在窗口关闭之前的行为,重写用
	//参数：无
	//返回值：是否设置成功
	virtual bool actionBeforeClosed(){return true;}
	//获得显示模式
	//参数：
	//返回值：显示模式
	ShowMode showMode(){return _showMode;}
	//设置显示模式
	//参数：
	//		mode：显示模式
	//返回值：无
	virtual void setShowMode(ShowMode mode){_showMode = mode;}
	//设置显示模式
	//参数：
	//		title：窗口标题
	//返回值：无
	virtual void setTitle(const char* title);
	//获得控件对象
	//参数：
	//		id：ID
	//返回值：控件对象指针
	void* getViewByID(const char* id);
	//激活所有的容器
	//参数：
	//返回值：无
	void activateAllContainers();
	//激活容器
	//参数：
	//		id：容器ID
	//返回值：无
	void activateContainer(const char* id);
	//激活容器
	//参数：无
	//返回值：id
	const char* getID(){return _id.c_str();}
	//设置窗口id
	//参数：
	//		id：ID
	//返回值：无
	void setID(const char* id){_id = id;}
	//设置窗口位置
	//参数：
	//		align：位置
	//返回值：无
	void setAlignment(Alignment align);
	//获得窗口初始宽度
	//参数：
	//返回值：初始宽度
	int getInitWidth(){return _initWidth;}
	//获得窗口初始高度
	//参数：
	//返回值：初始高度
	int getInitHeight(){return _initHeight;}
	//设置SplashWindow
	//参数：
	//		pSplashWindow：SplashWindow
	//		bShowSplashWindow：是否使用SplashWindow
	//返回值：初始高度
	void setSplashWindow(SplashWindow* pSplashWindow,bool bShowSplashWindow = true)
	{
		_splashWindow = pSplashWindow;
		_bShowSplashWindow = bShowSplashWindow;
	}
	
	friend class SplashWindow;
public slots:
	//显示窗口
	//参数：无
	//返回值：显示成功返回true
	virtual bool active();
	//最大化显示窗口
	//参数：无
	//返回值：无
	virtual void activeMaximized();
	//最小化显示窗口
	//参数：无
	//返回值：无
	virtual void activeMinimized();
	//显示窗口
	//参数：无
	//返回值：无
	virtual void activeNormal();
	//全屏显示窗口
	//参数：无
	//返回值：无
	virtual void activeFullScreen();
protected:
	//关闭事件
	//参数：
	//		ev：事件
	//返回值：是否设置成功
    void closeEvent(QCloseEvent *ev);
	//安装窗口内容
	//参数：无
	//返回值：无
	virtual void installContent();
	//准备UI
	//参数：无
	//返回值：成功返回true,否则返回false
	bool prepareUI();
	//显示窗口
	//参数：
	//		mode：显示模式
	//返回值：成功返回true,否则返回false
	virtual bool active(ShowMode mode);
	//窗口显示之前解析根节点的显示设置
	//参数：
	//		attr：节点指针
	//返回值：无
	void parseShowModeBeforeActived(ui_node* attr);
	//void parseShowModeAfterActived(ui_node* attr);
	//显示提示信息
	//参数：
	//		szMessage:显示信息
	//返回值：无
	void showSplashMessage(const char* szMessage);

	ui_node* _content; //窗口内容，不包括标题栏
	qt_ui_assembler* _assembler;
	std::string _id;
	std::string _layout_filename;
	ShowMode _showMode;
	bool _bPrepared;
	bool _bParsed;
	int _initPosX;
	int _initPosY;
	int _initWidth;
	int _initHeight;

	SplashWindow* _splashWindow;
	bool _bShowSplashWindow;

};

#endif

