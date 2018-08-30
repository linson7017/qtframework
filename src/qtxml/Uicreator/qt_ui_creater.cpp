#include "UICreator/qt_ui_creater.h"
#include "Uicreator/ui_node.h"
#include "Uicreator/event_handler.h"
#include "Res/R.h"
#include "Utils/variant.h"
#include "Utils/qt_standard.h"
#include "Utils/util.h"
#include "Utils/Log.h"


#include <QtWidgets>
#include <QtQuick>
#include <QtOpenGL/QGLWidget>
#include "UIs/sl_Button.h"
#include "UIs/sl_MutexButtonBox.h"
#include "UIs/sl_ImageWidget.h"
#include "UIs/sl_AnimationWidget.h"
#include "UIs/TitleBar.h"
#include "UIs/sl_VectorContainer.h"
#include "UIs/sl_MapContainer.h"
#include "UIs/sl_ToolPanel.h"

Q_DECLARE_METATYPE(ui_node*) //让qt识别ui_node类型

qt_ui_creater::qt_ui_creater()
{
}


qt_ui_creater::~qt_ui_creater()
{
}

bool qt_ui_creater::bindObjectWithNode(void* object, ui_node* node)
{
    if (node->getType() == ui_node::WIDGET || node->getType() == ui_node::LAYOUT)
    {
        if (getUINodeFromObject(object))
        {
            return true;
        }
        QObject* qobject = (QObject*)object;
        QVariant variant;
        variant.setValue(node);
        qobject->setProperty("ui_node", variant);
        return true;
    }
    else if (node->getType() == ui_node::ITEM)
    {
        if (strcmp(node->getName(), "TreeWidgetItem") == 0)
        {
            QTreeWidgetItem* item = (QTreeWidgetItem*)object;
            QVariant variant;
            variant.setValue(node);
            item->setData(0, Qt::UserRole, variant);
            return true;
        }
        else
        {
            QObject* qobject = (QObject*)object;
            QVariant variant;
            variant.setValue(node);
            qobject->setProperty("ui_node", variant);
            return true;
        }
    }
    else
    {
        return false;
    }
}

void qt_ui_creater::CreateButton(ui_node* node) {
    node->setType(ui_node::WIDGET);
    //QPushButton* button = new QPushButton;
    sl_Button* button = new sl_Button;

    if (node->hasAttribute("needToConfirm"))
    {
        button->setNeedToConfirm(STR_TO_BOOL(node->getAttribute("needToConfirm")));
    }
    if (node->hasAttribute("available"))
    {
        button->setAvailable(STR_TO_BOOL(node->getAttribute("available")));
    }

    if (node->hasAttribute("flat"))
    {
        button->setFlat(STR_TO_BOOL(node->getAttribute("flat")));
    }
    node->setObject(button);
    if (bindObjectWithNode(button, node))
    {
        QObject::connect(button, SIGNAL(clicked()), &gs_event_handler, SLOT(handle()));
        
        //	button->installEventFilter(&gs_event_handler);
    }
}

