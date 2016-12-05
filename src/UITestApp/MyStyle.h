#pragma once

#include <QtGui/QWindowsStyle>
class MyStyle:public QWindowsStyle
{
public:
	MyStyle(void);
	~MyStyle(void);

	void polish(QPalette &palette);
	void polish(QWidget *widget);
	void unpolish(QWidget *widget);
	int pixelMetric(PixelMetric metric, const QStyleOption *option,
		const QWidget *widget) const;
	int styleHint(StyleHint hint, const QStyleOption *option,
		const QWidget *widget, QStyleHintReturn *returnData) const;
	void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
		QPainter *painter, const QWidget *widget) const;
	void drawControl(ControlElement control, const QStyleOption *option,
		QPainter *painter, const QWidget *widget) const;

private:
	static void setTexture(QPalette &palette, QPalette::ColorRole role,
		const QPixmap &pixmap);
	static QPainterPath roundRectPath(const QRect &rect);
};

