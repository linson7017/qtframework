#pragma once
#include <UIs/CustomActivity.h>
class QTableView;
class ImageModel;
class QTimer;
class SimpleTable:public CustomActivity
{
	Q_OBJECT
public:
	SimpleTable(void);
	~SimpleTable(void);
	protected slots:
		void updateData();
private:
	QTableView* _tableView;
	ImageModel* _model;
	QTimer* _timer;
};

