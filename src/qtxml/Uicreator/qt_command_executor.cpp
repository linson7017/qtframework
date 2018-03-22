#include "qt_command_executor.h"
#include "Uicreator/ui_node.h"
#include "Utils/util.h"
#include "Common/app_env.h"
#include "Res/R.h"
#include "Utils/variant.h"
#include "Utils/qt_standard.h"


#include <string.h>
#include <iostream>
#include <QtCore/QVariant>
#include <QObject>

#include <qfmain/internal/iqf_main_ext.h>
#include <qfmain/iqf_properties.h>
#include <qfmain/iqf_subject.h>

//using namespace gise;
//构造函数
//参数：无
//返回值：无
qt_command_executor::qt_command_executor(void):QObject()
{
}

//析构函数
//参数：无
//返回值：无
qt_command_executor::~qt_command_executor(void)
{
}
//执行ui_node类型命令
//参数：node ui_node对象指针
//返回值：是否执行成功
//bool qt_command_executor::executeCommand(ui_node* node)
//{
//    QF::IQF_Main_Ext* pMain = (QF::IQF_Main_Ext*)app_env::getMainPtr();
//    if (node->hasAttribute("msgcommand"))
//    {
//        string command = node->getAttribute("msgcommand");
//
//        VarientMap vm = node->getParameters();
//        if (node->hasAttribute("property")||node->hasAttribute("itemProperty"))
//        {
//            if (node->hasAttribute("property"))
//            {
//                QObject* obj = (QObject*)node->getObject();
//                std::string propertyStr = node->getAttribute("property");
//                if (propertyStr.compare("object")==0)
//                {
//                    variant v;
//                    v.setPtr(obj);
//                    vm[propertyStr] = v;
//                }
//                else
//                {
//                    QVariant qProperty = obj->property(propertyStr.c_str());
//                    if (qProperty.isValid())
//                    {
//                        variant v;
//                        if (qt_standard::exchangProperty(qProperty, v))
//                        {
//                            vm[propertyStr] = v;
//                        }
//                    }
//                }   
//            }
//            if (node->hasAttribute("itemProperty"))
//            {
//                std::string propertyStr = node->getAttribute("itemProperty");
//                int i = propertyStr.find(":");
//                if (i != std::string::npos)
//                {
//                    std::string id = propertyStr.substr(0, i);
//                    std::string propertyName = propertyStr.substr(i + 1, propertyStr.length() - 1 - i);
//                    QObject* obj = (QObject*)R::Instance()->getObjectFromGlobalMap(id.c_str());
//                    QVariant qProperty = obj->property(propertyName.c_str());
//                    if (qProperty.isValid())
//                    {
//                        variant v;
//                        if (qt_standard::exchangProperty(qProperty, v))
//                        {
//                            vm[propertyName] = v;
//                        }
//                    }
//                }
//            }     
//        }
//        if (vm.size()>0)
//        {
//            pMain->SendMessage(command.c_str(), vm.size(), (void*)&vm);
//        }
//        else
//        {
//            pMain->SendMessage(command.c_str(), 0, (void*)node->getObject());
//        }
//        std::cout << "Execute Command " << command << std::endl;
//    }
//	if (node->hasAttribute("command"))
//	{
//		string command = node->getAttribute("command");
//		if (pMain->ExecuteCommand(command.c_str(), 0, 0))
//		{
//			//return true;
//			std::cout << "Execute Command " << command << " Successed !"<<std::endl;
//		}
//		else
//			std::cout << "Execute Command " << command << " Failed !"<<std::endl;
//	}
//
//    return true;
//
//    //xml_node* xmlNode = static_cast<xml_node*>(node);
//	//return executeCommand(xmlNode);
//}

bool qt_command_executor::execute(xml_node* command, xml_node* node)
{
    QF::IQF_Subject* pSubject = NULL;
    if (node->hasAttribute("ui_node") && STR_TO_BOOL(node->getAttribute("ui_node")))
    {
        ui_node* uiNode = (ui_node*)node;
        pSubject = (QF::IQF_Subject*)uiNode->getObject("subject");
    }
    QF::IQF_Main_Ext* pMain = (QF::IQF_Main_Ext*)app_env::getMainPtr();
    if (strcmp(command->getName(),"Command")==0)
    {
        if (command->hasAttribute("name"))
        {
            QF::IQF_Properties* properties = pMain->CreateProperties();
            parseCommandProperty(command, properties, node);
            bool success = pMain->ExecuteCommand(command->getAttribute("name"), properties, 0);
            properties->Release();
            return true;
        }
    }
    else if (strcmp(command->getName(), "MsgCommand") == 0)
    {
        if (command->hasAttribute("name"))
        {
            QF::IQF_Properties* properties = pMain->CreateProperties();
            parseCommandProperty(command, properties, node);
            if (pSubject)
            {
                pSubject->Notify(command->getAttribute("name"), properties->GetCount(), properties);
            }
            else
            {
                pMain->SendMessage(command->getAttribute("name"), properties->GetCount(), properties);
            }
            properties->Release();
            return true;
        }
    } 
    return false;
}

