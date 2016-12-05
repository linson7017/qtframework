/*!
 * \file sl_AnimationWidget.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#pragma once
#include <QLabel>

class QMovie;
/*!
 * \class sl_AnimationWidget
 *
 * \brief sl_AnimationWidget类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class sl_AnimationWidget:public QLabel
{
public:
	//构造函数
	//参数：
	//		filename:动画文件路径
	//返回值：无
	sl_AnimationWidget(const char* filename);
	//构造函数
	//参数：
	//		w：动画宽度
	//		h：动画高度
	//返回值：无
	sl_AnimationWidget(int w,int h);
	//构造函数
	//参数：
	//		imgFileName：动画路径
	//		w：动画宽度
	//		h：动画高度
	//返回值：无
	sl_AnimationWidget(const char* filename,int w,int h);
	//构造函数
	//参数：无
	//返回值：无
	sl_AnimationWidget(void);
	////析构函数
	//参数：无
	//返回值：无
	~sl_AnimationWidget(void);
	//设置动画路径，例：setAnimation("@image/***.gif")或者setAnimation("res/images/***.gif")
	//参数：
	//		filename：动画路径
	//返回值：无
	void setAnimation(const char* filename);
	//设置动画宽度
	//参数：
	//		w：动画宽度
	//返回值：无
	void setWidth(int w);
	//设置动画高度
	//参数：
	//		h：动画高度
	//返回值：无
	void setHeight(int h);
	//获得动画宽度
	//参数：无
	//返回值：动画宽度
	int getWidth(){return _width;}
	//获得动画高度
	//参数：无
	//返回值：动画高度
	int getHeight(){return _height;}
private:
	int _width;
	int _height;
	std::string _filename;
	QMovie* _movie;
	bool _bAnimationLoaded;
};

#endif

