#ifndef EMBEDDEDWIDGET_H
#define EMBEDDEDWIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class EmbeddedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EmbeddedWidget(QWidget *parent = 0);
    ~EmbeddedWidget();

private:
    Ui::Widget *ui;
};

#endif // EMBEDDEDWIDGET_H
