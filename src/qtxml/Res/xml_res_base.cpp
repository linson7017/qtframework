#include "Res/xml_res_base.h"
#include <Utils/util.h>
#include <Utils/sys_util.h>


xml_res_base::xml_res_base()
{
}


xml_res_base::~xml_res_base()
{
}

void xml_res_base::parseResourceXML(const char* dir)
{
    std::string uicommandResDir = dir;
    std::vector<std::string> files;
    std::vector<std::string>::const_iterator it;
    getAllFilesInCurrentDir(uicommandResDir, files, "*.xml");
    for (it = files.begin(); it != files.end(); ++it)
    {
        string filepath = uicommandResDir;
        filepath.append(*it);
        parseXML(filepath.c_str());
        _filesInfo[filepath] = sys_util::GetFileLastChangeTime(filepath.c_str());
    }
}

bool xml_res_base::filesInfoChanged(const char* dir,const char* filter)
{
    std::vector<std::string> files;
    std::vector<std::string>::const_iterator it;
    getAllFilesInCurrentDir(dir, files, filter);
    std::map< std::string, time_t> currentFileInfo;
    for (it = files.begin(); it != files.end(); ++it)
    {
        std::string filepath = dir;
        filepath.append(*it);
        currentFileInfo[filepath] = sys_util::GetFileLastChangeTime(filepath.c_str());
    }

    if (currentFileInfo.size() != _filesInfo.size())
    {
        return true;
    }
    else
    {

        for (std::map< string, time_t>::iterator it = _filesInfo.begin(); it != _filesInfo.end(); it++)
        {
            if (currentFileInfo.count(it->first) == 0)
            {
                return true;
            }
            else
            {
                if (currentFileInfo[it->first] != it->second)
                {
                    return true;
                }
            }
        }
        return false;
    }

}
