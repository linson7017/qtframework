#include "TableActivity.h"
#include <QTableWidget>
#include <QTimer>

TableActivity::TableActivity(void)
{
	setContentView("table.xml");
	_table = (QTableWidget*)getViewByID("table");
	for (int i=0;i<_table->rowCount();i++)
	{
		for (int j=0;j<_table->columnCount();j++)
		{
			QTableWidgetItem* item = new QTableWidgetItem("--");
			_table->setItem(i,j,item);
		}
	}
	//_table->setUpdatesEnabled(false)
	_timer = new QTimer;
	connect(_timer,SIGNAL(timeout()),this,SLOT(updateData()));
	_timer->start(100);
}


TableActivity::~TableActivity(void)
{
}

int count = 0;

void TableActivity::updateData()
{
	if (count>100)
	{
		count=0;
	}
	else
	{
		count++;
	}
	setUpdatesEnabled(false);
	//_table->setVisible(false);
	for (int i=0;i<_table->rowCount();i++)
	{
		for (int j=0;j<_table->columnCount();j++)
		{
			QTableWidgetItem* tableItem = _table->item(i,j);
			if (tableItem)
			{
				QString str;
				QString rowStr,colStr,countStr;
				str.append(rowStr.setNum(i)+colStr.setNum(j)+countStr.setNum(count));
				tableItem->setText(str);
			}	
		}
	}
	if (1)
	{
		setUpdatesEnabled(true);
	}
	
	//_table->setVisible(true);
}