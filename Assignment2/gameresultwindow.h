#ifndef GAMERESULTWINDOW_H
#define GAMERESULTWINDOW_H

#include <QDialog>
#include <QPushButton>

class GameResultWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameResultWindow(int playerScore, int AiScore, QWidget *parent = nullptr);

private slots:
    void quitGame();
    void startNewGame();

private:
    QPushButton *quitButton;
    QPushButton *startNewButton;
};

#endif // GAMERESULTWINDOW_H
