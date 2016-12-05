#include <UIs/sl_ImageWidget.h>
#include "Utils/util.h"
//构造函数
//参数：无
//返回值：无
sl_ImageWidget::sl_ImageWidget(void):_filename(""),_width(20),_height(20)
{
	setWidth(_width);
	setHeight(_height);
}
//构造函数
//参数：
//		imgFileName：图片路径
//返回值：无
sl_ImageWidget::sl_ImageWidget(const char* imgFileName):_filename(imgFileName),_width(20),_height(20)
{
	setWidth(_width);
	setHeight(_height);
	setImage(_filename.c_str());
}
//构造函数
//参数：
//		w：图片宽度
//		h：图片高度
//返回值：无
sl_ImageWidget::sl_ImageWidget(int w,int h):_filename(""),_width(w),_height(h)
{
	setWidth(_width);
	setHeight(_height);
}
//构造函数
//参数：
//		imgFileName：图片路径
//		w：图片宽度
//		h：图片高度
//返回值：无
sl_ImageWidget::sl_ImageWidget(const char* imgFileName,int w,int h):_filename(imgFileName),_width(w),_height(h)
{
	setWidth(_width);
	setHeight(_height);
	setImage(_filename.c_str());
}

////析构函数
//参数：无
//返回值：无
sl_ImageWidget::~sl_ImageWidget(void)
{
}
//设置image路径，例：setImage("@image/***.png")或者setImage("res/images/***.png")
	//参数：
	//		imgFileName：图片路径
	//返回值：无
void sl_ImageWidget::setImage(const char* imgFileName)
{
	std::string url;
	getResImageOrIconUrl(url,imgFileName);
	if (!url.empty())
	{
		this->setPixmap(QPixmap(url.c_str()).scaled(_width,_height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
	}else
	{
		this->setPixmap(QPixmap(imgFileName).scaled(_width,_height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
	}
	
}
//设置image宽度
//参数：
//		w：图片宽度
//返回值：无
void sl_ImageWidget::setWidth(int w)
{
	_width = w;
	setFixedWidth(_width);
}
//设置image高度
//参数：
//		h：图片高度
//返回值：无
void sl_ImageWidget::setHeight(int h)
{
	_height = h;
	setFixedHeight(_height);
}