void qt_ui_creater::CreateLabel(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QLabel* label = new QLabel;
    if (node->hasAttribute("text"))
    {
        std::string text = node->getAttribute("text");
        label->setText(STR_TO_RES_TEXT(str_replace_all(text, "\\n", "\n").c_str()));
    }
    if (node->hasAttribute("align"))
    {
        label->setAlignment(qt_standard::getAlignment(node->getAttribute("align")));
    }
    node->setObject(label);
}
void qt_ui_creater::CreateLineEdit(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QLineEdit* lineEdit = new QLineEdit;
    if (node->hasAttribute("text"))
    {
        lineEdit->setText(STR_TO_RES_TEXT(node->getAttribute("text")));
    }
    if (node->hasAttribute("readOnly"))
    {
        lineEdit->setReadOnly(STR_TO_BOOL(node->getAttribute("readOnly")));
    }
    if (node->hasAttribute("maxLength"))
    {
        lineEdit->setMaxLength(STR_TO_INT(node->getAttribute("maxLength")));
    }
    if (node->hasAttribute("inputMask"))
    {
        lineEdit->setInputMask(node->getAttribute("inputMask"));
    }
    if (node->hasAttribute("align"))
    {
        lineEdit->setAlignment(qt_standard::getAlignment(node->getAttribute("align")));
    }
    if (node->hasAttribute("echoMode"))
    {
        lineEdit->setEchoMode(qt_standard::getEchoMode(node->getAttribute("echoMode")));
    }
    //处理正则表达式
    if (node->hasAttribute("validator"))
    {
        QValidator *validator = NULL;
        std::string str = node->getAttribute("validator");
        if (str.find(":") != std::string::npos)
        {
            int i = str.find_first_of(":");
            std::string val = str.substr(i + 1, str.length());
            std::string type = str.substr(0, i);
            if (strcmp(type.c_str(), "int") == 0)
            {
                if (val.find(",") != std::string::npos)
                {
                    int j = val.find_first_of(",");
                    int minInt = STR_TO_INT(val.substr(0, j).c_str());
                    int maxInt = STR_TO_INT(val.substr(j + 1, val.length()).c_str());
                    validator = new QIntValidator(minInt, maxInt, NULL);
                }
            }
            else if (strcmp(type.c_str(), "double") == 0)
            {
                if (val.find(",") != std::string::npos)
                {
                    int j = val.find_first_of(",");
                    double minDouble = STR_TO_DOUBLE(val.substr(0, j).c_str());
                    double maxDouble = STR_TO_DOUBLE(val.substr(j + 1, val.length()).c_str());
                    validator = new QDoubleValidator(minDouble, maxDouble, 4, NULL);
                }
            }
            else if (strcmp(type.c_str(), "regExp") == 0)
            {
                QRegExp rx(val.c_str());
                validator = new QRegExpValidator(rx, NULL);
            }
        }
        if (validator)
        {
            lineEdit->setValidator(validator);
        }
    }
    node->setObject(lineEdit);
    if (bindObjectWithNode(lineEdit, node))
    {
        QObject::connect(lineEdit, SIGNAL(editingFinished()), &gs_event_handler, SLOT(handle()));
        //widget->installEventFilter(&gs_event_handler);
    }
}
void qt_ui_creater::CreateTabs(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QTabWidget* tabs = new QTabWidget;
    if (node->hasAttribute("tabPosition"))
    {
        tabs->setTabPosition(qt_standard::getTabPosition(node->getAttribute("tabPosition")));
    }
    if (node->hasAttribute("movable"))
    {
        tabs->setMovable(STR_TO_BOOL(node->getAttribute("movable")));
    }
    if (node->hasAttribute("closable"))
    {
        tabs->setTabsClosable(STR_TO_BOOL(node->getAttribute("closable")));
    }
    node->setObject(tabs);
}
void qt_ui_creater::CreateTab(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QWidget* tab = new QWidget;
    node->setObject(tab);
}
void qt_ui_creater::CreateSpinner(ui_node* node) {
    node->setType(ui_node::WIDGET);
    if (node->hasAttribute("valueType") && strcmp(node->getAttribute("valueType"), "double") == 0)
    {
        QDoubleSpinBox* doubleSpinner = new QDoubleSpinBox;
        if (node->hasAttribute("rangeMax") && node->hasAttribute("rangeMin"))
        {
            doubleSpinner->setRange(STR_TO_DOUBLE(node->getAttribute("rangeMin")),
                STR_TO_DOUBLE(node->getAttribute("rangeMax")));
        }
        if (node->hasAttribute("range"))
        {
            std::vector<std::string> rangeVec;
            std::string rangeStr = node->getAttribute("range");
            splitString(rangeStr, rangeVec, ",");
            if (rangeVec.size() == 2)
            {
                doubleSpinner->setRange(STR_TO_DOUBLE(rangeVec.at(0).c_str()), STR_TO_DOUBLE(rangeVec.at(1).c_str()));
            }
        }
        if (node->hasAttribute("singleStep"))
        {
            doubleSpinner->setSingleStep(STR_TO_DOUBLE(node->getAttribute("singleStep")));
        }
        if (node->hasAttribute("value"))
        {
            doubleSpinner->setValue(STR_TO_DOUBLE(node->getAttribute("value")));
        }
        node->setObject(doubleSpinner);
    }
    else
    {
        QSpinBox* spinner = new QSpinBox;
        if (node->hasAttribute("rangeMax") && node->hasAttribute("rangeMin"))
        {
            spinner->setRange(STR_TO_INT(node->getAttribute("rangeMin")),
                STR_TO_INT(node->getAttribute("rangeMax")));
        }
        if (node->hasAttribute("range"))
        {
            std::vector<std::string> rangeVec;
            std::string rangeStr = node->getAttribute("range");
            splitString(rangeStr, rangeVec, ",");
            if (rangeVec.size() == 2)
            {
                spinner->setRange(STR_TO_INT(rangeVec.at(0).c_str()), STR_TO_INT(rangeVec.at(1).c_str()));
            }
        }
        if (node->hasAttribute("singleStep"))
        {
            spinner->setSingleStep(STR_TO_INT(node->getAttribute("singleStep")));
        }
        if (node->hasAttribute("value"))
        {
            spinner->setValue(STR_TO_INT(node->getAttribute("value")));
        }
        node->setObject(spinner);
    }
}
void qt_ui_creater::CreateVSplitter(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QSplitter* vSplitter = new QSplitter(Qt::Vertical);
    node->setObject(vSplitter);
}
void qt_ui_creater::CreateHSplitter(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QSplitter* hSplitter = new QSplitter(Qt::Horizontal);
    node->setObject(hSplitter);
}
void qt_ui_creater::CreateGroupBox(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QGroupBox* groupBox = new QGroupBox;
    groupBox->setStyleSheet("QGroupBox{border-width:1px; border-style:solid; border-color:gray margin-top:1px} QGroupBox::title{subcontrol-origin:margin;subcontrol-position:top left;padding:0 1px}");
    if (node->hasAttribute("text"))
    {
        groupBox->setTitle(STR_TO_RES_TEXT(node->getAttribute("text")));
    }
    //是否画边框
    if (node->hasAttribute("flat"))
    {
        groupBox->setFlat(STR_TO_BOOL(node->getAttribute("flat")));
    }
    if (node->hasAttribute("checkable"))
    {
        groupBox->setCheckable(STR_TO_BOOL(node->getAttribute("checkable")));
        if (node->hasAttribute("checked"))
        {
            groupBox->setChecked(STR_TO_BOOL(node->getAttribute("checked")));
        }
        else
        {
            groupBox->setChecked(true);
        }
    }
    node->setObject(groupBox);
    if (bindObjectWithNode(groupBox, node))
    {
        QObject::connect(groupBox, SIGNAL(clicked()), &gs_event_handler, SLOT(handle()));
        //widget->installEventFilter(&gs_event_handler);
    }
}

