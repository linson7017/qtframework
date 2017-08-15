#include "util.h"
#include <QtCore/QDir>
#include <QtCore/QVariant>
#include "Uicreator/ui_node.h"
#include "Utils/Log.h"
#include "Common/app_env.h"
#include "Utils/Log.h"

#if defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__
#include <io.h>
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/io.h>
#endif
Q_DECLARE_METATYPE(ui_node*); 


#include "Res/R.h"

//将字符串转换为BOOL型
//参数：
//	str:输入字符
//返回值：true或者false
bool atob(const char* str)
{
	if(strcmp(str,"true")==0||strcmp(str,"TRUE")==0)  
		return true;    
	else          
		return false; 
}

std::pair<int, int> atoip(const char* str)
{
    std::vector<std::string> strVec;
    std::string temp = str;
    splitString(temp, strVec, ",");
    std::pair<int, int> result;
    result.first = atoi(strVec[0].c_str());
    result.second = atoi(strVec[1].c_str());
    return result;
}

//将字符串用";;"分离成字符数组
//参数：
//	str:输入字符
//返回值：字符数组
QStringList atosv(const char* str)
{
	QString qs = str;
	QStringList qsl = qs.split(";;");
	return qsl;
}

//获得字符资源
//参数：
//	str:输入字符
//返回值：字符资源
const char* getResText(const char* str)
{
	QString qs = QString::fromLocal8Bit(str);
	if (qs.contains("@string/"))
	{
		int i = qs.lastIndexOf("/");
		qs = qs.right(qs.length()-i-1);
		return R::Instance()->getStringResource(qs.toStdString().c_str());
	}else
	{
		return str;
	}
}


//获得样式资源
//参数：
//	str:输入字符
//返回值：样式资源
const char* getResStyle(const char* str)
{
	std::string res = str;
	if (res.find("@style/")!=std::string::npos)
	{
		int i = res.find_first_of("@style/");
		res = res.substr(i+7);
		return R::Instance()->getStyleResource(res.c_str());
	}else
		return R::Instance()->getStyleResource(str);
	
}

//获得res目录下image目录下的图片路径
//参数：
//	url:res目录下image目录下的图片路径
//	istr: 输入字符
//返回值：无
void getResImageUrl(std::string& url,const char* istr)
{
	std::string res = istr;
	url = app_env::getImageResDir();
	if (res.find("@image/")!=std::string::npos)
	{
		int i = res.find_first_of("@image/");
		url.append(res.substr(i+7));
	}
	else
		url.append(istr);

#if defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__
	char temp[1024];
	Gb2312ToUTF8(temp,url.c_str());
	url = temp;
#endif
	logFileOrPathExist(url.c_str());

}


//获得res目录下qml目录下的图片路径
//参数：
//	url:res目录下image目录下的qml路径
//	istr: 输入字符
//返回值：无
void getResQmlUrl(std::string& url,const char* istr)
{
	std::string res = istr;
	url = app_env::getQmlResDir();
	if (res.find("@qml/")!=std::string::npos)
	{
		int i = res.find_first_of("@qml/");
		url.append(res.substr(i+5));
	}
	else
		url.append(istr);

#if defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__
	char temp[1024];
	Gb2312ToUTF8(temp,url.c_str());
	url = temp;
#endif
	logFileOrPathExist(url.c_str());

}


//获得res目录下icon目录下的图片路径
//参数：
//	url:res目录下icon目录下的图片路径
//	istr: 输入字符
//返回值：无
void getResIconUrl(std::string& url,const char* istr)
{
	std::string res = istr;
	url = app_env::getIconResDir();
	if (res.find("@icon/")!=std::string::npos)
	{
		int i = res.find_first_of("@icon/");
		url.append(res.substr(i+5));
	}
	else
		url.append(istr);

#if defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__
	char temp[1024];
	Gb2312ToUTF8(temp,url.c_str());
	url = temp;
#endif
	logFileOrPathExist(url.c_str());
}

//获得res目录下images目录或者icons目录下的图片路径
//参数：
//	url:res目录下images目录或者icons目录下的图片路径
//	istr: 输入字符
//返回值：无
void getResImageOrIconUrl(std::string& url,const std::string& istr)
{
	if (istr.find("@image/")!=std::string::npos)
	{
		getResImageUrl(url,istr.c_str());
	}
	else if (istr.find("@icon/")!=std::string::npos)
	{
		getResIconUrl(url,istr.c_str());
	}
	else
		url = istr;

//#if defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__
//	//char temp[1024];
//	//Gb2312ToUTF8(temp,url.c_str());
//	//url = temp;
//#endif
//	logFileOrPathExist(url.c_str());
}

