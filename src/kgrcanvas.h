/***************************************************************************
                         kgrcanvas.h  -  description
                             -------------------
    begin                : Wed Jan 23 2002
    Copyright 2002 Marco Krger
    Copyright 2002 Ian Wadham <ianw2@optusnet.com.au>
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef KGRCANVAS_H
#define KGRCANVAS_H

#include <kgamecanvas.h>

#include "kgrplayfield.h"
#include "kgrsprite.h"

#include <qcursor.h>
#include <QLabel>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QList>

class KSvgRenderer;

class KGrCanvas : public KGameCanvasWidget
{
	Q_OBJECT
public:
	KGrCanvas (QWidget * parent, const double scale,
				const QString & systemDataDir);
	virtual ~KGrCanvas();

	void changeLandscape (const QString & name);

	QPoint getMousePos ();
	void setMousePos (int, int);

	bool changeSize (int);
	void setBaseScale ();

	//void updateCanvas ();
	void paintCell (int, int, char, int offset = 0);
	void setTitle (const QString&);

	void makeHeroSprite (int, int, int);
	void setHeroVisible (bool);
	void moveHero (int, int, int);

	void makeEnemySprite (int, int, int);
	void moveEnemy (int, int, int, int, int);
	void deleteEnemySprites();

	QPixmap getPixmap (char type);

signals:
	void mouseClick (int);
	void mouseLetGo (int);

protected:
	virtual void mousePressEvent ( QMouseEvent * mouseEvent );
	virtual void mouseReleaseEvent ( QMouseEvent * mouseEvent );

private:
	QCursor * m;

	KGrPlayField * playfield;
	int scaleStep;			// Current scale-factor of canvas.
	int baseScale;			// Starting scale-factor of canvas.
	int baseFontSize;

	int border;			// Number of tiles allowed for border.
	int cw, bw, lw, mw;		// Dimensions (in pixels) of the border.
	QColor borderColor, textColor;	// Border colours.
	QLabel * title;			// Title and top part of border.

	int freebg, nuggetbg, polebg, ladderbg, hladderbg;
	int edherobg, edenemybg, betonbg, brickbg, fbrickbg;
	int bgw, bgh;			// Size of KGoldrunner 2 tile QPixmap.
	int imgW, imgH;			// Scaled size of KGr 3 tile QImage.
	QImage bgPix;			// Strip of 18 tile images.

	int goldEnemy;

	KGrSprite * heroSprite;
	QList<KGrSprite *> * enemySprites;
	QList<KGameCanvasRectangle *> borderRectangles;

	void initView();
	void makeTiles();
	void makeBorder();
	void makeTitle();
	QColor colour;
	KGameCanvasRectangle * drawRectangle (int, int, int, int, int);
	void changeColours (const char * colours []);
	void recolourObject (const char * object [], const char * colours []);

	KSvgRenderer * svg;
	QString picsDataDir;
	QString filePrefixSVG;
};

#endif // KGRCANVAS_H
