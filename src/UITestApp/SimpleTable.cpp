#include "SimpleTable.h"
#include "pixeldelegate.h"
#include "imagemodel.h"
#include <QtGui>
#include <QtWidgets>
static int tableCol = 50;
static int tableRow = 50;
SimpleTable::SimpleTable(void)
{
	_model = new ImageModel(this);
	_tableView = new QTableView;
	_tableView->setShowGrid(false);
	_tableView->horizontalHeader()->hide();
	_tableView->verticalHeader()->hide();
	_tableView->horizontalHeader()->setMinimumSectionSize(1);
	_tableView->verticalHeader()->setMinimumSectionSize(1);
	_tableView->setModel(_model);

	PixelDelegate *delegate = new PixelDelegate(this);
	_tableView->setItemDelegate(delegate);

	setContentView("simple_table.xml");
	QHBoxLayout* layout = (QHBoxLayout*)getViewByID("layout");
	layout->addWidget(_tableView);

	QImage image;
	image.load("G:/images/internet-web-browser.png");
	//_model->setImage(image);
	QVector<QVector<QString>> data;
	for (int i=0;i<tableRow;i++)
	{
		QVector<QString> rowData;
		for (int j=0;j<tableCol;j++)
		{
			QString text(QString::number(i)+","+QString::number(j));
			rowData.push_back(text);
		}
		data.push_back(rowData);
	}
	_model->setTableData(data);

	_tableView->resizeColumnsToContents();
	_tableView->resizeRowsToContents();

	_timer = new QTimer;
	connect(_timer,SIGNAL(timeout()),this,SLOT(updateData()));
	_timer->start(10);

}


SimpleTable::~SimpleTable(void)
{
}

int simplecount = 0;
void SimpleTable::updateData()
{

	if (simplecount>100)
	{
		simplecount=0;
	}
	else
	{
		simplecount++;
	}
	setUpdatesEnabled(false);
	QVector<QVector<QString>> data;
	for (int i=0;i<tableRow;i++)
	{
		QVector<QString> rowData;
		for (int j=0;j<tableCol;j++)
		{
			QString text(QString::number(i+simplecount)/*+","+QString::number(j+simplecount)*/);
			rowData.push_back(text);
		}
		data.push_back(rowData);
	}
	_model->setTableData(data);
	setUpdatesEnabled(true);
}