//从Object中获得ui_node节点
//参数：
//	object:Object对象
//返回值：ui_node指针
void* getUINodeFromObject(void* object)
{
	QObject* qObject = (QObject*)object;
	return qObject->property("ui_node").value<ui_node*>();
}

//获得QVariant中的ui_node指针
//参数：
//	variant:Variant对象
//返回值：ui_node指针
void* getUINodeFromVariant(void* variant)
{
	QVariant* qVariant = (QVariant*)variant;
	return qVariant->value<ui_node*>();
}

//获得xml文件根节点
//参数：
//	filename:xml文件路径
//	root:xml根节点
//返回值：获得成功返回true,否则返回false
bool getXMLFileRoot(const char* filename,xml_node* root)
{
	xmlKeepBlanksDefault(0);
	xmlDocPtr doc;

	doc = xmlReadFile(filename,"utf-8",XML_PARSE_READER);
	if (doc == NULL)
	{
		xmlFreeDoc(doc);
		return false;
	}
	xmlNodePtr curXMLNode = xmlDocGetRootElement(doc);
	if (!curXMLNode)
	{
		return false;
	}
	if (!root)
	{
		root = new ui_node;
	}
	root->relateXMLNode(curXMLNode);
	xmlFreeDoc(doc);
	return true;
}

//是否存在文件或者文件夹路径
//参数：
//	path:路径
//返回值：存在返回true,否则返回false
bool fileOrPahtExist(const char* path)
{
	if (access(path,0))
		return false;
	else
		return true;
}

//将字符串中某个字符全部替换
//参数：
//	str:输入字符串
//	old_value:旧字符段
//	new_value:新字符段
//返回值：无
std::string&  str_replace_all(string& str,const std::string&  old_value,const std::string&  new_value)     
{     
	for(std::string::size_type   pos(0);   pos!=std::string::npos;   pos+=new_value.length())   
	{     
		if((pos=str.find(old_value,pos))!=std::string::npos)     
			str.replace(pos,old_value.length(),new_value);     
		else   break;     
	}     
	return   str;     
}

//将字符串通过特定字符分隔
//参数：
//	inStr:输入字符串
//	outStrVec:输出字符数组
//	sep:分隔符
//返回值：无
void splitString(std::string& inStr,std::vector<std::string>& outStrVec,std::string sep)
{
	std::string temp = inStr.c_str();
	char* result = NULL;
	result = strtok((char*)temp.data(),(char*)sep.data());
	while (result!=NULL)
	{
		outStrVec.push_back(result);
		result = strtok(NULL,(char*)sep.data());
	}
}

//去掉文件的扩展名称
//参数：
//	filename:文件名
//返回值：无
void removeExtension(std::string& filename)
{
	while (1)
	{
		if (filename.find(".")!=string::npos)
		{
			int i = filename.find_last_of(".");
			filename = filename.substr(0,i);
		}else
			break;
	}
}

//创建目录，包括递归创建
//参数：
//	path:目录路径
//	recurseFlag:是否地柜创建
//	perm:目录访问权限
//返回值：成功返回true,否则返回false
bool createDirectory(const char* path, bool recurseFlag, int perm)
{
	if(fileOrPahtExist(path)) 
	{
		return true;
	}
	std::string normalizedPath = path;
	str_replace_all(normalizedPath,"\\","/");
	std::string tempFile = normalizedPath;
	std::vector<std::string> result;
	if(recurseFlag)
	{
		std::string::iterator iter = tempFile.begin();
		std::string::size_type slash_pos = 0,end_slash_pos = 0;
		slash_pos = tempFile.find('/',slash_pos+1);
		end_slash_pos = tempFile.rfind('/');
		if (slash_pos == std::string::npos && end_slash_pos == std::string::npos)
		{
			if (!fileOrPahtExist(normalizedPath.c_str()))
			{
				//songling
#if defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__
				if ( _mkdir(normalizedPath.c_str()) != 0 ) 
#else
				if ( mkdir(normalizedPath.c_str(),perm) != 0 )
#endif


					return false;
			}
			return true;
		}
		while (slash_pos<=end_slash_pos)
		{
			if(slash_pos != end_slash_pos)
			{
				slash_pos = tempFile.find('/',slash_pos+1);
				normalizedPath = std::string(iter,iter+slash_pos);
			}else
			{
				normalizedPath = tempFile;
				slash_pos+=1;
			}
			if (!fileOrPahtExist(normalizedPath.c_str()))
			{
				//songling
#if defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__
				if ( _mkdir(normalizedPath.c_str()) != 0 ) 
#else
				if ( mkdir(normalizedPath.c_str(),perm) != 0 )
#endif
					return false;
			}
		}
	}
	return true;
}

