#pragma once
#include <QtGui>
#include <QtCore/QtCore>
#include <QtWidgets>

class GraphicButton : public QGraphicsWidget
{
	Q_OBJECT
	Q_PROPERTY(double angle READ angle WRITE setAngle)
public:
	typedef struct 
	{
		GraphicButton* btnTool;
		GraphicButton* btnNext;
	}GraphicButtonPair;

	GraphicButton(const QPixmap &pixmap, QGraphicsItem *parent = 0)
		: QGraphicsWidget(parent), _pix(pixmap),_pixRect(QRect(0.0,0.0,0.0,0.0))
	{
		setAcceptHoverEvents(true);
		setCacheMode(DeviceCoordinateCache);
		_bSelected = false;
		_bHovered = false;
		_bPressed = false;
		_string.clear();
		_stringColor = QColor(Qt::black);
		_angle = 0.0;
		_bCheckable = false;
		_bChecked = false;
		_checkState = Qt::Unchecked;
	}

	QRectF boundingRect() const
	{
		if (_rect.isValid())
		{
			return _rect;
		}
		else
			return QRectF(-65, -65, 130, 130);
	}

	QPainterPath shape() const
	{
		return _area;

	}
	void setText(QString string,QColor color=QColor("black"))
	{
		_string = string;
		_stringColor = color;

	}
	void setAngle(double angle){_angle = angle;}
	double angle(){return _angle;}
	void setTagPath(QPainterPath path){_pathTag = path;}
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
	{
		QRectF r = boundingRect().adjusted(-2,-2,2,2);
		float alpha = 100;
		QColor colorDarkGray(128,128,128,alpha);
		QColor colorLightGray(192,192,192,alpha);
		QColor colorWhite(255,255,255,alpha);
		QColor colorBlue(120,200,255,alpha);
		painter->save();
		painter->rotate(-_angle);
		if (isEnabled())
		{
			//QLinearGradient grad(r.topLeft(), r.bottomRight());
			QRadialGradient grad(r.center(),r.height()/2);
			grad.setColorAt(_bPressed ? 1 : 0, option->state & QStyle::State_MouseOver ? colorWhite : colorDarkGray);
			grad.setColorAt(_bPressed ? 0 : 1, colorDarkGray);
			painter->setPen(colorDarkGray);
			painter->setBrush(grad);


			painter->setRenderHint(QPainter::Antialiasing);
			painter->drawPath(_path);

			//QLinearGradient grad2(r.topLeft(), r.bottomRight());
			QRadialGradient grad2(r.center(),r.height()/2);
			grad.setColorAt(_bPressed ? 1 : 0, colorDarkGray);
			grad.setColorAt(_bPressed ? 0 : 1, colorLightGray);
			painter->setPen(Qt::NoPen);
			painter->setBrush(grad);

			if (_bPressed)
				painter->translate(1, 0);
			if (_bHovered)
				painter->translate(1, 0);
			painter->drawPath(_path);

			if (_bCheckable)
			{
				if (_checkState==Qt::Checked)
				{
					painter->translate(1, 0);
					QRadialGradient grad(r.center(),r.height()/2);
					grad.setColorAt( 0 , colorBlue);
					grad.setColorAt( 1 , colorDarkGray);
					painter->setPen(Qt::NoPen);
					painter->setBrush(grad);
					painter->drawPath(_path);
				}
			}


			if (!_pathTag.isEmpty())
			{
				painter->setPen(Qt::darkBlue);
				painter->drawPath(_pathTag);
			}
		}
		else
		{
			painter->setPen(colorDarkGray);
			painter->setBrush(QBrush(QColor(148,148,148,200)));
			painter->drawPath(_path);
		}
		painter->restore();
		if (!_string.isEmpty())
		{
			QFont textFont;
			textFont.setPixelSize(_pixRect.height()/3);
			//textFont.setBold(true);
			painter->setFont(textFont);
			QRect textRect = painter->fontMetrics().boundingRect(_string);
			painter->setPen(_stringColor);
			//painter->drawText(_pixRect.translated(-textRect.width(),-textRect.height()).center(),_string);
			painter->drawText(_pixRect,Qt::AlignLeft|Qt::AlignTop,_string);
		}
		if (!_pix.isNull())
		{
			QPixmap pix = _pix.scaled(_pixRect.width(),_pixRect.height());
			painter->drawPixmap(_pixRect.translated(-pix.width(),-pix.height()).center(),pix );
		}
	}
	void setPath(QPainterPath path){_path = path;}
	void setArea(QPainterPath area){_area = area;}
	void setBoundingRect(QRectF rect){_rect = rect;}
	void setPixmapRect(QRect pixRect){_pixRect = pixRect;}
	void setCheckable(bool checkable){_bCheckable = checkable;}
	bool checkable(){return _bCheckable;}
	bool isChecked()
	{
		if (_bCheckable)
		{
			switch (_checkState)
			{
			case Qt::Unchecked:
				return false;
			case Qt::Checked:
				return true;
			}
		}
		else
			return false;
	}
	void setChecked(bool bChekced)
	{
		if (_bCheckable)
		{
			if (bChekced)
			{
				_checkState = Qt::Checked;
				emit checked();
			}
			else
			{
				_checkState = Qt::Unchecked;
				emit unChecked();
			}
		}
	}
signals:
	void pressed();
	void clicked();
	void checked();
	void unChecked();
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *e)
	{
		_bSelected = true;
		_bPressed = true;
		_prePoint = e->pos();
		emit pressed();
		update();
	}

	void mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
	{
		if (_bSelected&&isEnabled())
		{
			emit clicked();
			_bSelected = false;
			if (_bCheckable)
			{
				switch (_checkState)
				{
				case Qt::Unchecked:
					setChecked(true);
					break;
				case Qt::Checked:
					setChecked(false);
					break;
				}
			}
		}
		_bPressed = false;
		update();
	}

	void mouseMoveEvent(QGraphicsSceneMouseEvent *e)
	{
		if (_bSelected)
		{
			QPointF d = _prePoint - e->pos();
			if (d.rx()*d.rx()+d.ry()*d.ry()>10.0)
			{
				_bSelected = false;
			}
		}
		update();
	}
	void hoverEnterEvent(QGraphicsSceneHoverEvent *)
	{
		_bHovered = true;
		update();
	}
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *)
	{
		_bHovered = false;
		update();
	}
private:
	QPixmap _pix;
	QPainterPath _area;
	QPainterPath _path;
	QRectF _rect;
	QRect _pixRect;
	bool _bSelected;
	QPointF _prePoint;
	bool _bHovered;
	bool _bPressed;
	QString _string;
	QColor _stringColor;
	QRectF _stringRect;
	double _angle;
	QPainterPath _pathTag;
	bool _bCheckable;
	bool _bChecked;
	Qt::CheckState _checkState;
};




