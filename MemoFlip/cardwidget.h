#ifndef CARDWIDGET_H
#define CARDWIDGET_H


#include <QPushButton>
#include <QPixmap>

class CardWidget : public QPushButton
{
    Q_OBJECT
public:
    explicit CardWidget(QWidget *parent = nullptr);

    void setFrontImage(const QPixmap &pixmap);
    void setBackImage(const QPixmap &pixmap);
    void showFront();
    void showBack();
    bool isFaceUp() const;
    void setMatched(bool matched);
    bool isMatched() const;
    void setPairId(int id);
    int getPairId() const;

signals:
    void clicked(CardWidget*);

private slots:
    void onClicked();

private:
    QPixmap frontPixmap;
    QPixmap backPixmap;
    bool faceUp;
    bool matched;
    int pairId;
};


#endif // CARDWIDGET_H
