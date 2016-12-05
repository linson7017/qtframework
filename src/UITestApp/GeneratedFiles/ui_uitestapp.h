/********************************************************************************
** Form generated from reading UI file 'uitestapp.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UITESTAPP_H
#define UI_UITESTAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UITestAppClass
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QRadioButton *radioButton;
    QPushButton *pushButton;
    QCheckBox *checkBox;
    QComboBox *comboBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *UITestAppClass)
    {
        if (UITestAppClass->objectName().isEmpty())
            UITestAppClass->setObjectName(QStringLiteral("UITestAppClass"));
        UITestAppClass->resize(600, 400);
        centralWidget = new QWidget(UITestAppClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(40, 40, 113, 20));
        radioButton = new QRadioButton(centralWidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(210, 40, 89, 16));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(210, 80, 75, 23));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(210, 150, 71, 16));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(410, 100, 69, 22));
        UITestAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(UITestAppClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 19));
        UITestAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(UITestAppClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        UITestAppClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(UITestAppClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        UITestAppClass->setStatusBar(statusBar);

        retranslateUi(UITestAppClass);

        QMetaObject::connectSlotsByName(UITestAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *UITestAppClass)
    {
        UITestAppClass->setWindowTitle(QApplication::translate("UITestAppClass", "UITestApp", 0));
        lineEdit->setText(QApplication::translate("UITestAppClass", "EmbeddedWidget", 0));
        radioButton->setText(QApplication::translate("UITestAppClass", "RadioButton", 0));
        pushButton->setText(QApplication::translate("UITestAppClass", "PushButton", 0));
        checkBox->setText(QApplication::translate("UITestAppClass", "CheckBox", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("UITestAppClass", "\346\226\260\345\273\272\351\241\271\347\233\2561", 0)
         << QApplication::translate("UITestAppClass", "\346\226\260\345\273\272\351\241\271\347\233\2562", 0)
         << QApplication::translate("UITestAppClass", "\346\226\260\345\273\272\351\241\271\347\233\2563", 0)
         << QApplication::translate("UITestAppClass", "\346\226\260\345\273\272\351\241\271\347\233\2564", 0)
         << QApplication::translate("UITestAppClass", "\346\226\260\345\273\272\351\241\271\347\233\2565", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class UITestAppClass: public Ui_UITestAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UITESTAPP_H
