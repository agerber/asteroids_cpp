//CommandCenter.h

#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include <QVector>
#include <QTimer>
#include "GameOp.h"
#include "GameOpsQueue.h"
#include "Falcon.h"
#include "Star.h"

//The CommandCenter is a singleton that manages the state of the game.
class CommandCenter : public QObject {
    Q_OBJECT

public:
    //the constructor is made private to create a singleton instance of this class
    static CommandCenter* getInstance();

    //this method initializes the game and its elements
    void initGame();

    //these methods increment the frame count and decrement the number of numFalcons respectively
    void incrementFrame();
    void initFalconAndDecrementFalconNum();

    //methods to add, remove or get op to our list of gameOps
    void addOp(GameOp op);
    GameOp* getOp();


    //getters and setters for all member properties
    int getNumFalcons() const;
    void setNumFalcons(int value);

    int getLevel() const;
    void setLevel(int value);

    long getScore() const;
    void setScore(long value);

    bool getPaused() const;
    void setPaused(bool value);

    bool getMuted() const;
    void setMuted(bool value);

    long getFrame() const;
    void setFrame(long frame);


    QVector<Movable*>& getMovDebris() ;
    void setMovDebris(QVector<Movable*>& value);

    QVector<Movable*> & getMovFriends();
    void setMovFriends(QVector<Movable*>& value);

    QVector<Movable*> & getMovFoes();
    void setMovFoes( QVector<Movable*>& value);

    QVector<Movable*> &getMovFloaters();
    void setMovFloaters(QVector<Movable*>& value);

    GameOpsQueue* getOpsQueue();
    void setOpsQueue(GameOpsQueue* value);

    Falcon* getFalcon() const;
    Star* getStar() const;

    bool isGameOver();



private:
    //the constructor is made private to create a singleton instance of this class
    CommandCenter();
    ~CommandCenter();

    void clearAll();
    void generateStarField();

    //member variables, including: number of falcons, level, score, paused, and muted boolean values,
    //a frame counter, a falcon object, and lists containing our movables subdivided by team
    int numFalcons;
    int level;
    long score;
    bool paused;
    bool muted;
    long frame;

    Falcon* falcon;

    QVector<Movable*> movDebris;
    QVector<Movable*> movFriends;
    QVector<Movable*> movFoes;
    QVector<Movable*> movFloaters;

    GameOpsQueue* opsQueue;

signals:
    //signal emitted when the game is over
    void gameOver();
};

#endif // COMMANDCENTER_H
