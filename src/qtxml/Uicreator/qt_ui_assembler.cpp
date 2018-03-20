#include "qt_ui_assembler.h"
#include <QtGui>
#include <QtWidgets>
#include <QtCore/QObject>
#include <QtOpenGL/QGLWidget>
#include <QtQuick>
#include "Uicreator/xml_ui_paser.h"
#include "Uicreator/event_handler.h"
#include "Uicreator/ui_node.h"
#include "Utils/variant.h"
#include "Res/R.h"
#include "UIs/sl_Button.h"
#include "UIs/sl_MutexButtonBox.h"
#include "UIs/sl_ImageWidget.h"
#include "UIs/sl_AnimationWidget.h"
#include "UIs/TitleBar.h"
#include "Utils/qt_standard.h"
#include "Utils/util.h"
#include "Utils/Log.h"
#include "UIs/sl_VectorContainer.h"
#include "UIs/sl_MapContainer.h"
#include "UIs/sl_ToolPanel.h"

#include "Common/app_env.h"

#include "UIs/QF_Plugin.h"
#include "Uicreator/qt_ui_creater.h"
#include "Utils/QObjectFactory.h"
#include "Utils/PluginFactory.h"
#ifdef USE_QCUSTOM_PLOT
#include <QCustomPlot.h>
#endif
#include <string.h>


#include <qfmain/internal/iqf_main_ext.h>
#include <qfmain/iqf_subject.h>

Q_DECLARE_METATYPE(ui_node*) //��qtʶ��ui_node����
//���캯��
//������root �ڵ����ĸ��ڵ�
//����ֵ����
qt_ui_assembler::qt_ui_assembler()
{
	//���ｫevent_handler��ָ��ȫ��Ψһһ��
    _root = new ui_node;
	_event_handler = &gs_event_handler;
}
//��������
//��������
//����ֵ����
qt_ui_assembler::~qt_ui_assembler(void)
{
	_root->release();
}

//��ø��ڵ������objectָ��
//��������
//����ֵ�����ڵ��������
void* qt_ui_assembler::getRootObject()
{
	return _root->getObject();
}
//����¼�������
//��������
//����ֵ���¼�������ָ��
void* qt_ui_assembler::getEventHandler()
{
	return _event_handler;
}
//��ø��ڵ�����
//��������
//����ֵ���ڵ�����
ui_node::NodeType qt_ui_assembler::getRootType()
{
	ui_node::NodeType type = _root->getType();
	return _root->getType();
}
//��װ
//��������
//����ֵ����
void qt_ui_assembler::assemble()
{
	parseUITree(_root);
    assembleUITree(_root);
    setupUITree(_root);
}
//�����ڵ���
//������node ���ڵ�ָ��
//����ֵ����
void qt_ui_assembler::parseUITree(ui_node* node)
{
	createUI(node);
	if (node->getChildNum() != 0)
	{
		for(int i=0; i < node->getChildNum(); i++)
		{
			ui_node* child_node = (ui_node*)node->getChild(i);
			//child_node->setParent(node); //���ýڵ�ĸ��ڵ�
			if (child_node)
			{
				createUI(child_node);
                parseUITree(child_node);
			}		
		}
	}
	else
	{
		return;
	}
}

void qt_ui_assembler::assembleUITree(ui_node* node)
{
    if (node->getChildNum() != 0)
    {
        for (int i = 0; i < node->getChildNum(); i++)
        {
            ui_node* child_node = (ui_node*)node->getChild(i);
            if (child_node)
            {
                //�жϸ��ڵ���ӽڵ��Ƿ���Ч
                if ((child_node->getObject()) && (node->getObject()))
                {
                    assembleNodes(node, child_node);
                    assembleUITree(child_node);
                }
            }
        }
    }
    else
    {
        return;
    }
}

void qt_ui_assembler::setupUITree(ui_node* node)
{
    QF::QF_Plugin* plugin = (QF::QF_Plugin*)node->getObject("plugin");
    if (plugin)
    {
        plugin->SetupResource();
    }
    if (node->getChildNum() != 0)
    {
        for (int i = 0; i < node->getChildNum(); i++)
        {
            ui_node* child_node = (ui_node*)node->getChild(i);
            if (child_node)
            {
                if (node->getObject("subject"))
                {
                    child_node->setObject(node->getObject("subject"),"subject");
                }
                setupUITree(child_node);
            }
        }
    }
    else
    {
        return;
    }
}


