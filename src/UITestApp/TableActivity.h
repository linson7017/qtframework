#pragma once
#include <UIs/CustomActivity.h>
class QTimer;
class QTableWidget;
class TableActivity:public CustomActivity
{
	Q_OBJECT
public:
	TableActivity(void);
	~TableActivity(void);
    void closeEvent(QCloseEvent *ev){QWidget::closeEvent(ev);}
	protected slots:
		void updateData();
private:
	QTableWidget* _table;
	QTimer* _timer;
};

