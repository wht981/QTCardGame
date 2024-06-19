#include "maingame.h"
#include "deck.h"
#include "gameresultwindow.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "ui_game.h"
#include "hand.h"
#include <QGraphicsColorizeEffect>


MainGame::MainGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainGame)
{
    ui->setupUi(this);

    // set ai cards layout
    for (int i = 0; i < 5; ++i) {
        QLabel *label = new QLabel(this);
        label->setFixedSize(125, 190);
        QPixmap originalPixmap(":/CardPics/CardsPic/back.png");
        QPixmap scaledPixmap = originalPixmap.scaled(label->size(), Qt::KeepAspectRatio);
        label->setPixmap(scaledPixmap);
        gridLayout->addWidget(label, 0, i);

        Ailabels[i] = label;
    }


    // set up player cards
    for (int i = 0; i < 5; ++i) {
        QPushButton *button = new QPushButton(this);
        button->setFixedSize(125, 190);
        button->setProperty("buttonValue", i); // button value are {0, 1, 2, 3, 4}
        button->setProperty("buttonState", false);
        button->setCheckable(true);
        button->setChecked(true);
        button->setStyleSheet("QPushButton {"
                              "    border: none;"
                              "    padding-top: 0px;"
                              "}");

        QPixmap pixmap(":/CardPics/CardsPic/back.png");
        QIcon icon(pixmap);
        button->setIcon(icon);
        button->setIconSize(pixmap.rect().size());
        gridLayout->addWidget(button, 3, i);

        cardbuttons[i] = button;
    }

    // set up player cards label
    for (int i = 0; i < 5; ++i) {
        QLabel *playerCardlabel = new QLabel(this);
        playerCardlabel->setFixedSize(125, 20);
        gridLayout->addWidget(playerCardlabel, 4, i);

        playerCardlabels[i] = playerCardlabel;
    }

    // set up Ai cards label
    for(int i = 0; i < 5; i++){
        QLabel *AiCardlabel = new QLabel(this);
        AiCardlabel->setFixedSize(125, 20);
        gridLayout->addWidget(AiCardlabel, 1, i);

        AiCardlabels[i] = AiCardlabel;
    }

    // set the deck label
    deckLabel->setFixedSize(125, 190);
    QPixmap originalPixmap(":/CardPics/CardsPic/back.png");
    QPixmap scaledPixmap = originalPixmap.scaled(deckLabel->size(), Qt::KeepAspectRatio);
    deckLabel->setPixmap(scaledPixmap);
    gridLayout->addWidget(deckLabel, 0, 5);


    // set swap button
    swapButton->setFixedSize(125, 20);
    gridLayout->addWidget(swapButton, 3, 5);

    // set next round button
    nextRoundButton->setFixedSize(125, 20);
    gridLayout->addWidget(nextRoundButton, 4, 5);

    setLayout(gridLayout);

    // deal cards and show player cards
    qDebug() << "Player Cards";
    playerHand.dealHand(deck);
    qDebug() << "AI Cards";
    AiHand.dealHand(deck);
    showPlayerCard(playerHand.getHandCard());

    // set handLabel： round, category, score etc
    setAllLabel(0);
    gridLayout->addWidget(handLabel, 2, 0, 1, 2);

    // add the prompt label to the layout
    setGamePrompt(0, 3);
    gridLayout->addWidget(gamePrompt, 2, 3, 1, 2);

    // set remain cards label
    cardRemainLabel->setText("Cards remain: " + QString::number(deck.getCardsNum()));
    gridLayout->addWidget(cardRemainLabel, 1, 5);

    // connect cardbuttons with signal function
    connect(cardbuttons[0], &QPushButton::pressed, this, &MainGame::onCardPressed);
    connect(cardbuttons[1], &QPushButton::pressed, this, &MainGame::onCardPressed);
    connect(cardbuttons[2], &QPushButton::pressed, this, &MainGame::onCardPressed);
    connect(cardbuttons[3], &QPushButton::pressed, this, &MainGame::onCardPressed);
    connect(cardbuttons[4], &QPushButton::pressed, this, &MainGame::onCardPressed);
    connect(swapButton, &QPushButton::pressed, this, &MainGame::on_swapCards_clicked);
    connect(nextRoundButton, &QPushButton::pressed, this, &MainGame::on_nextRound_clicked);
}

