#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QGridLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QPixmap>
#include <QImageReader>
#include <QLabel>
#include <QVBoxLayout>
#include <QRandomGenerator>
#include <algorithm>
#include <QTimer>
#include <QMessageBox>

GameWindow::GameWindow(const QString &username, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow),
    timeElapsed(0),    // Reset time
    score(0),           // Reset score
    correctMatches(0),  // Reset correct matches
    firstCard(nullptr), // Reset first card
    secondCard(nullptr),// Reset second card
    waitingForSecondClick(false), // Reset waiting state
    username(username)
{
    ui->setupUi(this);
    setWindowTitle("Game for " + username);;

    // Set up the timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::updateTimer);
    timer->start(1000);  // Timer updates every second

    // Create a QLabel to show the time and score
    timerLabel = new QLabel("Time: 0  Score: 0", this);  // Initial display includes score
    timerLabel->setAlignment(Qt::AlignLeft);
    timerLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    timerLabel->move(10, 10);  // Position it at the top left of the window
    timerLabel->resize(250, 30);  // Ensure it's wide enough to fit the text

    // Ensure Exit Button connection is correct
    connect(ui->exitButton, &QPushButton::clicked, this, &GameWindow::close); // Exits the game
    connect(ui->restartButton, &QPushButton::clicked, this, &GameWindow::restartGame);// Restarts the game

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(10);  // add spacing between the cards

    // Load card data from the database
    QList<CardData> cardDataList = loadCardDataFromDatabase();

    // Shuffle the card data list to ensure random selection
    QRandomGenerator *randGen = QRandomGenerator::global();
    std::shuffle(cardDataList.begin(), cardDataList.end(), *randGen);

    // Ensure there are enough cards (8 pairs for 16 cards)
    while (cardDataList.size() < 8) {
        // Duplicate some cards if there aren't enough
        cardDataList.append(cardDataList);
    }

    // Now we only need the first 8 pairs after shuffle
    QList<CardData> selectedCards = cardDataList.mid(0, 8);

    // Create 16 cards (8 pairs of image and concept)
    QList<QPushButton*> allCardButtons;
    for (int i = 0; i < 16; i += 2) {
        QPushButton *imageCardButton = new QPushButton(this);
        imageCardButton->setFixedSize(110, 110);
        imageCardButton->setStyleSheet("background-color: #4682b4;");  // Dark blue for the back of the card
        imageCardButton->setProperty("isRevealed", false);
        connect(imageCardButton, &QPushButton::clicked, this, &GameWindow::flipCard);

        QPushButton *conceptCardButton = new QPushButton(this);
        conceptCardButton->setFixedSize(110, 110);
        conceptCardButton->setStyleSheet("background-color: #4682b4;");  // Dark blue for the back of the card
        conceptCardButton->setProperty("isRevealed", false);
        connect(conceptCardButton, &QPushButton::clicked, this, &GameWindow::flipCard);

        if (i / 2 < selectedCards.size()) {
            const CardData &cardData = selectedCards[i / 2];
            imageCardButton->setProperty("id", cardData.id);  // Set the id as a property
            conceptCardButton->setProperty("id", cardData.id);  // Set the id as a property

            imageCardButton->setProperty("imageData", cardData.image);
            conceptCardButton->setProperty("concept", cardData.concept);
        }

        allCardButtons.append(imageCardButton);
        allCardButtons.append(conceptCardButton);
    }

    // Randomize the order of the cards
    std::shuffle(allCardButtons.begin(), allCardButtons.end(), *randGen);

    // Add randomized cards to the grid layout
    int index = 0;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (index < allCardButtons.size()) {
                QPushButton *cardButton = allCardButtons[index++];
                gridLayout->addWidget(cardButton, row, col);  // Place the card in the grid
            }
        }
    }

    // Set the grid layout for this QDialog
    setLayout(gridLayout);  // Use setLayout() instead of setCentralWidget()

}

void GameWindow::restartGame() {
    qDebug() << "Restart button clicked!";
    emit restartRequested();
}


GameWindow::~GameWindow()
{
    delete ui;
}

QList<CardData> GameWindow::loadCardDataFromDatabase()
{
    QList<CardData> cardDataList;

    // SQL query to load cardId, concept, and image from the database
    QSqlQuery query("SELECT id, concept, image FROM cards");
    while (query.next()) {
        CardData cardData;
        cardData.id = query.value(0).toInt(); // Get the ID from the first column
        cardData.concept = query.value(1).toString(); // Get the concept from the second column
        cardData.image = query.value(2).toByteArray(); // Get the image from the third column
        cardDataList.append(cardData);
    }

    return cardDataList;
}

