
#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QMessageBox>
#include <QTimer>
#include <algorithm>
#include <random>
#include <chrono>
#include <QLabel>
#include <QPushButton>
#include <QSettings>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWindow)
    , firstSelectedCard(nullptr)
    , secondSelectedCard(nullptr)
    , isProcessing(false)
    , moveCount(0)
    , elapsedTime(0)
{
    ui->setupUi(this);
    setWindowTitle("MemoFlip - Game");

    // initialize central widget and grid layout
    centralWidget = new QWidget(this);
    QGridLayout *mainLayout = new QGridLayout(centralWidget);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(20, 20, 20, 20);


    // Initialize move counter label
    moveLabel = new QLabel("Moves: 0", this);
    moveLabel->setObjectName("moveLabel"); // For easy access
    mainLayout->addWidget(moveLabel, 0, 0, 1, 2, Qt::AlignLeft);

    // Initialize timer label
    timerLabel = new QLabel("Time: 0s", this);
    timerLabel->setObjectName("timerLabel");
    mainLayout->addWidget(timerLabel, 0, 2, 1, 2, Qt::AlignRight);


    // Initialize grid layout for cards
    gridLayout = new QGridLayout();
    gridLayout->setSpacing(10);
    mainLayout->addLayout(gridLayout, 1, 0, 1, 4);


    // Initialize game timer
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &GameWindow::updateTimerLabel);
    gameTimer->start(1000); // Update every second

    // load, shuffle, setup card game
    loadCardData();
    shuffleCards();
    setupGame();

    // Connect control buttons
    connect(ui->shuffleButton, &QPushButton::clicked, this, &GameWindow::on_shuffleButton_clicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &GameWindow::on_exitButton_clicked);
    connect(ui->restartButton, &QPushButton::clicked, this, &GameWindow::on_restartButton_clicked);
}

GameWindow::~GameWindow()
{
    delete ui;
}
void GameWindow::on_exitButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit Game", "Are you sure you want to exit the game?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        close(); // Close the GameWindow
    }
}

void GameWindow::on_shuffleButton_clicked()
{
    shuffleCards();

    // Reset the game state
    for(auto &card : cardData)
    {
        // get the button by pairId or index
        // iterate through the card buttons
        // For example:
        // ui->card1, ui->card2, ..., ui->card16
        // Reset each button to show back
        QString cardName = QString("card%1").arg(card.pairId + 1);
        QPushButton* cardButton = this->findChild<QPushButton*>(cardName);
        if(cardButton){
            cardButton->setIcon(QIcon(":/images/backOfCard.png"));
            cardButton->setIconSize(cardButton->size());
            cardButton->setEnabled(true);
        }
    }

    resetSelection();
    moveCount = 0;
    elapsedTime = 0;
    updateMoveLabel();
    timerLabel->setText("Time: 0s");
    gameTimer->start(1000); // Restart timer
}
void GameWindow::on_restartButton_clicked()
{
    // Restart the game
    restartGame();
}

void GameWindow::loadCardData()
{
    // load card images and concept pairs here replace patchs with actual image paths
    // we assume 8 pairs

    for(int i = 0; i < 8; i++){
        QPixmap imagePixmap(QString(":/image/path.png").arg(i));
        QPixmap conceptPixmap(QString(":/images/concept.png").arg(i));

        if(imagePixmap.isNull() || conceptPixmap.isNull()){
            QMessageBox::critical(this, "Error", QString("Failed to load images for pair %1").arg(i));
            continue;
        }

        CardData imageCard;
        imageCard.frontImage = imagePixmap;
        imageCard.pairId = i;
        cardData.append(imageCard); // Image card

        CardData conceptCard;
        conceptCard.frontImage = conceptPixmap;
        conceptCard.pairId = i;
        cardData.append(conceptCard); // Concept card
    }
}
void GameWindow::shuffleCards()
{
    // Shuffle the cardData vector
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cardData.begin(), cardData.end(), std::default_random_engine(seed));
}