MainGame::~MainGame()
{
    delete ui;
}

void MainGame::showPlayerCard(std::vector<Card> handCard){
    for (int i = 0; i < 5; ++i) {
        QString imagePath = ":/CardPics/CardsPic/" + handCard[i].getName() + ".png";
        QPixmap originalPixmap(imagePath);

        // scale the pics
        QPixmap scaledPixmap = originalPixmap.scaled(cardbuttons[i]->size(), Qt::KeepAspectRatio);

        QIcon icon(scaledPixmap);
        cardbuttons[i]->setIcon(icon);
        cardbuttons[i]->setIconSize(scaledPixmap.size());
        playerCardlabels[i]->setText(handCard[i].getName());
    }
}

void MainGame::showAiCard(std::vector<Card> handCard){
    for (int i = 0; i < 5; ++i) {
        QString imagePath = ":/CardPics/CardsPic/" + handCard[i].getName() + ".png";
        QPixmap originalPixmap(imagePath);

        // scale the pics
        QPixmap scaledPixmap = originalPixmap.scaled(Ailabels[i]->size(), Qt::KeepAspectRatio);
        Ailabels[i]->setPixmap(scaledPixmap);
        AiCardlabels[i]->setText(handCard[i].getName());
    }
}

void MainGame::setAiCard(){
    for (int i = 0; i < 5; ++i) {
        QPixmap originalPixmap(":/CardPics/CardsPic/back.png");
        // scale the pics
        QPixmap scaledPixmap = originalPixmap.scaled(Ailabels[i]->size(), Qt::KeepAspectRatio);
        Ailabels[i]->setPixmap(scaledPixmap);
        AiCardlabels[i]->setText("");
    }
}

void MainGame::setAllLabel(bool showAiCategory){
    handLabel->setText("Round: " + QString::number(round) +
                       "\nPlayer score: " + QString::number(playerScore) +
                       "\nAi score: " + QString::number(AiScore) +
                       "\nPlayer hand category: " + playerHand.getHandName() +
                       "\nAi hand category: " + ((showAiCategory) ? AiHand.getHandName(): ""));
}

void MainGame::setGamePrompt(int cmd, int num){
    if(cmd == 0){
        gamePrompt->setText("You can swap " + QString::number(num) + " card");
    }else if(cmd == 1){
        gamePrompt->setText("You can not swap cards now");
    }else if(cmd == 2){
        gamePrompt->setText("Too much card, you can only swap " + QString::number(num) + " card");
    }else if(cmd == 3){
        gamePrompt->setText("Click \"next round\" button to \nmove the game to next round");
    }else if(cmd == 4){
        gamePrompt->setText("You can not swap cards now "
                            "\nClick \"Finish Game\" button to finish game");
    }
}

void MainGame::onCardPressed() {


    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int buttonValue = button->property("buttonValue").toInt();
    bool currentState = button->property("buttonState").toBool();

    button->setProperty("buttonState", !currentState);

    QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect(this);
    effect->setColor(Qt::gray);
    effect->setEnabled(false);
    button->setGraphicsEffect(effect);

    if (!currentState) { // check if button is pressed
        clickedCard.append(buttonValue);
        button->setStyleSheet("QPushButton {"
                              "    border: none;"
                              "    padding-top: 10px;" // move the button down 10px
                              "}");
         effect->setEnabled(true); // when push the button effect->setColor(Qt::gray);
    } else {
        clickedCard.removeAll(buttonValue);
         button->setStyleSheet("QPushButton {"
                               "    border: none;"
                               "    padding-top: 0px;"
                               "}");
         effect->setEnabled(false);
    }

    qDebug() << "Button values:" << clickedCard;
}


