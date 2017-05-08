/********************************************************************************
** Form generated from reading UI file 'sl_qtablewidgetitem.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SL_QTABLEWIDGETITEM_H
#define UI_SL_QTABLEWIDGETITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidgetItem>

QT_BEGIN_NAMESPACE

class Ui_sl_QTableWidgetItem
{
public:

    void setupUi(QTableWidgetItem *sl_QTableWidgetItem)
    {
        if (sl_QTableWidgetItem->objectName().isEmpty())
            sl_QTableWidgetItem->setObjectName(QStringLiteral("sl_QTableWidgetItem"));
        sl_QTableWidgetItem->resize(400, 300);

        retranslateUi(sl_QTableWidgetItem);

        QMetaObject::connectSlotsByName(sl_QTableWidgetItem);
    } // setupUi

    void retranslateUi(QTableWidgetItem *sl_QTableWidgetItem)
    {
        sl_QTableWidgetItem->setWindowTitle(QApplication::translate("sl_QTableWidgetItem", "sl_QTableWidgetItem", 0));
    } // retranslateUi

};

namespace Ui {
    class sl_QTableWidgetItem: public Ui_sl_QTableWidgetItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SL_QTABLEWIDGETITEM_H
