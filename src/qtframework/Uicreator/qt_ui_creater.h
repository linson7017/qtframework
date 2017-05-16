/*!
* \file qt_ui_creater.h
*
* \author 宋凌
* \date 五月 2016
*
*
*/
#pragma once

class ui_node;
class qt_ui_creater
{
public:
    qt_ui_creater();
    ~qt_ui_creater();
    //Widget
    static void CreateButton(ui_node* node);
    static void CreateLabel(ui_node* node);
    static void CreateLineEdit(ui_node* node);
    static void CreateTabs(ui_node* node);
    static void CreateTab(ui_node* node);
    static void CreateSpinner(ui_node* node);
    static void CreateVSplitter(ui_node* node);
    static void CreateHSplitter(ui_node* node);
    static void CreateGroupBox(ui_node* node);
    static void CreateComboBox(ui_node* node);
    static void CreateWidget(ui_node* node);
    static void CreateTextEdit(ui_node* node);
    static void CreateTable(ui_node* node);
    static void CreateSlider(ui_node* node);
    static void CreateVSlider(ui_node* node);
    static void CreateHSlider(ui_node* node);
    static void CreateVScrollBar(ui_node* node);
    static void CreateHScrollBar(ui_node* node);
    static void CreateDial(ui_node* node);
    static void CreateRadioButton(ui_node* node);
    static void CreateToolButton(ui_node* node);
    static void CreateCheckBox(ui_node* node);
    static void CreateFrame(ui_node* node);
    static void CreateGLWidget(ui_node* node);
    static void CreateScrollArea(ui_node* node);
    static void CreateDeclarativeView(ui_node* node);
    static void CreateProgressBar(ui_node* node);
    static void CreateStackedWidget(ui_node* node);
    static void CreateStackedLayout(ui_node* node);
    static void CreateTreeWidget(ui_node* node);
    static void CreateVToolBar(ui_node* node);
    static void CreateHToolBar(ui_node* node);
    static void CreateMenu(ui_node* node);
    static void CreateImageWidget(ui_node* node);
    static void CreateAnimationWidget(ui_node* node);
    static void CreateMainWindow(ui_node* node);
    static void CreateToolBar(ui_node* node);
    static void CreateFileSystemWidget(ui_node* node);
    static void CreateDateTimeEdit(ui_node* node);
    static void CreateDockWidget(ui_node* node);
    static void CreateMenuBar(ui_node* node);
    static void CreateListWidget(ui_node* node);

    //layout
    static void CreateVLayout(ui_node* node);
    static void CreateHLayout(ui_node* node);
    static void CreateGridLayout(ui_node* node);
    static void CreateTableLayout(ui_node* node);

    //Item
    static void CreateSpacing(ui_node* node);
    static void CreateStretch(ui_node* node);
    static void CreateComboBoxItem(ui_node* node);
    static void CreateTableItem(ui_node* node);
    static void CreateTableColumnItems(ui_node* node);
    static void CreateTableRowItems(ui_node* node);
    static void CreateTableRow(ui_node* node);
    static void CreateAction(ui_node* node);
    static void CreateMenuSeparator(ui_node* node);

    //Container
    static void CreateMutexButtonBox(ui_node* node);
    static void CreateButtonGroup(ui_node* node);
    static void CreateActionGroup(ui_node* node);
    static void CreateVectorContainer(ui_node* node);
    static void CreateMapContainer(ui_node* node);

    //customer
    static void CreateTitleBar(ui_node* node);


private:
    static bool bindObjectWithNode(void* object, ui_node* node);

    //创建树形ui节点树
    //参数：
    //		node: 节点指针
    //返回值：无
    static void createTreeUI(ui_node* node);
};

