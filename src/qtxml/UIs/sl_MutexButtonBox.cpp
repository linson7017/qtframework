#include "UIs/sl_MutexButtonBox.h"
#include "TriStateBtnClickListener.h"
#include "UIs/sl_Button.h"
#include "Res/R.h"
#include "Utils/util.h"
//构造函数
//参数：无
//返回值：无
sl_MutexButtonBox::sl_MutexButtonBox(void):_listener(NULL)
{
	_btnSelectedStyle = R::Instance()->getStyleResource("BlueButtonStyle");
	_btnNormalStyle = "";
	_btnActivatedStyle = R::Instance()->getStyleResource("GreenButtonStyle");
}

//析构函数
//参数：无
//返回值：无
sl_MutexButtonBox::~sl_MutexButtonBox(void)
{
}
//设置按钮激活的样式
//参数：
//		style:按钮激活的样式
//返回值：无
void sl_MutexButtonBox::setButtonActivatedStyle(const char* style)
{
	const char* stylesheet = STR_TO_RES_STYLE(style);
	if (stylesheet)
	{
		_btnActivatedStyle = stylesheet;
	}
}
//设置按钮正常的样式
//参数：
//		style:按钮正常的样式
//返回值：无
void sl_MutexButtonBox::setButtonNormalStyle(const char* style)
{
	const char* stylesheet = STR_TO_RES_STYLE(style);
	if (stylesheet)
	{
		_btnNormalStyle = stylesheet;
	}
	
}
//设置按钮激活被选择的样式
//参数：
//		style:按钮被选择的样式
//返回值：无
void sl_MutexButtonBox::setButtonSelectedStyle(const char* style)
{
	const char* stylesheet = STR_TO_RES_STYLE(style);
	if (stylesheet)
	{
		_btnSelectedStyle = stylesheet;
	}
}
//添加子按钮
//参数：
//		w:按钮指针
//返回值：无
void sl_MutexButtonBox::addChildButton(sl_Button* w)
{
	_childs.push_back(w);
	w->SetMutexBox((void*)this);
	w->SetMutexButton();
	if (_listener)
	{
		w->addClickListener(_listener);
	}
}
//初始化容器
//参数：无
//返回值：无
void sl_MutexButtonBox::init()
{
	if (!_listener)
	{
		_listener = new TriStateBtnClickListener(this);
		_listener->setButtonActivedStyle(_btnActivatedStyle.c_str());
		_listener->setButtonNormalStyle(_btnNormalStyle.c_str());
		_listener->setButtonSelectedStyle(_btnSelectedStyle.c_str());
	}
}


sl_Button* sl_MutexButtonBox::selectedButton()
{
	return _listener->selectedBtn();
}