//װ���ӽڵ�͸��ڵ�
//������father ���ڵ�ָ��, child �ӽڵ�
//����ֵ����
void qt_ui_assembler::assembleNodes(ui_node* father,ui_node* child)
{
	
	//װ���ӽڵ�͸��ڵ�
	switch (father->getType())
	{
	case ui_node::LAYOUT:
		{
			assembleLayoutAndWidgetOrLayout(father,child);
		}
		break;
	case ui_node::WIDGET:
		{
			if(child->getType()==ui_node::LAYOUT)
			{
				assembleWidgetAndLayout(father,child);
			}
			else if (child->getType()==ui_node::WIDGET)
			{
				assembleWidgetAndWidget(father,child);
			}
			else if (child->getType()==ui_node::ITEM)
			{
				assembleWidgetAndItem(father,child);
			}
			else if (child->getType()==ui_node::ITEMS)
			{
				assembleWidgetAndItems(father,child);
			}
		}
		break;
	case ui_node::CONTAINER:
		{
			assembleContainerAndWidget(father,child);
		}
		break;
	case ui_node::ITEM:
		{
			if (strcmp(father->getName(),"Action")==0)
			{
				QAction* action = (QAction*)father->getObject();
				if (strcmp(child->getName(),"Menu")==0)
				{
					QMenu* menu = (QMenu*)child->getObject();
					action->setMenu(menu);
				}
			}
		}
		break;
	default:
		break;
	}
}
//װ��Layout��Widget����Layout��Layout
//������father ���ڵ�ָ��, child �ӽڵ�
//����ֵ����
void qt_ui_assembler::assembleLayoutAndWidgetOrLayout(ui_node* father,ui_node* child)
{
	if(strcmp(father->getName(),"VLayout")==0||strcmp(father->getName(),"HLayout")==0)
	{
		QBoxLayout* layout = (QBoxLayout*)father->getObject();
		if (child->getType()==ui_node::LAYOUT)
		{
			QLayout* child_layout = (QLayout*)child->getObject();
			if (child->hasAttribute("stretch"))
			{
				layout->addLayout(child_layout,STR_TO_INT(child->getAttribute("stretch")));
			}else
			{
				layout->addLayout(child_layout);
			}
			if (child->hasAttribute("align"))
			{
				layout->setAlignment(child_layout,qt_standard::getAlignment(child->getAttribute("align")));
			}

		}
		else if (child->getType()==ui_node::WIDGET)
		{
			QWidget* child_widget =(QWidget*)child->getObject();
			if (child->hasAttribute("stretch"))
			{
				layout->addWidget(child_widget,STR_TO_INT(child->getAttribute("stretch")));
			}else
			{
				layout->addWidget(child_widget);
			}
			if (child->hasAttribute("align"))
			{
				layout->setAlignment(child_widget,qt_standard::getAlignment(child->getAttribute("align")));
			}
		}
		else if (child->getType()==ui_node::ITEM)
		{
			if (strcmp(child->getName(),"Spacing")==0&&child->hasAttribute("size"))
			{
				layout->addSpacing(STR_TO_INT(child->getAttribute("size")));
			}
			if (strcmp(child->getName(),"Stretch")==0&&child->hasAttribute("size"))
			{
				layout->addStretch(STR_TO_INT(child->getAttribute("size")));
			}
		}
	}
	else if (strcmp(father->getName(),"GridLayout")==0)
	{
		QGridLayout* layout = (QGridLayout*)father->getObject();
		if (child->hasAttribute("row")&&child->hasAttribute("col"))
		{
			int r = STR_TO_INT(child->getAttribute("row"));
			int c = STR_TO_INT(child->getAttribute("col"));
			int rs = child->hasAttribute("rowSpan")?STR_TO_INT(child->getAttribute("rowSpan")):1;
			int cs = child->hasAttribute("colSpan")?STR_TO_INT(child->getAttribute("colSpan")):1;
			Qt::Alignment align = child->hasAttribute("align")?qt_standard::getAlignment(child->getAttribute("align")):(Qt::Alignment)0;
			bool colEqual = father->hasAttribute("colEqual")?STR_TO_BOOL(father->getAttribute("colEqual")):false; //�ж��ǲ���ÿһ�п����ͬ
			if (child->getType()==ui_node::WIDGET)
			{
				QWidget* child_widget = (QWidget*)child->getObject();
				layout->addWidget(child_widget,r,c,rs,cs,align);
			}
			else if (child->getType()==ui_node::LAYOUT)
			{
				QLayout* child_layout = (QLayout*)child->getObject();
				layout->addLayout(child_layout,r,c,rs,cs,align);
			}
			if (colEqual)
			{
				layout->setColumnStretch(c,1);
			}	
		}
	}
	else if (strcmp(father->getName(),"StackedLayout")==0)
	{
		QStackedLayout* layout = (QStackedLayout*)father->getObject();
		if (child->getType()==ui_node::WIDGET)
		{
			QWidget* child_widget = (QWidget*)child->getObject();
			if (child->hasAttribute("index"))
			{
				int i = STR_TO_INT(child->getAttribute("index"));
				layout->insertWidget(i,child_widget);
				if (father->hasAttribute("initIndex"))
				{
					int j = STR_TO_INT(father->getAttribute("initIndex"));
					if (i==j)
					{
						layout->setCurrentIndex(j);
					}	
				}

			}else
			{
				layout->addWidget(child_widget);
			}
		}	
	}
	else if (strcmp(father->getName(),"TableLayout")==0)
	{
		QGridLayout* layout = (QGridLayout*)father->getObject();
		if (child->hasAttribute("row"))
		{
			int row = STR_TO_INT(child->getAttribute("row"));
			int num = child->getChildNum();
			for (int i=0;i<num;i++)
			{
				ui_node* temp = child->getChild(i);
				createUI(temp);
				if (temp->getType()==ui_node::WIDGET)
				{
					Qt::Alignment align = temp->hasAttribute("align")?qt_standard::getAlignment(temp->getAttribute("align")):(Qt::Alignment)0;
					QWidget* temp_widget = (QWidget*)temp->getObject();
					layout->addWidget(temp_widget,row,i,align);
				}
				else if (temp->getType()==ui_node::LAYOUT)
				{
					Qt::Alignment align = temp->hasAttribute("align")?qt_standard::getAlignment(temp->getAttribute("align")):(Qt::Alignment)0;
					QLayout* temp_layout = (QLayout*)temp->getObject();
					layout->addLayout(temp_layout,row,i,align)		;
				}
			}
		}
	}	
}
//װ��Widget��Layout
//������father ���ڵ�ָ��, child �ӽڵ�
//����ֵ����
void qt_ui_assembler::assembleWidgetAndLayout(ui_node* father,ui_node* child)
{
	QWidget* widget = (QWidget*)father->getObject();
	QLayout* child_layout = (QLayout*)child->getObject();
	widget->setLayout(child_layout);
	if (strcmp(father->getName(),"VSplitter")==0||strcmp(father->getName(),"HSplitter")==0)
	{
		QSplitter* widget = (QSplitter*)father->getObject();
		QWidget* temp_widget = new QWidget;
		temp_widget->setContentsMargins(0,0,0,0);
		QLayout* child_layout = (QLayout*)child->getObject();
		temp_widget->setLayout(child_layout);
		widget->addWidget(temp_widget);
	}
}
//װ��Widget��Widget
//������father ���ڵ�ָ��, child �ӽڵ�
//����ֵ����
void qt_ui_assembler::assembleWidgetAndWidget(ui_node* father,ui_node* child)
{
	QWidget* child_widget = (QWidget*)child->getObject();
	if (strcmp(father->getName(),"Tabs")==0)
	{
		QTabWidget* widget = (QTabWidget*)father->getObject();
		if (child->hasAttribute("index"))
		{
			int i = STR_TO_INT(child->getAttribute("index"));
			if (child->hasAttribute("icon"))
			{
				std::string url;
				getResImageOrIconUrl(url,child->getAttribute("icon"));
				QIcon icon(url.c_str());
				widget->insertTab(i,child_widget,icon,child->getAttribute("text"));
			}
			else
			{
				widget->insertTab(i,child_widget,child->getAttribute("text"));
			}
			if (father->hasAttribute("initIndex"))
			{
				int j = STR_TO_INT(father->getAttribute("initIndex"));
				if (i==j)
				{
					widget->setCurrentIndex(j);
				}	
			}

		}else
		{
			if (child->hasAttribute("icon"))
			{
				std::string url;
				getResImageOrIconUrl(url,child->getAttribute("icon"));
				QIcon icon(url.c_str());
				widget->addTab(child_widget,icon,child->getAttribute("text"));
			}
			else
			{
				widget->addTab(child_widget,child->getAttribute("text"));
			}
		}
	}
	else if (strcmp(father->getName(),"Tab")==0)
	{
		QWidget* widget = (QWidget*)father->getObject();
		widget->setContentsMargins(0,0,0,0);
		QVBoxLayout* temp_layout = new QVBoxLayout;
		temp_layout->setContentsMargins(0,0,0,0);
		temp_layout->addWidget(child_widget);
		widget->setLayout(temp_layout);
	}
	else if (strcmp(father->getName(),"VSplitter")==0||strcmp(father->getName(),"HSplitter")==0)
	{
		QSplitter* widget = (QSplitter*)father->getObject();
		widget->addWidget(child_widget);
        if (father->getChild(father->getChildNum()-1)==child)
        {
            for (int i=0;i<father->getChildNum();i++)
            {
                if (child->hasAttribute("stretch"))
                {
                    widget->setStretchFactor(i, STR_TO_INT(child->getAttribute("stretch")));
                } 
            }
        }
	}
	else if (strcmp(father->getName(),"StackedWidget")==0)
	{
		QStackedWidget* widget = (QStackedWidget*)father->getObject();
		if (child->hasAttribute("index"))
		{
			int i = STR_TO_INT(child->getAttribute("index"));
			widget->insertWidget(i,child_widget);
			if (father->hasAttribute("initIndex"))
			{
				int j = STR_TO_INT(father->getAttribute("initIndex"));
				if (i==j)
				{
					widget->setCurrentIndex(j);
				}	
			}

		}else
		{
			widget->addWidget(child_widget);
		}
	}
	else if (strcmp(father->getName(),"ScrollArea")==0)
	{
		QScrollArea* widget = (QScrollArea*)father->getObject();
		widget->setWidget(child_widget);
	}
    else if (strcmp(father->getName(), "MainWindow") == 0)
    {
        QMainWindow* mainWindow = (QMainWindow*)father->getObject();
        if (strcmp(child->getName(), "ToolBar") == 0)
        {
            if (child->hasAttribute("toolBarArea"))
            {
                mainWindow->addToolBar(qt_standard::getToolBarArea(child->getAttribute("toolBarArea")),(QToolBar*)child_widget);
            }
            else
            {
                mainWindow->addToolBar((QToolBar*)child_widget);
            }
        }
        else if (strcmp(child->getName(), "DockWidget") == 0)
        {
            if (child->hasAttribute("dockWidgetArea")&& child->hasAttribute("orientation"))
            {
                mainWindow->addDockWidget(qt_standard::getDockWidgetArea(child->getAttribute("dockWidgetArea")),
                    (QDockWidget*)child_widget,
                    qt_standard::getOrientation(child->getAttribute("orientation")));
            }
            else if (child->hasAttribute("dockWidgetArea"))
            {
                mainWindow->addDockWidget(qt_standard::getDockWidgetArea(child->getAttribute("dockWidgetArea")),
                    (QDockWidget*)child_widget);
            }
            else
            {
                mainWindow->addDockWidget(Qt::LeftDockWidgetArea,
                    (QDockWidget*)child_widget);
            }
            if (child->hasAttribute("tabfiedDocWidgetID"))
            {
                QDockWidget* docWidget = (QDockWidget*)R::Instance()->getObjectFromGlobalMap(child->getAttribute("tabfiedDocWidgetID"));
                if (docWidget)
                {
                    mainWindow->tabifyDockWidget(docWidget, (QDockWidget*)child_widget);
                }
            }
        }
        else if (strcmp(child->getName(), "Widget") == 0)
        {
            if (child->hasAttribute("centerWidget")&&STR_TO_BOOL(child->getAttribute("centerWidget")))
            {
                mainWindow->setCentralWidget(child_widget);
            }
        }
        else if (strcmp(child->getName(), "MenuBar") == 0)
        {
            mainWindow->setMenuBar((QMenuBar*)child_widget);
        }

        if (child->hasAttribute("centerWidget") && STR_TO_BOOL(child->getAttribute("centerWidget")))
        {
            mainWindow->setCentralWidget(child_widget);
        }

        if (child->hasAttribute("statusBar") && STR_TO_BOOL(child->getAttribute("statusBar")))
        {
            QStatusBar* bar = dynamic_cast<QStatusBar*>(child_widget);
            if (bar)
            {
                mainWindow->setStatusBar(bar);
            }  
        }

    }
    else if (strcmp(father->getName(), "MenuBar") == 0)
    {
        QMenuBar* menuBar = (QMenuBar*)father->getObject();
        if (strcmp(child->getName(), "Menu") == 0)
        {
            menuBar->addMenu((QMenu*)child->getObject());
        }
    }
    else if (strcmp(father->getName(), "ToolBar") == 0)
    {
        QToolBar* toolBar = (QToolBar*)father->getObject();
        if (strcmp(child->getName(), "Menu") == 0)
        {
            QMenu* menu = (QMenu*)child->getObject();
            toolBar->addAction(menu->menuAction());
        }
    }
    else if (strcmp(father->getName(), "DockWidget") == 0)
    {
        QDockWidget* dockWidget = (QDockWidget*)father->getObject();
        dockWidget->setWidget(child_widget);
    }
    else if (strcmp(father->getName(), "ToolBox") == 0)
    {
        QToolBox* toolBox = (QToolBox*)father->getObject();
        if (child->hasAttribute("text"))
        {
            if (child->hasAttribute("index"))
            {
                   if (child->hasAttribute("icon"))
                   {
                       std::string iconUrl;
                       getResImageOrIconUrl(iconUrl, child->getAttribute("icon"));
                       toolBox->insertItem(STR_TO_INT(child->getAttribute("index")),child_widget, QIcon(iconUrl.c_str()),child->getAttribute("text"));
                   }
                   else
                   {
                       toolBox->insertItem(STR_TO_INT(child->getAttribute("index")), child_widget, child->getAttribute("text"));
                   }
            }
            else
            {
                if (child->hasAttribute("icon"))
                {
                    std::string iconUrl;
                    getResImageOrIconUrl(iconUrl, child->getAttribute("icon"));
                    toolBox->addItem(child_widget, QIcon(iconUrl.c_str()), child->getAttribute("text"));
                }
                else
                {
                    toolBox->addItem(child_widget, child->getAttribute("text"));
                }
                QString index = QString("%1").arg(toolBox->count() - 1);
                child->addAttribute("index", index.toLocal8Bit().constData());
            }
        }
    }

	////�����ڴ����Ծ���λ�ðڷſؼ�����Ҫ��geometry����,��Ҫ��װ������setGeometry�������ӿؼ��޷�ȷ��������
	QWidget* widget = (QWidget*)father->getObject();
	if (child->hasAttribute("geometry"))
	{
		child_widget->setParent(widget);
		std::vector<std::string> gv;
		std::string geometryStr = child->getAttribute("geometry");
		splitString(geometryStr,gv,",");
		if (gv.size()==4)
		{
			int x = STR_TO_INT(gv.at(0).c_str());
			int y = STR_TO_INT(gv.at(1).c_str());
			int w = STR_TO_INT(gv.at(2).c_str());
			int h = STR_TO_INT(gv.at(3).c_str());
			child_widget->setGeometry(x,y,w,h);
			child_widget->setFixedSize(w,h);
		}	
        else
        {
            child_widget->setGeometry(0.0, 0.0, child_widget->width(),child_widget->height());
        }
	}
}
//װ��Widget��Item
//������father ���ڵ�ָ��, child �ӽڵ�
//����ֵ����
void qt_ui_assembler::assembleWidgetAndItem(ui_node* father,ui_node* child)
{
	if (strcmp(father->getName(),"Table")==0)
	{
		QTableWidget* widget =  (QTableWidget*)father->getObject();
		if (strcmp(child->getName(),"TableItem")==0&&child->hasAttribute("row")&&child->hasAttribute("col"))
		{
			QTableWidgetItem* item = (QTableWidgetItem*)child->getObject();
			int row = STR_TO_INT(child->getAttribute("row"));
			int col = STR_TO_INT(child->getAttribute("col"));
			widget->setItem(row,col,item);
		}

	}
    else if (strcmp(father->getName(), "ComboBox") == 0)
    {
        QComboBox* comboBox = (QComboBox*)father->getObject();
        if (strcmp(child->getName(), "ComboBoxItem") == 0)
        {
            //createUI(child);
            if (child->getObject() && child->hasAttribute("text"))
            {
                comboBox->addItem(STR_TO_RES_TEXT(child->getAttribute("text")));
            }
        }
    }

	if (strcmp(child->getName(),"MenuSeparator")==0)
	{
		QWidget* widget = (QWidget*)father->getObject();
		QAction* action = (QAction*)child->getObject();
		action->setSeparator(true);
		widget->addAction(action);
	}
	else if (strcmp(child->getName(),"Action")==0)
	{
		QWidget* widget = (QWidget*)father->getObject();
		QAction* action = (QAction*)child->getObject();
		action->setParent(widget);
		widget->addAction(action);
	}
}
//װ��Widget��Items
//������father ���ڵ�ָ��, child �ӽڵ�
//����ֵ����
void qt_ui_assembler::assembleWidgetAndItems(ui_node* father,ui_node* child)
{
	if (strcmp(father->getName(),"Table")==0)
	{
		if (strcmp(child->getName(),"TableColumnItems")==0)
		{
			
			int col = STR_TO_INT(child->getAttribute("col"));
			int row = STR_TO_INT(child->getAttribute("row"));
			QTableWidget* table = (QTableWidget*)father->getObject();
			int width = 50;
			int height = 20;
			bool bH = false;
			if (child->hasAttribute("width"))
			{
				width = STR_TO_INT(child->getAttribute("width"));
				table->setColumnWidth(col,width);
			}
			if (child->hasAttribute("height"))
			{
				height = STR_TO_INT(child->getAttribute("height"));
				bH = true;
			}
			if (child->hasAttribute("resizeMode"))
			{
				table->horizontalHeader()->setSectionResizeMode(col,qt_standard::getHeaderResizeMode(child->getAttribute("resizeMode")));
				table->horizontalHeader()->resizeSection(col,width);
			}
			for (int i=0;i<child->getChildNum();i++)
			{
				if (bH)
				{
					table->setRowHeight(STR_TO_INT(child->getChild(i)->getAttribute("row")),
						height);
				}
				assembleNodes(father,child->getChild(i));
			}
		}
		if (strcmp(child->getName(),"TableRowItems")==0)
		{
			int col = STR_TO_INT(child->getAttribute("col"));
			int row = STR_TO_INT(child->getAttribute("row"));
			QTableWidget* table = (QTableWidget*)father->getObject();
			int width = 50;
			int height = 20;
			bool bW = false;
			if (child->hasAttribute("width"))
			{
				width = STR_TO_INT(child->getAttribute("width"));
				bW = true;
			}
			if (child->hasAttribute("height"))
			{
				height = STR_TO_INT(child->getAttribute("height"));
				table->setRowHeight(row,height);
			}
			if (child->hasAttribute("resizeMode"))
			{
				table->horizontalHeader()->setSectionResizeMode(row,qt_standard::getHeaderResizeMode(child->getAttribute("resizeMode")));
				table->horizontalHeader()->resizeSection(row,height);
			}
			for (int i=0;i<child->getChildNum();i++)
			{
				if (bW)
				{
					table->setColumnWidth(STR_TO_INT(child->getChild(i)->getAttribute("col")),
						width);
				}
				assembleNodes(father,child->getChild(i));
			}
		}
	}
}
//װ��Container��Widget
//������father ���ڵ�ָ��, child �ӽڵ�
//����ֵ����
void qt_ui_assembler::assembleContainerAndWidget(ui_node* father,ui_node* child)
{
	if (strcmp(father->getName(),"MutexButtonBox")==0)
	{
		if (strcmp(child->getName(),"Button")==0)
		{
			sl_MutexButtonBox* box = (sl_MutexButtonBox*)father->getObject();
			sl_Button* child_widget = (sl_Button*)child->getObject();
			box->addChildButton(child_widget);
			assembleNodes(father->getParent(),child);
		}
		
	}	
	else if(strcmp(father->getName(),"ButtonGroup")==0)
	{
		if (strcmp(child->getName(),"Button")==0||strcmp(child->getName(),"RadioButton")==0
			||strcmp(child->getName(),"CheckBox")==0||strcmp(child->getName(),"ToolButton")==0)
		{
			QAbstractButton* btn = (QAbstractButton*)child->getObject();
			QButtonGroup* btnGroup = (QButtonGroup*)father->getObject();
			btnGroup->addButton(btn);
			assembleNodes(father->getParent(),child);
		}
	}
	else if(strcmp(father->getName(),"ActionGroup")==0)
	{
		if (strcmp(child->getName(),"Action")==0)
		{
			QAction* action = (QAction*)child->getObject();
			QActionGroup* actionGroup = (QActionGroup*)father->getObject();
			actionGroup->addAction(action);
			assembleNodes(father->getParent(),child);
		}
	}
	else if(strcmp(father->getName(),"VectorContainer")==0)
	{
		sl_VectorContainer* container = (sl_VectorContainer*)father->getObject();
		container->addChild(child->getObject());
		assembleNodes(father->getParent(),child);
	}
	else if(strcmp(father->getName(),"MapContainer")==0)
	{
		sl_MapContainer* container = (sl_MapContainer*)father->getObject();
		if (child->hasAttribute("key"))
		{
			container->addChild(STR_TO_INT(child->getAttribute("key")),child->getObject());
		}
		assembleNodes(father->getParent(),child);
	}
}