void MainGame::on_swapCards_clicked()
{
    if(round == 5){
         qDebug() << "no enough cards to swap";
         return;
    }
    if(clickedCard.empty()){
        qDebug() << "no cards selected";
    }else if(clickedCard.size() > 3){
        qDebug() << "you can only select three card";
    }else if(swapCardnum + clickedCard.size() > 3){
        qDebug() << "you can only swap three card";
    }else{
        // player swap some cards
        playerHand.swapCard(clickedCard, deck);
        showPlayerCard(playerHand.getHandCard());
        qDebug() << "you swap " + QString::number(clickedCard.size()) + " card";
        swapCardnum = swapCardnum + clickedCard.size();

        setAllLabel(0);

        // Ai swaps some cards
        for(int i = 0; i<clickedCard.size(); i++){
            int swapCardPos = AiPlayer.swapCardStrategy(AiHand);
            AiHand.swapCard(swapCardPos, deck);
            qDebug() << "Ai has swapped the " + QString::number(swapCardPos) +"th card";
        }
    }

    if(swapCardnum < 3){
        setGamePrompt(0, 3-swapCardnum);
    }else if(swapCardnum == 3){
        setGamePrompt(1, 0);
    }
}

void MainGame::compareHand(){
    if(playerHand.getBest().category > AiHand.getBest().category){
        playerScore++;
        qDebug() << playerHand.getHandName() + " > " + AiHand.getHandName();
    }else if(playerHand.getBest().category == AiHand.getBest().category){
        for(int i = 0; i < playerHand.getBest().handValue.size(); i++){
            if(playerHand.getBest().handValue[i] > AiHand.getBest().handValue[i]){
                qDebug() << "Same " + playerHand.getHandName() + " but " + QString::number(playerHand.getBest().handValue[i]) + " > " + QString::number(AiHand.getBest().handValue[i]);
                playerScore++;
                return;
            }else if(playerHand.getBest().handValue[i] < AiHand.getBest().handValue[i]){
                qDebug() << "Same " + playerHand.getHandName() + " but " + QString::number(playerHand.getBest().handValue[i]) + " < " + QString::number(AiHand.getBest().handValue[i]);
                AiScore++;
                return;
            }
        }
        qDebug() << "Totally same rank, this round is a draw";
    }else if(playerHand.getBest().category < AiHand.getBest().category){
        AiScore++;
        qDebug() << playerHand.getHandName() + " < " + AiHand.getHandName();
    }
}

// if % 2 == 1, only show the ai card category, if % 2 == 0, go to next round.
void MainGame::on_nextRound_clicked(){

    if(nextRoundClickCount % 2 == 1){
        showAiCard(AiHand.getHandCard());
        qDebug() << "player hand category: " + playerHand.getHandName();
        qDebug() << "Ai hand category: " + AiHand.getHandName();
        compareHand();
        qDebug() << "player score: " + QString::number(playerScore);
        qDebug() << "Ai score: " + QString::number(AiScore);
        setAllLabel(1);
        disconnect(swapButton, &QPushButton::pressed, this, &MainGame::on_swapCards_clicked);
        setGamePrompt(3, 0);
    }else if(nextRoundClickCount % 2 == 0){
        playerHand.dealHand(deck);
        AiHand.dealHand(deck);
        setAiCard();
        showPlayerCard(playerHand.getHandCard());
        round++;
        setAllLabel(0);
        connect(swapButton, &QPushButton::pressed, this, &MainGame::on_swapCards_clicked);
        swapCardnum = 0;
        cardRemainLabel->setText("Cards remain: " + QString::number(deck.getCardsNum()));
        setGamePrompt(0, 3);
    }
    if(round == 5){
        nextRoundButton->setText("Finish Game");
        setGamePrompt(4, 0);
    }
    if(round > 5){
        // when game over, show game result

        GameResultWindow *resultWindow = new GameResultWindow(playerScore, AiScore, this);
        this->close();
        resultWindow->show();

    }
    nextRoundClickCount++;
}

