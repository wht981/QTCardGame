#ifndef MAINGAME_H
#define MAINGAME_H

#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "qgridlayout.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include <QWidget>

namespace Ui {
class MainGame;
}

class MainGame : public QWidget
{
    Q_OBJECT

public:
    explicit MainGame(QWidget *parent = nullptr);
    ~MainGame();



private slots:
    void onCardPressed();
    void on_swapCards_clicked();
    void on_nextRound_clicked();


private:
    Ui::MainGame *ui;

    //game init
    Deck deck;
    Hand playerHand;
    Hand AiHand;
    Player AiPlayer;

    //game values
    QVector<int> clickedCard;
    int round = 1;
    int playerScore = 0;
    int AiScore = 0;
    int swapCardnum = 0; // the times that swapping card
    int nextRoundClickCount = 1; // if % 2 == 1, only show the ai card category, if % 2 == 0, go to next round.
    int cardRemain;

    // layout values
    QGridLayout *gridLayout = new QGridLayout(this);
    QLabel *Ailabels[5];
    QLabel *deckLabel = new QLabel(this);
    QLabel *cardRemainLabel = new QLabel(this);
    QLabel *handLabel = new QLabel(this);
    QLabel *roundLabel = new QLabel(this);
    QLabel *gamePrompt = new QLabel(this);
    QPushButton *cardbuttons[5];
    QLabel *playerCardlabels[5];
    QLabel *AiCardlabels[5];
    QPushButton *swapButton = new QPushButton("Swap Cards", this);
    QPushButton *nextRoundButton = new QPushButton("Next Round", this);

    // show the card in layout
    void showPlayerCard(std::vector<Card> handCard);
    void showAiCard(std::vector<Card> handCard);
    void setAiCard(); // Not shown Ai card;

    void setAllLabel(bool showAiCategory); // this function used to set all text label in the layout
    void setGamePrompt(int cmd, int num);

    //compare the card
    void compareHand();
};

#endif // MAINGAME_H
