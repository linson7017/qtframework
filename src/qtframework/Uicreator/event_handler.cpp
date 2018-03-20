#include "event_handler.h"
#include <QtCore/QEvent>
#include <QtGui>
#include <Uicreator/ui_node.h>
#include <Res/R.h>
#include <Utils/util.h>
#include <Uicreator/qt_command_executor.h>
#include <Uicreator/qt_uicommand_executor.h>
#include <UIs/sl_Button.h>
#include <UIs/GraphicButton.h>
#include <Utils/variant.h>
#include <Utils/qt_standard.h>
#include <Common/app_env.h>
#include <qf_messagedef.h>
//#include "gise_config.h"
//#include "main/igis_main.h"
#include "qf_messagedef.h"

//���캯��
//������parent ��ָ��
//����ֵ����
event_handler::event_handler(QObject* parent):QObject(parent),_shortcutString("")
{
}
//��������
//��������
//����ֵ����
event_handler::~event_handler(void)
{
}
//������ִ��ui_node��������
//������node ui_node����ָ��
//����ֵ����
void event_handler::parseAndExecuteCommandForUINode(ui_node* node)
{
	qt_uicommand_executor::executeCommand(node);
	qt_command_executor::executeCommand(node);
}
//������ִ��xml_node��������
//������node xml_node����ָ��
//����ֵ����
void event_handler::parseAndExecuteCommandForXmlNode(xml_node* node)
{
	qt_uicommand_executor::executeCommand(node);
	qt_command_executor::executeCommand(node);
}

//�����ݲ���Ϊ���͵���Ϣ
//��Ϣ����
//������int ��������
//����ֵ����
void event_handler::handle(int inParam)
{
	QObject* sender = this->sender();
	ui_node* node = (ui_node*)getUINodeFromObject(sender); 
	if (strcmp(node->getName(),"ComboBox")==0)  //combobox�������ı�ִ������
	{
		parseAndExecuteCommandForUINode(node);
		//shisx �����������б�item�е����� item���ܱ���ɾ�� 
		//���������б�item�е�����
        ui_node* selectedItemNode = node->getChild(inParam);
        if (!selectedItemNode)
            return;
        parseAndExecuteCommandForUINode(selectedItemNode);
	}
	else if (strcmp(node->getName(),"ProgressBar")==0)
	{
		QProgressBar* bar = (QProgressBar*)sender;
		if (inParam >= bar->maximum())  //�������������ִ������
		{
			parseAndExecuteCommandForUINode(node);
		}	
	}
    else if (strcmp(node->getName(),"HSlider")==0)
    {
        parseAndExecuteCommandForUINode(node);
     }
}
//��Ϣ����
//������int ��������, int ��������
//����ֵ����
void event_handler::handle(int iParam1,int iParam2)
{
	QObject* sender = this->sender();
	ui_node* node = (ui_node*)getUINodeFromObject(sender); 
	int ssi = senderSignalIndex();
	int ssic = sender->metaObject()->indexOfSignal(SIGNAL(sender->cellClicked(int,int)));
	int ssidc = sender->metaObject()->indexOfSignal(SIGNAL(sender->cellDoubleClicked(int,int)));
	if (strcmp(node->getName(),"Table")==0)  //TableWidget��Ԫ��˫������
	{
		//gise::IGIS_Main* pMain = (gise::IGIS_Main*)app_env::getMainPtr();
		////ssx
		//if (node->hasAttribute("msgcommand"))
		//{
		//	string command = node->getAttribute("msgcommand");
		//	int icommand = STR_TO_INT(command.c_str());
		//	pMain->SendMessage(icommand, 0, (void*)node->getAttribute("id"));		
		//}		
	}
}

//����ؼ���Ϣ
//��Ϣ����
//��������
//����ֵ����
void event_handler::handle()
{
	QObject* sender = this->sender();
	if (!sender)
	{
		return;
	}
	ui_node* node = (ui_node*)getUINodeFromObject(sender);  //���Object�д��ui_nodeָ��
	if (!node)
	{
		return;
	}
	if (strcmp(node->getName(),"Button")==0)
	{
		
		sl_Button* btn = (sl_Button*)sender;
		if(strcmp(node->getParent()->getName(), "MutexButtonBox") == 0)
		{
			//�����ⰴť�����¼���Ӧ�Ƶ�TriStateBtnClickListener::onClick��ʵ�� 
			return;
		}
        parseAndExecuteCommandForUINode(node);
		
	}
	else if (strcmp(node->getName(),"Action")==0)
	{
		QAction* action = (QAction*)sender;
		bool bExecute =false;
		if (action->isCheckable()&&action->isChecked())
		{
				bExecute = true;
		}
		else
		{
			bExecute = true;
		}
		if (bExecute)
		{
			parseAndExecuteCommandForUINode(node);
		}	
	}
	else if (strcmp(node->getName(),"LineEdit")==0)
	{
		QLineEdit* lineEdit = (QLineEdit*)sender;
		QString text = lineEdit->text();
		parseAndExecuteCommandForUINode(node);
	}
	else if (strcmp(node->getName(),"RadioButton")==0)
	{
		QRadioButton* radioButton = (QRadioButton*)sender;
		if (radioButton->isChecked()&&radioButton->isCheckable())
		{
			parseAndExecuteCommandForUINode(node);
		}
	}
	else if (strcmp(node->getName(),"GroupBox")==0)
	{
		QGroupBox* groupBox = (QGroupBox*)sender;
		if (groupBox->isChecked()&&groupBox->isCheckable())
		{
			parseAndExecuteCommandForUINode(node);
		}
	}
	else if (strcmp(node->getName(),"CheckBox")==0)
	{
		QCheckBox* checkBox = (QCheckBox*)sender;
		//shisx	û��checkҲҪ��Ӧ�¼�
		if (checkBox->isCheckable())
		//if (checkBox->isChecked()&&checkBox->isCheckable())
		{
			parseAndExecuteCommandForUINode(node);
		}
	}
	//��ʱ����
	else if (strcmp(node->getName(),"TreeWidget")==0)
	{
		QTreeWidget* treeWidget = (QTreeWidget*)sender;
		parseAndExecuteCommandForUINode(node);
	}
	else if (strcmp(node->getName(),"Tool")==0)
	{
		//GraphicButton* gBtn = (GraphicButton*)sender;
		parseAndExecuteCommandForUINode(node);
	}
}

