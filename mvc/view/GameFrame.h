#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <QWidget>
#include <QLayout>

class GameFrame : public QWidget {
    Q_OBJECT

public:
    GameFrame(QWidget *parent = nullptr);

private:
    void initialize();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    QVBoxLayout *layout;
};

#endif // GAMEFRAME_H