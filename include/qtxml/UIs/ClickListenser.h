#pragma once
#include <QtCore/QObject>
#include "Listener.h"
#include "Common/qtxml_com.h"
class ui_node;

class QTXML_EXPORT ClickListenser : public Listener
{
	Q_OBJECT
public:
	ClickListenser(void);
	virtual ~ClickListenser(void);
	virtual void onClick(ui_node* sender)=0;
	public slots:
		virtual void trigger();
};

