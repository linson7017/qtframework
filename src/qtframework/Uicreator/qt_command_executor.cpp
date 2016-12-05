#include "qt_command_executor.h"
#include "Uicreator/ui_node.h"
#include "Utils/util.h"
#include "Common/app_env.h"
//#include "gise_config.h"
//#include "main/igis_main.h"


#include <string.h>

#include <QMessageBox>
#include <QtCore/QVariant>

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
bool qt_command_executor::executeCommand(ui_node* node)
{
	xml_node* xmlNode = static_cast<xml_node*>(node);
	return executeCommand(xmlNode);
	
}
//执行xml_node类型命令
//参数：node xml_node对象指针
//返回值：是否执行成功
bool qt_command_executor::executeCommand(xml_node* node)
{
	//gise::IGIS_Main* pMain = (gise::IGIS_Main*)app_env::getMainPtr();
	//if (!pMain)
	//{
	//	char szMsg[1024];
	//	if (node->hasAttribute("command")||node->hasAttribute("msgcommand")||node->hasAttribute("toolcommand"))
	//	{
	//		sprintf(szMsg, "QtFrameWork ERROR: Execute command of node \"%s\" %s failed! Because IGIS_Main is not initialized!\n",node->getName(),node->hasAttribute("id")?node->getAttribute("id"):"");
	//		printf(szMsg);
	//	}
	//	return false;
	//}
	//if (node->hasAttribute("command"))
	//{
	//	string command = node->getAttribute("command");
	//	int icommand = STR_TO_INT(command.c_str());
	//	if (pMain->ExecuteCommand(icommand, 0, 0))
	//	{
	//		return true;
	//	}else
	//		return false;
	//}
	////ssx
	//if (node->hasAttribute("msgcommand"))
	//{
	//	string command = node->getAttribute("msgcommand");
	//	int icommand = STR_TO_INT(command.c_str());
	//	pMain->SendMessage(icommand, 0, (void*)node->getAttribute("id"));		
	//}
	//if (node->hasAttribute("toolcommand"))
	//{
	//	string sToolID = node->getAttribute("toolcommand");
	//	int iToolID = STR_TO_INT(sToolID.c_str());
	//	if (pMain->SelectTool(iToolID))
	//	{
	//		return true;
	//	}else
	//		return false;
	//}
	return false;
}