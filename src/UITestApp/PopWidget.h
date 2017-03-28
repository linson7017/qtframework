#pragma once
#include <UIs/CustomActivity.h>
class PopWidget : public CustomActivity
{
	Q_OBJECT
public:
	PopWidget(void);
	~PopWidget(void);
    void closeEvent(QCloseEvent *ev){
       // QWidget::closeEvent(ev);
    }
	public slots:
		void showMessageBox();
};