void qt_ui_creater::CreateComboBox(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QComboBox* comboBox = new QComboBox;
    if (node->hasAttribute("initIndex"))
    {
        comboBox->setCurrentIndex(STR_TO_INT(node->getAttribute("initIndex")));
    }
    node->setObject(comboBox);
    if (bindObjectWithNode(comboBox, node))
    {
        QObject::connect(comboBox, SIGNAL(currentIndexChanged(int)), &gs_event_handler, SLOT(handle(int)));
    }
}
void qt_ui_creater::CreateWidget(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QWidget* widget = new QWidget;
    node->setObject(widget);
}
void qt_ui_creater::CreateTextEdit(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QTextEdit* textEdit = new QTextEdit;
    if (node->hasAttribute("lineWrap"))
    {
        int w = STR_TO_INT(node->getAttribute("lineWrap"));
        textEdit->setLineWrapMode(QTextEdit::FixedPixelWidth);
        textEdit->setLineWrapColumnOrWidth(w);
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }
    if (node->hasAttribute("text"))
    {
        std::string text = node->getAttribute("text");
        textEdit->setText(STR_TO_RES_TEXT(str_replace_all(text, "\\n", "\n").c_str()));
    }
    if (node->hasAttribute("readOnly"))
    {
        textEdit->setReadOnly(STR_TO_BOOL(node->getAttribute("readOnly")));
    }
    node->setObject(textEdit);
}
void qt_ui_creater::CreateTable(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QTableWidget* table = new QTableWidget(1, 1);
    if (node->hasAttribute("col"))
    {
        table->setColumnCount(STR_TO_INT(node->getAttribute("col")));
    }
    if (node->hasAttribute("row"))
    {
        table->setRowCount(STR_TO_INT(node->getAttribute("row")));
    }
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);  //表格默认不可编辑
    if (node->hasAttribute("editable"))
    {
        if (STR_TO_BOOL(node->getAttribute("editable")))
        {
            table->setEditTriggers(QAbstractItemView::DoubleClicked);
        }
    }
    if (node->hasAttribute("vHeaderVisible"))
    {
        table->verticalHeader()->setVisible(STR_TO_BOOL(node->getAttribute("vHeaderVisible")));
    }
    if (node->hasAttribute("hHeaderVisible"))
    {
        table->horizontalHeader()->setVisible(STR_TO_BOOL(node->getAttribute("hHeaderVisible")));
    }
    if (node->hasAttribute("hHeaderLabels"))
    {
        table->setHorizontalHeaderLabels(STR_TO_STR_VECTOR(node->getAttribute("hHeaderLabels")));
    }
    if (node->hasAttribute("vHeaderLabels"))
    {
        table->setVerticalHeaderLabels(STR_TO_STR_VECTOR(node->getAttribute("vHeaderLabels")));
    }

    //table->resizeColumnsToContents();  //使表格列宽与内容适应 20151103
    //table->resizeRowsToContents(); //使表格列宽与内容适应
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);  //使表格列宽与内容大小适应
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionsMovable(true);  //使表头可以拖拽改变大小
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    table->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
    table->verticalHeader()->setSectionsMovable(true);


    if (node->hasAttribute("vHeaderResizeMode"))
    {
        table->verticalHeader()->setSectionResizeMode(qt_standard::getHeaderResizeMode(node->getAttribute("vHeaderResizeMode")));
    }
    if (node->hasAttribute("hHeaderResizeMode"))
    {
        table->horizontalHeader()->setSectionResizeMode(qt_standard::getHeaderResizeMode(node->getAttribute("hHeaderResizeMode")));
    }

    if (node->hasAttribute("hMinimumSectionSize"))
    {
        table->horizontalHeader()->setMinimumSectionSize(STR_TO_INT(node->getAttribute("hMinimumSectionSize"))); //设置表头最小尺寸
    }
    else
    {
        table->horizontalHeader()->setMinimumSectionSize(60);
    }
    if (node->hasAttribute("vMinimumSectionSize"))
    {
        table->verticalHeader()->setMinimumSectionSize(STR_TO_INT(node->getAttribute("vMinimumSectionSize")));
    }
    else
    {
        table->verticalHeader()->setMinimumSectionSize(20);
    }
    //ssx设置垂直表头最小宽度40
    if (node->hasAttribute("vMinimumHeadeSize"))
    {
        table->verticalHeader()->setMinimumWidth(STR_TO_INT(node->getAttribute("vMinimumHeadeSize")));
    }
    else
    {
        table->verticalHeader()->setMinimumWidth(40);
    }
    node->setObject(table);
    if (bindObjectWithNode(table, node))
    {
        QObject::connect(table, SIGNAL(cellDoubleClicked(int, int)), &gs_event_handler, SLOT(handle(int, int)));
        //QObject::connect(table,SIGNAL(cellClicked(int,int)),&gs_event_handler,SLOT(handle(int,int)));
    }
}
void qt_ui_creater::CreateSlider(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QSlider* slider = new QSlider;
    node->setObject(slider);
}
void qt_ui_creater::CreateVSlider(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QSlider* vSlider = new QSlider(Qt::Vertical);
    node->setObject(vSlider);
}
void qt_ui_creater::CreateHSlider(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QSlider* hSlider = new QSlider(Qt::Horizontal);
    node->setObject(hSlider);
    //shisx 
    if (bindObjectWithNode(hSlider, node))
    {
        QObject::connect(hSlider, SIGNAL(valueChanged(int)), &gs_event_handler, SLOT(handle(int)));
    }
}
void qt_ui_creater::CreateVScrollBar(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QScrollBar* vScrollBar = new QScrollBar(Qt::Vertical);
    node->setObject(vScrollBar);
}
void qt_ui_creater::CreateHScrollBar(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QScrollBar* hScrollBar = new QScrollBar(Qt::Horizontal);
    node->setObject(hScrollBar);
}
void qt_ui_creater::CreateDial(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QDial* dial = new QDial;
    node->setObject(dial);
}
void qt_ui_creater::CreateRadioButton(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QRadioButton* radioBtn = new QRadioButton;
    node->setObject(radioBtn);
    if (bindObjectWithNode(radioBtn, node))
    {
        QObject::connect(radioBtn, SIGNAL(clicked()), &gs_event_handler, SLOT(handle()));
    }
}
void qt_ui_creater::CreateToolButton(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QToolButton* toolBtn = new QToolButton;
    node->setObject(toolBtn);
    if (bindObjectWithNode(toolBtn, node))
    {
        QObject::connect(toolBtn, SIGNAL(clicked()), &gs_event_handler, SLOT(handle()));
    }
}
void qt_ui_creater::CreateCheckBox(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QCheckBox* checkBox = new QCheckBox;
    if (node->hasAttribute("checkState"))
    {
        checkBox->setCheckState(qt_standard::getCheckState(node->getAttribute("checkState")));
    }
    node->setObject(checkBox);
    if (bindObjectWithNode(checkBox, node))
    {
        QObject::connect(checkBox, SIGNAL(clicked()), &gs_event_handler, SLOT(handle()));
    }
}
void qt_ui_creater::CreateFrame(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QFrame* frame = new QFrame;
    if (node->hasAttribute("shape"))
    {
        frame->setFrameShape(qt_standard::getFrameShape(node->getAttribute("shape")));
    }
    if (node->hasAttribute("shadow"))
    {
        frame->setFrameShadow(qt_standard::getFrameShadow(node->getAttribute("shadow")));
    }
    if (node->hasAttribute("lineWidth"))
    {
        frame->setLineWidth(STR_TO_INT(node->getAttribute("lineWidth")));
    }
    node->setObject(frame);
}
void qt_ui_creater::CreateGLWidget(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QGLWidget* glwidget = new QGLWidget;
    node->setObject(glwidget);
}
void qt_ui_creater::CreateScrollArea(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QScrollArea* scrollArea = new QScrollArea;
    node->setObject(scrollArea);
}
void qt_ui_creater::CreateDeclarativeView(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QQuickView* declarativeView = new QQuickView;
    if (node->hasAttribute("source"))
    {
        std::string urlStr;
        getResQmlUrl(urlStr, node->getAttribute("source"));
        declarativeView->setSource(QUrl::fromLocalFile(urlStr.c_str()));

    }
    if (node->hasAttribute("resizeMode"))
    {
        if (strcmp(node->getAttribute("resizeMode"), "SizeViewToRootObject") == 0)
        {
            declarativeView->setResizeMode(QQuickView::SizeViewToRootObject);
        }
        else if (strcmp(node->getAttribute("resizeMode"), "SizeRootObjectToView") == 0)
        {
            declarativeView->setResizeMode(QQuickView::SizeRootObjectToView);
        }
    }

    if (node->hasAttribute("graphicSystem"))
    {
        //if (strcmp(node->getAttribute("graphicSystem"),"gl")==0)
        //{
        //	QGLFormat format = QGLFormat::defaultFormat();
        //	format.setSampleBuffers(false);
        //	format.setSwapInterval(1);
        //	QGLWidget* glWidget = new QGLWidget(/*format*/);
        //	glWidget->setAutoFillBackground(false);
        //	declarativeView->setRenderTarget(glWidget->grabFrameBuffer());
        //}		
    }

    node->setObject(declarativeView);
}
void qt_ui_creater::CreateProgressBar(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QProgressBar* progressBar = new QProgressBar;
    if (node->hasAttribute("rangeMax"))
    {
        progressBar->setMaximum(STR_TO_INT(node->getAttribute("rangeMax")));
    }
    if (node->hasAttribute("rangeMin"))
    {
        progressBar->setMinimum(STR_TO_INT(node->getAttribute("rangeMin")));
    }
    if (node->hasAttribute("range"))
    {
        std::vector<std::string> rangeVec;
        std::string rangeStr = node->getAttribute("range");
        splitString(rangeStr, rangeVec, ",");
        if (rangeVec.size() == 2)
        {
            progressBar->setRange(STR_TO_INT(rangeVec.at(0).c_str()), STR_TO_INT(rangeVec.at(1).c_str()));
        }
    }
    if (node->hasAttribute("value"))
    {
        progressBar->setValue(STR_TO_INT(node->getAttribute("value")));
    }
    node->setObject(progressBar);
    if (bindObjectWithNode(progressBar, node))
    {
        QObject::connect(progressBar, SIGNAL(valueChanged(int)), &gs_event_handler, SLOT(handle(int)));
    }
}
void qt_ui_creater::CreateStackedWidget(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QStackedWidget* stackedWidget = new QStackedWidget;
    node->setObject(stackedWidget);
    if (bindObjectWithNode(stackedWidget, node))
    {
        //widget->installEventFilter(&gs_event_handler);
    }
}

