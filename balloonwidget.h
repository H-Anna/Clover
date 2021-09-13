#ifndef BALLOONWIDGET_H
#define BALLOONWIDGET_H

#include <QObject>
#include <QWidget>
#include <QAction>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QTextBrowser>

class BalloonWidget: public QWidget
{
    Q_OBJECT
public:
    BalloonWidget(QWidget *parent = nullptr);
    ~BalloonWidget();
signals:
    void printTextSignal(const QString& text);
    void changeBalloonSignal(const QString& path);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent*) override;

private:
    QPoint dragPosition;
    QPixmap displayedImage;
    QTextEdit* textEdit;

    void setupTextBrowser();

private slots:
    void printText(const QString& text);
    void changeBalloon(const QString& path);
};

#endif // BALLOONWIDGET_H
