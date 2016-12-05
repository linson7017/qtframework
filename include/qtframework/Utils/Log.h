/*!
 * \file Log.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#ifndef LOG_H
#define LOG_H

#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include "Common/qtframework_com.h"
using namespace std;
/*!
 * \class Log
 *
 * \brief Log类
 *
 * \author 宋凌
 * \date 五月 2016
 */
class QTFRAMEWORK_EXPORT Log
{
public:
	//日志类型
	enum LOG_TYPE
	{
		LOG_WARN,  //警告
		LOG_ERROR, //错误
		LOG_INFO   //消息
	};
	//写log
	//参数：
	//	type:日志类型
	//	fmt :日志内容
	//返回值：无
	void log(LOG_TYPE type,const char* fmt,...);
	//初始化log文件
	//参数：无
	//返回值：无
	bool init();
	//获得是否开启log
	//参数：无
	//返回值：开启返回true，否则返回false
	bool getEnabled(){return _bEnabled;}
	//设置是否开启log
	//参数：
	//		b:是否开启log
	//返回值：无
	void setEnabled(bool b){_bEnabled = b;}
	//获得Log实例
	//参数：无
	//返回值：实例指针
	static Log* Instance()
	{
		if (_log == 0)
		{
			_log = new Log;
		}
		return _log;
	}
	
public:
	 //程序结束析构单例实例
	class Garbo
	{
	public:
		//构造函数
		Garbo(){}
		//析构函数
		~Garbo()
		{
			if (_log)
			{
				delete _log; //删除Log实例
			}
		}
	};
private:
	//构造函数
	//参数：无
	//返回值：无
	Log(void);
	//析构函数
	//参数：无
	//返回值：无
	~Log(void);
	//输出为字符串
	//参数：
	//		value:数据
	//返回值：字符串
	template<typename T> string valueToStr(T value)
	{
		ostringstream ost;
		ost<<value;
		return ost.str();
	}
	//获得时间字符串
	//参数：
	//		ts:时间字符串
	//返回值：无
	void getTimeStr(string& ts);
	//获得是否打开log文件
	//参数：无
	//返回值：打开返回true，否则返回false
	bool getOpened(){return _bOpened;}
	//设置是否打开log文件
	//参数：
	//		b:是否打开log文件
	//返回值：无
	void setOpened(bool b){_bOpened = b;}
	//打开log文件
	//参数：无
	//返回值：无
	bool open();
	//关闭log文件
	//参数：无
	//返回值：无
	void close();
	bool _bEnabled;
	bool _bOpened;
	std::ofstream _oLogFile;
	string _logFilename;

	static Log* _log;
	static Garbo _garbo;
};

#endif