void qt_ui_creater::CreateTreeWidget(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QTreeWidget* treeWidget = new QTreeWidget;
    if (node->hasAttribute("colCount"))
    {
        treeWidget->setColumnCount(STR_TO_INT(node->getAttribute("colCount")));
    }
    else
    {
        treeWidget->setColumnCount(1);
    }
    if (node->hasAttribute("text"))
    {
        treeWidget->setHeaderLabel(node->getAttribute("text"));
    }
    if (node->hasAttribute("headerLabels"))
    {
        treeWidget->setHeaderLabels(STR_TO_STR_VECTOR(node->getAttribute("headerLabels")));
    }
    //添加TreeWidget的根节点
    for (int i = 0; i < node->getChildNum(); i++)
    {
        ui_node* childNode = node->getChild(i);
        createTreeUI(childNode);
        if (childNode->getObject())
        {
            QTreeWidgetItem* item = (QTreeWidgetItem*)childNode->getObject();
            treeWidget->addTopLevelItem(item);
        }
    }
    //默认设置子节点全部展开
    treeWidget->expandAll();
    node->setObject(treeWidget);
    //添加选择变化的响应
    if (bindObjectWithNode(treeWidget, node))
    {
        //QObject::connect(treeWidget,SIGNAL(itemSelectionChanged()),&gs_event_handler,SLOT(handle()));
        if (node->hasAttribute("event"))
        {
            if (strcmp("itemChanged",node->getAttribute("event"))==0)
            {
                QObject::connect(treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), &gs_event_handler, SLOT(handle(QTreeWidgetItem*, int)));
            }
        }
        QObject::connect(treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),&gs_event_handler,SLOT(handle(QTreeWidgetItem*,int)));
    }
}
void qt_ui_creater::CreateVToolBar(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QToolBar* vToolBar = new QToolBar;
    vToolBar->setOrientation(Qt::Vertical);
    if (node->hasAttribute("toolButtonStyle"))
    {
        vToolBar->setToolButtonStyle(qt_standard::getToolButtonStyle(node->getAttribute("toolButtonStyle")));
    }
    else
    {
        vToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    }
    node->setObject(vToolBar);
}
void qt_ui_creater::CreateHToolBar(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QToolBar* hToolBar = new QToolBar;
    hToolBar->setOrientation(Qt::Horizontal);
    if (node->hasAttribute("toolButtonStyle"))
    {
        hToolBar->setToolButtonStyle(qt_standard::getToolButtonStyle(node->getAttribute("toolButtonStyle")));
    }
    else
    {
        hToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    }
    node->setObject(hToolBar);
}
void qt_ui_creater::CreateMenu(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QMenu* menu = new QMenu;
    if (node->hasAttribute("title"))
    {
        menu->setTitle(node->getAttribute("title"));
    }
    if (node->hasAttribute("icon"))
    {
        std::string url;
        getResImageOrIconUrl(url, node->getAttribute("icon"));
        QIcon* icon = new QIcon(url.c_str());
        menu->setIcon(*icon);
    }
    else
    {
        menu->setTitle(" ");
    }
    node->setObject(menu);
}
void qt_ui_creater::CreateImageWidget(ui_node* node) {
    node->setType(ui_node::WIDGET);
    sl_ImageWidget* imageWidget = new sl_ImageWidget();
    if (node->hasAttribute("image"))
    {
        imageWidget->setImage(node->getAttribute("image"));
    }
    if (node->hasAttribute("width"))
    {
        imageWidget->setWidth(STR_TO_INT(node->getAttribute("width")));
    }
    if (node->hasAttribute("height"))
    {
        imageWidget->setHeight(STR_TO_INT(node->getAttribute("height")));
    }
    node->setObject(imageWidget);
}
void qt_ui_creater::CreateAnimationWidget(ui_node* node) {
    node->setType(ui_node::WIDGET);
    node->addAttribute("align", "top"); //默认置顶
    sl_AnimationWidget* animationWidget = new sl_AnimationWidget;
    if (node->hasAttribute("width"))
    {
        animationWidget->setWidth(STR_TO_INT(node->getAttribute("width")));
    }
    if (node->hasAttribute("height"))
    {
        animationWidget->setHeight(STR_TO_INT(node->getAttribute("height")));
    }
    if (node->hasAttribute("image"))
    {
        animationWidget->setAnimation(node->getAttribute("image"));
    }
    node->setObject(animationWidget);
}
void qt_ui_creater::CreateMainWindow(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QMainWindow* mainWindow = new QMainWindow;
    if (node->hasAttribute("tabShape"))
    {
        mainWindow->setTabShape(qt_standard::getTabShape(node->getAttribute("tabShape")));
    }
    if (node->hasAttribute("tabPosition"))
    {
        std::vector<std::string> temp;
        std::string str = node->getAttribute("tabPosition");
        splitString(str, temp, ";");
        if (temp.size()==2)
        {
            mainWindow->setTabPosition(qt_standard::getDockWidgetArea(temp.at(0).c_str()),
                qt_standard::GetTabPosition(temp.at(1).c_str()));
        }
        else if (temp.size() == 1)
        {
            mainWindow->setTabPosition(Qt::AllDockWidgetAreas,
                qt_standard::GetTabPosition(str.c_str()));
        }
    }

    node->setObject(mainWindow);
}
void qt_ui_creater::CreateToolBar(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QToolBar* toolbar = new QToolBar;
    if (node->hasAttribute("toolButtonStyle"))
    {
        toolbar->setToolButtonStyle(qt_standard::getToolButtonStyle(node->getAttribute("toolButtonStyle")));
    }
    if (node->hasAttribute("iconSize"))
    {
        std::pair<int, int> size = STR_TO_INT_PAIR(node->getAttribute("iconSize"));
        toolbar->setIconSize(QSize(size.first, size.second));
    }
    node->setObject(toolbar);
}
void qt_ui_creater::CreateFileSystemWidget(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QFileSystemModel* model = new QFileSystemModel;
    model->setRootPath("");
    if (node->hasAttribute("rootPath"))
    {
        model->setRootPath(node->getAttribute("rootPath"));
    }
    QTreeView* tree = new QTreeView;
    tree->setModel(model);
    // Demonstrating look and feel features
    tree->setAnimated(false);
    tree->setIndentation(20);
    tree->setSortingEnabled(true);
    tree->setWindowTitle(QObject::tr("Dir View"));
    node->setObject(tree);
}
void qt_ui_creater::CreateDateTimeEdit(ui_node* node) {
    node->setType(ui_node::WIDGET);
    QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate());
    node->setObject(dateEdit);
}
void qt_ui_creater::CreateDockWidget(ui_node* node)
{
    node->setType(ui_node::WIDGET);
    QDockWidget* dockWidget = new QDockWidget;
    if (node->hasAttribute("windowTitle"))
    {
        dockWidget->setWindowTitle(node->getAttribute("windowTitle"));
    }
    if (node->hasAttribute("features"))
    {
        dockWidget->setFeatures(qt_standard::getDockWidgetFeatures(node->getAttribute("features")));
    }
    if(node->hasAttribute("floating"))
    {
        dockWidget->setFloating(STR_TO_BOOL(node->getAttribute("floating")));
    }
    node->setObject(dockWidget);
}

