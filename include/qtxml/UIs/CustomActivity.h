/*!
 * \file CustomActivity.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#ifndef CUSTOMACTIVITY_H
#define CUSTOMACTIVITY_H

#pragma once
#include "UIs/Activity.h"
#include "Common/qtframework_com.h"

class TitleBar;
class QTimer;
/*!
 * \class CustomActivity
 *
 * \brief CustomActivity类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class QTFRAMEWORK_EXPORT CustomActivity : public Activity
{
	Q_OBJECT
public:
	//鼠标区域
	enum MouseArea
	{
		Left,
		Right,
		Top,
		Bottom,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		Other
	};
	////构造函数
	//参数：无
	//返回值：无
	CustomActivity(void);
	////构造函数
	//参数：无
	//返回值：无
	CustomActivity(SplashWindow* pSplashWindow);
	//设置显示模式
	//参数：
	//		mode:显示模式
	//返回值：资源
	void setShowMode(ShowMode mode);
	//析构函数
	//参数：无
	//返回值：无
	~CustomActivity(void);
	//最小化事件
	//参数：无
	//返回值：无
	virtual void minimizeActivityEvent();
	//最大化事件
	//参数：无
	//返回值：无
	virtual void maximizeActivityEvent();
	//关闭事件
	//参数：无
	//返回值：无
	virtual void closeActivityEvent();
	////重写放大缩小函数
	//显示事件
	//参数：无
	//返回值：无
	virtual void showEvent(QShowEvent *e);
	//隐藏事件
	//参数：无
	//返回值：无
    virtual void hideEvent(QHideEvent *e);
	//激活
	//参数：无
	//返回值：激活成功返回true,否则返回false
    virtual bool active();
private slots:
	//最小化窗口
	//参数：无
	//返回值：无
	void minimizeActivity();
	//最大化窗口
	//参数：无
	//返回值：无
	void maximizeActivity();
	//关闭窗口
	//参数：无
	//返回值：无
	void closeActivity();
	//重定位鼠标
	//参数：无
	//返回值：无
	void regionMouse();
protected:
	//绘制事件
	//参数：
	//		event:事件
	//返回值：无
	void paintEvent(QPaintEvent *);
	virtual void installContent();
	//鼠标移动事件
	//参数：
	//		event:事件
	//返回值：无
	void mouseMoveEvent(QMouseEvent *event);
	//鼠标按下事件
	//参数：
	//		event:事件
	//返回值：无
	void mousePressEvent(QMouseEvent *event);
	//鼠标松开事件
	//参数：
	//		event:事件
	//返回值：无
	void mouseReleaseEvent(QMouseEvent *event);	
	//离开窗口事件
	//参数：
	//		event:事件
	//返回值：无
	void leaveEvent(QEvent *event);
	//进入窗口事件
	//参数：
	//		event:事件
	//返回值：无
	void enterEvent(QEvent *event);
	//选中事件
	//参数：
	//		event:事件
	//返回值：无
    void focusInEvent(QFocusEvent *event);
	//脱离焦点事件
	//参数：
	//		event:事件
	//返回值：无
    void focusOutEvent(QFocusEvent * event);
	//窗口创建之前的行为
	//参数：无
	//返回值：成功返回true,否则返回false
	bool actionBeforeCreated();
	//窗口创建之后的行为
	//参数：无
	//返回值：成功返回true,否则返回false
	bool actionAfterActived();
	

	TitleBar* _titleBar;
private:
	void relateTitleBar();

	MouseArea _mouseArea;
	bool _dragging;
	int _curMouseX;
	int _curMouseY;
	int _preWidth;
	int _preHeight;
	int _preX;
    int _preY;
	ShowMode _preShowMode;
	QTimer* _timer;
};

#endif
