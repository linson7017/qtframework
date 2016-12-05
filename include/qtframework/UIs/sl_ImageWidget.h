/*!
 * \file sl_ImageWidget.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#ifndef SL_IMAGEWIDGET_H
#define SL_IMAGEWIDGET_H

#pragma once
#include <QLabel>
#include "Common/qtframework_com.h"
/*!
 * \class sl_ImageWidget
 *
 * \brief 图片控件
 *
 * \author 宋凌
 * \date 五月 2016
 */
class QTFRAMEWORK_EXPORT sl_ImageWidget : public QLabel
{
public:
	//构造函数
	//参数：
	//		imgFileName：图片路径
	//返回值：无
	sl_ImageWidget(const char* imgFileName);
	//构造函数
	//参数：
	//		w：图片宽度
	//		h：图片高度
	//返回值：无
	sl_ImageWidget(int w,int h);
	//构造函数
	//参数：
	//		imgFileName：图片路径
	//		w：图片宽度
	//		h：图片高度
	//返回值：无
	sl_ImageWidget(const char* imgFileName,int w,int h);
	//构造函数
	//参数：无
	//返回值：无
	sl_ImageWidget(void);
	////析构函数
	//参数：无
	//返回值：无
	~sl_ImageWidget(void);
	//设置image路径，例：setImage("@image/***.png")或者setImage("res/images/***.png")
	//参数：
	//		imgFileName：图片路径
	//返回值：无
	void setImage(const char* imgFileName);
	//设置image宽度
	//参数：
	//		w：图片宽度
	//返回值：无
	void setWidth(int w);
	//设置image高度
	//参数：
	//		h：图片高度
	//返回值：无
	void setHeight(int h);
	//获得image宽度
	//参数：无
	//返回值：图片宽度
	int getWidth(){return _width;}
	//获得image高度
	//参数：无
	//返回值：图片高度
	int getHeight(){return _height;}
private:
	int _width;
	int _height;
	std::string _filename;
};

#endif

