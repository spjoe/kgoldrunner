/***************************************************************************
                         kgrscene.h  -  description
                             -------------------
    begin                : Fri Aug 04 2006
    Copyright 2006 Mauricio Piacentini <mauricio@tabuleiro.com>
    Copyright 2006 Dmitry Suzdalev <dimsuz@gmail.com>
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef KGRPLAYFIELD_H
#define KGRPLAYFIELD_H

#include <kgamecanvas.h>

#include <QObject>
#include <QPixmap>
#include <QList>
#include <QPainter>

/**
 * The KGrPlayField is a KGameCanvasGroup managing the graphical representation
 * of the playfield.
 */
class KGrPlayField : public KGameCanvasGroup
{
public:
    explicit KGrPlayField (KGameCanvasAbstract* canvas = NULL);
    ~KGrPlayField();

    /** Set the tile at grid position (x, y) to be tilenum */
    void setTile (int x, int y, int tilenum);
    
    /** Set the background for the playground */
    void setBackground (const bool create, const QImage * background,
				const QPoint & tl);
    
    /** 
     * Set the tileset to use for the playfield and clear it to the background. 
     * The origin relative to the canvas is passed in \param topLeft, the
     * number of tiles the playground is composed of are passed in \param h and
     * \param v, and \param tileWidth and \tileHeight contain the size of the
     * single tile.
     **/
    void setTiles (QList<QPixmap> * tileset, const QPoint & topLeft,
	const int h, const int v, const int tilewidth, const int tileheight);

private:
    QList<KGameCanvasPixmap *> m_tilesprites;
    QList<QPixmap> * m_tileset;
    int m_tilew;
    int m_tileh;
    int m_numTilesH;
    int m_numTilesV;
    KGameCanvasPixmap * m_background;
};

#endif // KGRPLAYFIELD_H
