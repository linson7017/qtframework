#pragma once
#include "UIs/ClickListenser.h"
#include <string>
class sl_Button;
class AsynchronousAction;
class sl_MutexButtonBox;
class ui_node;

class TriStateBtnClickListener: public ClickListenser
{
	Q_OBJECT
public:
	enum StatusType
	{
		NORMAL,
		CONFIRMED,
		DISCARDED,
		RETURNED
	};
	TriStateBtnClickListener(sl_MutexButtonBox* btnBox);
	~TriStateBtnClickListener(void);
	void onClick(ui_node* sender=NULL);
	virtual void showConfirmDialog(ui_node* sender=NULL);
	virtual void confirmedAction(ui_node* sender=NULL);
	virtual void discardedAction(ui_node* sender=NULL);
	virtual void returnedAction(ui_node* sender=NULL);
	virtual void setButtonActivedStyle(const char* style){_btnActivatedStyle = style;}
	virtual void setButtonNormalStyle(const char* style){_btnNormalStyle=style;}
	virtual void setButtonSelectedStyle(const char* style){_btnSelectedStyle=style;}
	void setAsynchronousAction(AsynchronousAction* asynAction){_asynAction = asynAction;}
	sl_Button* selectedBtn(){return _pSelectedBtn;}
	public slots:
		void returned(){returnedAction(_sender);}
		void refreshChildren();
private:
	void relateChildButton();

	sl_MutexButtonBox* _pBtnBox;
	int _btnNum;
	//bool _confirmed;
	StatusType _curStats;
	sl_Button* _pSelectedBtn;
	AsynchronousAction* _asynAction;
	std::string _btnActivatedStyle;
	std::string _btnNormalStyle;
	std::string _btnSelectedStyle;
};

