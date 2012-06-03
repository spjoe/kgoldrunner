/****************************************************************************
 *    Copyright 2012  Ian Wadham <iandw.au@gmail.com>                       *
 *                                                                          *
 *    This program is free software; you can redistribute it and/or         *
 *    modify it under the terms of the GNU General Public License as        *
 *    published by the Free Software Foundation; either version 2 of        *
 *    the License, or (at your option) any later version.                   *
 *                                                                          *
 *    This program is distributed in the hope that it will be useful,       *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *    GNU General Public License for more details.                          *
 *                                                                          *
 *    You should have received a copy of the GNU General Public License     *
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ****************************************************************************/

// This main program is only a vehicle for testing g.h, g.cpp, kgrrenderer.h,
// kgrrenderer.cpp, kgrthemetypes.h and kgrthemetypes.cpp.  Testmain.cpp, g.h
// and g.cpp are not part of the final KGoldrunner.

#include <KAboutData>
#include <KCmdLineArgs>
#include <KLocale>
#include <KApplication>

#include <QMainWindow>
#include <QGraphicsView>

#include "g.h"

static const char description[] =
    I18N_NOOP ("KGoldrunner is a game of action and puzzle solving");

// The intention is to keep the KGoldrunner version number in line with KDE.
static const char version[] = "4.9";

int main (int argc, char **argv)
{
    KAboutData about ("kgoldrunner", 0, ki18n ("KGoldrunner"),
                     version, ki18n (description),
                     KAboutData::License_GPL,
                     ki18n ("(C) 2003 Ian Wadham and Marco Krüger"),
                     KLocalizedString(), "http://games.kde.org/kgoldrunner" );
    KCmdLineArgs::init (argc, argv, &about);

    KApplication app;
    QMainWindow * window = new QMainWindow();
    GV * view = new GV (window);
    view->setMinimumSize (512, 384);
    window->setCentralWidget (view);

    window->show();

    return app.exec();
}