void qt_ui_creater::CreateMenuBar(ui_node* node)
{
    node->setType(ui_node::WIDGET);
    QMenuBar* menuBar = new QMenuBar;
    node->setObject(menuBar);
}

void qt_ui_creater::CreateListWidget(ui_node* node)
{
    node->setType(ui_node::WIDGET);
    QListWidget* listWidget = new QListWidget;
    node->setObject(listWidget);
}

void qt_ui_creater::CreateToolBox(ui_node* node)
{
    node->setType(ui_node::WIDGET);
    QToolBox* toolBox = new QToolBox;
    node->setObject(toolBox);
}


void qt_ui_creater::CreateVLayout(ui_node* node) {
    node->setType(ui_node::LAYOUT);
    QVBoxLayout* vLayout = new QVBoxLayout;
    node->setObject(vLayout);
}
void qt_ui_creater::CreateHLayout(ui_node* node) {
    node->setType(ui_node::LAYOUT);
    QHBoxLayout* hLayout = new QHBoxLayout;
    node->setObject(hLayout);
}
void qt_ui_creater::CreateGridLayout(ui_node* node) {
    node->setType(ui_node::LAYOUT);
    QGridLayout* gridLayout = new QGridLayout;
    node->setObject(gridLayout);
}
void qt_ui_creater::CreateStackedLayout(ui_node* node) {
    node->setType(ui_node::LAYOUT);
    QStackedLayout* stackedLayout = new QStackedLayout;
    node->setObject(stackedLayout);
    bindObjectWithNode(stackedLayout, node);
}
void qt_ui_creater::CreateTableLayout(ui_node* node) {
    node->setType(ui_node::LAYOUT);
    //QFormLayout* hlayout = new QFormLayout;
    QGridLayout* layout = new QGridLayout;
    node->setObject(layout);
}


