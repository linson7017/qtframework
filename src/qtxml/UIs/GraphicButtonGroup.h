#pragma once
#include <QGraphicsWidget>
#include <QObject>
#include "GraphicButton.h"
class GraphicButtonGroup : public QGraphicsWidget
{
	Q_OBJECT
public:
	GraphicButtonGroup(void);
	~GraphicButtonGroup(void);
	void setCenterButton(GraphicButton* btnCenter){_btnCenter = btnCenter;}
	GraphicButton* centerButton(){return _btnCenter;}
	void addButtonPair(GraphicButton::GraphicButtonPair* btnPair){_btnPairs.push_back(btnPair);}

	void setupAnimation();
	public slots:
		void fold();
		void unfold();
		void packup();
signals:
		void emit_fold();
		void emit_unfold();
		void emit_packup();
private:
	GraphicButton* _btnCenter;
	QList<GraphicButton::GraphicButtonPair*> _btnPairs;
	bool _bPackup;
	QState* _rootState;
	QState* _unfoldState;
	QState* _packupState;
};