void GameWindow::updateCardButtonWithImage(QPushButton *cardButton, const QByteArray &imageData)
{
    // Convert the image data (blob) to a QImage
    QImage image = QImage::fromData(imageData);
    if (!image.isNull()) {
        // Scale the image to completely fill the button (ignoring aspect ratio)
        image = image.scaled(cardButton->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        // Convert the QImage to QPixmap and set it as the card button's icon
        QPixmap pixmap = QPixmap::fromImage(image);
        cardButton->setIcon(pixmap);
        cardButton->setIconSize(cardButton->size());  // Set the icon size to match the button's size

        // Ensure the button's text (like "Image") is hidden if the image is set
        cardButton->setText("");  // Remove the text on image cards
    }
}

void GameWindow::flipCard() {
    QPushButton *card = qobject_cast<QPushButton *>(sender());
    if (!card) return;

    bool isRevealed = card->property("isRevealed").toBool();

    // If the card is already revealed, ignore it
    if (isRevealed) return;

    // Reveal the card
    card->setProperty("isRevealed", true);
    if (card->property("imageData").isValid()) {
        // Show the image
        QByteArray imageData = card->property("imageData").toByteArray();
        updateCardButtonWithImage(card, imageData);
        card->setStyleSheet("background-color: #add8e6;");  // Light blue color for front
    } else if (card->property("concept").isValid()) {
        // Show the concept text
        QString concept = card->property("concept").toString();

        // Clear existing layout if any
        if (card->layout()) {
            QLayout *layout = card->layout();
            while (QLayoutItem *item = layout->takeAt(0)) {
                delete item->widget();
                delete item;
            }
            delete layout;
        }

        // Create a new label for the concept text
        QLabel *conceptLabel = new QLabel(concept, card);
        conceptLabel->setWordWrap(true);
        conceptLabel->setAlignment(Qt::AlignCenter);
        conceptLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: black;");

        // Create a new layout and add the label
        QVBoxLayout *conceptLayout = new QVBoxLayout(card);
        conceptLayout->addWidget(conceptLabel);
        card->setLayout(conceptLayout);

        card->setStyleSheet("background-color: #add8e6;");  // Light blue color for front
    }

    // Debug: Print the card's ID when clicked
    int id = card->property("id").toInt();
    qDebug() << "Card clicked with ID:" << id;

    // If it's the first card clicked, store it
    if (!firstCard) {
        firstCard = card;
        firstCardId = id; // Use ID from the database
        return;
    }

    // If it's the second card clicked, store it
    secondCard = card;
    secondCardId = id; // Use ID from the database

    // Compare first and second cards based on the ID
    waitingForSecondClick = true;

    // If the cards match (same ID)
    if (firstCardId == secondCardId) {
        // Cards match, reset variables and leave them revealed
        firstCard = nullptr;
        secondCard = nullptr;
        waitingForSecondClick = false;
        correctMatches++;  // Increment the correct match count
        qDebug() << "Match found!";

        // Update score based on the number of correct matches
        score = correctMatches * 10 - (timeElapsed / 5);
        timerLabel->setText("Time: " + QString::number(timeElapsed) + "  Score: " + QString::number(score));

        // Check if the game is complete (all pairs found)
        if (correctMatches == 8) {
            // Game complete, show a message
             QMessageBox::information(this, "Game Over", "Congratulations, " + username + "! You have completed the game.", QMessageBox::Ok);
        }
    } else {
        // If the cards do not match, flip them back after a short delay
        QTimer::singleShot(500, this, [this]() {
            // Debugging output
            qDebug() << "Cards do not match, flipping back.";

            // Check if cards are still unmatched before flipping back
            if (!firstCard || !secondCard) return; // Prevent actions if cards have been cleared

            // Flip cards back
            flipCardBack(firstCard);
            flipCardBack(secondCard);

            firstCard = nullptr;
            secondCard = nullptr;
            waitingForSecondClick = false;
        });
    }
}

void GameWindow::flipCardBack(QPushButton *card) {
    if (!card) return;

    // Reset the card to its flipped state (no concept or image)
    card->setProperty("isRevealed", false);

    // Remove the QLabel (for concept cards) and reset styles
    if (card->layout()) {
        // Clear the concept text layout
        QLayout *layout = card->layout();
        while (QLayoutItem *item = layout->takeAt(0)) {
            delete item->widget();
            delete item;
        }
        delete layout;
    }

    // For image cards, reset to dark blue background and clear any image
    card->setStyleSheet("background-color: #4682b4;");  // Dark blue for the back
    card->setIcon(QPixmap());  // Clear the image
    card->setText("");  // Clear any text (if any)
}

void GameWindow::updateTimer() {
    timeElapsed++;
    // Formula for scoring
    score = correctMatches * 10 - (timeElapsed / 5);
    timerLabel->setText("Time: " + QString::number(timeElapsed) + "  Score: " + QString::number(score));
}


//Shuffle function still under development
void GameWindow::shuffleCards() {
    QList<QPushButton*> cardButtons;

    // Collect all the card buttons in the grid layout
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            QWidget *widget = gridLayout->itemAtPosition(i, j)->widget();
            if (widget) {
                cardButtons.append(qobject_cast<QPushButton*>(widget));
            }
        }
    }

    // Shuffle the list of card buttons
    QRandomGenerator *randGen = QRandomGenerator::global();
    std::shuffle(cardButtons.begin(), cardButtons.end(), *randGen);

    // Re-add shuffled buttons back to the grid layout
    int index = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            gridLayout->addWidget(cardButtons[index++], i, j);
        }
    }
}
