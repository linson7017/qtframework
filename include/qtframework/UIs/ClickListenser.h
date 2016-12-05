#pragma once
#include <QtCore/QObject>
#include "Listener.h"
#include "Common/qtframework_com.h"
class ui_node;

class QTFRAMEWORK_EXPORT ClickListenser : public Listener
{
	Q_OBJECT
public:
	ClickListenser(void);
	virtual ~ClickListenser(void);
	virtual void onClick(ui_node* sender)=0;
	public slots:
		virtual void trigger();
};

