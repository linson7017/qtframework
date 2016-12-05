#include "sl_ToolPanel.h"
#include <QtGui>
#include "GraphicButton.h"
#include "Uicreator/ui_node.h"
#include "Uicreator/event_handler.h"
#include "Utils/util.h"
#include "GraphicButtonGroup.h"
static const qreal PI   = qreal(3.14159265358979323846);

sl_ToolPanel::sl_ToolPanel(ui_node* p_ui_node):_root(p_ui_node),_pressed(false)
{
	_width = 500;
	_height = 500;
	if (_root)
	{
		if (_root->hasAttribute("width"))
		{
			_width = STR_TO_INT(_root->getAttribute("width"));
			setFixedWidth(STR_TO_INT(_root->getAttribute("width")));
		}
		if (_root->hasAttribute("height"))
		{
			_height = STR_TO_INT(_root->getAttribute("height"));
			setFixedHeight(STR_TO_INT(_root->getAttribute("height")));
		}
		if (_root->hasAttribute("size"))
		{
			std::vector<std::string> sizeStrVec;
			std::string sizeStr = _root->getAttribute("size");
			splitString(sizeStr,sizeStrVec,",");
			if (sizeStrVec.size()==2)
			{
				_width = STR_TO_INT(sizeStrVec.at(0).c_str());
				_height = STR_TO_INT(sizeStrVec.at(1).c_str());
				setFixedSize(_width,_height);
			}
		}
	}
	else
	{
		setGeometry(50,50,_width,_height);
	}
	
	setStyleSheet("background:transparnet;border:0px");
	setWindowOpacity(1);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setBackgroundBrush(Qt::transparent);
	_scene = new QGraphicsScene(-_width/2, -_height/2, _width, _height);
	_scene->setBackgroundBrush(Qt::transparent);
	setScene(_scene);


	createPanel(_root);
	internalLink(_root);
	//_scene->addItem((GraphicButtonGroup*)_root->getObject());
	GraphicButtonGroup* buttonFirstLevel = (GraphicButtonGroup*)_root->getObject();

	//buttonFirstLevel->setupAnimation();

	buttonFirstLevel->show();


}


sl_ToolPanel::~sl_ToolPanel(void)
{
	if (_scene!=NULL)
	{
		delete _scene;
		_scene = NULL;
	}
	
}

