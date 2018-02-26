#include "xml_ui_base.h"
#include <vector>

#include "Utils/util.h" 
#include "Uicreator/ui_node.h"
#include "Uicreator/xml_ui_paser.h"
#include "Common/app_env.h"


xml_ui_base::xml_ui_base(const char* dir):_dir(dir)
{
    parseXML(dir);
}


xml_ui_base::~xml_ui_base()
{
    if (_dir.compare(app_env::getUIResDir())==0)
    {
        return;
    }
    for (ResMapType::iterator it = _res_map.begin(); it != _res_map.end(); it++)
    {
        if (it->second)
        {
            it->second->release();
        }
    }
}

ui_node* xml_ui_base::getUIRootNode(const char* id)
{
    ResMapType::iterator it = _res_map.find(id);
    if (it != _res_map.end())
    {
        return it->second;
    }
    else
    {
        return NULL;
    }
}

void xml_ui_base::parseXML(const char* dir)
{
    std::string panelResDir = dir;
    std::vector<std::string> files;
    getAllFilesInCurrentDir(panelResDir, files, "*.xml");
    std::vector<std::string>::const_iterator it;

    for (it = files.begin(); it != files.end(); ++it)
    {
        string filepath = panelResDir;
        filepath.append(*it);
        ui_node* node = new ui_node;
        if (xml_ui_paser::parserXML(filepath.c_str(), node))
        {
            if (node->hasAttribute("id"))
            {
                string id = node->getAttribute("id");
                if (!_res_map.count(id.c_str()))
                {
                    _res_map[id] = node;
                }
            }
        }
    }
}