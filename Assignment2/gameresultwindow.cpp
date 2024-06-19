#include "gameresultwindow.h"
#include "maingame.h"
#include "qapplication.h"
#include "qlabel.h"

GameResultWindow::GameResultWindow(int playerScore, int AiScore, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Game Result");
    setFixedSize(300, 150);

    // create quit game button
    quitButton = new QPushButton("Quit Game", this);
    quitButton->setGeometry(50, 50, 100, 40);
    connect(quitButton, &QPushButton::clicked, this, &GameResultWindow::quitGame);

    // create new game button
    startNewButton = new QPushButton("Start New Game", this);
    startNewButton->setGeometry(150, 50, 100, 40);
    connect(startNewButton, &QPushButton::clicked, this, &GameResultWindow::startNewGame);

    // show game result
    if (playerScore > AiScore) {
        QLabel *resultLabel = new QLabel("You Wins!", this);
        resultLabel->setGeometry(50, 20, 200, 20);
    } else if (playerScore < AiScore) {
        QLabel *resultLabel = new QLabel("AI Wins!", this);
        resultLabel->setGeometry(50, 20, 200, 20);
    } else {
        QLabel *resultLabel = new QLabel("It's a tie!", this);
        resultLabel->setGeometry(50, 20, 200, 20);
    }
}

void GameResultWindow::quitGame() {
    QApplication::quit();
}

void GameResultWindow::startNewGame() {
    MainGame *mainGameWindow = new MainGame();

    mainGameWindow->show();

    this->close();
}
