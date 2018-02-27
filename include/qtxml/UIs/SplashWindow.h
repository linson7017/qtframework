#ifndef SPLASHWINDOW_H
#define SPLASHWINDOW_H

/*!
 * \file SplashWindow.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once
#include <QSplashScreen>
//#include "UIs/Activity.h"
#include "Common/qtxml_com.h"
#include <QtCore/QThread>
class Activity;
class QLabel;
class QPixmap;
class sl_Timer;

/*!
 * \class SplashWindow
 *
 * \brief 启动窗口
 *
 * \author 宋凌
 * \date 五月 2016
 */
class QTXML_EXPORT SplashWindow:public QSplashScreen
{
	Q_OBJECT
public:
	//构造函数
	//参数：无
	//返回值：无
	SplashWindow(void);
	//析构函数
	//参数：无
	//返回值：无
	~SplashWindow(void);
	//设置延时启动时间
	//参数：
	//		duration:延时启动时间
	//返回值：无
	void setDelay(int duration);
	//设置关联的窗口
	//参数：
	//		activity:关联的指针窗口
	//返回值：无
	/*void setActivity(Activity* activity)
	{
	_relateActivity = activity;
	if (_relateActivity)
	_relateActivity->_splashWindow = this;
	}*/
	//开始启动
	//参数：无
	//返回值：无
	//bool start();
	//设置启动窗口的布局内容
	//参数：
	//		layout_filename:布局文件路径
	//返回值：无
	void setContentView(const char* layout_filename);
	//关闭延时
	//参数：无
	//返回值：无
	//void disableDelay(){_bDelay =false;}
	//开启延时
	//参数：无
	//返回值：无
	//void enableDelay(){_bDelay = true;}
	//设置显示信息的文本控件ID
	//参数：
	//		szMessageID:文本控件ID
	//返回值：是否设置成功
	bool setMessageLabelID(const char* szMessageID);
	//设置显示信息
	//参数：
	//		szMessage:显示信息
	//返回值：无
	void showMessage(const char* szMessage);

	void setBackground(const char* szFileName);
protected:

protected slots:
	//void activeRelatedActivity();
private:
	//20150925
	Activity* _contentActivity;
	Activity* _relateActivity;
	sl_Timer* _delay;
	bool _bDelay;
	bool _activeSuccess;
	QLabel* _pMessage;
};

#endif