void sl_ToolPanel::createPanel(ui_node* node)
{
	if (strcmp(node->getName(),"ToolPanel"))
	{
		return;
	}
	
	GraphicButtonGroup *buttonParent = new GraphicButtonGroup();
	node->setObject(buttonParent);
	_scene->addItem(buttonParent);
	buttonParent->hide();

	int num = node->getChildNum();
	int radiusInW = _width/10;
	int radiusOutWMargin = _width/28;
	int radiusW = _width*3/7;
	int radiusOutW = radiusW+radiusOutWMargin;

	int radiusInH = _height/10;
	int radiusOutHMargin = _height/28;
	int radiusH = _height*3/7;
	int radiusOutH = radiusH+radiusOutHMargin;

	int arcSize = radiusOutHMargin*3/4;
	int centerTagSize = radiusInW*3/4;

	double angle = 360.0/num;
	for (int i=0;i<num;i++)
	{
		ui_node* childNode = node->getChild(i);
		if (strcmp(childNode->getName(),"Tool"))
		{
			return;
		}
		GraphicButton *buttonNext = new GraphicButton(QPixmap(), buttonParent);
		GraphicButton *button = NULL;
		if (childNode->hasAttribute("icon"))
		{
			std::string url;
			getResImageOrIconUrl(url,childNode->getAttribute("icon"));
			button = new GraphicButton(QPixmap(url.c_str()), buttonParent);
		}
		else
		{
			button = new GraphicButton(QPixmap(), buttonParent);
		}
		if (childNode->hasAttribute("text"))
		{
			if (childNode->hasAttribute("color"))
			{
				button->setText(QString(childNode->getAttribute("text")).replace("\\n","\n"),QColor(childNode->getAttribute("textColor")));
			}
			else
			{

				button->setText(QString(childNode->getAttribute("text")).replace("\\n","\n"));
			}
		}
		if (childNode->hasAttribute("checkable"))
		{
			button->setCheckable(STR_TO_BOOL(childNode->getAttribute("checkable")));
		}
		if (bindQObjectAndNode(button,childNode))
		{
			QObject::connect(button,SIGNAL(clicked()),&gs_event_handler,SLOT(handle()));
			if (button->checkable())
			{
				QObject::connect(button,SIGNAL(checked()),&gs_event_handler,SLOT(handle()));
			}
		}
		GraphicButton::GraphicButtonPair* btnPair = new GraphicButton::GraphicButtonPair;
		btnPair->btnTool = button;
		btnPair->btnNext = buttonNext;
		childNode->setObject(btnPair);
		buttonParent->addButtonPair(btnPair);
		/*_scene->addItem(button);
		_scene->addItem(buttonNext);*/

		QRectF r(-radiusW,-radiusH,2*radiusW,2*radiusH);
		
		//////////////功能按钮////////////////
		//绘制区域
		QPainterPath areaPie;
		areaPie.moveTo(r.center());
		areaPie.arcTo(r, (double)(i-0.5)*angle,
			angle);
		QPainterPath areaPieSmall;
		areaPieSmall.addEllipse(r.center(),radiusInW,radiusInH);
		QPainterPath area;
		area.addPath(areaPie);
		area.addPath(areaPieSmall);
		area.setFillRule(Qt::OddEvenFill);

		//绘制形状
		QPainterPath pathPie;
		pathPie.moveTo(r.center());
		pathPie.arcTo(r, (double)-0.5*angle,
			angle);
		QPainterPath pathPieSmall;
		pathPieSmall.addEllipse(r.center(),radiusInW,radiusInH);
		QPainterPath path;
		path.addPath(pathPie);
		path.addPath(pathPieSmall);
		path.setFillRule(Qt::OddEvenFill);

		//图标位置
		QRect pixRect;
		QPointF centerPos;
		double w = (radiusW-radiusInW)/2;
		double h = (radiusH-radiusInH)/2;
		double radiusPixW = (radiusInW+radiusW)/2;
		double radiusPixH = (radiusInH+radiusH)/2;
		double theta = angle*i*PI/180.0;
		centerPos.setX(radiusPixW*qCos(theta));
		centerPos.setY(-radiusPixH*qSin(theta));
		pixRect.setRect(centerPos.rx(),centerPos.ry(),w,h);

		button->setAngle(angle*(i));
		button->setBoundingRect(r);
		button->setArea(area.simplified());
		button->setPath(path.simplified());
		button->setPos(0.0,0.0);
		button->setPixmapRect(pixRect);

		////////////////////next按钮////////////////////////
		buttonNext->setEnabled(false);
		//绘制区域
		QPainterPath areaPieLarge;
		areaPieLarge.moveTo(r.center());
		QRectF rOut(-radiusOutW,-radiusOutH,2*radiusOutW,2*radiusOutH);
		areaPieLarge.arcTo(rOut, (double)(i-0.5)*angle,
			angle);
		QPainterPath areaN;
		areaN.addPath(areaPieLarge);
		areaN.addPath(areaPie);
		areaN.setFillRule(Qt::OddEvenFill);
		//绘制形状
		QPainterPath pathPieLarge;
		pathPieLarge.moveTo(r.center());
		//rOut(-radiusOutW,-radiusOutH,2*radiusOutW,2*radiusOutH);
		pathPieLarge.arcTo(rOut, (double)-0.5*angle,
			angle);
		QPainterPath pathN;
		pathN.addPath(pathPieLarge);
		//pathN.addPath(pathPie);
		//pathN.setFillRule(Qt::OddEvenFill);

		if (childNode->getChildNum()==1)
		{
			ui_node* childNodeNext = childNode->getChild(0);
			if (strcmp(childNodeNext->getName(),"ToolPanel"))
			{
				return;
			}
			buttonNext->setEnabled(true);
			//标记
			QPainterPath pathTag;
			pathTag.moveTo(radiusOutW,0);
			pathTag.lineTo(radiusOutW-arcSize,arcSize);
			pathTag.moveTo(radiusOutW,0);
			pathTag.lineTo(radiusOutW-arcSize,-arcSize);
			buttonNext->setTagPath(pathTag);
			//pathN.addPath(pathTag)
			createPanel(childNodeNext);

		}
		buttonNext->setAngle(angle*(i));
		buttonNext->setBoundingRect(rOut);
		buttonNext->setArea(areaN.simplified());
		buttonNext->setPath(pathN.simplified());
		buttonNext->setPos(0.0,0.0);
		
	}

	GraphicButton *buttonCenter = new GraphicButton(QPixmap(), buttonParent);
	QRectF r(-(radiusInW-2),-(radiusInH-2),2*(radiusInW-2),2*(radiusInH-2));
	buttonCenter->setBoundingRect(r);
	QPainterPath pathCenterCircle;
	pathCenterCircle.addEllipse(r);
	buttonCenter->setPath(pathCenterCircle);
	buttonCenter->setArea(pathCenterCircle);

	QPainterPath pathTag;
	if (node->getParent())
	{
		pathTag.moveTo(centerTagSize/2,0);
		pathTag.lineTo(-centerTagSize/2,0);
		pathTag.lineTo(-centerTagSize/2+centerTagSize/5,centerTagSize/5);
		pathTag.moveTo(-centerTagSize/2,0);
		pathTag.lineTo(-centerTagSize/2+centerTagSize/5,-centerTagSize/5);
	}
	else
	{
		//QPolygonF ploygon;
		double tempY = -centerTagSize*qTan(PI/3.0)/4;
		pathTag.moveTo(centerTagSize/2,0);
		pathTag.lineTo(centerTagSize/4,tempY);
		pathTag.lineTo(-centerTagSize/4,tempY);
		pathTag.lineTo(-centerTagSize/2,0);
		pathTag.lineTo(-centerTagSize/4,-tempY);
		pathTag.lineTo(centerTagSize/4,-tempY);
		pathTag.closeSubpath();
	}
	buttonCenter->setTagPath(pathTag);
	buttonCenter->setPos(0,0);
	buttonCenter->setPixmapRect(QRect(0,0,radiusInW/2,radiusInH/2));
	buttonParent->setCenterButton(buttonCenter);
}

