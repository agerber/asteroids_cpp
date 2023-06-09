class SoundRunnable : public QRunnable
{
public:
    SoundRunnable(const QString &path) : m_path(path) {}

protected:
    void run() override
    {
        QMediaPlayer player;
        QBuffer buffer;
        QUrl url = QUrl::fromLocalFile(m_path);
        buffer.open(QIODevice::ReadWrite);
        player.setMedia(url);
        player.setVolume(50);

        // Play sound
        player.play();

        // Wait until finished
        while (player.state() == QMediaPlayer::PlayingState) {
            QThread::msleep(100);
        }
        player.stop();
    }

private:
    QString m_path;
};