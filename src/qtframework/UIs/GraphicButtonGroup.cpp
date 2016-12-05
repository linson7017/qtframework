#include "GraphicButtonGroup.h"


GraphicButtonGroup::GraphicButtonGroup(void):_bPackup(true)
{
	_rootState = new QState();
	_unfoldState = new QState(_rootState);
	_packupState = new QState(_rootState);
}


GraphicButtonGroup::~GraphicButtonGroup(void)
{
	if (_rootState!=NULL)
	{
		delete _rootState;
		_rootState = NULL;
	}
	if (_unfoldState!=NULL)
	{
		delete _unfoldState;
		_unfoldState = NULL;
	}
	if (_packupState!=NULL)
	{
		delete _packupState;
		_packupState = NULL;
	}
}

void GraphicButtonGroup::setupAnimation()
{
	//ÔõÃ´ÀÏÊÇ±À£¿£¿£¡£¡
	QStateMachine* machine = new QStateMachine;
	machine->addState(_rootState);
	machine->setInitialState(_rootState);
	_rootState->setInitialState(_packupState);
	for (int i = 0; i < _btnPairs.size(); i++) 
	{
		GraphicButton::GraphicButtonPair* pair = _btnPairs.at(i);

		QRectF rectTool = pair->btnTool->boundingRect();
		double angleTool = pair->btnTool->angle();
		QRectF rectNext = pair->btnNext->boundingRect();
		double angleNext = pair->btnNext->angle();

		_unfoldState->assignProperty(pair->btnNext, "geometry", rectNext.translated(rectNext.width()/2,rectNext.height()/2));
		_unfoldState->assignProperty(pair->btnTool, "geometry", rectTool.translated(rectTool.width()/2,rectTool.height()/2));
		_unfoldState->assignProperty(pair->btnNext, "visible", true);
		_unfoldState->assignProperty(pair->btnTool, "visible", true);
		
		_packupState->assignProperty(pair->btnNext, "geometry", rectNext.translated(rectNext.width()/2-20*cos(angleNext*3.14/180),rectNext.height()/2-20*sin(angleNext*3.14/180)));
		_packupState->assignProperty(pair->btnTool, "geometry", rectTool.translated(rectTool.width()/2-20*cos(angleTool*3.14/180),rectTool.height()/2-20*sin(angleTool*3.14/180)));
		_packupState->assignProperty(pair->btnNext, "visible", false);
		_packupState->assignProperty(pair->btnTool, "visible", false);
	}
	

	QParallelAnimationGroup *group = new QParallelAnimationGroup;
	for (int i = 0; i < _btnPairs.size(); ++i) {
		QPropertyAnimation *animGTool = new QPropertyAnimation(_btnPairs.at(i)->btnTool, "geometry");
		animGTool->setDuration(750 + i * 25);
		animGTool->setEasingCurve(QEasingCurve::OutBack);
		group->addAnimation(animGTool);

		QPropertyAnimation *animGNext = new QPropertyAnimation(_btnPairs.at(i)->btnNext, "geometry");
		animGNext->setDuration(750 + i * 20);
		animGNext->setEasingCurve(QEasingCurve::OutBack);
		group->addAnimation(animGNext);

	}
	QAbstractTransition *trans = _rootState->addTransition(this, SIGNAL(emit_unfold()), _unfoldState);
	trans->addAnimation(group);
	trans = _rootState->addTransition(this, SIGNAL(emit_packup()), _packupState);
	trans->addAnimation(group);

	machine->start();
}

void GraphicButtonGroup::fold()
{
	emit_packup();
	hide();
}


void GraphicButtonGroup::unfold()
{
	emit_unfold();
	show();
}

void GraphicButtonGroup::packup()
{
	if (_bPackup)
	{
		emit_unfold();
		for (int i=0;i<_btnPairs.size();i++)
		{
			_btnPairs.at(i)->btnNext->show();
			_btnPairs.at(i)->btnTool->show();
		}
		_bPackup = false;
	}
	else
	{
		emit_packup();
		for (int i=0;i<_btnPairs.size();i++)
		{
			_btnPairs.at(i)->btnNext->hide();
			_btnPairs.at(i)->btnTool->hide();
		}
		_bPackup = true;
	}
	
}