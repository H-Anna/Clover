#ifndef BALLOONWIDGET_H
#define BALLOONWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QPlainTextEdit>
#include <QTimer>
#include <QTextBrowser>
#include <QDesktopServices>

#include <QDebug>

class BalloonWidget: public QWidget
{
    Q_OBJECT;
public:
    BalloonWidget(QWidget *parent = nullptr);
    ~BalloonWidget();

    QPlainTextEdit* textHolder;

signals:
    void balloonLoadedSignal();

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

    QTextBrowser* textBrowser;
    unsigned int textCursor;
    QTimer* textTimer;
    QString printingText;

    void setupTextBrowser();

private slots:
    void prepareText(const QString& text);
    void printText();
    void changeBalloon(const QString& path);

    void textBrowserUpdate();
    void PrintAnchor(const QUrl& link);
};

#endif // BALLOONWIDGET_H
