#pragma once
#include <QGraphicsView>
#include <QtCore/QPointF>
class ui_node;
class GraphicButton;
class QGraphicsScene;

class sl_ToolPanel : public QGraphicsView
{
public:
	sl_ToolPanel(ui_node* p_ui_node);
	~sl_ToolPanel(void);
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	void createPanel(ui_node* node);
	void internalLink(ui_node* node);
private:
	ui_node* _root;
	bool _pressed;
	QPointF _oldPoint;
	QPointF _oldPos;
	QGraphicsScene* _scene;

	int _width;
	int _height;
};

