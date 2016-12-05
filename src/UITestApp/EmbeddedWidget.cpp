#include "EmbeddedWidget.h"
#include "ui_embeddedWidget.h"

EmbeddedWidget::EmbeddedWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

EmbeddedWidget::~EmbeddedWidget()
{
    delete ui;
}