void qt_ui_creater::CreateMutexButtonBox(ui_node* node) {
    node->setType(ui_node::CONTAINER);
    sl_MutexButtonBox* mutexBtnBox = new sl_MutexButtonBox;
    if (node->hasAttribute("buttonSelectedStyle"))
    {
        mutexBtnBox->setButtonSelectedStyle(node->getAttribute("buttonSelectedStyle"));
    }
    if (node->hasAttribute("buttonActivatedStyle"))
    {
        mutexBtnBox->setButtonActivatedStyle(node->getAttribute("buttonActivatedStyle"));
    }
    if (node->hasAttribute("buttonNormalStyle"))
    {
        mutexBtnBox->setButtonNormalStyle(node->getAttribute("buttonNormalStyle"));
    }
    mutexBtnBox->init();
    node->setObject(mutexBtnBox);
}
void qt_ui_creater::CreateButtonGroup(ui_node* node) {
    node->setType(ui_node::CONTAINER);
    QButtonGroup* btnGroup = new QButtonGroup();
    node->setObject(btnGroup);
}
void qt_ui_creater::CreateActionGroup(ui_node* node) {
    node->setType(ui_node::CONTAINER);
    QActionGroup* actionGroup = new QActionGroup(NULL);
    node->setObject(actionGroup);
}
void qt_ui_creater::CreateVectorContainer(ui_node* node) {
    node->setType(ui_node::CONTAINER);
    sl_VectorContainer* container = new sl_VectorContainer;
    node->setObject(container);
}
void qt_ui_creater::CreateMapContainer(ui_node* node) {
    node->setType(ui_node::CONTAINER);
    sl_MapContainer* container = new sl_MapContainer;
    node->setObject(container);
}


