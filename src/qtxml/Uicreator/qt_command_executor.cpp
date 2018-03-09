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

//执行xml_node类型命令
//参数：node xml_node对象指针
//返回值：是否执行成功
bool qt_command_executor::executeCommand(xml_node* node)
{
	QF::IQF_Main_Ext* pMain = (QF::IQF_Main_Ext*)app_env::getMainPtr();
	if (!pMain)
	{
		return false;
	}
    if (!node->hasAttribute("command")&&!node->hasAttribute("msgcommand"))
    {
        return false;
    }
	if (node->hasAttribute("command"))
	{
        std::string res = node->getAttribute("command");
        if (res.find("@command/") != std::string::npos)
        {
            int i = res.find_first_of("@command/");
            res = res.substr(i + 9);
        }
        else
        {
            return pMain->ExecuteCommand(res.c_str(), 0, 0);
        }
        xml_node* command = (xml_node*)R::Instance()->getCommandResource(res.c_str());
        if (command->hasAttribute("name"))
        {
            QF::IQF_Properties* properties=pMain->CreateProperties();
            parseCommandProperty(command, properties,node);
            bool success = pMain->ExecuteCommand(command->getAttribute("name"), properties, 0);
            properties->Release();
            return success;
        }
        else
        {
            return false;
        }	
	}
	if (node->hasAttribute("msgcommand"))
	{
		string command = node->getAttribute("msgcommand");
        pMain->SendMessage(command.c_str(), 0, 0);
	}
	return false;
}

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
                std::vector<std::string> strv;
                splitString(content, strv, ":");
                if (strv.size() != 2)
                {
                    continue;
                }
                if (strcmp(child->getAttribute("type"),"Node")==0)
                { 
                    if (strv[0].compare("sender")==0)
                    {
                        if (sender->hasAttribute(strv[1].c_str()))
                        {
                            properties->SetStringProperty(child->getAttribute("name"), sender->getAttribute(strv[1].c_str()));
                        }
                    }
                    else
                    {
                        xml_node* node = (xml_node*)R::Instance()->getIdentifiedNode(strv[0].c_str());
                        if (node)
                        {
                            if (node->hasAttribute(strv[1].c_str()))
                            {
                                properties->SetStringProperty(child->getAttribute("name"), node->getAttribute(strv[1].c_str()));
                            }
                        }
                    }    
                }
                else if (strcmp(child->getAttribute("type"), "Object") == 0)
                {
                    QObject* obj = NULL;
                    if (strv[0].compare("sender") == 0)
                    {
                        ui_node* ui_sender = dynamic_cast<ui_node*>(sender);
                        if (ui_sender)
                        {
                            obj = (QObject*)ui_sender->getObject();
                        }
                    }
                    else
                    {
                        obj = (QObject*)R::Instance()->getObjectFromGlobalMap(strv[0].c_str());
                    } 
                    if (obj)
                    {
                        QVariant v = obj->property(strv[1].c_str());
                        setProperty(properties, child->getAttribute("name"), v);
                    }
                }
                else if (strcmp(child->getAttribute("type"), "Value") == 0)
                {
                    QVariant v;
                    qt_standard::getProperty(content.c_str(), v);
                    setProperty(properties, child->getAttribute("name"), v);
                }
            }
        }
    }
}

void qt_command_executor::setProperty(QF::IQF_Properties* properties, const char* name, const QVariant& v)
{
    if (v.isValid())
    {
        switch (v.type())
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