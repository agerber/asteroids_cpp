#include "GameFrame.h"
#include <iostream>

GameFrame::GameFrame()
    : sf::RenderWindow(sf::VideoMode(800, 600), "Game Frame")
{
    try {
        initialize();
    } catch (...) {
        std::cerr << "An exception occurred." << std::endl;
    }
}

GameFrame::~GameFrame() {
    close();
}

void GameFrame::initialize() {
    setVerticalSyncEnabled(true);
}

void GameFrame::handleCloseEvent() {
    close();
    std::exit(0);  // Ensures the application quits
}


/**
#include "GameFrame.h"
#include <QCloseEvent>
#include <QDebug>
#include <QApplication>

GameFrame::GameFrame(QWidget *parent)
    : QWidget(parent), layout(new QVBoxLayout())
{
    try {
        initialize();
    } catch (...) {
        qDebug() << "An exception occurred.";
    }
}

void GameFrame::initialize()
{
    setLayout(layout);
}

void GameFrame::closeEvent(QCloseEvent *event)
{
    event->accept();
    QCoreApplication::quit();
}
**/
