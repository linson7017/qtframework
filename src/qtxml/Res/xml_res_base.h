/********************************************************************
	FileName:    xml_res_base.h
	Author:        Ling Song
	Date:           Month 2 ; Year 2018
	Purpose:	     
*********************************************************************/
#ifndef xml_res_base_h__
#define xml_res_base_h__

#include <map>
#include <string>
#include <memory>

#define CHECK_FILES_CHANGED(dir) \
if (filesInfoChanged(app_env::getDir(app_env::dir)))  \
{          \
    releaseResource(); \
    parseResourceXML(app_env::getDir(app_env::dir));   \
}

class xml_res_base
{
public:
    xml_res_base();
    ~xml_res_base();

protected:
    bool filesInfoChanged(const char* dir,const char* filter="*.xml");
    void parseResourceXML(const char* dir);
    virtual void parseXML(const char* filename) = 0;
    virtual void releaseResource() { _filesInfo.clear(); };
    std::map< std::string, time_t> _filesInfo;
};
#endif // xml_res_base_h__