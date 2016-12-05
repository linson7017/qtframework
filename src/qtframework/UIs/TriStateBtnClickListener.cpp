#include "TriStateBtnClickListener.h"
#include "UIs/sl_Button.h"
#include <QMessageBox>
#include "UIs/AsynchronousAction.h"
#include "UIs/sl_MutexButtonBox.h"
#include "Uicreator/ui_node.h"
#include "Utils/util.h"
#include "Uicreator/qt_uicommand_executor.h"
#include "Uicreator/qt_command_executor.h"
#include <Res/R.h>


TriStateBtnClickListener::TriStateBtnClickListener(sl_MutexButtonBox* btnBox)
	:_curStats(NORMAL),_pBtnBox(btnBox),_pSelectedBtn(NULL)
{

	_btnSelectedStyle = R::Instance()->getStyleResource("BlueButtonStyle");
	_btnNormalStyle = "";
	_btnActivatedStyle = R::Instance()->getStyleResource("GreenButtonStyle");
}



TriStateBtnClickListener::~TriStateBtnClickListener(void)
{
}

void TriStateBtnClickListener::relateChildButton()
{
	/*for (int i=0;i<_btnNum;i++)
	{
	sl_Button* b = *(_pBtnArray+i);
	connect(b,SIGNAL(availabled()),this,SLOT(refreshChildren()));
	}*/
	
}

void TriStateBtnClickListener::refreshChildren()
{
	//sl_Button* currentBtn = (sl_Button*)this->sender();
	//currentBtn->setStyle(_btnSelectedStyle.c_str());
	//for (int i=0;i<_btnNum;i++)
	//{
	//	sl_Button* b = *(_pBtnArray+i);
	//	if (b != currentBtn)
	//	{
	//		b->setStyle(_btnNormalStyle.c_str());
	//		b->setAvailable(true);
	//	}
	//}
}

void TriStateBtnClickListener::showConfirmDialog(ui_node* sender)
{
	/*QString information = "Are you sure to switch status to ";
	information.append(sender->getAttribute("text"));
	information.append("?");
	QMessageBox msgBox;
	msgBox.setWindowTitle("Ensure MessageBox.");
	msgBox.setInformativeText(information);
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Discard);
	msgBox.setDefaultButton(QMessageBox::Discard);
	int ret =  msgBox.exec();
	if (ret == QMessageBox::Yes)
	_curStats = CONFIRMED;
	else
	_curStats = DISCARDED;*/
	//_curStats = CONFIRMED;
}

void TriStateBtnClickListener::confirmedAction(ui_node* sender)
{
	//用异步的方法多次调用导致程序卡死
	/*void* data = new int(3);
	_asynAction->setParameter(data);
	QObject::connect(_asynAction,SIGNAL(finished()),this,SLOT(returned()));
	if (_asynAction->isRunning())
	{
	_asynAction->terminate();
	}
	_asynAction->start();*/
	
}

void TriStateBtnClickListener::discardedAction(ui_node* sender)
{
}

void TriStateBtnClickListener::onClick(ui_node* sender)
{
	showConfirmDialog(sender);
	sl_Button* pCurBtn = (sl_Button*)sender->getObject();
	if (pCurBtn->availlabe())
	{
		if (pCurBtn->needToConfirm())
		{
			if (!pCurBtn->confirmed())
			{
//				return;
			}
		}
		pCurBtn->setStyle(_btnSelectedStyle.c_str());
		_pSelectedBtn = pCurBtn;
		pCurBtn->setAvailable(false);
		int btnNUm = _pBtnBox->buttonNum();
		for (int i=0;i<btnNUm;i++)
		{
			sl_Button* b = _pBtnBox->getChildButton(i);
			if (b != pCurBtn)
			{
				b->setStyle(_btnNormalStyle.c_str());
				b->setAvailable(true);
			}
		}
		confirmedAction(sender);
	}
	else
	{
		discardedAction(sender);
	}
	//shisx
	ui_node* node = (ui_node*)getUINodeFromObject(pCurBtn);  //获得Object中存的ui_node指针
	if (!node)
	{
		return;
	}

	//是否需要弹出确认对话框
	if (pCurBtn->needToConfirm())
	{
		pCurBtn->setConfirmed(false);
		std::string information="";
		if (node->hasAttribute("confirmDialogText"))
		{
			information.append(node->getAttribute("confirmDialogText"));
			str_replace_all(information,"\\n","\n");
		}
		else
		{
			information.append( R::Instance()->getStringResource("sure_to_switch"));
			information.append(node->getAttribute("text"));
			information.append( R::Instance()->getStringResource("status"));
			information.append("?");
		}
		QMessageBox msgBox;
		msgBox.setWindowTitle(R::Instance()->getStringResource("confirm_dialog"));
		msgBox.setInformativeText(information.c_str());
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Cancel);
		QWidget* pa = (QWidget*)R::Instance()->getObjectFromGlobalMap("main");
		if(pa)
		{
			msgBox.setParent((QWidget*)R::Instance()->getObjectFromGlobalMap("main"));
		}
		msgBox.setWindowFlags(Qt::Dialog);

		QPoint pos = pCurBtn->pos();
		pos = pCurBtn->mapToGlobal(pos);
		int x = pos.x();
		int y = pos.y();//shisx 按钮位置弹出比较合理
		if(x > 1400) x = 1400;
		if(y > 1800) y = 1800;//2 screen 1680 * 2100
		msgBox.move(x,y);
		int ret =  msgBox.exec();
		if (ret == QMessageBox::Yes)
			pCurBtn->setConfirmed(true);
		else
			pCurBtn->setConfirmed(false);
	}
	if (node->hasAttribute("uicommand"))
	{
		if (pCurBtn->needToConfirm())//判断按钮是否需要对话框确认
		{
			if (pCurBtn->confirmed())
			{
				qt_uicommand_executor::executeCommand(node);
			}
		}else//不需要确认直接执行命令
		{
			qt_uicommand_executor::executeCommand(node);
		}	
	}

	//ssx		
	if (pCurBtn->needToConfirm())//判断按钮是否需要对话框确认
	{
		if (pCurBtn->confirmed())
		{
			qt_command_executor::executeCommand(node);
		}
	}else//不需要确认直接执行命令
	{
		qt_command_executor::executeCommand(node);
	}	
}

void TriStateBtnClickListener::returnedAction(ui_node* sender)
{
	/*_curStats = RETURNED;
	if (1)
	{
	_pCurBtn->setStyle(R::Instance()->getStyleResource("GreenButtonStyle"));
	}*/
}
