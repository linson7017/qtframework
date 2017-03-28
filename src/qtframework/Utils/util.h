/*!
 * \file util.h
 *
 * \author 宋凌
 * \date 五月 2016
 *
 * 
 */
#pragma once
#include <QString>
#include <QStringList>
#include <QObject>
#include <string>
#include <vector>
#include "Utils/Log.h"

class xml_node;
class ui_node;
/*
一些常用的全局函数，包括字符串的操作，资源的读取转换等
*/

/////////字符串转换

//将字符串转换为BOOL型
//参数：
//	str:输入字符
//返回值：true或者false
bool atob(const char* str);

std::pair<int, int> atoip(const char* str);

//将字符串用";;"分离成字符数组
//参数：
//	str:输入字符
//返回值：字符数组
QStringList atosv(const char* str);

//获得字符资源
//参数：
//	str:输入字符
//返回值：字符资源
const char* getResText(const char* str);

//获得样式资源
//参数：
//	str:输入字符
//返回值：样式资源
const char* getResStyle(const char* str);

//获得res目录下image目录下的图片路径
//参数：
//	url:res目录下image目录下的图片路径
//	istr: 输入字符
//返回值：无
void getResImageUrl(std::string& url,const char* istr);

//获得res目录下qml目录下的图片路径
//参数：
//	url:res目录下image目录下的qml路径
//	istr: 输入字符
//返回值：无
void getResQmlUrl(std::string& url,const char* istr);


//获得res目录下icon目录下的图片路径
//参数：
//	url:res目录下icon目录下的图片路径
//	istr: 输入字符
//返回值：无
void getResIconUrl(std::string& url,const char* istr);

//获得res目录下images目录或者icons目录下的图片路径
//参数：
//	url:res目录下images目录或者icons目录下的图片路径
//	istr: 输入字符
//返回值：无
void getResImageOrIconUrl(std::string& url,const std::string& istr);

/******************** 字符串转换 **************************/
#define STR_TO_INT(str) atoi(str)  //字符串到整型
#define STR_TO_DOUBLE(str) atof(str)  //字符串到double
#define STR_TO_BOOL(str)  atob(str)  //字符串到bool
#define STR_TO_ALIGN(str)  atoalign(str)  //字符串到Qt::Aligment
#define STR_TO_STR_VECTOR(str) atosv(str)  //字符串到QStringList
#define STR_TO_RES_TEXT(str) getResText(str)  //字符串到资源字符串
#define STR_TO_RES_STYLE(str) getResStyle(str)  //字符串到资源字Style
#define STR_TO_INT_PAIR(str) atoip(str)

/*********************** ui_node节点操作 *********************/
//从Object中获得ui_node节点
//参数：
//	object:Object对象
//返回值：ui_node指针
void* getUINodeFromObject(void* object);

//获得QVariant中的ui_node指针
//参数：
//	variant:Variant对象
//返回值：ui_node指针
void* getUINodeFromVariant(void* variant);

//获得xml文件根节点
//参数：
//	filename:xml文件路径
//	root:xml根节点
//返回值：获得成功返回true,否则返回false
bool getXMLFileRoot(const char* filename,xml_node* root);


/****************** 字符串操作 ********************/
//分割,C++实现
//将字符串通过特定字符分隔
//参数：
//	inStr:输入字符串
//	outStrVec:输出字符数组
//	sep:分隔符
//返回值：无
void splitString(std::string& inStr,std::vector<std::string>& outStrVec,std::string sep);

//将字符串中某个字符全部替换
//参数：
//	str:输入字符串
//	old_value:旧字符段
//	new_value:新字符段
//返回值：无
std::string&  str_replace_all(std::string&  str,const std::string&  old_value,const std::string&  new_value);


/******************* 目录操作 *********************/
//去掉文件的扩展名称
//参数：
//	filename:文件名
//返回值：无
void removeExtension(std::string& filename);

//是否存在文件或者文件夹路径
//参数：
//	path:路径
//返回值：存在返回true,否则返回false
bool fileOrPahtExist(const char* path);

//创建目录，包括递归创建
//参数：
//	path:目录路径
//	recurseFlag:是否地柜创建
//	perm:目录访问权限
//返回值：成功返回true,否则返回false
bool createDirectory(const char* path, bool recurseFlag = true, int perm = 0775);

//从路径字符串中提取出磁盘(eg:"D:")，路径(eg:"D:/a/b/c/"),文件名(eg:"exename"),后缀(eg:"exe")
//参数：
//	path:路径字符串
//	drive:盘符
//	dir:目录路径
//	fname:文件名
//	ext:文件后缀
//返回值：无
void splitpath(const char*path,  std::string& drive, std::string& dir, std::string& fname, std::string& ext);

//读取文件夹下所有文件的文件名
//参数：
//	path:目录路径
//	files:文件名数组
//	filter:过滤器，文件后缀
//返回值：无
void getAllFilesInCurrentDir(std::string path,std::vector<std::string>& files,std::string filter="");

/******************* 编码变换 *********************/
//Gb2312编码字符转换为UTF8 字符
//参数：
//	szOut:输出字符串
//	szIn:输入字符串
//返回值：无
void Gb2312ToUTF8(char *szOut, const char *szIn);



//一些专用日志输出
//判断文件或者路径是否存在
//参数：
//	path:路径
//	type:输出日志类型
//返回值：无
void logFileOrPathExist(const char* path,Log::LOG_TYPE type=Log::LOG_WARN,bool autoCreate = false);



bool bindQObjectAndNode(QObject* object,ui_node* node);