void qt_ui_creater::CreateTitleBar(ui_node* node) {
    node->setType(ui_node::CUSTOMER);
    node->addAttribute("align", "top"); //默认置顶
    TitleBar* widget = new TitleBar;
    node->setObject(widget);
}


void qt_ui_creater::CreateSpacing(ui_node* node) {
    QObject* object = new QObject;
    node->setType(ui_node::ITEM);
    node->setObject(object);
}
void qt_ui_creater::CreateStretch(ui_node* node) {
    QObject* object = new QObject;
    node->setType(ui_node::ITEM);
    node->setObject(object);
}
void qt_ui_creater::CreateComboBoxItem(ui_node* node) {
    node->setType(ui_node::ITEM);
    QObject* object = new QObject;
    node->setObject(object);
    bindObjectWithNode(object, node);
}
void qt_ui_creater::CreateTableItem(ui_node* node) {
    node->setType(ui_node::ITEM);
    QTableWidgetItem* tableItem = new QTableWidgetItem;
    if (node->hasAttribute("text"))
    {
        string text = node->getAttribute("text");
        tableItem->setText(STR_TO_RES_TEXT(str_replace_all(text, "\\n", "\n").c_str()));
    }
    if (node->hasAttribute("background-color"))
    {
        tableItem->setBackgroundColor(getResText(node->getAttribute("background-color")));
    }
    //文字默认居中
    tableItem->setTextAlignment(Qt::AlignCenter);
    if (node->hasAttribute("text-align"))
    {
        tableItem->setTextAlignment(qt_standard::getAlignment(node->getAttribute("text-align")));
    }
    node->setObject(tableItem);
}

