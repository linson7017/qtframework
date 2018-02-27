/*!
 * \file qt_context.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#ifndef QT_CONTEXT_H
#define QT_CONTEXT_H

#pragma once
#include <vector>
#include "Common/qtxml_com.h"
struct sl_Rect
{
	int x0;
	int y0;
	int x1;
	int y1;
	int w;
	int h;
};

class QApplication;
class QTranslator;
/*!
 * \class qt_context
 *
 * \brief qt_context类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class QTXML_EXPORT qt_context
{
public:
	//构造函数
	//参数：app QApplication指针
	//返回值：无
	qt_context(QApplication* app);
	//析构函数
	~qt_context(void);
	//getter
	//获得屏幕数量
	//参数：无
	//返回值：屏幕数量
	static int getScreenNum(){return _screenNum;}
	//获得屏幕大小
	//参数：
	//		i: 屏幕索引
	//返回值：屏幕大小
	static sl_Rect* getScreenRect(int i){return _screenRects.at(i);}
	//获得屏幕宽度
	//参数：
	//		i: 屏幕索引
	//返回值：屏幕宽度
	static int getScreenWidth(int i);
	//获得屏幕高度
	//参数：
	//		i: 屏幕索引
	//返回值：屏幕高度
	static int getScreenHeight(int i);
	//设置application编码格式
	//参数：
	//		coding: 编码格式
	//返回值：是否设置成功
	static bool setApplicationCoding(const char* coding);
	//设置application默认语言
	//参数：
	//		languageStr: 语言类型
	//返回值：是否设置成功
	static bool setDefaultLanguage(const char* languageStr);
	//设置application样式
	//参数：
	//		style: 样式
	//返回值：无
	static void setApplicationStyle(const char* style);
	//添加动态库添加目录
	//参数：
	//		path： 路径
	//返回值：无
	static void addLibraryPath(const char* path);
private:
	static int _screenNum; //屏幕数量
	static int _primaryScreen; //主屏幕
	static std::vector<sl_Rect*> _screenRects; //屏幕尺寸序列
	static QTranslator* _translator; //翻译器
};

#endif

