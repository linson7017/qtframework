/*!
 * \file Listener.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once
#include <QtCore/QObject>
class ui_node;
/*!
 * \class Listener
 *
 * \brief 监听类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class Listener :public QObject
{
	Q_OBJECT
public:
	//构造函数
	//参数：无
	//返回值：无
	Listener(void);
	//析构函数
	//参数：无
	//返回值：无
	~Listener(void);
	public slots:
		//触发
		//参数：无
		//返回值：无
		virtual void trigger();
protected:
	ui_node* _sender;
};