//从路径字符串中提取出磁盘(eg:"D:")，路径(eg:"D:/a/b/c/"),文件名(eg:"exename"),后缀(eg:"exe")
//参数：
//	path:路径字符串
//	drive:盘符
//	dir:目录路径
//	fname:文件名
//	ext:文件后缀
//返回值：无
void splitpath(const char*path, std::string& drive, std::string& dir, std::string& fname, std::string& ext)
{
	std::string temp = path;
	str_replace_all(temp,"\\","/");
	std::vector<std::string> v;
	splitString(temp,v,"/");
	int size = v.size();
	if (size<=1)
	{
		dir=temp;
		fname="";
		ext="";
	}
	else
	{
		fname = v.at(size-1);
		if (fname.find(".")!=std::string::npos)
		{
			int index = fname.find_first_of(".");
			ext = fname.substr(index+1,fname.size()-1);
			fname = fname.substr(0,index);
		}
		if (temp.find(":")!=std::string::npos)
		{
			int i = temp.find_first_of(":");
			drive = temp.substr(0,i+1);
		}
		else
		{
			drive="";
		}
		dir = temp;
		if (temp.find("/")!=std::string::npos)
		{
			int j = dir.find_last_of("/");
			dir = dir.substr(0,j+1);
		}
		
	}
	
}

//读取文件夹下所有文件的文件名
//参数：
//	path:目录路径
//	files:文件名数组
//	filter:过滤器，文件后缀
//返回值：无
void getAllFilesInCurrentDir(std::string path,std::vector<std::string>& files,std::string filter)
{
	/*long hFile = 0;
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo))!=-1)
	{
		do 
		{
			if ((fileinfo.attrib&_A_SUBDIR))
			{
				;
			}
			else
			{
				std::string filename = fileinfo.name;
				if (filter.empty())
				{
					files.push_back(fileinfo.name);
					return;
				}
				int i = filename.find_first_of(".");
				std::string ext = "*";
				ext.append(filename.substr(i,filename.length()-1));
				if (strcmp(ext.c_str(),filter.c_str())==0)
				{
					files.push_back(fileinfo.name);
				}
			}
		} 
		while (_findnext(hFile,&fileinfo)==0);
		_findclose(hFile);
	}*/
	QStringList qfiles;
#if defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__
	char temp[1024];
	Gb2312ToUTF8(temp,path.c_str());
	path = temp;
#endif
	QDir dir(path.c_str());
	QStringList filters;
	filters << filter.c_str() ;
	qfiles = dir.entryList(filters);
	QStringList::const_iterator it;
	for (it = qfiles.constBegin(); it != qfiles.constEnd(); ++it )
	{
		files.push_back((*it).toStdString());
	}
}

//Gb2312编码字符转换为UTF8 字符
//参数：
//	szOut:输出字符串
//	szIn:输入字符串
//返回值：无
void Gb2312ToUTF8(char *szOut, const char *szIn)
{
	char * pszIn = (char *)szIn;	
	char * pszOut = (char *)szOut;	
	size_t nIn = strlen(szIn);	
	size_t nOut = 1024;	

	iconv_t type = iconv_open("UTF-8", "GB2312");
	iconv(type, (const char **)&pszIn, &nIn, (char **)&pszOut, &nOut);
	iconv_close(type);

	szOut[1024-nOut]=0;	
}

//判断文件或者路径是否存在
//参数：
//	path:路径
//	type:输出日志类型
//返回值：无
void logFileOrPathExist(const char* path,Log::LOG_TYPE type, bool autoCreate)
{
	if (fileOrPahtExist(path))
	{		
	}
	else
	{
        char szMsg[1024];
        if (autoCreate)
        {
            createDirectory(path);
            sprintf(szMsg, "Create Directory %s! \r\n", path);
            printf(szMsg);
        }
        else
        {
            sprintf(szMsg, "%s does not exist! \r\n", path);
            printf(szMsg);
        }		
	}
}


bool bindQObjectAndNode(QObject* object,ui_node* node)
{

	if (getUINodeFromObject(object))
	{
		return true;
	}
	if (object)
	{
		QVariant variant;
		variant.setValue(node);
		object->setProperty("ui_node",variant);
		return true;
	}else
		return false;
	
}