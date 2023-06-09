#pragma once

#include <QFile>
#include <QSoundEffect>
#include <QThread>

class Sound
{
public:
    Sound() {}

    static void playSound(QString filePath)
    {
        auto soundThread = new QThread();
        auto soundPlayer = new QSoundEffect();
        soundPlayer->setSource(QUrl(filePath));
        soundPlayer->moveToThread(soundThread);

        QObject::connect(soundThread, &QThread::started, soundPlayer, &QSoundEffect::play);
        QObject::connect(soundPlayer, &QSoundEffect::playingChanged, soundThread, &QThread::quit);
        QObject::connect(soundPlayer, &QSoundEffect::destroyed, soundThread, &QThread::deleteLater);

        soundThread->start();
    }

    static QSoundEffect* clipForLoopFactory(const QString& fileName)
    {
        auto loopClip = new QSoundEffect();

        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        loopClip->setSource(QUrl::fromLocalFile(file.fileName()));

        return loopClip;
    }
};