void sl_ToolPanel::internalLink(ui_node* node)
{
	if (strcmp(node->getName(),"ToolPanel"))
	{
		return;
	}
	int num = node->getChildNum();
	
	for (int i=0;i<num;i++)
	{
		ui_node* childNode = node->getChild(i);
		if (strcmp(childNode->getName(),"Tool"))
		{
			return;
		}
		if (childNode->getChildNum()==1)
		{
			ui_node* childNodeNext = childNode->getChild(0);
			if (strcmp(childNodeNext->getName(),"ToolPanel"))
			{
				return;
			}
			GraphicButton::GraphicButtonPair* btnPair = (GraphicButton::GraphicButtonPair*)childNode->getObject();
			
			GraphicButton* btnN = btnPair->btnNext;
			GraphicButtonGroup *panel = (GraphicButtonGroup *)node->getObject();
			GraphicButtonGroup *childPanel = (GraphicButtonGroup *)childNodeNext->getObject();
			if (panel&&childPanel)
			{
				QObject::connect(btnN,SIGNAL(clicked()),panel,SLOT(fold()));
				QObject::connect(btnN,SIGNAL(clicked()),childPanel,SLOT(unfold()));
				internalLink(childNodeNext);
			}
			
		}
	}
	if (node->getParent())
	{
		ui_node* nodeparent = node->getParent();
		if (strcmp(node->getParent()->getName(),"Tool"))
		{
			return;
		}
		ui_node* parentNode = nodeparent->getParent();
		if (parentNode)
		{
			GraphicButtonGroup *panelParent = (GraphicButtonGroup *)parentNode->getObject();
			GraphicButtonGroup *panel = (GraphicButtonGroup *)node->getObject();
			GraphicButton* btnCenter = panel->centerButton();
			QObject::connect(btnCenter,SIGNAL(clicked()),panel,SLOT(fold()));
			QObject::connect(btnCenter,SIGNAL(clicked()),panelParent,SLOT(unfold()));
		}
		
	}
	else
	{
		GraphicButtonGroup *panel = (GraphicButtonGroup *)node->getObject();
		GraphicButton* btnCenter = panel->centerButton();
		QObject::connect(btnCenter,SIGNAL(clicked()),panel,SLOT(packup()));
	}

	GraphicButtonGroup *panelCurrent = (GraphicButtonGroup *)node->getObject();
	if (panelCurrent)
	{
		panelCurrent->setupAnimation();
	}
}

void sl_ToolPanel::mousePressEvent(QMouseEvent *event)
{
	_pressed = true;
	_oldPoint = event->globalPos();
	_oldPos = pos();
	QGraphicsView::mousePressEvent(event);
}

void sl_ToolPanel::mouseReleaseEvent(QMouseEvent *event)
{
	_pressed = false;
	QGraphicsView::mouseReleaseEvent(event);
}

void sl_ToolPanel::mouseMoveEvent(QMouseEvent *event)
{
	if (_pressed)
	{
		double dx = event->globalX()-_oldPoint.rx();
		double dy = event->globalY()-_oldPoint.ry();
		//_oldPoint = curPoint;
		move(_oldPos.rx()+dx,_oldPos.ry()+dy);
	}
	QGraphicsView::mouseMoveEvent(event);
}