//执行xml_node类型命令
//参数：node xml_node对象指针
//返回值：是否执行成功
bool qt_command_executor::executeCommand(xml_node* node)
{
    QF::IQF_Subject* pSubject = NULL;
    if (node->hasAttribute("ui_node") && STR_TO_BOOL(node->getAttribute("ui_node")))
    {
        ui_node* uiNode = (ui_node*)node;
        pSubject = (QF::IQF_Subject*)uiNode->getObject("subject");
    }
	QF::IQF_Main_Ext* pMain = (QF::IQF_Main_Ext*)app_env::getMainPtr();
	if (!pMain)
	{
		return false;
	}
    if (!node->hasAttribute("command")&&!node->hasAttribute("msgcommand"))
    {
        return false;
    }
    bool executeCommandSuccess = true;
	if (node->hasAttribute("command"))
	{
        std::string res = node->getAttribute("command");
        if (res.find("@command/") != std::string::npos)
        {
            int i = res.find_first_of("@command/");
            res = res.substr(i + 9);
            xml_node* command = (xml_node*)R::Instance()->getCommandResource(res.c_str());
            execute(command, node);
        }
        else
        {
            executeCommandSuccess &= pMain->ExecuteCommand(res.c_str(), 0, 0);
        }
        if (!executeCommandSuccess)
        {
            printf("Execute command %s failed!", res.c_str());
        }
	}
	if (node->hasAttribute("msgcommand"))
	{
        std::string res = node->getAttribute("msgcommand");
        if (res.find("@msgcommand/") != std::string::npos)
        {
            int i = res.find_first_of("@msgcommand/");
            res = res.substr(i +12);
            xml_node* msgcommand = (xml_node*)R::Instance()->getCommandResource(res.c_str());
            execute(msgcommand, node);
        }
        else
        {
            if (pSubject)
            {
                pSubject->Notify(node->getAttribute("msgcommand"), 0, 0);
            }
            else
            {
                pMain->SendMessage(node->getAttribute("msgcommand"), 0, 0);
            }
        }
	}
	return false;
}

#include "json/reader.h"

void qt_command_executor::parseCommandProperty(xml_node* commandNode, QF::IQF_Properties* properties, xml_node* sender)
{
    if (commandNode->getChildNum() != 0)
    {
        for (int i = 0; i < commandNode->getChildNum(); i++)
        {
            xml_node* child = commandNode->getChild(i);
            if (child->hasAttribute("name")&& child->hasAttribute("type"))
            {
                std::string content = child->getContent();
                if (content.empty())
                {
                    continue;
                }
                /*std::vector<std::string> strv;
                splitString(content, strv, ":");
                if (strv.size() != 2)
                {
                    continue;
                }*/
                if (strcmp(child->getAttribute("type"),"Node")==0)
                { 
                    xml_node* node = NULL;
                    Json::Value root;
                    Json::Reader reader;
                    if (reader.parse(content, root, false))
                    {
                        std::string id = root.get("id", "").asString();
                        node = id.empty() ? sender : R::Instance()->getIdentifiedNode(root.get("id","").asString().c_str());
                        if (node)
                        {
                            if (node->hasAttribute(root.get("name","").asString().c_str()))
                            {
                                setProperty(properties, child->getAttribute("name"), 
                                    QVariant(node->getAttribute(root.get("name", "").asString().c_str())), root.get("type", "").asString().c_str());
                            }

                        }
                    }
                }
                else if (strcmp(child->getAttribute("type"), "Object") == 0)
                {
                    QObject* obj = NULL;
                    Json::Value root;
                    Json::Reader reader;
                    if (reader.parse(content, root, false))
                    {
                        std::string id = root.get("id", "").asString();
                        obj = (QObject*)(id.empty()? dynamic_cast<ui_node*>(sender)->getObject() : R::Instance()->getObjectFromGlobalMap(id.c_str()));
                        if (obj)
                        {
                            QVariant v = obj->property(root.get("name", "").asString().c_str());
                            setProperty(properties, child->getAttribute("name"), v, root.get("type", "").asString().c_str());
                        }
                    }    
                }
                else if (strcmp(child->getAttribute("type"), "Value") == 0)
                {
                    xml_node* node = NULL;
                    Json::Value root;
                    Json::Reader reader;
                    if (reader.parse(content, root, false))
                    {
                          setProperty(properties, child->getAttribute("name"),
                               QVariant(root.get("value","").asString().c_str()), root.get("type", "").asString().c_str());
                    }
                }
                else if (strcmp(child->getAttribute("type"), "Json") == 0)
                {
                    setProperty(properties, child->getAttribute("name"),
                        QVariant(content.c_str()));
                }
            }
        }
    }
}

void qt_command_executor::setProperty(QF::IQF_Properties* properties, const char* name, const QVariant& v, const char* convertType)
{
    if (v.isValid())
    {
        QVariant::Type type = QVariant::Invalid;
        if (strcmp(convertType,"")==0)
        {
            type = v.type();
        }
        else
        {
            type = QVariant::nameToType(convertType);
        }  
        switch (type)
        {
        case QVariant::Int:
            properties->SetIntProperty(name, v.toInt());
            break;
        case QVariant::Double:
            properties->SetDoubleProperty(name, v.toDouble());
            break;
        case QVariant::Bool:
            properties->SetBoolProperty(name, v.toBool());
            break;
        case QVariant::String:
            properties->SetStringProperty(name, v.toString().toLocal8Bit().constData());
            break;
        }
    }
}