//#include <Utils/Log.h>
#include <string.h>
#include <stdarg.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include "Common/app_env.h"
#include "Utils/util.h"
#include "Res/R.h"
#include "Utils/variant.h"

#if defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__ 
#include <io.h>
#else
#include <sys/io.h>
#endif

Log* Log::_log = NULL;
Log::Garbo Log::_garbo;
//构造函数
//参数：无
//返回值：无
Log::Log(void):_bEnabled(true)
{
	if (_bEnabled)
	{
		init();
	}
}

//析构函数
//参数：无
//返回值：无
Log::~Log(void)
{
	close();  //程序退出关闭文档
}
//打开log文件
//参数：无
//返回值：无
bool Log::open()
{
	_oLogFile.open(_logFilename.c_str(),ios_base::out|ios_base::app);
	if (!_oLogFile)
	{
		std::cerr<<"error: unable to open log file:" <<_logFilename<<std::endl;
		return false;
	}
	_bOpened = true;
	return true;
}
//关闭log文件
//参数：无
//返回值：无
void Log::close()
{
	if (_oLogFile.is_open())
	{
		_oLogFile.close();
		_bOpened = false;
	}
}
//初始化log文件
//参数：无
//返回值：无
bool Log::init()
{
	time_t tNow;
	time(&tNow);

	tm* tLoacal = localtime(&tNow);
	string strFormat = "%Y%m%d_%H%M%S";
	char strDateTime[30] = {'\0'};
	strftime(strDateTime,30,strFormat.c_str(),tLoacal);
	_logFilename = app_env::getLogDir();
	if (access(_logFilename.c_str(),0))
	{
		createDirectory(_logFilename.c_str());
	}
	_logFilename.append(strDateTime);
	_logFilename.append(".log");
	return open();
}
//获得时间字符串
//参数：
//		ts:时间字符串
//返回值：无
void Log::getTimeStr(string& ts)
{
	time_t tNow;
	time(&tNow);

	tm* tLoacal = localtime(&tNow);
	string strFormat = "%Y-%m-%d  %H:%M:%S ";
	char strDateTime[30] = {'\0'};
	strftime(strDateTime,30,strFormat.c_str(),tLoacal);
	ts = strDateTime;
}
//写log
//参数：
//	type:日志类型
//	fmt :日志内容
//返回值：无
void Log::log(LOG_TYPE type,const char* fmt,...)
{
	const variant* p_variant = R::getConfigResource("WriteLog");
	if(!p_variant) return;
	if(p_variant->getBool()) return;	
	string currentTime;
	getTimeStr(currentTime);
	switch (type)
	{
	case LOG_WARN:
		_oLogFile<<"[WARN] ";
		break;
	case LOG_INFO:
		_oLogFile<<"[INFO] ";
		break;
	case LOG_ERROR:
		_oLogFile<<"[ERROR] ";
		break;
	default:
		_oLogFile<<"[INFO] ";
		break;
	}
	_oLogFile<<currentTime.c_str()<<"\n";

	char outstr[255];
	va_list arglist;
	va_start(arglist,fmt);
	char temp[255];
	strcpy(temp,fmt);
	char Format[255];

	char *p = strchr(temp,'%');
	int i=0;
	int iParam;
	char *sParam;
	double fParam;
	char outTemp[255];
	while(p!=NULL)
	{
		while((*p<'a'||*p>'z')&&(*p!=0))
			p++;
		if (*p==0)
			break;
		p++;

		int nChar = p-temp;
		strncpy(Format,temp,nChar);
		Format[nChar]=0;
		strncpy(outTemp,Format,nChar-2);
		outTemp[nChar-2]=0;
		_oLogFile<<outTemp;
		if (Format[nChar-1]=='d')
		{
			iParam = va_arg(arglist,int);
			_oLogFile<<iParam;
		}
		else if (Format[nChar-1]=='f')
		{
			fParam = va_arg(arglist,double);
			_oLogFile<<fParam;
		}
		else if (Format[nChar-1]=='s')
		{
			sParam = va_arg(arglist,char*);
			_oLogFile<<sParam;
		}
		

		i++;
		strcpy(temp,p);
		if (*p==0)
			break;
		p=strchr(temp,'%');
	}
	if (temp[0]!=0)
	{
		_oLogFile<<temp;
	}
	_oLogFile<<"\n"<<"\n";
	_oLogFile.flush(); //将内容写入物理内存
}