//���ڵ��е�����������ø�QObject�����ڴ��ݸ�����ִ����
//��ui_node�ڵ��object����
//������object object����ָ��, node �ڵ�ָ��
//����ֵ���Ƿ�����ɹ�
bool qt_ui_assembler::bindObjectWithNode(void* object,ui_node* node) 
{
	if (node->getType()==ui_node::WIDGET||node->getType()==ui_node::LAYOUT)
	{
		if (getUINodeFromObject(object))
		{
			return true;
		}
		QObject* qobject = (QObject*)object;
		QVariant variant;
		variant.setValue(node);
		qobject->setProperty("ui_node",variant);
		return true;
	}
	else if (node->getType()==ui_node::ITEM)
	{
		if (strcmp(node->getName(),"TreeWidgetItem")==0)
		{
			QTreeWidgetItem* item = (QTreeWidgetItem*)object;
			QVariant variant;
			variant.setValue(node);
			item->setData(0,Qt::UserRole,variant);	
			return true;
		}
		else
		{
			QObject* qobject = (QObject*)object;
			QVariant variant;
			variant.setValue(node);
			qobject->setProperty("ui_node",variant);
			return true;
		}
	}
	else
	{
		return false;
	}
}
//IDע��
//������node �ڵ�ָ��
//����ֵ����
void qt_ui_assembler::registerID(ui_node* node)
{
	if (node->hasAttribute("id"))
	{
		std::string id = node->getAttribute("id");
		if (_IDMap.count(id.c_str()))
		{
           // Log::Instance()->log(Log::LOG_WARN, "duplicate definition of id %s", id.c_str());
            printf("duplicate definition of id %s\n", id.c_str());
			//�ظ�����ID	
		}
		else
		{
            void*obj = node->getObject();
            if (obj)
            {
                QObject* qObj = (QObject*)obj;
                qObj->setObjectName(id.c_str());
            }
			_IDMap[id] = node->getObject();
			//����ȫ�ֵ�UINodeMap
			R::Instance()->addObjectGlobalMap(id.c_str(),node->getObject());
            R::Instance()->addIdentifiedNode(id.c_str(), node);
		}
	}
}
//��ö���ָ��
//������id ����id
//����ֵ������ָ��
void* qt_ui_assembler::getObjectByID(const char* id)
{
	IDObjectMapType::iterator it = _IDMap.find(id);
	if (it != _IDMap.end())
	{
		return it->second;
	}
	else
	{
		char szMsg[1024];
		sprintf(szMsg, "QtFrameWork ERROR: The object whose ID is %s does not exist!\n",id);
		printf(szMsg);
		return NULL;
	}
}
//����ÿ���ڵ��ʵ��
//������node �ڵ�ָ��
//����ֵ����
bool qt_ui_assembler::createUI(ui_node* node)
{
    node->addAttribute("ui_node", "true");
	if (node->getObject())
	{
		return true;
	}
	if (strcmp(node->getName(),"Button")==0)
	{
        qt_ui_creater::CreateButton(node);
	}
	else if (strcmp(node->getName(),"VLayout")==0)
	{
        qt_ui_creater::CreateVLayout(node);
	}
	else if (strcmp(node->getName(),"HLayout")==0)
	{
        qt_ui_creater::CreateHLayout(node);
	}
	else if (strcmp(node->getName(),"GridLayout")==0)
	{
        qt_ui_creater::CreateGridLayout(node);
	}
	else if (strcmp(node->getName(),"Label")==0)
	{
        qt_ui_creater::CreateLabel(node);
	}
	else if (strcmp(node->getName(),"LineEdit")==0)
	{
        qt_ui_creater::CreateLineEdit(node);
	}
	else if (strcmp(node->getName(),"Spacing")==0)
	{
        qt_ui_creater::CreateSpacing(node);
	}
	else if (strcmp(node->getName(),"Stretch")==0)
	{
        qt_ui_creater::CreateStretch(node);
	}
	else if (strcmp(node->getName(),"MutexButtonBox")==0)
	{
        qt_ui_creater::CreateMutexButtonBox(node);
	}
	else if (strcmp(node->getName(),"Tabs")==0)
	{
        qt_ui_creater::CreateTabs(node);
	}
	else if (strcmp(node->getName(),"Tab")==0)
	{
        qt_ui_creater::CreateTab(node);
	}
	else if (strcmp(node->getName(),"Spinner")==0)
	{
        qt_ui_creater::CreateSpinner(node);
	}
	else if (strcmp(node->getName(),"VSplitter")==0)
	{
        qt_ui_creater::CreateVSplitter(node);
	}
	else if (strcmp(node->getName(),"HSplitter")==0)
	{
        qt_ui_creater::CreateHSplitter(node);
	}
	else if (strcmp(node->getName(),"GroupBox")==0)
	{
        qt_ui_creater::CreateGroupBox(node);

	}
	else if (strcmp(node->getName(),"ComboBox")==0)
	{
        qt_ui_creater::CreateComboBox(node);
	}
	else if (strcmp(node->getName(),"ComboBoxItem")==0)
	{
        qt_ui_creater::CreateComboBoxItem(node);
	}
	else if (strcmp(node->getName(),"Widget")==0)
	{
        qt_ui_creater::CreateWidget(node);

	}
	else if (strcmp(node->getName(),"TextEdit")==0)
	{
        qt_ui_creater::CreateTextEdit(node);
	}

	else if (strcmp(node->getName(),"Table")==0)
	{
        qt_ui_creater::CreateTable(node);
	}
	else if (strcmp(node->getName(),"TableItem")==0)
	{
        qt_ui_creater::CreateTableItem(node);
	}
	else if (strcmp(node->getName(),"TableColumnItems")==0)
	{
        qt_ui_creater::CreateTableColumnItems(node);

	}
	else if (strcmp(node->getName(),"TableRowItems")==0)
	{
        qt_ui_creater::CreateTableRowItems(node);
	}
	else if (strcmp(node->getName(),"Slider")==0)
	{
        qt_ui_creater::CreateSlider(node);
	}
	else if (strcmp(node->getName(),"VSlider")==0)
	{
        qt_ui_creater::CreateVSlider(node);
	}
	else if (strcmp(node->getName(),"HSlider")==0)
	{
        qt_ui_creater::CreateHSlider(node);
	}
	else if (strcmp(node->getName(),"VScrollBar")==0)
	{
        qt_ui_creater::CreateVScrollBar(node);
	}
	else if (strcmp(node->getName(),"HScrollBar")==0)
	{
        qt_ui_creater::CreateHScrollBar(node);
	} 
	else if (strcmp(node->getName(),"Dial")==0)
	{
        qt_ui_creater::CreateDial(node);
	}
	else if (strcmp(node->getName(),"RadioButton")==0)
	{
        qt_ui_creater::CreateRadioButton(node);
	}
	else if (strcmp(node->getName(),"ToolButton")==0)
	{
        qt_ui_creater::CreateToolButton(node);
	}
	else if (strcmp(node->getName(),"CheckBox")==0)
	{
        qt_ui_creater::CreateCheckBox(node);
	}
	else if (strcmp(node->getName(),"Frame")==0)
	{
        qt_ui_creater::CreateFrame(node);
	}
	else if (strcmp(node->getName(),"GLWidget")==0)
	{
        qt_ui_creater::CreateGLWidget(node);
	}
	else if (strcmp(node->getName(),"ScrollArea")==0)
	{
        qt_ui_creater::CreateScrollArea(node);
	}
	else if (strcmp(node->getName(),"DeclarativeView")==0)
	{
        qt_ui_creater::CreateDeclarativeView(node);
	}
	else if (strcmp(node->getName(),"TableLayout")==0)
	{
        qt_ui_creater::CreateTableLayout(node);
	}
	else if (strcmp(node->getName(),"TableRow")==0)
	{
        qt_ui_creater::CreateTableRow(node);
	}
	else if (strcmp(node->getName(),"ProgressBar")==0)
	{
        qt_ui_creater::CreateProgressBar(node);
	}
	else if (strcmp(node->getName(),"StackedWidget")==0)
	{
        qt_ui_creater::CreateStackedWidget(node);
	}
	else if (strcmp(node->getName(),"StackedLayout")==0)
	{
        qt_ui_creater::CreateStackedLayout(node);
	}
	else if (strcmp(node->getName(),"TreeWidget")==0)
	{
        qt_ui_creater::CreateTreeWidget(node);

	}
    else if (strcmp(node->getName(), "ListWidget") == 0)
    {
        qt_ui_creater::CreateListWidget(node);
    }
	else if (strcmp(node->getName(),"VToolBar")==0)
	{
        qt_ui_creater::CreateVToolBar(node);
	}
	else if (strcmp(node->getName(),"HToolBar")==0)
	{
        qt_ui_creater::CreateHToolBar(node);
	}
    else if (strcmp(node->getName(), "ToolBox") == 0)
    {
        qt_ui_creater::CreateToolBox(node);
    }
	else if (strcmp(node->getName(),"Menu")==0)
	{
        qt_ui_creater::CreateMenu(node);
	}
	else if (strcmp(node->getName(),"Action")==0)
    {
        qt_ui_creater::CreateAction(node);
		
	}
    else if (strcmp(node->getName(), "MenuBar") == 0)
    {
        qt_ui_creater::CreateMenuBar(node);

    }
	else if (strcmp(node->getName(),"MenuSeparator")==0)
	{
        qt_ui_creater::CreateMenuSeparator(node);
	}
	//ButtonGroup������ʢ�Ű�ť�ģ���Ҫ��RadioButton�Ļ�����������
	else if (strcmp(node->getName(),"ButtonGroup")==0)
	{
        qt_ui_creater::CreateButtonGroup(node);
	}
	//ActionGroup������ʢ��Action�ģ���Ҫ��Action�Ļ�����������
	else if (strcmp(node->getName(),"ActionGroup")==0)
	{
        qt_ui_creater::CreateActionGroup(node);
	}
	else if (strcmp(node->getName(),"ImageWidget")==0)
	{
        qt_ui_creater::CreateImageWidget(node);
	}
	else if (strcmp(node->getName(),"AnimationWidget")==0)
	{
        qt_ui_creater::CreateAnimationWidget(node);
	}
    else if (strcmp(node->getName(), "MainWindow") == 0)
    {
        qt_ui_creater::CreateMainWindow(node);
    }
    else if (strcmp(node->getName(), "ToolBar") == 0)
    {
        qt_ui_creater::CreateToolBar(node);
    }
    else if (strcmp(node->getName(), "DockWidget") == 0)
    {
        qt_ui_creater::CreateDockWidget(node);
    }
	else if (strcmp(node->getName(),"FileSystemWidget")==0)
	{
        qt_ui_creater::CreateFileSystemWidget(node);
	}
	else if (strcmp(node->getName(),"DateTimeEdit")==0)
	{
        qt_ui_creater::CreateDateTimeEdit(node);
	}
	else if (strcmp(node->getName(),"TitleBar")==0)
	{
        qt_ui_creater::CreateTitleBar(node);
	}
	else if (strcmp(node->getName(),"VectorContainer")==0)
	{
        qt_ui_creater::CreateVectorContainer(node);
	}
	else if (strcmp(node->getName(),"MapContainer")==0)
	{
        qt_ui_creater::CreateMapContainer(node);
	}
	else
	{
		/*************���ж��Ƿ����û��Զ���Widget*******************///20150925
		if (R::getCustomWidget(node->getName())) //����ֻ����Widget��Ŀؼ�
		{
			node->setType(ui_node::WIDGET);
			node->setObject(R::getCustomWidget(node->getName()));
		}
		else
		{
            //�ж��Ƿ�ע�ᵽ����
            auto factoryCreateObject = QObjectFactory::Instance()->Create(node->getName());
            auto factoryCreatePlugin = QF::PluginFactory::Instance()->Create(node->getName());
            if (factoryCreateObject)
            {
                QWidget* widget = dynamic_cast<QWidget*>(factoryCreateObject);
                if (widget)
                {
                    node->setType(ui_node::WIDGET);
                    node->setObject(widget);
                }

                QF::QF_Plugin* plugin = dynamic_cast<QF::QF_Plugin*>(factoryCreateObject);
                if (plugin)
                {
                    plugin->SetAttributes(node->getAttributeMap());
                    plugin->SetMainPtr((QF::IQF_Main*)app_env::getMainPtr());
                    plugin->InitResource();
                    node->setObject(plugin,"plugin");
                    if (plugin->GetPluginHandle()&& !widget)
                    {
                        node->setType(ui_node::WIDGET);
                        node->setObject(plugin->GetPluginHandle());
                    }
                }
            }
            else if (factoryCreatePlugin)
            {
                QF::QF_Plugin* plugin = dynamic_cast<QF::QF_Plugin*>(factoryCreatePlugin);
                if (plugin)
                {
                    plugin->SetAttributes(node->getAttributeMap());
                    plugin->SetMainPtr((QF::IQF_Main*)app_env::getMainPtr());
                    plugin->InitResource();
                    node->setObject(plugin, "plugin");
                    if (plugin->GetPluginHandle())
                    {
                        node->setType(ui_node::WIDGET);
                        node->setObject(plugin->GetPluginHandle());
                    }
                }
            }
			else if (!node->getObject())
			{
				if (strcmp("Holder",node->getName())==0)
				{
					if (node->hasAttribute("id"))
					{
						char szMsg[1024];
						sprintf(szMsg, "QtFrameWork ERROR: The Holder node whose id is \"%s\" is not bounded! Please check weather its id exists in ui resource! \n",node->getAttribute("id"));
						printf(szMsg);
					}
					else
					{
						char szMsg[1024];
						sprintf(szMsg, "QtFrameWork ERROR: Create UI %s failed! Holder node should be bounded to the ui resource!\n",node->getName());
						printf(szMsg);
					}
					return false;
				}
#ifndef _DEBUG
                if (node->hasAttribute("id"))
                {
                    char szMsg[1024];
                    sprintf(szMsg, "QtFrameWork ERROR: Create UI %s whose id is \"%s\" failed!! Please check if the name of the node is correct!\n", node->getName(), node->getAttribute("id"));
                  //  printf(szMsg);
                }
                else
                {
                    char szMsg[1024];
                    sprintf(szMsg, "QtFrameWork ERROR: Create UI %s failed!! Please check if the name of the node is correct!\n", node->getName());
                   // printf(szMsg);
                }
#endif		
				return false;
			}
		}
	}
	//*************Widgetͨ����������**********************//
	if(node->getType()==ui_node::WIDGET)
	{
		ParseWidgetCommonAttribute(node);
	}
	//*************Layoutͨ����������**********************//
	if (node->getType()==ui_node::LAYOUT)
	{
		ParseLayoutCommonAttribute(node);
	}
	//*************���ñ�����Ԫ�����е�����**********************//
	ParseObjectProperty(node);
    //*************��������˿���ģ�飬�ҿ���ģ�鱻ע��**********************//
    if (node->hasAttribute("pluginModel"))
    {
        auto factoryCreatePlugin = QF::PluginFactory::Instance()->Create(node->getAttribute("pluginModel"));
        if (factoryCreatePlugin)
        {
            QF::QF_Plugin* plugin = dynamic_cast<QF::QF_Plugin*>(factoryCreatePlugin);
            if (plugin)
            {
                plugin->SetAttributes(node->getAttributeMap());
                plugin->SetMainPtr((QF::IQF_Main*)app_env::getMainPtr());
                plugin->InitResource();
                node->setObject(plugin, "plugin");
                QF::IQF_Subject* pSubject = ((QF::IQF_Main_Ext*)app_env::getMainPtr())->CreateSubject();
                node->setObject(pSubject, "subject");
                pSubject->Attach(plugin);
            }
        }
    }
	 //����ID�Ŀؼ�����map
	registerID(node);
	
	return true;
}
//����Widget���ͽڵ�Ĺ�������
//������node �ڵ�ָ��
//����ֵ����
void qt_ui_assembler::ParseWidgetCommonAttribute(ui_node* node)
{
	QWidget* widget = (QWidget*)node->getObject();
    bindObjectWithNode(widget, node);
	//��Widget�����¼�������,��ʱ������������¼��������˵���
	if (node->hasAttribute("menu"))
	{
		//����Widget��node
		if (1)
		{
			widget->installEventFilter(_event_handler);
			string menuID = node->getAttribute("menu");
			string str="@menu/";
			if (menuID.find(str)!=std::string::npos)
			{
				menuID = menuID.substr(menuID.find_first_of(str)+6);
				ui_node* menuRootNode = R::Instance()->getMenuResource(menuID.c_str());
				if (menuRootNode)
				{
					//ʵ������װ��˵�
					parseUITree(menuRootNode);
                    assembleUITree(menuRootNode);
				}	
			}
		}
	}

	if (node->hasAttribute("toolpanel"))
	{
		//����Widget��node
		if (1)
		{
			//widget->installEventFilter(_event_handler);
			string toolpanelID = node->getAttribute("toolpanel");
			string str="@toolpanel/";
			if (toolpanelID.find(str)!=std::string::npos)
			{
				toolpanelID = toolpanelID.substr(toolpanelID.find_first_of(str)+11);
				ui_node* panelRootNode = R::Instance()->getToolpanelResource(toolpanelID.c_str());
				if (panelRootNode)
				{
					//ʵ������װ��˵�
					sl_ToolPanel* panel = new sl_ToolPanel(panelRootNode);
					panel->setParent(widget);
				}	
			}
		}
	}

	//�ؼ�����С�ߴ�
	const variant* variantWMW = R::Instance()->getConfigResource("WidgetMinimumWidth");
	if (variantWMW)
	{
		int w = R::Instance()->getConfigResource("WidgetMinimumWidth")->value<int>();
		widget->setMinimumWidth(variantWMW->value<int>()); 
	}
	const variant* variantWMH = R::Instance()->getConfigResource("WidgetMinimumHeight");
	if (variantWMH)
	{
		widget->setMinimumHeight(variantWMH->value<int>()); 
	}
	//����ָ���ؼ���С�ߴ�
	if (node->hasAttribute("minWidth"))
	{
		widget->setMinimumWidth(STR_TO_INT(node->getAttribute("minWidth")));
	}
	if (node->hasAttribute("minHeight"))
	{
		widget->setMinimumHeight(STR_TO_INT(node->getAttribute("minHeight")));
	}
	//���ÿؼ��Ƿ����
	if (node->hasAttribute("disabled"))
	{
		widget->setDisabled(STR_TO_BOOL(node->getAttribute("disabled")));
	}
	//���ÿؼ��Ƿ�ɼ�
	if (node->hasAttribute("visible"))
	{
		widget->setVisible(STR_TO_BOOL(node->getAttribute("visible")));
	}
	//���ÿؼ��ĳ�ʼ��С
	if (node->hasAttribute("width"))
	{
		widget->setFixedWidth(STR_TO_INT(node->getAttribute("width")));
	}
	if (node->hasAttribute("height"))
	{
		widget->setFixedHeight(STR_TO_INT(node->getAttribute("height")));
	}
	if (node->hasAttribute("size"))
	{
		std::vector<std::string> sizeStrVec;
		std::string sizeStr = node->getAttribute("size");
		splitString(sizeStr,sizeStrVec,",");
		if (sizeStrVec.size()==2)
		{
			int w = STR_TO_INT(sizeStrVec.at(0).c_str());
			int h = STR_TO_INT(sizeStrVec.at(1).c_str());
			widget->setFixedSize(w,h);
		}
	}
	if (node->hasAttribute("minSize"))
	{
		std::vector<std::string> sizeStrVec;
		std::string sizeStr = node->getAttribute("minSize");
		splitString(sizeStr,sizeStrVec,",");
		if (sizeStrVec.size()==2)
		{
			int w = STR_TO_INT(sizeStrVec.at(0).c_str());
			int h = STR_TO_INT(sizeStrVec.at(1).c_str());
			widget->setMinimumSize(w,h);
		}
	}
	//����Widget�����ڲ��ؼ�����ʽ
	if (node->hasAttribute("style"))
	{
		std::string res = node->getAttribute("style");
		const char* stylesheet =getResStyle(node->getAttribute("style"));
		widget->setStyleSheet(stylesheet);

	}
	//��������
	if (node->hasAttribute("font"))
	{
		std::string fontStr = node->getAttribute("font");
		std::vector<std::string> fontVec;
		splitString(fontStr,fontVec," ");
		QFont font;
		int size = fontVec.size();
		switch (size)
		{
		case 4:
			font.setWeight(STR_TO_INT(fontVec.at(3).c_str()));
		case 3:
			font.setFamily(fontVec.at(2).c_str());
		case 2:
			font.setPointSize(STR_TO_INT(fontVec.at(1).c_str()));
		case 1:
			font.setBold(STR_TO_BOOL(fontVec.at(0).c_str()));
		default:
			break;
		}
		
	}
	//���ñ�����ɫ
	if (node->hasAttribute("background-color"))
	{
		QPalette palette;
		widget->setAutoFillBackground(true);
		palette.setColor(widget->backgroundRole(),QColor(getResText(node->getAttribute("background-color"))));
		widget->setPalette(palette);
	}
	//���ÿؼ��ı���ͼƬ
	if (node->hasAttribute("background-image"))
	{
		//std::string res = node->getAttribute("background-image");
		std::string url ;
		getResImageUrl(url,node->getAttribute("background-image"));
		QPalette palette;
		widget->setAutoFillBackground(true);
		//����widget�Ĵ�С��������ͼƬ�Ĵ�С
		palette.setBrush(widget->backgroundRole(),QBrush(QPixmap(url.c_str())));
		widget->setPalette(palette);
	}
	//widget�ڲ��ؼ���margin��С����
	if (node->hasAttribute("contents_margin"))
	{
		int contents_margin = STR_TO_INT(node->getAttribute("contents_margin"));
		widget->setContentsMargins(contents_margin,contents_margin,contents_margin,contents_margin);
	}
	else if (node->hasAttribute("contents_margin_left")&&node->hasAttribute("contents_margin_top")
		&&node->hasAttribute("contents_margin_right")&&node->hasAttribute("contents_margin_bottom"))
	{
		int contents_margin_left = STR_TO_INT(node->getAttribute("contents_margin_left"));
		int contents_margin_top = STR_TO_INT(node->getAttribute("contents_margin_top"));
		int contents_margin_right = STR_TO_INT(node->getAttribute("contents_margin_right"));
		int contents_margin_buttom = STR_TO_INT(node->getAttribute("contents_margin_bottom"));
		widget->setContentsMargins(contents_margin_left,contents_margin_top,contents_margin_right,contents_margin_buttom);
	}
	//����widget����ʾ����
	if (node->hasAttribute("mask"))
	{
		std::string res = node->getAttribute("mask");
		if (res.find("@image/")!= std::string::npos)
		{
			std::string url;
			getResImageUrl(url,res.c_str());
			QPixmap pixmap(url.c_str());
			//����ͼƬ��С������widget��С
			//pixmap.scaled(widget->width(),widget->height());
			widget->setFixedSize(pixmap.width(),pixmap.height());
			widget->setMask(pixmap.mask()); //����Ҫע�����maskͼƬ��ñȱ���ͼƬ��һЩ�����򱳾�ͼƬ������ʾ��ȫ
		}		
	}
	//����Widget����ʾ������
	const variant* showToolTipVariant = R::Instance()->getConfigResource("ShowToolTip");
	bool bShowToolTip = (showToolTipVariant!=NULL)?showToolTipVariant->getBool():true;
	if (bShowToolTip)
	{
		if (node->hasAttribute("tip"))
		{
			if (1)
			{
				widget->installEventFilter(_event_handler);
			}
		}
	}

	///////////////������ͬ����Ŀؼ�����///////////////
	if (strcmp(node->getName(),"VSlider")==0||strcmp(node->getName(),"HSlider")==0
		||strcmp(node->getName(),"VScrollBar")==0||strcmp(node->getName(),"HScrollBar")==0
		||strcmp(node->getName(),"Dial")==0)
	{
		QAbstractSlider* slider = (QAbstractSlider*)node->getObject();
		if (node->hasAttribute("value"))
		{
			slider->setValue(STR_TO_INT(node->getAttribute("value")));
		}
		if (node->hasAttribute("rangeMax"))
		{
			slider->setMaximum(STR_TO_INT(node->getAttribute("rangeMax")));
		}
		if (node->hasAttribute("rangeMin"))
		{
			slider->setMinimum(STR_TO_INT(node->getAttribute("rangeMin")));
		}
		if (node->hasAttribute("range"))
		{
			std::vector<std::string> rangeVec;
			std::string rangeStr = node->getAttribute("range");
			splitString(rangeStr,rangeVec,",");
			if (rangeVec.size()==2)
			{
				slider->setRange(STR_TO_INT(rangeVec.at(0).c_str()),STR_TO_INT(rangeVec.at(1).c_str()));
			}
		}
	}
	if (strcmp(node->getName(),"Button")==0||strcmp(node->getName(),"CheckBox")==0
		||strcmp(node->getName(),"RadioButton")==0||strcmp(node->getName(),"ToolButton")==0)
	{
		QAbstractButton* btn = (QAbstractButton*)node->getObject();
		if (node->hasAttribute("text"))
		{
			std::string text=node->getAttribute("text"); 
			btn->setText(STR_TO_RES_TEXT(str_replace_all(text,"\\n","\n").c_str())); //���⻯�ַ����еĻ��з�ת��Ϊ�����Ļ��з�
		}
		if (node->hasAttribute("icon"))
		{
			std::string iconUrl;
			getResImageOrIconUrl(iconUrl,node->getAttribute("icon"));
			QIcon icon(iconUrl.c_str());
			btn->setIcon(icon);
		}
		if (node->hasAttribute("checkable"))
		{
			btn->setCheckable(STR_TO_BOOL(node->getAttribute("checkable")));
		}
		if (node->hasAttribute("checked"))
		{
			btn->setCheckable(true);
			btn->setChecked(STR_TO_BOOL(node->getAttribute("checked")));
		}
	}

	//��Widget����ToolTip
	/*const variant* bShowToolTop = R::Instance()->getConfigResource("ShowToolTip");
	if (bShowToolTop)
	{
	if (bShowToolTop->value<bool>())
	{
	QString tooltip;
	tooltip.append("name:");
	tooltip.append(node->getName());
	tooltip.append("\n");
	tooltip.append("id:");
	tooltip.append(node->getAttribute("id"));
	tooltip.append("\n");

	xml_node::AttributeMapType attriMap = node->getAttributeMap();
	xml_node::AttributeMapType::iterator it = attriMap.begin();
	while(it!=attriMap.end())
	{
	if (strcmp(it->first.c_str(),"id"))
	{
	tooltip.append(it->first.c_str());
	tooltip.append(":");
	tooltip.append(it->second.c_str());
	tooltip.append("\n");
	}
	it++;
	}
	widget->setToolTip(tooltip);
	}	
	}*/
}
//����Layout���ͽڵ�Ĺ�������
//������node �ڵ�ָ��
//����ֵ����
void qt_ui_assembler::ParseLayoutCommonAttribute(ui_node* node)
{
	QLayout* layout = (QLayout*)node->getObject();
	//�����ڲ��ؼ���С�ĳߴ磬С����С�ߴ粻������С
	//layout->setSizeConstraint(QLayout::SetMinimumSize);
	//���ô����ڲ�����margin��С
	if (node->hasAttribute("spacing"))
	{
		layout->setSpacing(STR_TO_INT(node->getAttribute("spacing")));
	}
	if (node->hasAttribute("contents_margin"))
	{
		int contents_margin = STR_TO_INT(node->getAttribute("contents_margin"));
		layout->setContentsMargins(contents_margin,contents_margin,contents_margin,contents_margin);
	}
	else if (node->hasAttribute("contents_margin_left")&&node->hasAttribute("contents_margin_top")
		&&node->hasAttribute("contents_margin_right")&&node->hasAttribute("contents_margin_buttom"))
	{
		int contents_margin_left = STR_TO_INT(node->getAttribute("contents_margin_left"));
		int contents_margin_top = STR_TO_INT(node->getAttribute("contents_margin_top"));
		int contents_margin_right = STR_TO_INT(node->getAttribute("contents_margin_right"));
		int contents_margin_buttom = STR_TO_INT(node->getAttribute("contents_margin_buttom"));
		layout->setContentsMargins(contents_margin_left,contents_margin_top,contents_margin_right,contents_margin_buttom);
	}
}
//�����ڵ��QProperty
//������node �ڵ�ָ��
//����ֵ����
void qt_ui_assembler::ParseObjectProperty(ui_node* node)
{
	//ֱ��ͨ���ؼ���Ԫ�������ı�������ֵ
#ifndef RECOGNIZE_QPORPERTY_DISABLED
	if (node->getObject())
	{
		QObject* obj = (QObject*)node->getObject();
		xml_node::AttributeMapType attributeMap = node->getAttributeMap();
		xml_node::AttributeMapType::iterator amIt = attributeMap.begin();
		while(amIt != attributeMap.end())
		{
			QString name = amIt->first.c_str();
			if (name.left(2)=="p_")
			{
				QString propertyName = name.mid(2);
				//QString value = amIt->second;
                QVariant property;
                if (qt_standard::getProperty(amIt->second.c_str(), property))
                {
                    bool ret = obj->setProperty(propertyName.toLocal8Bit().constData(), property);
                }
                else
                {
                    property.setValue(QString(amIt->second.c_str()));
                    bool ret = obj->setProperty(propertyName.toLocal8Bit().constData(), property);
                }
			}
			//QPushButton
			++amIt;
		}
	}
#endif
}

