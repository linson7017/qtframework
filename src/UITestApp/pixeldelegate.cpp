/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "pixeldelegate.h"




PixelDelegate::PixelDelegate(QObject *parent)
    : QAbstractItemDelegate(parent)
{
    pixelSize = 40;
	m_text = "";
	pix1.load("G:/images/blueStone.png");
	pix2.load("G:/images/yellowStone.png");
}

void PixelDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());
   // int size = qMin(option.rect.width(), option.rect.height());
   // int brightness = index.model()->data(index, Qt::DisplayRole).toInt();
   // double radius = (size/2.0) - (brightness/255.0 * size/2.0);
   // if (radius == 0.0)
   //     return;
    
    //painter->setRenderHint(QPainter::Antialiasing, true);
   // painter->setPen(Qt::NoPen);
    /*if (option.state & QStyle::State_Selected)
        painter->setBrush(option.palette.highlightedText());
    else
        painter->setBrush(option.palette.text());*/
    /*painter->drawEllipse(QRectF(option.rect.x() + option.rect.width()/2 - radius,
                                option.rect.y() + option.rect.height()/2 - radius,
                                2*radius, 2*radius));*/
	painter->save();
	QFont font;
	font.setStyleStrategy(QFont::NoFontMerging);
	painter->setFont(font);
	painter->setRenderHint(QPainter::NonCosmeticDefaultPen);
	QString text = index.model()->data(index,Qt::DisplayRole).toString();
	if (1)
	{
		m_text = text;
		painter->drawText(option.rect,text);
		/*QPixmap pix;
		if ((text.toInt()%2)==0)
		{
		painter->drawPixmap(option.rect,pix1);
		}
		else
		{
		painter->drawPixmap(option.rect,pix2);
		}*/
		//painter->drawRect(option.rect);
	}
	painter->restore();
}

QSize PixelDelegate::sizeHint(const QStyleOptionViewItem & /* option */,
                              const QModelIndex & /* index */) const
{
    return QSize(30, 16);
}

void PixelDelegate::setPixelSize(int size)
{
    pixelSize = size;
}
