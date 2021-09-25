#ifndef BALLOONWIDGET_H
#define BALLOONWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QTextBrowser>
#include <QTimer>

class BalloonWidget: public QWidget
{
    Q_OBJECT
public:
    BalloonWidget(QWidget *parent = nullptr);
    ~BalloonWidget();
signals:
    void prepareTextSignal(const QString& text);
    void changeBalloonSignal(const QString& path);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent*) override;

private:
    QPoint dragPosition;
    QPixmap displayedImage;
    QTextBrowser* textBrowser;
    int textIdx;
    QTimer* textTimer;
    QString printingText;

    void setupTextBrowser();
    void printByChar(const QString& text);


private slots:
    void prepareText(const QString& text);
    void printText();
    void changeBalloon(const QString& path);
};

#endif // BALLOONWIDGET_H
