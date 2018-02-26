#include <UIs/sl_Button.h>
#include <UIs/ClickListenser.h>
#include <string.h>
#include <QtGui>
#include <Utils/util.h>
#include <Common/app_env.h>
//构造函数
//参数：无
//返回值：无
sl_Button::sl_Button():QPushButton(),_bAvailable(true),_bNeedToConfirm(false),_bConfirmed(false)
{
	_bMutexButton = false;
}

////析构函数
//参数：无
//返回值：无
sl_Button::~sl_Button()
{
}
//添加监听器
//参数：
//		listenser:监听器
//返回值：无
void sl_Button::addClickListener(ClickListenser* listenser)
{
	QObject::connect(this,SIGNAL(clicked()),listenser,SLOT(trigger()));
}
//移除监听器
//参数：
//		listenser:监听器
//返回值：无
void sl_Button::removeClickListenser(ClickListenser* listenser)
{
	this->disconnect(listenser);
}
//设置按钮样式
//参数：
//		style:样式
//返回值：无
void sl_Button::setStyle(const char* style)
{
	setStyleSheet(style);
}

void sl_Button::setStyle(std::string style)
{
	setStyle(style.c_str());
}

//设置按钮icon
//参数：
//		icon:icon路径
//返回值：无
void sl_Button::setIcon(const char* icon)
{
	string iconStr = icon;
	std::string url;
	if (iconStr.find("@icon/")!=std::string::npos)
	{
		getResIconUrl(url,iconStr.c_str());
		
	}
	else if (iconStr.find("@image/")!=std::string::npos)
	{
		getResImageUrl(url,iconStr.c_str());
	}
	else
	{
		url = app_env::getImageResDir();
		url.append(icon);
	}
	if (!url.empty())
	{
		QPushButton::setIcon(QIcon(url.c_str()));
	}
}
//设置按钮背景图片
//参数：
//		resImg:图片路径
//返回值：无
void sl_Button::setBackgroundImage(const char* resImg)
{

}
