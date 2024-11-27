#include "cardwidget.h"
#include <QPropertyAnimation>

CardWidget::CardWidget(QWidget *parent) :
    QPushButton(parent),
    pairId(-1),
    faceUp(false),
    matched(false)
{
    // set fixed size for simplicity
    setFixedSize(100, 150);
    // Initialize with back image
    connect(this, &QPushButton::clicked, this, &CardWidget::onClicked);
}

void CardWidget::setFrontImage(const QPixmap &pixmap)
{
    frontPixmap = pixmap;
}

void CardWidget::setBackImage(const QPixmap &pixmap)
{
    backPixmap = pixmap;
    setIcon(QIcon(backPixmap));
    setIconSize(size());
}
void CardWidget::setPairId(int id)
{
    pairId = id;
}
int CardWidget::getPairId() const
{
    return pairId;
}

void CardWidget::showFront()
{
    if (matched) return;
    //flip animation:
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(300);
    animation->setStartValue(this->geometry());

    setIcon(QIcon(frontPixmap));
    setIconSize(size());
    faceUp = true;
    update();
}
void CardWidget::showBack()
{
    if (matched) return;

    //flip animation:
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(300);
    animation->setStartValue(this->geometry());

    setIcon(QIcon(backPixmap));
    setIconSize(size());
    faceUp = false;
    update();
}

bool CardWidget::isFaceUp() const
{
    return faceUp;
}

bool CardWidget::isMatched() const
{
    return matched;
}
void CardWidget::setMatched(bool isMatched)
{
    matched = isMatched;
    if (matched) {
        setDisabled(true);
        setStyleSheet("border: 2px solid green;"); // Indicate matched cards
    }
}

void CardWidget::onClicked()
{
    if(!faceUp && !matched)
    {
        emit clicked(this);
    }
}

