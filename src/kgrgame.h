/***************************************************************************
    Copyright 2003 Marco Krüger <grisuji@gmx.de>
    Copyright 2003 Ian Wadham <ianw2@optusnet.com.au>
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
***************************************************************************/
#ifndef KGRGAME_H
#define KGRGAME_H

// Macros to smooth out the differences between Qt 1 and Qt 2 classes.
//
// "myStr" converts a QString object to a C language "char*" character string.
// "myChar" extracts a C language character (type "char") from a QString object.
//
#define myStr		toLatin1().constData
#define myChar(i)	at((i)).toLatin1()

#include <QObject>
#include <QList>

#include <QColor>
#include <QPixmap>
#include <QLabel>
#include <QFrame>
#include <QTimer>

#include "kgrconsts.h"	// OBSOLESCENT - 30/12/08
#include "kgrglobals.h"

#include "kgrgameio.h"
#include "kgrcanvas.h"

/**
Sets up games and levels in KGoldrunner and controls the play.

@author Ian Wadham
*/

class KDialog;

class KGrSoundBank;
class KGrEditor;
class KGrLevelPlayer;

class KGrGame : public QObject
{
Q_OBJECT
public:
    KGrGame (KGrCanvas * theView,
             const QString & theSystemDir, const QString & theUserDir);
    ~KGrGame();

    bool initGameLists();

    void quickStartDialog();
    void setInitialTheme (const QString & themeFilepath);

    int  getLevel();

    bool inMouseMode();			// True if the game is in mouse mode.
    bool inEditMode();			// True if the game is in editor mode.
    bool isLoading();			// True if a level is being loaded.

    bool saveOK();			// Check if edits were saved.

    QString	getTitle();		// Collection - Level NNN, Name.

    void setEditObj (char newEditObj);	// Set object for editor to paint.

    QString getDirectory (Owner o);

    inline bool isFrozen() { return gameFrozen; }

    // Flags to control author's debugging aids.
    static bool bugFix;
    static bool logging;

public slots:
    void kbControl (int dirn);

    void gameActions (int action);
    void editActions (int action);
    void editToolbarActions (int action);

    void initGame();			// Do the game object's first painting.

    void startLevelOne();		// Start any game from level 1.
    void startAnyLevel();		// Start any game from any level.
    void startNextLevel();		// Start next level of current game.

    void setPlaySounds (bool on_off);	// Set sound enabled or disabled.

    // Set mouse, keyboard or laptop-hybrid control of the hero.
    void setControlMode (const Control mode);

    void startLevel (int startingAt, int requestedLevel);
    void newGame (const int lev, const int gameIndex);
    void startTutorial();		// Start tutorial game.
    void showHint();			// Show hint for current level.

    void showHighScores();		// Show high scores for current game.

    void incScore (int);		// Update the score.
    void endLevel (const int result);	// Hero completed the level or he died.
    void herosDead();			// Hero was caught or he quit (key Q).
    void showHiddenLadders();		// Show hidden ladders (nuggets gone).
    void levelCompleted();		// Hero completed the level.
    void goUpOneLevel();		// Start next level.

    void saveGame();			// Save game ID, score and level.
    void loadGame();			// Re-load game, score and level.

    void heroStep (bool climbing);	// The hero has put a foot on the floor.
    void heroFalls (bool startStop);	// The hero has started/stopped falling.
    void heroDigs();			// The hero is digging.

signals:
    void showScore (long);		// For main window to show the score.
    void showLives (long);		// For main window to show lives left.
    void showLevel (int);		// For main window to show the level.

    void hintAvailable (bool);		// For main window to adjust menu text.

    void setEditMenu (bool);		// Enable/Disable edit menu items.
    void defaultEditObj();		// Set default edit-toolbar button.

    void markRuleType (char);		// Mark KGoldrunner/Traditional rules.
    void gameFreeze (bool);		// Do visual feedback in the GUI.

    void quitGame();			// Used for Quit option in Quick Start.

    // Used to set/clear toggle actions and enable/disable actions.
    void setToggle (const char * actionName, const bool onOff);
    void setAvail  (const char * actionName, const bool onOff);

private:
    KDialog * qs;			// Pointer to Quick Start dialog box.
    QString initialThemeFilepath;

private slots:
    void quickStartPlay();
    void quickStartNewGame();
    void quickStartUseMenu();
    void quickStartQuit();

private slots:
    void finalBreath();			// Hero is dead: re-start the level.

private:
    int  loadLevel (int levelNo);
    bool readLevelData (int levelNo, KGrLevelData & d);
    void showTutorialMessages (int levelNo);

    void checkHighScore();		// Check if high score for current game.

    int  selectedGame;

/******************************************************************************/
/**************************  PLAYFIELD AND GAME DATA  *************************/
/******************************************************************************/

private:
    KGrLevelPlayer *            levelPlayer;	// Where the level is played.

    KGrCanvas *			view;		// Where the game is displayed.
    QString			systemDataDir;	// System games are stored here.
    QString			userDataDir;	// User games are stored here.

    int				level;		// Current play/edit level.
    QString			levelName;	// Level name (optional).
    QString			levelHint;	// Level hint (optional).

    long			lives;		// Lives remaining.
    long			score;		// Current score.
    long			startScore;	// Score at start of level.

    bool			newLevel;	// Next level will be a new one.
    bool			loading;	// Stop input until it's loaded.

    bool			gameFrozen;	// Game stopped.
    bool			modalFreeze;	// Stop game during dialog.
    bool			messageFreeze;	// Stop game during message.

    QTimer *			dyingTimer;	// For pause when the hero dies.

    int				lgHighlight;	// Row selected in "loadGame()".

/******************************************************************************/
/*******************************  SOUND SUPPORT *******************************/
/******************************************************************************/
    KGrSoundBank *effects;
    enum { 
	    GoldSound, 
	    StepSound, 
	    ClimbSound, 
	    FallSound, 
	    DigSound, 
	    LadderSound, 
	    DeathSound, 
	    CompletedSound, 
	    VictorySound,
	    GameOverSound,
	    NumSounds };
    QVector< int > fx;

public slots:
    void dbgControl (int code);	// Authors' debugging aids.

    void freeze();		// Stop the gameplay action.
    void unfreeze();		// Restart the gameplay action.
    void setMessageFreeze (bool);

private:
    KGrEditor * editor;		// The level-editor object.

    Control controlMode;	// How to control the hero (e.g. K/B or mouse).

/******************************************************************************/
/***********************   GAME PROPERTIES AND METHODS   **********************/
/******************************************************************************/

private:
    QList<KGrGameData *>        gameList;	// A list of available games.
    KGrGameData *		gameData;	// Data for the current game.
    int				gameIndex;	// The index in the game-list.
    Owner			owner;		// The game's owner.

    bool loadGameData (Owner);

/******************************************************************************/
/**********************    WORD-WRAPPED MESSAGE BOX    ************************/
/******************************************************************************/

    void myMessage (QWidget * parent, const QString &title, const QString &contents);
};

#endif