//����ϵͳ�¼�
//�¼�������
//������obj ��������, event �¼�ָ��
//����ֵ���Ƿ������
bool event_handler::eventFilter(QObject *obj, QEvent *event)
{
	ui_node* node = (ui_node*)getUINodeFromObject(obj);
	if (event->type() == QEvent::MouseButtonRelease)
	{
		//����ֲ��¼����ж��Ƿ����
		if (!node)
		{
			return false;
		}
		QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
		if (mouseEvent->button()==Qt::RightButton)
		{
			if (node->hasAttribute("menu"))
			{
				std::string menuID = node->getAttribute("menu");
				std::string str = "@menu/";
				if (menuID.find(str)!=std::string::npos)
				{
					menuID = menuID.substr(menuID.find_first_of(str)+6);
					R* r = R::Instance();
					QMenu* menu = (QMenu*)R::Instance()->getObjectFromGlobalMap(menuID.c_str());
					if (menu)
					{
						menu->exec(mouseEvent->globalPos());
					}
				}
			}
		}
		else if (mouseEvent->button()==Qt::LeftButton)
		{
			if (node->getType()==ui_node::WIDGET)
			{
				QWidget* widget = (QWidget*)obj;
				widget->setFocus();
			}	
		}
		return QObject::eventFilter(obj, event);
	}
	else if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
		std::string keyText = qt_standard::getKeySymbol((Qt::Key)keyEvent->key());		
		_shortcutString.clear();
		if (keyEvent->modifiers())
		{
			Qt::KeyboardModifiers keyModifiers = keyEvent->modifiers();
			std::string modifierText = qt_standard::getModifiersSymbol(keyModifiers);	
			_shortcutString.append(modifierText);
		}
		if (strcmp(keyText.c_str(),"Key_Control")!=0&&strcmp(keyText.c_str(),"Key_Shift")!=0
			&&strcmp(keyText.c_str(),"Key_Alt")!=0)
		{
			_shortcutString.append(keyText);
		}
		xml_node* shortcutKey = NULL;
		if (_shortcutString.compare(_shortcutString.size()-1,1,"+")!=0) //����ַ�������
		{
			shortcutKey = R::Instance()->getShortcutResource(_shortcutString.c_str());
		}
		if (shortcutKey)
		{
			parseAndExecuteCommandForXmlNode(shortcutKey);
		}
		else
		{
			return QObject::eventFilter(obj, event);
		}
	}
	else if (event->type() == QEvent::KeyRelease)
	{
		_shortcutString.clear();
		return QObject::eventFilter(obj, event);
	}
	else if (event->type() == QEvent::ToolTip)
	{
		if (!node)
		{
			return false;
		}
		if (app_env::showTooltipOn())
		{
			if (node->hasAttribute("tip"))
			{
				QHelpEvent* helpEvent = static_cast<QHelpEvent*>(event);
				QWidget* widget = static_cast<QWidget*>(obj);
				std::string text=node->getAttribute("tip"); 
				QToolTip::showText(helpEvent->globalPos(),STR_TO_RES_TEXT(str_replace_all(text,"\\n","\n").c_str()),
					widget,widget->rect());
			}
		}
		return QObject::eventFilter(obj, event);
	}
	else 
		return QObject::eventFilter(obj, event);
}

//��Ϣ����
//������QTreeWidgetItem* ��������, int ��������
//����ֵ����
void event_handler::handle(QTreeWidgetItem* treeWidgetItem,int col)
{
	QObject* sender = this->sender();
	ui_node* node = (ui_node*)getUINodeFromObject(sender); 
	if (strcmp(node->getName(),"TreeWidget")==0)
	{
		//ִ��TreeWidget�ڵ�����
		parseAndExecuteCommandForUINode(node);
		//ִ���ӽڵ�����
		if (treeWidgetItem->checkState(col)==Qt::Checked/*||treeWidgetItem->checkState(col)==Qt::PartiallyChecked*/)
		{
			QVariant* qv = &treeWidgetItem->data(0,Qt::UserRole);
			if (qv->isValid())
			{
				ui_node* itemnode = (ui_node*)getUINodeFromVariant(qv);
				parseAndExecuteCommandForUINode(itemnode);
			}
		}	
	}    

}
