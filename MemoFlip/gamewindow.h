#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include <QList>
#include <QPushButton>
#include <QTimer>
#include <QLabel>
#include <QSqlQuery>
#include <QByteArray>
#include <QImage>
#include <QGridLayout>

namespace Ui {
class GameWindow;
}

// Struct to hold concept, image, and ID for cards
struct CardData {
    QString concept;   // Concept text on the card
    QByteArray image;  // Image data for the card
    int id;            // Unique ID for matching pairs
};

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(const QString &username, QWidget *parent = nullptr);  // Constructor now takes `username`
    ~GameWindow();

signals:
    void restartRequested();  // Signal to request a game restart

private:
    Ui::GameWindow *ui;
    QTimer *timer;            // Game timer
    QLabel *timerLabel;       // Label to display elapsed time
    int timeElapsed;          // Elapsed time in seconds
    int score;                // Current score
    int correctMatches;       // Correct matches count
    QString username;         // Player's username

    QGridLayout *gridLayout;  // Grid layout for cards

    QList<CardData> loadCardDataFromDatabase();  // Load cards from database
    void updateCardButtonWithImage(QPushButton *cardButton, const QByteArray &imageData);  // Update button image
    void flipCardBack(QPushButton *card);  // Flip card back to its hidden state

    QPushButton *firstCard = nullptr;  // First clicked card
    QPushButton *secondCard = nullptr; // Second clicked card
    QString firstCardData;             // Concept/image of first card
    bool waitingForSecondClick = false; // Waiting for second click flag
    int firstCardId = -1;              // First card's ID
    int secondCardId = -1;             // Second card's ID

private slots:
    void updateTimer();    // Timer slot
    void flipCard();       // Handle card flips
    void shuffleCards();   // Shuffle the cards
    void restartGame();    // Restart the game
};

#endif // GAMEWINDOW_H
