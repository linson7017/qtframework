#include "qt_uicommand_executor.h"
#include "UIs/Activity.h"
#include "Uicreator/ui_node.h"
#include "Uicreator/xml_node.h"
#include "Uicreator/xml_ui_paser.h"
#include "UIs/CustomActivity.h"
#include "Common/app_env.h"
#include "Common/qt_context.h"
#include "Res/R.h"
#include "Utils/util.h"
#include "Utils/xml_util.h"
#include "Utils/qt_standard.h"
#include "UIs/sl_Button.h"
#include "UIs/sl_MutexButtonBox.h"
#include "Utils/Log.h"

#include <QtGui>
#include <QtWidgets>
#include <QtCore/QVariant>

//构造函数
//参数：无
//返回值：无
qt_uicommand_executor::qt_uicommand_executor(void)
{
}

//析构函数
//参数：无
//返回值：无
qt_uicommand_executor::~qt_uicommand_executor(void)
{
}
//执行命令
//参数：uicommand uicommand类型节点指针, sender 消息发送者
//返回值：是否执行成功
bool qt_uicommand_executor::execute(xml_node* uicommand,ui_node* sender)
{
	if (!uicommand||!uicommand->hasAttribute("type"))
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: Please define the type of UICommand \"%s\"\n",uicommand->getAttribute("id"));
		printf(szMsg);
		return false;
	}
    std::string type = uicommand->getAttribute("type");
	if (strcmp(type.c_str(),"PopDialog")==0||strcmp(type.c_str(),"PopActivity")==0)
	{
		Activity* activity = NULL;
		if (uicommand->hasAttribute("layout"))
		{
			string layoutfilePaht = app_env::getDir(app_env::LAYOUT);
			string layout = uicommand->getAttribute("layout");
			layoutfilePaht.append(layout);
			//判断是以文件格式还是id来命名layout
			if (layout.find(".xml")!=std::string::npos) //如果是以xml文件格式
			{

				if (fileOrPahtExist(layoutfilePaht.c_str()))
				{
					ui_node* xmlRoot = new ui_node;
					if (xml_util::getXMLFileRoot(layoutfilePaht.c_str(),xmlRoot))
					{
						string id;
						if (!xmlRoot->hasAttribute("id"))
						{
							id = layout;
							removeExtension(id);
							activity = R::Instance()->getActivity(id.c_str());
						}
						else
						{
							id = xmlRoot->getAttribute("id");
							activity = R::Instance()->getActivity(xmlRoot->getAttribute("id"));
						}
						if (!activity) //如果没有找到则自动创建并以文件名为id
						{
                            if (xmlRoot->hasAttribute("CustomStyle")&&STR_TO_BOOL(xmlRoot->getAttribute("CustomStyle")))
                            {
                                activity = new CustomActivity; //默认都是MainActivity的子窗口内
                            }
                            else
                            {
                                activity = new Activity; //默认都是MainActivity的子窗口内
                            }
                            
							activity->setContentView(layout.c_str());
							R::Instance()->addActivity(id.c_str(),activity); 
						}	
					}
					else
					{
						char szMsg[1024];
						sprintf(szMsg, "QtFrameWork ERROR: In UICommand \"%s\" :file \"%s\" is not exeisted\n",uicommand->getAttribute("id"),layoutfilePaht.c_str());
						printf(szMsg);
						return false; 
					}
				}
				else
				{
					char szMsg[1024];
					sprintf(szMsg, "QtFrameWork ERROR: In UICommand \"%s\" :file \"%s\" is not exeisted\n",uicommand->getAttribute("id"),layoutfilePaht.c_str());
					printf(szMsg);
					return false;
				}
			}
			else  //以id格式
			{
				activity = R::Instance()->getActivity(layout.c_str());	
				if (!activity)
					return false;	
			}
        	if (strcmp(type.c_str(),"PopDialog")==0)
        	{
        		activity->setWindowFlags(Qt::Dialog); //以dialog形式显示
        	}
            if (!activity->isVisible())
            {
				activity->active();
            }
		}
		else
		{
			if (uicommand->hasAttribute("id"))
			{
				char szMsg[1024];
				sprintf(szMsg, "QtFrameWork ERROR: In UICommand \"%s\":Do not have layout property\n",uicommand->getAttribute("id"));
				printf(szMsg);
			}else
			{
				char szMsg[1024];
				sprintf(szMsg, "QtFrameWork ERROR: In UICommand:Do not have layout property\n");
				printf(szMsg);
			}
			return false;
		}
		return true;
	}
	else if (strcmp(type.c_str(),"CloseDialog")==0)
	{
		if (uicommand->hasAttribute("activityID"))
		{
			Activity* activity = R::Instance()->getActivity(uicommand->getAttribute("activityID"));
			if (activity)
			{
				activity->close();
				return true;
			}
		}
		else
		{
			if (!sender)
			{
				return false;
			}
			std::string id = sender->getAttribute("id");
			if (id.find(".")!=std::string::npos)
			{
				int i = id.find_first_of(".");
				string dialogID = id.substr(0,i);
				Activity* activity = R::Instance()->getActivity(dialogID.c_str());
				if (activity)
				{
					activity->close();
					return true;
				}
			}else
			{
				Activity* activity = R::Instance()->getActivity(id.c_str());
				if (activity)
				{
					activity->close();
					return true;
				}
			}
		}
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: In UICommand %s:Activity not found. The ID of activity to close may not defined.\n",uicommand->getAttribute("id"));
		printf(szMsg);
		return false;
	}
	//使一个widget不可用
	else if (strcmp(type.c_str(),"DisableWidget")==0)
	{
		if (uicommand->hasAttribute("widgetID"))
		{
			QWidget* widget = (QWidget*)R::Instance()->getObjectFromGlobalMap(uicommand->getAttribute("widgetID"));
			if (widget)
			{
				widget->setDisabled(true);
				return true;
			} 
			else
				return false;
		}
		else
			return false;
	}
	//使一个widget可用
	else if (strcmp(type.c_str(),"EnableWidget")==0)
	{
		if (uicommand->hasAttribute("widgetID"))
		{
			QWidget* widget = (QWidget*)R::Instance()->getObjectFromGlobalMap(uicommand->getAttribute("widgetID"));
			if (widget)
			{
				widget->setDisabled(false);
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	//弹出一个MessageBox
	else if (strcmp(type.c_str(),"PopMessageBox")==0)
	{
		if (uicommand->hasAttribute("information"))
		{
			QMessageBox msgBox;
			if (sender)
			{
				msgBox.setParent((QWidget*)sender->getObject());
			}
			if (uicommand->hasAttribute("title"))
			{
				msgBox.setWindowTitle(uicommand->getAttribute("title"));
			}
			msgBox.setInformativeText(uicommand->getAttribute("information"));
			msgBox.setStandardButtons(QMessageBox::Yes);
			msgBox.setWindowFlags(Qt::Dialog);
			msgBox.exec();
			return true;
		}
		else
			return false;
	}
	else if (strcmp(type.c_str(),"ChangeWidgetStyle")==0)
	{
		if (uicommand->hasAttribute("widgetID"))
		{
			std::string widgetid = uicommand->getAttribute("widgetID");
			QWidget* widget = (QWidget*)R::Instance()->getObjectFromGlobalMap(uicommand->getAttribute("widgetID"));
			if (!widget)
			{
				return false;
			}
            if (uicommand->hasAttribute("style"))
            {
                widget->setStyleSheet(getResStyle(uicommand->getAttribute("style")));
            }
            else
            {
                return false;
            }
			return true;
        }
        else
        {
            return false;
        }
	}
	else if (strcmp(type.c_str(),"ChangeButtonIcon")==0)
	{
		if (uicommand->hasAttribute("widgetID")&&uicommand->hasAttribute("icon"))
		{
			sl_Button* btn = (sl_Button*)R::Instance()->getObjectFromGlobalMap(uicommand->getAttribute("widgetID"));
			std::string iconUrl;
			getResImageOrIconUrl(iconUrl,uicommand->getAttribute("icon"));
			btn->setIcon(iconUrl.c_str());
		}
	}
    else if (strcmp(type.c_str(), "ChangeApplicationStyle") == 0)
    {
        if (uicommand->hasAttribute("style"))
        {
            qt_context::setApplicationStyle(uicommand->getAttribute("style"));
            return true;
        }
        else if (sender->getParameter("style").getType()!=variant::UnKnown)
        {
            QVariant qv;
            if (qt_standard::getProperty(sender->getParameter("style").getString(), qv))
            {
                qt_context::setApplicationStyle(qv.toString().toLocal8Bit().constData());
            } 
            return true;
        }
        else
            return false;
    }
	else if (strcmp(type.c_str(),"SwitchWidget")==0)
	{
		if (uicommand->hasAttribute("widgetID"))
		{
			//QStackedWidget* stackedWidget = (QStackedWidget*)R::Instance()->getObjectFromGlobalMap(uicommand->getAttribute("widgetID"));
			QObject* object = (QObject*)R::Instance()->getObjectFromGlobalMap(uicommand->getAttribute("widgetID"));
			if (!object)
			{
				char szMsg[1024];
				sprintf(szMsg, "QtFrameWork ERROR: The widget \"%s\" of uicommand  \"%s\" does not exist!\n",uicommand->getAttribute("widgetID"),type.c_str());
				printf(szMsg);
				return false;
			}
			ui_node* node = (ui_node*)getUINodeFromObject(object);
			if (!node)
			{
				char szMsg[1024];
				sprintf(szMsg, "QtFrameWork ERROR: The widget \"%s\" of uicommand \"%s\" does not bind a ui_node!\n",uicommand->getAttribute("widgetID"),type.c_str());
				printf(szMsg);
				return false;
			}
			if (strcmp(node->getName(),"StackedWidget")==0)
			{
				QStackedWidget* stackedWidget = (QStackedWidget*)object;
				int curIndex = stackedWidget->currentIndex();
				if (uicommand->hasAttribute("index"))
				{
					int index = STR_TO_INT(uicommand->getAttribute("index"));
					if (index==curIndex)
						return false;
					else
						curIndex = index;

				}else
				{
					int num = stackedWidget->count();
					if (curIndex>=num-1)
					{
						curIndex=0;
					}else
					{
						curIndex++;
					}
				}
				stackedWidget->setCurrentIndex(curIndex);
				stackedWidget->updateGeometry();
				return true;
			}
			else if (strcmp(node->getName(),"StackedLayout")==0)
			{
				QStackedLayout* stackedLayout = (QStackedLayout*)object;
				int curIndex = stackedLayout->currentIndex();
				if (uicommand->hasAttribute("index"))
				{
					int index = STR_TO_INT(uicommand->getAttribute("index"));
					if (index==curIndex)
						return false;
					else
						curIndex = index;

				}else
				{
					int num = stackedLayout->count();
					if (curIndex>=num-1)
					{
						curIndex=0;
					}else
					{
						curIndex++;
					}
				}
				stackedLayout->setCurrentIndex(curIndex);
				return true;
			}
			else
			{
				char szMsg[1024];
				sprintf(szMsg, "QtFrameWork ERROR: The widget \"%s\" of uicommand \"%s\" is not one of the StackedWidget and StackedLayout!\n",uicommand->getAttribute("widgetID"),type.c_str());
				printf(szMsg);
				return false;
			}
			
		}else
		{			
			return false;
		}
	}
	//隐藏id为widgetID的控件，会改变布局
	else if (strcmp(type.c_str(),"HideWidget")==0)
	{
		if (uicommand->hasAttribute("widgetID"))
		{
			QWidget* widget = (QWidget*)R::Instance()->getObjectFromGlobalMap(uicommand->getAttribute("widgetID"));
			if (widget)
			{
				widget->hide();
			}
			else
				return false;
		}
		else
			return false;
	}
	//显示id为widgetID的控件，会改变布局
	else if (strcmp(type.c_str(),"ShowWidget")==0)
	{
		if (uicommand->hasAttribute("widgetID"))
		{
			QWidget* widget = (QWidget*)R::Instance()->getObjectFromGlobalMap(uicommand->getAttribute("widgetID"));
			if (widget)
			{
				widget->show();
                return true;
			}
			else
				return false;
		}
		else
			return false;
	}
    else if (strcmp(type.c_str(), "ToggleWidget") == 0)
    {
        if (uicommand->hasAttribute("widgetID"))
        {
            QWidget* widget = (QWidget*)R::Instance()->getObjectFromGlobalMap(uicommand->getAttribute("widgetID"));
            if (!widget)
            {
                return false;
            }

            if (strcmp(sender->getName(),"Button")==0|| strcmp(sender->getName(), "RadioButton") == 0
                || strcmp(sender->getName(), "CheckBox") == 0 || strcmp(sender->getName(), "ToolButton") == 0)
            {
                QAbstractButton * btn = (QAbstractButton *)sender->getObject();
                if (btn->isCheckable())
                {
                    widget->setVisible(btn->isChecked());
                }
                else
                {
                    widget->setVisible(!widget->isVisible());
                }
            }
            else if (strcmp(sender->getName(), "Action") == 0)
            {
                QAction * btn = (QAction *)sender->getObject();
                if (btn->isCheckable())
                {
                    widget->setVisible(btn->isChecked());
                }
                else
                {
                    widget->setVisible(!widget->isVisible());
                }
            }
            else
            {
                widget->setVisible(!widget->isVisible());
            } 
            if (sender->getParent())
            {
                ui_node* node = (ui_node*)getUINodeFromObject(widget);
                if (node&&strcmp(node->getParent()->getName(), "ToolBox") == 0)
                {
                    QToolBox* tooBox = (QToolBox*)node->getParent()->getObject();
                    if (widget->isVisible())
                    {
                        tooBox->addItem(widget, node->getAttribute("text"));
                    }
                    else
                    {
                        int index = tooBox->indexOf(widget);
                        if (index!=-1)
                        {
                            tooBox->removeItem(tooBox->indexOf(widget));
                        }        
                    }
                }
            }
            return true;
        }
        else
            return false;
    }
	else if (strcmp(type.c_str(),"ResizeWidget")==0)
	{
		if (uicommand->hasAttribute("widgetID"))
		{
			QWidget* widget = (QWidget*)R::Instance()->getObjectFromGlobalMap(uicommand->getAttribute("widgetID"));
			if (widget)
			{
				if (uicommand->hasAttribute("width"))
				{
					widget->setFixedWidth(STR_TO_INT(uicommand->getAttribute("width")));
				}
				if (uicommand->hasAttribute("height"))
				{
					widget->setFixedHeight(STR_TO_INT(uicommand->getAttribute("height")));
				}
				if (uicommand->hasAttribute("size"))
				{
					std::vector<std::string> sizeVec;
					std::string sizeStr = uicommand->getAttribute("size");
					splitString(sizeStr,sizeVec,",");
					if (sizeVec.size()==2)
					{
						int w = STR_TO_INT(sizeVec.at(0).c_str());
						int h = STR_TO_INT(sizeVec.at(1).c_str());
						widget->setFixedSize(w,h);
					}		
				}
			}
			else
				return false;
		}
		else
			return false;
	}
    else if (strcmp(type.c_str(), "SetParameter") == 0)
    {
       if (uicommand->hasAttribute("targetID")&&uicommand->hasAttribute("key")&&uicommand->hasAttribute("value"))
       {
           xml_node* targetNode = R::Instance()->getIdentifiedNode(uicommand->getAttribute("targetID"));
           if (targetNode)
           {
               targetNode->setParameter(uicommand->getAttribute("key"),
                   variant(uicommand->getAttribute("value")));
           }
       }
    }
    else if (strcmp(type.c_str(), "ExistApplication") == 0)
    {
        qApp->exit();
    }
	else
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: The type in UICommand \"%s\" is not one of the default type: PopDialog, PopActivity, CloseDialog \
			DisableWidget, EnableWidget, PopMessageBox, ChangeWidgetStyle, ChangeButtonIcon, SwitchWidget\n",uicommand->getAttribute("id"));
		printf(szMsg);
	}
	
}
//执行xml_node类型命令
//参数：node xml_node对象指针
//返回值：是否执行成功
bool qt_uicommand_executor::executeCommand(xml_node* node)
{
	R* r = R::Instance();
	if (!node->hasAttribute("uicommand"))
	{
		return false;
	}
    ui_node* uinode = dynamic_cast<ui_node*>(node);
	std::string res = node->getAttribute("uicommand");
	if (res.find("@uicommand/")!=std::string::npos)
	{
		int i = res.find_first_of("@uicommand/");
		res = res.substr(i+11);
	}
	else
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: UICommand \"%s\" does not exist! Please check if you have defined it exactly in form \"uicommand=@uicommand/XXX \"\n",res.c_str());
		printf(szMsg);
		return false;
	}
	xml_node* uicommand = (xml_node*)R::Instance()->getCommandResource(res.c_str());
	if (!uicommand)
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: UICommand \"%s\" does not exist! Please check if you have defined it in res/uicommands~\n",res.c_str());
		printf(szMsg);
		return false;
	}
	//处理单个命令
	if (strcmp(uicommand->getName(),"UICommand")==0)
	{
		return execute(uicommand, uinode);
	}
	//处理多个命令
	else if (strcmp(uicommand->getName(),"Commands")==0)
	{
		int commandNum = uicommand->getChildNum();
		for (int i=0;i<commandNum;i++)
		{
			xml_node* command = uicommand->getChild(i);
			if (strcmp(command->getName(),"UICommand")==0)
			{
				execute(command, uinode);
			}
		}
		return true;
	}
	return false;
}