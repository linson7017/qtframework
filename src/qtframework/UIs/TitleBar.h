/*!
 * \file TitleBar.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once
#include <QWidget>
#include <QFrame>

class ui_node;
class QToolButton;
class QLabel;
class sl_ImageWidget;
class QPixmap;
class Activity;
/*!
 * \class TitleBar
 *
 * \brief 窗口标题栏
 *
 * \author 宋凌
 * \date 五月 2016
 */
class TitleBar : public QWidget
{
	Q_OBJECT
public:
	//构造函数
	//参数：
	//		activity：窗口
	//返回值：无
	TitleBar(Activity* activity=NULL);
	//析构函数
	//参数：无
	//返回值：无
	~TitleBar(void);
	//设置标题栏对应的ui节点
	//参数：
	//		node：ui节点
	//返回值：无
	void setTitleNode(ui_node* node){_titleNode = node;}
	//设置标题栏对应的窗口
	//参数：
	//		activity：窗口
	//返回值：无
	void setParentActivity(Activity* activity){_parentActivity = activity;}
	//设置最小化按钮对应的图片路径
	//参数：
	//		url：图片路径
	//返回值：无
	void setMinimizeButtonImage(const char* url);
	//设置最大化按钮对应的图片路径
	//参数：
	//		url：图片路径
	//返回值：无
	void setMaximizeButtonImage(const char* url);
	//设置恢复按钮对应的图片路径
	//参数：
	//		url：图片路径
	//返回值：无
	void setRestoreButtonImage(const char* url);
	//设置关闭按钮对应的图片路径
	//参数：
	//		url：图片路径
	//返回值：无
	void setCloseButtonImage(const char* url);
	//设置icon图片路径
	//参数：
	//		url：图片路径
	//返回值：无
	void setIconImage(const char* url);
	//设置标题栏文字
	//参数：
	//		text：标题栏文字
	//返回值：无
	void setTitleText(const char* text);
	//设置标题栏高度
	//参数：
	//		size：高度
	//返回值：无
	void setTitleSize(int size);
	//更新最大化按钮图片
	//参数：无
	//返回值：无
	void updateMaximizeButtonImage();
	//设置最小化按钮是否显示
	//参数：
	//		b：是否显示
	//返回值：无
	void setMinimizeButtonVisible(bool b);
	//设置最大化按钮是否显示
	//参数：
	//		b：是否显示
	//返回值：无
	void setMaximizeButtonVisible(bool b);
	//设置关闭按钮是否显示
	//参数：
	//		b：是否显示
	//返回值：无
	void setCloseButtonVisible(bool b);
	//设置标题栏文字是否显示
	//参数：
	//		b：是否显示
	//返回值：无
	void setTitleTextVisible(bool b);
	//设置标题栏icon是否显示
	//参数：
	//		b：是否显示
	//返回值：无
	void setIconVisible(bool b);
protected slots:
	//最小化窗口
	//参数：无
	//返回值：无
	void minimizeParentWidget();
	//最大化窗口
	//参数：无
	//返回值：无
	void maximizeParentWidget();
	//关闭窗口
	//参数：无
	//返回值：无
	void closeParentWidget();
signals:
	//最小化按钮被点击
	//参数：无
	//返回值：无
	void minimizeButtonClicked();
	//最大化按钮被点击
	//参数：无
	//返回值：无
	void maximizeButtonClicked();
	//关闭按钮被点击
	//参数：无
	//返回值：无
	void closeButtonClicked();
protected:
	//控制窗口操作
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
	//鼠标双击事件
	//参数：
	//		event:事件
	//返回值：无
	void mouseDoubleClickEvent(QMouseEvent *event);
	//获得图片路径
	//参数：
	//		pix:位图
	//		url:图片路径
	//返回值：无
	void getPixelImage(QPixmap* pix,const char* url);
	

protected:
	ui_node* _titleNode;
	QToolButton* _minimizeBtn;  //最小化按钮
	QToolButton* _maximizeBtn; //最大化按钮
	QToolButton* _closeBtn; //最退出按钮
	QLabel* _titleText;  //标题文字
	sl_ImageWidget* _iconImage;  //标题图标
	int _size;  //标题栏大小

	QPixmap* _maxPix,*_restorePix,*_minPix,*_closePix;
	Activity* _parentActivity;

	bool _dragging;
	bool _minimized;
	int _pwPreX;  //父窗口之前的位置
	int _pwPreY;
	int _preMouseX; //鼠标之前的位置
	int _preMouseY;

};