void GameWindow::setupGame()
{
    // Ensure there are 16 cards
    if(cardData.size() < 16){
        QMessageBox::critical(this, "Error", "Not enough card data to set up the game.");
        return;
    }

    // Clear any existing buttons in gridLayout
    QLayoutItem* child;
    while ((child = ui->gridLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }

    // Create 16 cards (4x4 grid)
    for(int i = 0; i < 16; i++){
        CardWidget* card = new CardWidget(this);
        card->setBackImage(QPixmap(":/images/backOfCard.png"));
        card->setFrontImage(cardData[i].frontImage); // Show image or concept on front of card
        card->setPairId(cardData[i].pairId); // Assign pairId for matching
        connect(card, &CardWidget::clicked, this, &GameWindow::handleCardClicked);
        cards.append(card);
        ui->gridLayout->addWidget(card, i / 4, i % 4);
    }
}

void GameWindow::handleCardClicked(CardWidget*card)
{
    if(isProcessing || card->isFaceUp() || card->isMatched())
        return;

    card->showFront();

    if(!firstSelectedCard)
    {
        firstSelectedCard = card;
    }
    else if(!secondSelectedCard && card != firstSelectedCard)
    {
        secondSelectedCard = card;
        isProcessing = true;

        // Increment move count
        moveCount++;
        updateMoveLabel();

        // check for match
        bool isMatch = false;

        // mapping logic: same QPixmap
        if(firstSelectedCard->getPairId() == secondSelectedCard->getPairId())
        {
            isMatch = true;
        }

        if(isMatch)
        {
            firstSelectedCard->setMatched(true);
            secondSelectedCard->setMatched(true);
            resetSelection();
            isProcessing = false;

            // check if all cards matched:
            bool allMatched = true;
            for (auto c : cards)
            {
                if(!c->isMatched())
                {
                    allMatched = false;
                    break;
                }
            }
            if(allMatched)
            {
                 gameTimer->stop(); // Stop the timer
                QMessageBox::information(this, "Congratulations!", "You've matched all the cards!");
                updateHighScores();
                displayHighScores();
            }
        }
        else
        {
            // not a match: flip the card back after a short delay
            QTimer::singleShot(1000, this, [=](){
                firstSelectedCard->showBack();
                secondSelectedCard->showBack();
                resetSelection();
                isProcessing = false;
            });
        }
    }
}
void GameWindow::resetSelection()
{
    firstSelectedCard = nullptr;
    secondSelectedCard = nullptr;
}
// Update the move counter label
void GameWindow::updateMoveLabel()
{
    moveLabel->setText(QString("Moves: %1").arg(moveCount));
}

// Update the timer label every second
void GameWindow::updateTimerLabel()
{
    elapsedTime++;
    timerLabel->setText(QString("Time: %1s").arg(elapsedTime));
}
void GameWindow::restartGame()
{
    // Reset game state
    for(auto card : cards)
    {
        gridLayout->removeWidget(card);
        delete card;
    }
    cards.clear();
    cardData.clear();
    firstSelectedCard = nullptr;
    secondSelectedCard = nullptr;
    isProcessing = false;
    moveCount = 0;
    elapsedTime = 0;

    // Reset labels
    moveLabel->setText("Moves: 0");
    timerLabel->setText("Time: 0s");

    // Restart timer
    gameTimer->start(1000);

    // Reload and shuffle cards
    loadCardData();
    shuffleCards();
    setupGame();
}
void GameWindow::updateHighScores()
{
    QSettings settings("YourCompany", "MemoFlip");
    QString keyTime = "HighScores/BestTime";
    QString keyMoves = "HighScores/LeastMoves";

    int bestTime = settings.value(keyTime, INT_MAX).toInt();
    int leastMoves = settings.value(keyMoves, INT_MAX).toInt();

    bool newRecord = false;

    if(elapsedTime < bestTime)
    {
        settings.setValue(keyTime, elapsedTime);
        newRecord = true;
        QMessageBox::information(this, "New Record!", "You've achieved a new best time!");
    }

    if(moveCount < leastMoves)
    {
        settings.setValue(keyMoves, moveCount);
        newRecord = true;
        QMessageBox::information(this, "New Record!", "You've achieved a new least moves count!");
    }

}
// Display current high scores
void GameWindow::displayHighScores()
{
    QSettings settings("YourCompany", "MemoFlip");
    int bestTime = settings.value("HighScores/BestTime", 0).toInt();
    int leastMoves = settings.value("HighScores/LeastMoves", 0).toInt();

    QMessageBox::information(this, "High Scores", QString("Best Time: %1s\nLeast Moves: %2").arg(bestTime).arg(leastMoves));
}

