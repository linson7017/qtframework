#include <UIs/sl_AnimationWidget.h>
#include <QMovie>
#include "Utils/util.h"
#include "Utils/Log.h"
//构造函数
//参数：无
//返回值：无
sl_AnimationWidget::sl_AnimationWidget(void):_filename(""),_width(50),_height(50),_bAnimationLoaded(false)
{
	_movie = new QMovie;
	setWidth(_width);
	setHeight(_height);
}
//构造函数
//参数：
//		filename:动画文件路径
//返回值：无
sl_AnimationWidget::sl_AnimationWidget(const char* filename):_filename(filename),_width(50),_height(50),_bAnimationLoaded(false)
{
	_movie = new QMovie;
	setWidth(_width);
	setHeight(_height);
	setAnimation(_filename.c_str());
}
//构造函数
//参数：
//		w：动画宽度
//		h：动画高度
//返回值：无
sl_AnimationWidget::sl_AnimationWidget(int w,int h):_filename(""),_width(w),_height(h),_bAnimationLoaded(false)
{
	_movie = new QMovie;
	setWidth(_width);
	setHeight(_height);
}
//构造函数
//参数：
//		imgFileName：动画路径
//		w：动画宽度
//		h：动画高度
//返回值：无
sl_AnimationWidget::sl_AnimationWidget(const char* filename,int w,int h):_filename(filename),_width(w),_height(h),_bAnimationLoaded(false)
{
	_movie = new QMovie;
	setWidth(_width);
	setHeight(_height);
	setAnimation(_filename.c_str());
}
////析构函数
//参数：无
//返回值：无
sl_AnimationWidget::~sl_AnimationWidget(void)
{
}
//设置动画路径，例：setAnimation("@image/***.gif")或者setAnimation("res/images/***.gif")
	//参数：
	//		filename：动画路径
	//返回值：无
void sl_AnimationWidget::setAnimation(const char* filename)
{
	std::string url;
	getResImageOrIconUrl(url,filename);
	_movie->setFileName(url.c_str());
	if (_movie->isValid())
	{
		_movie->setCacheMode(QMovie::CacheAll);
		setMovie(_movie);
		_movie->start();
	}
	else
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: Could not find plugin to read %s\n",url.c_str());
		printf(szMsg);
	}
	_bAnimationLoaded = true;
}
//设置动画宽度
//参数：
//		w：动画宽度
//返回值：无
void sl_AnimationWidget::setWidth(int w)
{
	_width = w;
	setFixedWidth(_width);
	QSize size = _movie->scaledSize();
	_movie->setScaledSize(QSize(_width,size.height()));
	if (_bAnimationLoaded)
	{
		setAnimation(_filename.c_str());
	}

}
//设置动画高度
//参数：
//		h：动画高度
//返回值：无
void sl_AnimationWidget::setHeight(int h)
{
	_height = h;
	setFixedHeight(_height);
	QSize size = _movie->scaledSize();
	_movie->setScaledSize(QSize(size.width(),_height));
	if (_bAnimationLoaded)
	{
		setAnimation(_filename.c_str());
	}
}