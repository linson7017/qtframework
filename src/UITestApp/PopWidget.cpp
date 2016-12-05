#include "PopWidget.h"
#include <QPushButton>
#include <QMessageBox>
PopWidget::PopWidget(void)
{
	setContentView("graph.xml");
	QPushButton* btn = (QPushButton*)getViewByID("Button");
	connect(btn,SIGNAL(clicked()),this,SLOT(showMessageBox()));
}


PopWidget::~PopWidget(void)
{
}

void PopWidget::showMessageBox()
{
	QMessageBox mb;
	mb.setInformativeText("Signal Rescived In PopWidget!");
	mb.exec();
}