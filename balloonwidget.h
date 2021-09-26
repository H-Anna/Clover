#ifndef BALLOONWIDGET_H
#define BALLOONWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QPlainTextEdit>
#include <QTimer>

class BalloonWidget: public QWidget
{
    Q_OBJECT
public:
    BalloonWidget(QWidget *parent = nullptr);
    ~BalloonWidget();

    void clearBalloonText();
    void appendHtml(const QString& text);
signals:
    void prepareTextSignal(const QString& text);
    void changeBalloonSignal(const QString& path);
    void finishedTextPrintSignal();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent*) override;

private:
    QPoint dragPosition;
    QPixmap displayedImage;
    QPlainTextEdit* textBrowser;
    int textIdx;
    QTimer* textTimer;
    QString printingText;

    void setupTextBrowser();

private slots:
    void prepareText(const QString& text);
    void printText();
    void changeBalloon(const QString& path);
};

#endif // BALLOONWIDGET_H