void qt_ui_creater::CreateTableColumnItems(ui_node* node) {
    node->setType(ui_node::ITEMS);
    QObject* object = new QObject;
    if (node->hasAttribute("col") && node->hasAttribute("size"))
    {
        int size = STR_TO_INT(node->getAttribute("size"));
        int row = 0;
        bool bHasText = false;
        bool bHasBackgroundColor = false;
        bool bHasTexts = false;
        string text = "";
        string backgroundColor = "";
        string textAlign = "center";
        std::vector<std::string> stringList;
        if (node->hasAttribute("row"))
        {
            row = STR_TO_INT(node->getAttribute("row"));
        }
        if (node->hasAttribute("text"))
        {
            text = node->getAttribute("text");
            bHasText = true;
        }
        if (node->hasAttribute("texts"))
        {
            string texts = node->getAttribute("texts");
            splitString(texts, stringList, ";;");
            bHasTexts = true;
        }
        if (node->hasAttribute("background-color"))
        {
            backgroundColor = getResText(node->getAttribute("background-color"));
            bHasBackgroundColor = true;
        }
        if (node->hasAttribute("text-align"))
        {
            textAlign = node->getAttribute("text-align");
        }

        for (int i = 0; i < size; i++)
        {
            ui_node* child_node = new ui_node;
            child_node->setName("TableItem");
            child_node->addAttribute("col", node->getAttribute("col"));
            char rowStr[50];
            sprintf(rowStr, "%d", row);
            child_node->addAttribute("row", rowStr);
            if (bHasText)
            {
                child_node->addAttribute("text", text.c_str());
            }
            if (bHasBackgroundColor)
            {
                child_node->addAttribute("background-color", backgroundColor.c_str());
            }
            if (bHasTexts)
            {
                if (i < stringList.size())
                {
                    child_node->addAttribute("text", stringList.at(i).c_str());
                }
            }
            child_node->addAttribute("text-align", textAlign.c_str());
            //createUI(child_node);
            node->addChild(child_node);
            row++;
        }
    }
    node->setObject(object);
}
void qt_ui_creater::CreateTableRowItems(ui_node* node) {
    node->setType(ui_node::ITEMS);
    QObject* object = new QObject;
    if (node->hasAttribute("row") && node->hasAttribute("size"))
    {
        int size = STR_TO_INT(node->getAttribute("size"));
        int col = 0;
        bool bHasText = false;
        bool bHasBackgroundColor = false;
        bool bHasTexts = false;
        string text = "";
        string backgroundColor = "";
        string textAlign = "center";
        std::vector<std::string> stringList;
        if (node->hasAttribute("col"))
        {
            col = STR_TO_INT(node->getAttribute("col"));
        }
        if (node->hasAttribute("text"))
        {
            text = node->getAttribute("text");
            bHasText = true;
        }
        if (node->hasAttribute("background-color"))
        {
            backgroundColor = getResText(node->getAttribute("background-color"));
            bHasBackgroundColor = true;
        }
        if (node->hasAttribute("texts"))
        {
            string texts = node->getAttribute("texts");
            splitString(texts, stringList, ";;");
            bHasTexts = true;
        }
        if (node->hasAttribute("text-align"))
        {
            textAlign = node->getAttribute("text-align");
        }
        for (int i = 0; i < size; i++)
        {
            ui_node* child_node = new ui_node;
            child_node->setName("TableItem");
            child_node->addAttribute("row", node->getAttribute("row"));
            char colStr[50];
            sprintf(colStr, "%d", col);
            child_node->addAttribute("col", colStr);
            if (bHasText)
            {
                child_node->addAttribute("text", text.c_str());
            }
            if (bHasBackgroundColor)
            {
                child_node->addAttribute("background-color", backgroundColor.c_str());
            }
            if (bHasTexts)
            {
                if (i < stringList.size())
                {
                    child_node->addAttribute("text", stringList.at(i).c_str());
                }
            }
            child_node->addAttribute("text-align", textAlign.c_str());
            //createUI(child_node);
            node->addChild(child_node);
            col++;
        }
    }
    node->setObject(object);
}
void qt_ui_creater::CreateTableRow(ui_node* node) {
    node->setType(ui_node::ITEM);
    QObject* object = new QObject;
    node->setObject(object);
}
void qt_ui_creater::CreateAction(ui_node* node) {
    node->setType(ui_node::ITEM);
    QAction* action = new QAction(NULL);
    if (node->hasAttribute("text"))
    {
        action->setText(node->getAttribute("text"));
    }
    if (node->hasAttribute("iconText"))
    {
        action->setIconText(node->getAttribute("iconText"));
    }
    if (node->hasAttribute("icon"))
    {
        std::string url;
        getResImageOrIconUrl(url, node->getAttribute("icon"));
        QIcon* icon = new QIcon(url.c_str());
        action->setIcon(*icon);
    }
    if (node->hasAttribute("checkable"))
    {
        action->setCheckable(STR_TO_BOOL(node->getAttribute("checkable")));
    }
    if (node->hasAttribute("checked"))
    {
        action->setCheckable(true);
        action->setChecked(STR_TO_BOOL(node->getAttribute("checked")));
    }
    if (node->hasAttribute("tip"))
    {
        action->setToolTip(node->getAttribute("tip"));
    }
    node->setObject(action);
    //添加action的响应
    if (bindObjectWithNode(action, node))
    {
        QObject::connect(action, SIGNAL(triggered()), &gs_event_handler, SLOT(handle()));
    }
}
void qt_ui_creater::CreateMenuSeparator(ui_node* node) {
    node->setType(ui_node::ITEM);
    //Separator是一种特殊的QAction
    QAction* actionMenu = new QAction(NULL);
    node->setObject(actionMenu);
}


//创建叶子节点为树节点的节点
//创建树形ui节点树
//参数：node 节点指针
//返回值：无
void qt_ui_creater::createTreeUI(ui_node* node)
{
    if (strcmp(node->getName(), "TreeWidgetItem") == 0)
    {
        node->setType(ui_node::ITEM);
        QTreeWidgetItem* treeItem = NULL;
        if (node->hasAttribute("textList"))
        {
            treeItem = new QTreeWidgetItem(STR_TO_STR_VECTOR(node->getAttribute("textList")));
        }
        else if (node->hasAttribute("text"))
        {
            treeItem = new QTreeWidgetItem;
            treeItem->setText(0, node->getAttribute("text"));
        }
        if (node->hasAttribute("checkState"))
        {
            treeItem->setCheckState(0, qt_standard::getCheckState(node->getAttribute("checkState")));
        }
        treeItem->setExpanded(true);
        node->setObject(treeItem);
        bindObjectWithNode(treeItem, node);
        if (node->getChildNum())
        {
            for (int i = 0; i < node->getChildNum(); i++)
            {
                ui_node* childNode = node->getChild(i);
                createTreeUI(childNode);
                QTreeWidgetItem* childItem = (QTreeWidgetItem*)childNode->getObject();
                treeItem->addChild(childItem);
            }
        }
    }
    else
    {
        return;
    }
}