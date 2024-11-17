#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QPair>
#include <QLabel>
#include <QTimer>
#include "cardwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

struct CardData
{
    QPixmap frontImage;
    int pairId;
};

class GameWindow  : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void handleCardClicked(CardWidget* card);
    void restartGame();
    void on_exitButton_clicked();
    void on_shuffleButton_clicked();
    void on_restartButton_clicked();

private:
    Ui::GameWindow *ui;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVector<CardWidget*> cards;
    QVector<CardData> cardData; // pair of front images (image and corresponding concept description)

    CardWidget* firstSelectedCard;
    CardWidget* secondSelectedCard;
    bool isProcessing;

    int moveCount;
    int elapsedTime;
    QLabel* moveLabel;
    QLabel* timerLabel;
    QTimer* gameTimer;

    void loadCardData();
    void shuffleCards();
    void setupGame();
    void resetSelection();
    void updateMoveLabel();
    void updateTimerLabel();
    void updateHighScores();
    void displayHighScores();

};

#endif // GAMEWINDOW_H
