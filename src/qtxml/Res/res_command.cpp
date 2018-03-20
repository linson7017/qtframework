#include "res_command.h"
#include "Uicreator/xml_node.h"
#include "Common/app_env.h"
#include "Utils/Log.h"
#include "Utils/util.h"
#include "Utils/sys_util.h"

//���캯��
//��������
//����ֵ����
res_command::res_command(void)
{
    _res_map.clear();
    _filesInfo.clear();
    parseResourceXML(app_env::getDir(app_env::COMMAND_RESOURCE));
}

//��������
//��������
//����ֵ����
res_command::~res_command(void)
{
}
//���UICommand��Դ
//������id ID
//����ֵ����Դ
xml_node* res_command::getCommandRes(const char* id)
{
    CHECK_FILES_CHANGED(COMMAND_RESOURCE)
    XMLNodeMapType::iterator it = _res_map.find(id);
    if (it != _res_map.end())
    {
        return it->second;
    }
    else
    {
        return NULL;
    }
}

void res_command::releaseResource()
{
    xml_res_base::releaseResource();
    for (XMLNodeMapType::iterator it = _res_map.begin();it!=_res_map.end();it++)
    {
        it->second->release();
    }
    _res_map.clear();
}



//���������ļ�xml
//������filename �ļ�·��
//����ֵ����
void res_command::parseXML(const char* filename)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile(filename);
    if (error != tinyxml2::XML_SUCCESS)
    {
        printf("Load xml file %s failed! Error code: %s \n", filename, doc.ErrorStr());
        return;
    }
    tinyxml2::XMLElement* str = doc.RootElement();
    while (str != NULL)
    {
        if ((strcmp(str->Name(), "UICommand") == 0)|| (strcmp(str->Name(), "Command") == 0)|| (strcmp(str->Name(), "MsgCommand") == 0))
        {
            xml_node* strNode = new xml_node;
            strNode->relateXMLNode(str);
            strNode->addAttribute("commandType", str->Name());
            tinyxml2::XMLElement* propertyNode = str->FirstChildElement();
            while (propertyNode != NULL)
            {
                if (strcmp(propertyNode->Name(), "Property") == 0)
                {
                    xml_node* pn = new xml_node;
                    pn->relateXMLNode(propertyNode);
                    strNode->addChild(pn);
                }
                propertyNode = propertyNode->NextSiblingElement();
            }
            if (strNode->hasAttribute("id"))
            {
                _res_map[strNode->getAttribute("id")] = strNode;
            }
        }
        else if (strcmp(str->Name(), "Commands") == 0)
        {
            xml_node* commandsNode = new xml_node;
            commandsNode->relateXMLNode(str);
            tinyxml2::XMLElement* strchild = str->FirstChildElement();
            while (strchild != NULL)
            {
                if ((strcmp(strchild->Name(), "UICommand") == 0) || (strcmp(strchild->Name(), "Command") == 0) || (strcmp(strchild->Name(), "MsgCommand") == 0))
                {
                    xml_node* commandNode = new xml_node;
                    commandNode->relateXMLNode(strchild);
                    commandNode->addAttribute("commandType", strchild->Name());
                    tinyxml2::XMLElement* propertyNode = strchild->FirstChildElement();
                    while (propertyNode!=NULL)
                    {
                         if (strcmp(propertyNode->Name(), "Property") == 0)
                         {
                             xml_node* pn = new xml_node;
                             pn->relateXMLNode(propertyNode);
                             commandNode->addChild(pn);
                         }
                         propertyNode = propertyNode->NextSiblingElement();
                    }
                    commandsNode->addChild(commandNode);
                }
                strchild = strchild->NextSiblingElement();
            }
            if (commandsNode->hasAttribute("id"))
            {
                _res_map[commandsNode->getAttribute("id")] = commandsNode;
            }

        }
        str = str->NextSiblingElement();
    }
}
