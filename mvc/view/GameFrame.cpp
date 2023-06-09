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
